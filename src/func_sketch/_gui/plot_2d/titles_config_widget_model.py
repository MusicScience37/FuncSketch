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

"""Class of the view model of configurations of titles of the plot."""

import kivy.event
import kivy.properties

from func_sketch._cpp import PlotConfig


class TitlesConfigWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of configurations of titles of the plot."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    plot_title = kivy.properties.StringProperty("")
    """Title of the plot."""

    x_axis_title = kivy.properties.StringProperty("")
    """Title of the x axis."""

    y_axis_title = kivy.properties.StringProperty("")
    """Title of the y axis."""

    def init(self) -> None:
        """Initialize.

        Note:
            This method should be called after the shared state is set.
        """
        plot_config: PlotConfig = self.shared_state.plot_config
        self.plot_title = plot_config.plot_title
        self.x_axis_title = plot_config.axes.x_axis_title
        self.y_axis_title = plot_config.axes.y_axis_title

        self.shared_state.bind(
            on_plot_config_changed=self._on_shared_plot_config,
        )

    def _on_shared_plot_config(
        self, _instance: object, _source: object, value: PlotConfig
    ) -> None:
        """Callback when the on_plot_config_changed event is dispatched."""
        self.plot_title = value.plot_title
        self.x_axis_title = value.axes.x_axis_title
        self.y_axis_title = value.axes.y_axis_title

    def on_plot_title(self, _instance: object, value: str) -> None:
        """Callback when the plot_title property is changed."""
        plot_config: PlotConfig = self.shared_state.plot_config
        if plot_config.plot_title == value:
            return
        plot_config.plot_title = value
        self.shared_state.update_plot_config(self, plot_config)

    def on_x_axis_title(self, _instance: object, value: str) -> None:
        """Callback when the x_axis_title property is changed."""
        plot_config: PlotConfig = self.shared_state.plot_config
        if plot_config.axes.x_axis_title == value:
            return
        plot_config.axes.x_axis_title = value
        self.shared_state.update_plot_config(self, plot_config)

    def on_y_axis_title(self, _instance: object, value: str) -> None:
        """Callback when the y_axis_title property is changed."""
        plot_config: PlotConfig = self.shared_state.plot_config
        if plot_config.axes.y_axis_title == value:
            return
        plot_config.axes.y_axis_title = value
        self.shared_state.update_plot_config(self, plot_config)
