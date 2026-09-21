#!/usr/bin/env python3

# This file is licensed under MIT license as follows:
#
# Copyright 2026 MusicScience37 (Kenta Kabashima)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

"""Helper script to perform profiling."""

import os
import subprocess
from pathlib import Path

import click

THIS_DIR = Path(__file__).absolute().parent
PROF_RESULTS_DIR = THIS_DIR.parent / "cpp" / "tests" / "profiling" / "results"


@click.command()
@click.argument(
    "binary_path",
    nargs=1,
    type=click.Path(exists=True, executable=True, resolve_path=True),
)
@click.option(
    "--freq",
    "frequency",
    default=100,
    type=int,
    show_default=True,
    help="Frequency of the profiling.",
)
@click.option(
    "--nodecount",
    "nodecount",
    default=100,
    type=int,
    show_default=True,
    help="Number of nodes in the result.",
)
@click.option(
    "--focus",
    "focus",
    default="",
    type=str,
    show_default=False,
    help="Function to focus on.",
)
@click.option("--reuse", is_flag=True, help="Reuse the same profiling data.")
def perform_profiling(
    binary_path: str, frequency: int, nodecount: int, focus: str, reuse: bool
):
    """Perform profiling of the given binary.

    The given binary is assumed to be linked with libprofiler,
    includes ProfilerStart / ProfilerStop calls,
    and write profiling results to the a file with a name like `<binary_name>.prof`.
    """
    name = str(Path(binary_path).stem)
    click.echo(
        click.style(f"Start profiling of {name}", bold=True) + f" (at {binary_path})"
    )

    Path(PROF_RESULTS_DIR).mkdir(exist_ok=True, parents=True)

    if not reuse:
        env = os.environ
        env["CPUPROFILE_FREQUENCY"] = str(frequency)
        process_result = subprocess.run(
            [binary_path], env=env, cwd=str(PROF_RESULTS_DIR), check=True
        )
        click.echo(
            click.style(
                f"{name} finished with exit code: {process_result.returncode}",
                bold=True,
            )
        )

    pprof_command = [
        "pprof",
        "-pdf",
        f"-nodecount={nodecount}",
    ]
    if focus:
        pprof_command.append(f"-focus={focus}")
    pprof_command.append(str(binary_path))
    pprof_command.append(str(PROF_RESULTS_DIR / f"{name}.prof"))
    with open(str(PROF_RESULTS_DIR / f"{name}.pdf"), mode="wb") as file:
        process_result = subprocess.run(
            pprof_command,
            stdout=file,
            check=False,
        )
    click.echo(
        click.style(
            f"pprof finished with exit code: {process_result.returncode}", bold=True
        )
    )


if __name__ == "__main__":
    perform_profiling()  # pylint: disable=no-value-for-parameter
