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

"""Class of widgets to show plots."""

import kivy.graphics.texture
import kivy.properties
import kivy.uix.image
import numpy

from func_sketch._gui.constants import DEFAULT_PLOT_CONFIG, DEFAULT_PLOT_RANGE
from func_sketch._impl.plotter import Plotter


class PlotWidget(kivy.uix.image.Image):
    """Class of widgets to show plots."""

    shared_state = kivy.properties.ObjectProperty()

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        super().__init__(**kwargs)

        self._plotter = Plotter(DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG)

        self._prepare_texture()

    def on_shared_state(self, _instance: object, _value: object) -> None:
        """Callback when the shared_state property is set."""
        self.shared_state.bind(
            plot_range=self._on_shared_plot_range,
            plot_config=self._on_shared_plot_config,
            sampled_curves=self._on_shared_sampled_curves,
        )
        self._update_plot()

    def on_size(self, _instance: object, _value: object) -> None:
        """Callback when the size of the widget is changed."""
        self._prepare_texture()
        self._update_plot()

    def _on_shared_plot_range(self, _instance: object, _value: object) -> None:
        """Callback when the plot_range property is set in shared_state."""
        self._plotter.plot_range = self.shared_state.plot_range
        self._update_plot()

    def _on_shared_plot_config(self, _instance: object, _value: object) -> None:
        """Callback when the plot_config property is set in shared_state."""
        self._plotter.config = self.shared_state.plot_config
        self._update_plot()

    def _on_shared_sampled_curves(self, _instance: object, _value: object) -> None:
        """Callback when the sampled_curves property is set in shared_state."""
        self._update_plot()

    def _prepare_texture(self) -> None:
        """Prepare texture for the plot."""
        self._image_buffer = numpy.zeros(
            (int(self.height), int(self.width), 3), dtype=numpy.uint8
        )
        self._texture = kivy.graphics.texture.Texture.create(
            size=(int(self.width), int(self.height)), colorfmt="rgb"
        )
        self._texture.blit_buffer(
            self._image_buffer.tobytes(), colorfmt="rgb", bufferfmt="ubyte"
        )
        self._texture.flip_vertical()
        self.texture = self._texture

    def _update_plot(self) -> None:
        """Update the plot."""
        self._plotter(self.shared_state.sampled_curves, self._image_buffer)
        self._texture.blit_buffer(
            self._image_buffer.tobytes(), colorfmt="rgb", bufferfmt="ubyte"
        )
