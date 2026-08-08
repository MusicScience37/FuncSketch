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

"""Test of SharedState."""

from func_sketch._cpp import PlotConfig, PlotRange, PointList, RGBColor
from func_sketch._gui.constants import NUM_CURVES
from func_sketch._gui.shared_state import SharedState
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.sampled_curve import SampledCurve


class TestSharedState:
    """Test of SharedState."""

    def test_initial_values(self) -> None:
        """Test initial values."""
        state = SharedState()

        assert state.plot_range is not None
        assert state.plot_config is not None
        assert len(state.curve_configs) == NUM_CURVES
        assert len(state.sampled_curves) == NUM_CURVES

    def test_update_plot_range(self) -> None:
        """Test to update plot range."""
        state = SharedState()

        on_plot_range_changed_list = []
        state.bind(
            on_plot_range_changed=lambda instance, source, value: on_plot_range_changed_list.append(
                (source, value)
            )
        )

        source = "test"
        new_plot_range = PlotRange((-1.0, 1.0), (-2.0, 2.0))
        state.update_plot_range(source, new_plot_range)

        assert state.plot_range == new_plot_range
        assert len(on_plot_range_changed_list) == 1
        assert on_plot_range_changed_list[0][0] == source
        assert on_plot_range_changed_list[0][1] is new_plot_range

    def test_update_plot_config(self) -> None:
        """Test to update plot config."""
        state = SharedState()

        on_plot_config_changed_list = []
        state.bind(
            on_plot_config_changed=lambda instance, source, value: on_plot_config_changed_list.append(
                (source, value)
            )
        )

        source = "test"
        new_plot_config = PlotConfig()
        state.update_plot_config(source, new_plot_config)

        assert state.plot_config == new_plot_config
        assert len(on_plot_config_changed_list) == 1
        assert on_plot_config_changed_list[0][0] == source
        assert on_plot_config_changed_list[0][1] is new_plot_config

    def test_update_curve_config(self) -> None:
        """Test to update curve config."""
        state = SharedState()

        on_curve_config_changed_list = []
        state.bind(
            on_curve_config_changed=lambda instance, source, index, value: on_curve_config_changed_list.append(
                (source, index, value)
            )
        )

        source = "test"
        index = 1
        new_curve_config = CurveConfig(
            function_expression_str="x", color=RGBColor(1, 2, 3)
        )
        state.update_curve_config(source, index, new_curve_config)

        assert state.curve_configs[index] == new_curve_config
        assert len(on_curve_config_changed_list) == 1
        assert on_curve_config_changed_list[0][0] == source
        assert on_curve_config_changed_list[0][1] == index
        assert on_curve_config_changed_list[0][2] is new_curve_config

    def test_update_sampled_curve(self) -> None:
        """Test to update sampled curve."""
        state = SharedState()

        on_sampled_curve_changed_list = []
        state.bind(
            on_sampled_curve_changed=lambda instance, source, index, value: on_sampled_curve_changed_list.append(
                (source, index, value)
            )
        )

        source = "test"
        index = 1
        new_sampled_curve = SampledCurve(samples=PointList([]), color=RGBColor(1, 2, 3))
        state.update_sampled_curve(source, index, new_sampled_curve)

        assert state.sampled_curves[index] == new_sampled_curve
        assert len(on_sampled_curve_changed_list) == 1
        assert on_sampled_curve_changed_list[0][0] == source
        assert on_sampled_curve_changed_list[0][1] == index
        assert on_sampled_curve_changed_list[0][2] is new_sampled_curve
