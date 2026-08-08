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

"""Class of FuncSketch GUI widget."""

import kivy.properties
import kivy.uix.boxlayout

from func_sketch._gui.shared_state import SharedState


class FuncSketchWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of FuncSketch GUI widget."""

    shared_state = kivy.properties.ObjectProperty(SharedState())
    """Shared state object."""
