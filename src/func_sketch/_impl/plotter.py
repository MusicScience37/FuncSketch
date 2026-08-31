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

"""Class of plotting."""

import numpy
import numpy.typing

from func_sketch._cpp import (
    PlotConfig,
    PlotRange,
)
from func_sketch._cpp import Plotter as CppPlotter
from func_sketch._impl.sampled_curve import SampledCurve


class Plotter:
    """Class of plotting."""

    def __init__(self, plot_range: PlotRange, config: PlotConfig) -> None:
        """Constructor.

        Args:
            plot_range: Range of the plot.
            config: Configuration of the plot.
        """
        self._plotter = CppPlotter(plot_range, config)

    @property
    def plot_range(self) -> PlotRange:
        """Range of the plot."""
        raise NotImplementedError()

    @plot_range.setter
    def plot_range(self, value: PlotRange) -> None:
        """Set range of the plot.

        Args:
            value: Range of the plot.
        """
        self._plotter.range = value

    @property
    def config(self) -> PlotConfig:
        """Configuration of the plot."""
        raise NotImplementedError()

    @config.setter
    def config(self, value: PlotConfig) -> None:
        """Set configuration of the plot.

        Args:
            value: Configuration of the plot.
        """
        self._plotter.config = value

    def desired_size(self, height: int, width: int) -> None:
        """Set the desired size of images.

        Args:
            height: Desired height of the plots.
            width: Desired width of the plots.
        """
        self._plotter.desired_size(height, width)

    @property
    def actual_size(self) -> tuple[int, int]:
        """Actual size of images, as a pair of height and width of the plots."""
        return self._plotter.actual_size

    def __call__(
        self,
        sampled_curves: list[SampledCurve],
        image: numpy.typing.NDArray[numpy.uint8],
    ) -> None:
        """Plot curves.

        Args:
            sampled_curves: List of sampled curves.
            image: Image to plot curves.
        """
        self._plotter.write_background(image)
        for sampled_curve in sampled_curves:
            self._plotter.write_curve(sampled_curve.samples, sampled_curve.color, image)
