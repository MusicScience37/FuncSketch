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

"""Test of FuncSketchWidget."""

import kivy.lang

from func_sketch._gui.func_sketch_widget import FuncSketchWidget

kivy.lang.Builder.load_file("func_sketch_widget.kv")


def _ignore(_) -> None:
    pass


class TestFuncSketchWidget:
    """Test of FuncSketchWidget."""

    def test_initialization(self) -> None:
        """Test of initialization."""
        # Simply checks that the initialization of the application does not cause an error.
        widget = FuncSketchWidget()
        _ignore(widget)

    def test_update_function(self) -> None:
        """Test to update a function."""
        # Simply checks that the update does not cause an error.
        # Actual functionality should be checked visually.
        widget = FuncSketchWidget()

        widget.shared_state.curve_configs[0].function_expression_str = "x**2"
