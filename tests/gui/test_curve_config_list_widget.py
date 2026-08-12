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

"""Test of CurveConfigListWidget."""

import kivy.lang

from func_sketch._cpp import PlotConfig, PlotRange
from func_sketch._gui.curve_config_list_widget import CurveConfigListWidget
from func_sketch._gui.shared_state import SharedState

kivy.lang.Builder.load_file("curve_config_list_widget.kv")


# pylint: disable=protected-access


class TestCurveConfigListWidget:
    """Test of CurveConfigListWidget."""

    def test_update_in_curve_config_widget(self) -> None:
        """Test for updates in a CurveConfigWidget."""
        shared_state = SharedState()
        widget = CurveConfigListWidget(shared_state=shared_state)

        widget._curve_config_widgets[0].expression_text = "x**2"

        assert shared_state.curve_configs[0].function_expression_str == "x**2"
        assert len(shared_state.sampled_curves[0].samples.points) > 0

    def test_plot_range_update(self) -> None:
        """Test for updates in the plot range."""
        shared_state = SharedState()
        widget = CurveConfigListWidget(shared_state=shared_state)

        widget._curve_config_widgets[0].expression_text = "x**2"
        shared_state.plot_range = PlotRange((-2.0, 2.0), (-1.0, 1.0))

        assert shared_state.curve_configs[0].function_expression_str == "x**2"
        assert len(shared_state.sampled_curves[0].samples.points) > 0
        assert shared_state.sampled_curves[0].samples.points[0].x == -2.0

    def test_plot_config_update(self) -> None:
        """Test for updates in the plot config."""
        # Check of the change according to PlotConfig is difficult here.
        # But check that this operation does not cause an error.

        shared_state = SharedState()
        widget = CurveConfigListWidget(shared_state=shared_state)

        widget._curve_config_widgets[0].expression_text = "x**2"
        shared_state.plot_config = PlotConfig()

        assert shared_state.curve_configs[0].function_expression_str == "x**2"
        assert len(shared_state.sampled_curves[0].samples.points) > 0
