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

"""Test of RangeConfigWidget."""

import pathlib

import kivy.lang

import func_sketch._gui.range_config_widget as range_config_widget_module
from func_sketch._cpp import PlotRange
from func_sketch._gui.range_config_widget import RangeConfigWidget
from func_sketch._gui.shared_state import SharedState

_KV_FILE = pathlib.Path(range_config_widget_module.__file__).with_name(
    "range_config_widget.kv"
)
kivy.lang.Builder.load_file(str(_KV_FILE))


class TestRangeConfigWidgetSharedStateSync:
    """Test of synchronization from shared_state to the child widgets."""

    def test_children_are_initialized_from_shared_state(self) -> None:
        """Test that the text inputs are initialized from shared_state.plot_range."""
        shared_state = SharedState(
            plot_range=PlotRange(x_range=(-1.0, 2.0), y_range=(-4.0, 5.0))
        )

        widget = RangeConfigWidget(shared_state=shared_state)

        assert widget.x_min_text_input.value == -1.0
        assert widget.x_max_text_input.value == 2.0
        assert widget.y_min_text_input.value == -4.0
        assert widget.y_max_text_input.value == 5.0


class TestRangeConfigWidgetChildrenToSharedStateSync:
    """Test of synchronization from the child widgets to shared_state."""

    def test_x_min_text_input_updates_shared_state(self) -> None:
        """Test that changing x_min_text_input.value updates shared_state.plot_range."""
        shared_state = SharedState(
            plot_range=PlotRange(x_range=(-1.0, 2.0), y_range=(-4.0, 5.0))
        )
        widget = RangeConfigWidget(shared_state=shared_state)
        on_plot_range_changed_list = []
        shared_state.bind(
            on_plot_range_changed=lambda instance, source, value: on_plot_range_changed_list.append(
                (source, value)
            )
        )

        widget.x_min_text_input.value = -10.0

        assert shared_state.plot_range.x_range == (-10.0, 2.0)
        assert shared_state.plot_range.y_range == (-4.0, 5.0)
        assert len(on_plot_range_changed_list) == 1
        assert on_plot_range_changed_list[0][0] is widget
        assert on_plot_range_changed_list[0][1] is shared_state.plot_range

    def test_x_max_text_input_updates_shared_state(self) -> None:
        """Test that changing x_max_text_input.value updates shared_state.plot_range."""
        shared_state = SharedState(
            plot_range=PlotRange(x_range=(-1.0, 2.0), y_range=(-4.0, 5.0))
        )
        widget = RangeConfigWidget(shared_state=shared_state)
        on_plot_range_changed_list = []
        shared_state.bind(
            on_plot_range_changed=lambda instance, source, value: on_plot_range_changed_list.append(
                (source, value)
            )
        )

        widget.x_max_text_input.value = 10.0

        assert shared_state.plot_range.x_range == (-1.0, 10.0)
        assert shared_state.plot_range.y_range == (-4.0, 5.0)
        assert len(on_plot_range_changed_list) == 1
        assert on_plot_range_changed_list[0][0] is widget
        assert on_plot_range_changed_list[0][1] is shared_state.plot_range

    def test_y_min_text_input_updates_shared_state(self) -> None:
        """Test that changing y_min_text_input.value updates shared_state.plot_range."""
        shared_state = SharedState(
            plot_range=PlotRange(x_range=(-1.0, 2.0), y_range=(-4.0, 5.0))
        )
        widget = RangeConfigWidget(shared_state=shared_state)
        on_plot_range_changed_list = []
        shared_state.bind(
            on_plot_range_changed=lambda instance, source, value: on_plot_range_changed_list.append(
                (source, value)
            )
        )

        widget.y_min_text_input.value = -20.0

        assert shared_state.plot_range.x_range == (-1.0, 2.0)
        assert shared_state.plot_range.y_range == (-20.0, 5.0)
        assert len(on_plot_range_changed_list) == 1
        assert on_plot_range_changed_list[0][0] is widget
        assert on_plot_range_changed_list[0][1] is shared_state.plot_range

    def test_y_max_text_input_updates_shared_state(self) -> None:
        """Test that changing y_max_text_input.value updates shared_state.plot_range."""
        shared_state = SharedState(
            plot_range=PlotRange(x_range=(-1.0, 2.0), y_range=(-4.0, 5.0))
        )
        widget = RangeConfigWidget(shared_state=shared_state)
        on_plot_range_changed_list = []
        shared_state.bind(
            on_plot_range_changed=lambda instance, source, value: on_plot_range_changed_list.append(
                (source, value)
            )
        )

        widget.y_max_text_input.value = 20.0

        assert shared_state.plot_range.x_range == (-1.0, 2.0)
        assert shared_state.plot_range.y_range == (-4.0, 20.0)
        assert len(on_plot_range_changed_list) == 1
        assert on_plot_range_changed_list[0][0] is widget
        assert on_plot_range_changed_list[0][1] is shared_state.plot_range


class TestRangeConfigWidgetInvalidRange:
    """Test of the behavior when the range of the plot is invalid."""

    def test_x_min_greater_than_or_equal_to_x_max_shows_error(self) -> None:
        """Test that shared_state is not updated and an error is shown when x_min >= x_max."""
        shared_state = SharedState(
            plot_range=PlotRange(x_range=(-1.0, 2.0), y_range=(-4.0, 5.0))
        )
        widget = RangeConfigWidget(shared_state=shared_state)
        on_plot_range_changed_list = []
        shared_state.bind(
            on_plot_range_changed=lambda instance, source, value: on_plot_range_changed_list.append(
                (source, value)
            )
        )

        widget.x_min_text_input.value = 5.0

        assert shared_state.plot_range.x_range == (-1.0, 2.0)
        assert shared_state.plot_range.y_range == (-4.0, 5.0)
        assert on_plot_range_changed_list == []
        assert widget.error_message == "Invalid X range: min >= max"

    def test_y_min_greater_than_or_equal_to_y_max_shows_error(self) -> None:
        """Test that shared_state is not updated and an error is shown when y_min >= y_max."""
        shared_state = SharedState(
            plot_range=PlotRange(x_range=(-1.0, 2.0), y_range=(-4.0, 5.0))
        )
        widget = RangeConfigWidget(shared_state=shared_state)
        on_plot_range_changed_list = []
        shared_state.bind(
            on_plot_range_changed=lambda instance, source, value: on_plot_range_changed_list.append(
                (source, value)
            )
        )

        widget.y_min_text_input.value = 10.0

        assert shared_state.plot_range.x_range == (-1.0, 2.0)
        assert shared_state.plot_range.y_range == (-4.0, 5.0)
        assert on_plot_range_changed_list == []
        assert widget.error_message == "Invalid Y range: min >= max"
