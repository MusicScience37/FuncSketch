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

"""Class to sample points of curves."""

from func_sketch._cpp import (
    ExpressionParser,
    FunctionSampler,
    PlotConfig,
    PlotRange,
)
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.sampled_curve import SampledCurve


class CurveSampler:
    """Class to sample points of curves."""

    def __init__(self, plot_range: PlotRange, config: PlotConfig) -> None:
        """Constructor.

        Args:
            plot_range: Range of the plot.
            config: Configuration of the plot.
        """
        self._parser = ExpressionParser()
        self._sampler = FunctionSampler(plot_range, config)

    @property
    def plot_range(self) -> PlotRange:
        """Get range of the plot.

        Returns:
            Range of the plot.
        """
        raise NotImplementedError()

    @plot_range.setter
    def plot_range(self, value: PlotRange) -> None:
        """Set range of the plot.

        Args:
            value: Range of the plot.
        """
        self._sampler.range = value

    @property
    def config(self) -> PlotConfig:
        """Get configuration of the plot.

        Returns:
            Configuration of the plot.
        """
        raise NotImplementedError()

    @config.setter
    def config(self, value: PlotConfig) -> None:
        """Set configuration of the plot.

        Args:
            value: Configuration of the plot.
        """
        self._sampler.config = value

    def __call__(self, curve_config: CurveConfig) -> SampledCurve:
        """Sample points of a curve.

        Args:
            curve_config: Configuration of the curve.

        Returns:
            Sampled curve.
        """
        expression = self._parser(curve_config.function_expression_str)
        samples = self._sampler(expression)
        return SampledCurve(samples, curve_config.color)
