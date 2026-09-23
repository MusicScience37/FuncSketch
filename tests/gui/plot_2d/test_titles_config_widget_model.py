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

"""Test of TitlesConfigWidgetModel."""

from func_sketch._cpp import PlotConfig
from func_sketch._gui.plot_2d.shared_state import SharedState
from func_sketch._gui.plot_2d.titles_config_widget_model import TitlesConfigWidgetModel


def _create_model(shared_state: SharedState) -> TitlesConfigWidgetModel:
    """Create a TitlesConfigWidgetModel bound to the given shared state.

    Args:
        shared_state: Shared state to bind.

    Returns:
        Created model.
    """
    model = TitlesConfigWidgetModel()
    model.shared_state = shared_state
    model.init()
    return model


class TestTitlesConfigWidgetModel:
    """Test of TitlesConfigWidgetModel."""

    def test_init(self) -> None:
        """Test of initialization from the shared state."""
        shared_state = SharedState()
        config = shared_state.plot_config
        config.plot_title = "Plot"
        config.axes.x_axis_title = "Time"
        config.axes.y_axis_title = "Value"

        model = _create_model(shared_state)

        assert model.plot_title == "Plot"
        assert model.x_axis_title == "Time"
        assert model.y_axis_title == "Value"

    def test_titles_to_shared_state(self) -> None:
        """Test for updates of titles reflected to the shared state."""
        shared_state = SharedState()
        model = _create_model(shared_state)
        on_plot_config_changed = []
        shared_state.bind(
            on_plot_config_changed=lambda _instance, source, _value: on_plot_config_changed.append(
                source
            )
        )

        model.plot_title = "Plot"
        model.x_axis_title = "Time"
        model.y_axis_title = "Value"

        assert shared_state.plot_config.plot_title == "Plot"
        assert shared_state.plot_config.axes.x_axis_title == "Time"
        assert shared_state.plot_config.axes.y_axis_title == "Value"
        assert on_plot_config_changed == [model, model, model]

    def test_titles_from_shared_state(self) -> None:
        """Test for updates of titles from the shared state."""
        shared_state = SharedState()
        model = _create_model(shared_state)
        on_plot_config_changed = []
        shared_state.bind(
            on_plot_config_changed=lambda _instance, source, _value: on_plot_config_changed.append(
                source
            )
        )

        config = PlotConfig()
        config.plot_title = "Plot"
        config.axes.x_axis_title = "Time"
        config.axes.y_axis_title = "Value"
        shared_state.update_plot_config(None, config)

        assert model.plot_title == "Plot"
        assert model.x_axis_title == "Time"
        assert model.y_axis_title == "Value"
        assert on_plot_config_changed == [None]
