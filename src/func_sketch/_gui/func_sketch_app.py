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

"""Class of FuncSketch GUI application."""

import kivy.app
import kivy.lang

from func_sketch._gui.func_sketch_widget import FuncSketchWidget


class FuncSketchApp(kivy.app.App):
    """Class of FuncSketch GUI application."""

    def build(self):
        """Build the GUI application."""
        kivy.lang.Builder.load_file("func_sketch_widget.kv")
        return FuncSketchWidget()


if __name__ == "__main__":
    FuncSketchApp().run()
