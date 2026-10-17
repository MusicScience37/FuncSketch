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

"""Test of SwitchSelectorWidget."""

from func_sketch._gui.common.switch_selector_widget import SwitchSelectorWidget
from func_sketch._impl.curve_type import CurveType

_OPTIONS = [("a", "Option A"), ("b", "Option B"), ("c", "Option C")]


class TestSwitchSelectorWidget:
    """Test of SwitchSelectorWidget."""

    def test_initial_state(self) -> None:
        """Test that switches are created according to the initial options."""
        widget = SwitchSelectorWidget(options=_OPTIONS, selected="b")

        switches = list(reversed(widget.children))
        assert [switch.text for switch in switches] == [
            "Option A",
            "Option B",
            "Option C",
        ]
        assert [switch.active for switch in switches] == [False, True, False]

    def test_select_by_release(self) -> None:
        """Test that releasing a switch selects its option."""
        widget = SwitchSelectorWidget(options=_OPTIONS, selected="a")
        on_selected = []
        widget.bind(selected=lambda _instance, value: on_selected.append(value))

        switches = list(reversed(widget.children))
        switches[2].dispatch("on_release")

        assert widget.selected == "c"
        assert on_selected == ["c"]
        assert [switch.active for switch in switches] == [False, False, True]

    def test_release_selected_switch(self) -> None:
        """Test that releasing the selected switch keeps the selection."""
        widget = SwitchSelectorWidget(options=_OPTIONS, selected="a")

        switches = list(reversed(widget.children))
        switches[0].dispatch("on_release")

        assert widget.selected == "a"
        assert [switch.active for switch in switches] == [True, False, False]

    def test_change_selected(self) -> None:
        """Test that changing selected updates the active states."""
        widget = SwitchSelectorWidget(options=_OPTIONS, selected="a")

        widget.selected = "b"

        switches = list(reversed(widget.children))
        assert [switch.active for switch in switches] == [False, True, False]

    def test_change_options(self) -> None:
        """Test that changing options recreates switches."""
        widget = SwitchSelectorWidget(options=_OPTIONS, selected="b")

        widget.options = [("b", "New B"), ("d", "New D")]

        switches = list(reversed(widget.children))
        assert [switch.text for switch in switches] == ["New B", "New D"]
        assert [switch.active for switch in switches] == [True, False]

    def test_enum_values(self) -> None:
        """Test that values other than strings can be used."""
        widget = SwitchSelectorWidget(
            options=[
                (CurveType.EXPLICIT, "Explicit"),
                (CurveType.PARAMETERIZED, "Parameterized"),
            ],
            selected=CurveType.EXPLICIT,
        )

        switches = list(reversed(widget.children))
        switches[1].dispatch("on_release")

        assert widget.selected == CurveType.PARAMETERIZED
        assert [switch.active for switch in switches] == [False, True]
