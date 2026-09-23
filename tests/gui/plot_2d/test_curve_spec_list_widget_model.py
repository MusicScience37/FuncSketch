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

"""Test of CurveSpecListWidgetModel."""

from func_sketch._cpp import PlotConfig, PlotRange
from func_sketch._gui.plot_2d.curve_spec_list_widget_model import (
    CurveSpecListWidgetModel,
)
from func_sketch._gui.plot_2d.shared_state import SharedState


def _create_model(shared_state: SharedState) -> CurveSpecListWidgetModel:
    """Create a CurveSpecListWidgetModel bound to the given shared state.

    Args:
        shared_state: Shared state to bind.

    Returns:
        Created model.
    """
    model = CurveSpecListWidgetModel()
    model.shared_state = shared_state
    model.init()
    return model


class TestCurveSpecListWidgetModel:
    """Test of CurveSpecListWidgetModel."""

    def test_update_in_curve_spec_model(self) -> None:
        """Test for updates in a CurveSpecWidgetModel."""
        shared_state = SharedState()
        model = _create_model(shared_state)

        model.curve_models[0].expression_text = "x**2"

        assert shared_state.curve_specs[0].function_expression_str == "x**2"
        assert len(shared_state.sampled_curves[0].points) > 0

    def test_plot_range_update(self) -> None:
        """Test for updates in the plot range."""
        shared_state = SharedState()
        model = _create_model(shared_state)

        model.curve_models[0].expression_text = "x**2"
        shared_state.update_plot_range(None, PlotRange((-2.0, 2.0), (-1.0, 1.0)))

        assert shared_state.curve_specs[0].function_expression_str == "x**2"
        assert len(shared_state.sampled_curves[0].points) > 0
        assert shared_state.sampled_curves[0].points[0].x == -2.0

    def test_plot_config_update(self) -> None:
        """Test for updates in the plot config."""
        # Check of the change according to PlotConfig is difficult here.
        # But check that this operation does not cause an error.

        shared_state = SharedState()
        model = _create_model(shared_state)

        model.curve_models[0].expression_text = "x**2"
        shared_state.update_plot_config(None, PlotConfig())

        assert shared_state.curve_specs[0].function_expression_str == "x**2"
        assert len(shared_state.sampled_curves[0].points) > 0

    def test_show_legend_to_shared_state(self) -> None:
        """Test for updates of show_legend reflected to the shared state."""
        shared_state = SharedState()
        model = _create_model(shared_state)
        on_plot_config_changed = []
        shared_state.bind(
            on_plot_config_changed=lambda _instance, source, _value: on_plot_config_changed.append(
                source
            )
        )

        model.show_legend = True

        assert shared_state.plot_config.legend.visible
        assert on_plot_config_changed == [model]

    def test_show_legend_from_shared_state(self) -> None:
        """Test for updates of show_legend from the shared state."""
        shared_state = SharedState()
        model = _create_model(shared_state)
        on_plot_config_changed = []
        shared_state.bind(
            on_plot_config_changed=lambda _instance, source, _value: on_plot_config_changed.append(
                source
            )
        )

        config = PlotConfig()
        config.legend.visible = True
        shared_state.update_plot_config(None, config)

        assert model.show_legend
        assert on_plot_config_changed == [None]

    def test_empty_curve_name(self) -> None:
        """Test that an empty curve name is replaced with the default name."""
        shared_state = SharedState()
        model = _create_model(shared_state)

        model.curve_models[0].curve_name = "Test"
        assert shared_state.curve_specs[0].name == "Test"

        model.curve_models[0].curve_name = ""
        assert shared_state.curve_specs[0].name == "Curve 1"
