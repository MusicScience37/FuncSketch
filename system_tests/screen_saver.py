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

"""Class to save screenshots."""

import pathlib

import kivy.app
import kivy.uix.widget


class ScreenshotSaver:
    """Class to save screenshots."""

    def __init__(self, base_path: str) -> None:
        """Constructor."""
        self._base_path = base_path
        self._counter = 0
        pathlib.Path(base_path).parent.mkdir(parents=True, exist_ok=True)

    def save(self, name: str, widget: kivy.uix.widget.Widget | None = None) -> None:
        """Save a screenshot."""
        if widget is None:
            widget = kivy.app.App.get_running_app().root

        full_path = f"{self._base_path}_{self._counter:02}_{name}.png"
        widget.export_to_png(full_path)  # type: ignore
        self._counter += 1
