# Copyright 2026 MusicScience37 (Kenta Kabashima)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Configuration of pytest."""

import os
import pathlib

import pytest

# This must be set before importing Kivy.
os.environ["KIVY_NO_ARGS"] = "1"


from system_tests.screen_saver import ScreenshotSaver  # noqa: PLC0415


@pytest.fixture
def screenshot_saver(request: pytest.FixtureRequest) -> ScreenshotSaver:
    """Screenshot saver fixture.

    Returns:
        The instance of ScreenshotSaver.
    """
    module_name = str(request.module.__name__)
    module_name = module_name.replace(".", "_")
    module_name = module_name.removeprefix("system_tests_")
    test_name = request.node.name
    base_path = (
        pathlib.Path(__file__).absolute().parent
        / "screenshots"
        / f"{module_name}"
        / f"{test_name}"
    )
    saver = ScreenshotSaver(str(base_path))
    return saver
