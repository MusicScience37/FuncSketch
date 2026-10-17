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

"""Class of the view model of a curve specification."""

import kivy.event
import kivy.properties

from func_sketch._cpp import CurveSampler, ExplicitCurveSpec
from func_sketch._gui.common.color_util import rgb_color_to_rgba
from func_sketch._gui.common.sync_properties import sync_properties
from func_sketch._gui.plot_2d.explicit_curve_spec_widget_model import (
    ExplicitCurveSpecWidgetModel,
)


class CurveSpecWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of a curve specification."""

    curve_spec = kivy.properties.ObjectProperty()
    """Curve specification."""

    error_message = kivy.properties.StringProperty("")
    """Error message related to the curve specification."""

    def __init__(
        self,
        curve_sampler: CurveSampler,
        initial_curve_spec: ExplicitCurveSpec,
        **kwargs,
    ) -> None:
        """Constructor.

        Args:
            curve_sampler: Curve sampler.
            initial_curve_spec: Initial curve specification.
                Its name is used as the default name of the curve.
            **kwargs: Additional keyword arguments for the EventDispatcher.
        """
        self.explicit_curve_spec_widget_model = ExplicitCurveSpecWidgetModel(
            curve_sampler=curve_sampler,
            default_curve_name=initial_curve_spec.name,
        )
        self.explicit_curve_spec_widget_model.curve_spec = initial_curve_spec
        super().__init__(**kwargs)
        sync_properties(
            self.explicit_curve_spec_widget_model, "curve_spec", self, "curve_spec"
        )

    def _get_curve_name(self) -> str:
        """Get the name of the curve.

        Returns:
            Name of the curve.
        """
        return self.curve_spec.name

    curve_name = kivy.properties.AliasProperty(
        _get_curve_name,
        bind=("curve_spec",),
        cache=True,
    )
    """Name of the curve."""

    def _get_curve_color_as_rgba(self) -> tuple[float, float, float, float]:
        """Get the color of the curve as an RGBA tuple.

        Returns:
            Color of the curve as an RGBA tuple.
        """
        return rgb_color_to_rgba(self.curve_spec.color)

    curve_color_as_rgba = kivy.properties.AliasProperty(
        _get_curve_color_as_rgba,
        bind=("curve_spec",),
        cache=True,
    )
    """Color of the curve as an RGBA tuple."""
