#!/usr/bin/env python3
"""Script run in CI for tests in Linux."""

import os
import pathlib
import subprocess
import time
import typing

import click

THIS_DIR = pathlib.Path(__file__).absolute().parent
ROOT_DIR = THIS_DIR.parent

BUILD_TYPE_DICT = {
    "debug": "Debug",
    "release": "Release",
    "ausan": "Debug",
    "coverage_cpp": "Debug",
    "coverage_python": "Release",
    "pre-commit": "Release",
    "clang-tidy": "Release",
    "docs": "Release",
}

TEST_TYPE_VARIABLES = {
    "debug": {
        "FUNC_SKETCH_BUILD_TESTS": "ON",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "OFF",
        "FUNC_SKETCH_WRITE_JUNIT": "ON",
    },
    "release": {
        "FUNC_SKETCH_BUILD_TESTS": "ON",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "OFF",
        "FUNC_SKETCH_WRITE_JUNIT": "ON",
    },
    "ausan": {
        "FUNC_SKETCH_BUILD_TESTS": "ON",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "ON",
        "FUNC_SKETCH_WRITE_JUNIT": "ON",
    },
    "coverage_cpp": {
        "FUNC_SKETCH_BUILD_TESTS": "ON",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "OFF",
        "FUNC_SKETCH_WRITE_JUNIT": "ON",
        "CMAKE_CXX_FLAGS": "-fprofile-instr-generate -fcoverage-mapping",
        "CMAKE_MODULE_LINKER_FLAGS": "-fprofile-instr-generate -fcoverage-mapping",
    },
    "coverage_python": {
        "FUNC_SKETCH_BUILD_TESTS": "ON",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "OFF",
        "FUNC_SKETCH_WRITE_JUNIT": "ON",
    },
    "pre-commit": {
        "FUNC_SKETCH_BUILD_TESTS": "OFF",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "OFF",
        "FUNC_SKETCH_WRITE_JUNIT": "OFF",
    },
    "clang-tidy": {
        "FUNC_SKETCH_BUILD_TESTS": "ON",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "OFF",
        "FUNC_SKETCH_WRITE_JUNIT": "OFF",
    },
    "docs": {
        "FUNC_SKETCH_BUILD_TESTS": "OFF",
        "FUNC_SKETCH_ENABLE_CCACHE": "ON",
        "FUNC_SKETCH_ENABLE_AUSAN": "OFF",
        "FUNC_SKETCH_WRITE_JUNIT": "OFF",
    },
}


def execute_command(command: typing.List[str], cwd: str, env=None) -> None:
    """Execute a command in a subprocess.

    Args:
        command (typing.List[str]): Command to execute.
        cwd (str): Working directory for the command.
        env (dict, optional): Environment variables for the command. Defaults to None.
    """
    click.echo(click.style(f">> {command}", bold=True, fg="green"))
    subprocess.run(command, check=True, cwd=cwd, env=env)


def _ignore(_):
    pass


@click.command()
@click.option("--compiler_type", "compiler_type", required=True)
@click.option("--test_type", "test_type", required=True)
@click.option("--build_dir", "build_dir", required=True)
def check_tests_for_condition(
    compiler_type: str,
    test_type: str,
    build_dir: str,
) -> None:
    """Check tests for a specific condition.

    Args:
        compiler_type (str): Type of the compiler.
        test_type (str): Type of the test.
        build_dir (str): Path to the build directory.
    """
    _ignore(compiler_type)
    os.makedirs(build_dir, exist_ok=True)

    # Configure
    command = [
        "cmake",
        "..",
        "-G",
        "Ninja",
    ]
    build_type = BUILD_TYPE_DICT[test_type]
    command = command + [f"-DCMAKE_BUILD_TYPE={build_type}"]
    for key, value in TEST_TYPE_VARIABLES[test_type].items():
        command = command + [f"-D{key}={value}"]

    execute_command(command, cwd=build_dir)

    # Build
    if test_type not in ["clang-tidy"]:
        execute_command(["cmake", "--build", "."], cwd=build_dir)

    # Prepare
    env = os.environ.copy()
    if test_type == "coverage_cpp":
        coverage_dir = pathlib.Path(build_dir).absolute() / "coverage"
        coverage_dir.mkdir(parents=True, exist_ok=True)
        env["LLVM_PROFILE_FILE"] = str(coverage_dir / "coverage_%p.profraw")

    # Test
    if test_type in ["debug", "release", "ausan", "coverage_cpp", "coverage_python"]:
        execute_command(
            ["ctest", "-V"],
            cwd=build_dir,
            env=env,
        )
        if test_type in ["debug", "release", "coverage_cpp", "coverage_python"]:
            command = ["xvfb-run", "poetry", "run", "pytest", "tests", "-v"]
            if test_type == "coverage_python":
                command = command + [
                    "--cov=func_sketch",
                    "--cov-report",
                    "term",
                    "--cov-report",
                    "xml:coverage_python.xml",
                    "--cov-report",
                    "html:coverage_python",
                ]
            execute_command(
                command,
                cwd=str(ROOT_DIR),
                env=env,
            )
        if test_type in ["release"]:
            time.sleep(5)  # Wait for a few seconds for xvfb.
            execute_command(
                [
                    "xvfb-run",
                    "poetry",
                    "run",
                    "pytest",
                    "bench",
                    "-v",
                    "--benchmark-json=benchmark.json",
                ],
                cwd=str(ROOT_DIR),
                env=env,
            )
            execute_command(
                [
                    "poetry",
                    "run",
                    "python",
                    "scripts/generate_benchmark_metrics.py",
                    "benchmark.json",
                    "bench_metrics.txt",
                ],
                cwd=str(ROOT_DIR),
                env=env,
            )

    # Pre-commit
    if test_type == "pre-commit":
        execute_command(
            ["poetry", "run", "pre-commit", "run", "--all-files"],
            cwd=str(ROOT_DIR),
            env=env,
        )

    # clang-tidy
    if test_type == "clang-tidy":
        execute_command(
            ["poetry", "run", "clang-tidy-checker", "--build_dir", build_dir],
            cwd=str(ROOT_DIR),
            env=env,
        )

    # Documentation
    if test_type == "docs":
        execute_command(
            ["poetry", "run", "./docs/build.sh"],
            cwd=str(ROOT_DIR),
            env=env,
        )


if __name__ == "__main__":
    check_tests_for_condition()
