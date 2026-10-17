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

from func_sketch._cpp import CurveSampler, ExplicitCurveSpec, ParameterizedCurveSpec
from func_sketch._gui.common.color_util import rgb_color_to_rgba
from func_sketch._gui.common.sync_properties import sync_properties
from func_sketch._gui.plot_2d.explicit_curve_spec_widget_model import (
    ExplicitCurveSpecWidgetModel,
)
from func_sketch._gui.plot_2d.parameterized_curve_spec_widget_model import (
    ParameterizedCurveSpecWidgetModel,
)
from func_sketch._impl.curve_type import CurveType


class CurveSpecWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of a curve specification."""

    curve_type = kivy.properties.ObjectProperty(CurveType.EXPLICIT)
    """Type of the curve."""

    error_message = kivy.properties.StringProperty("")
    """Error message related to the curve specification."""

    _explicit_curve_spec = kivy.properties.ObjectProperty()
    """Specification of the explicit curve synchronized with the child model."""

    _parameterized_curve_spec = kivy.properties.ObjectProperty()
    """Specification of the parameterized curve synchronized with the child model."""

    def __init__(
        self,
        curve_sampler: CurveSampler,
        initial_curve_spec: ExplicitCurveSpec | ParameterizedCurveSpec,
        **kwargs,
    ) -> None:
        """Constructor.

        Args:
            curve_sampler: Curve sampler.
            initial_curve_spec: Initial curve specification.
                Its name is used as the default name of the curve,
                and its color is used for all types of curves.
            **kwargs: Additional keyword arguments for the EventDispatcher.
        """
        self.explicit_curve_spec_widget_model = ExplicitCurveSpecWidgetModel(
            curve_sampler=curve_sampler,
            default_curve_name=initial_curve_spec.name,
            curve_color=initial_curve_spec.color,
        )
        self.parameterized_curve_spec_widget_model = ParameterizedCurveSpecWidgetModel(
            curve_sampler=curve_sampler,
            default_curve_name=initial_curve_spec.name,
            curve_color=initial_curve_spec.color,
        )
        super().__init__(**kwargs)
        sync_properties(
            self.explicit_curve_spec_widget_model,
            "curve_spec",
            self,
            "_explicit_curve_spec",
        )
        sync_properties(
            self.parameterized_curve_spec_widget_model,
            "curve_spec",
            self,
            "_parameterized_curve_spec",
        )
        self.curve_spec = initial_curve_spec

    def _get_curve_spec(self) -> ExplicitCurveSpec | ParameterizedCurveSpec:
        """Get the curve specification of the current type.

        Returns:
            Curve specification.
        """
        if self.curve_type == CurveType.EXPLICIT:
            return self._explicit_curve_spec
        if self.curve_type == CurveType.PARAMETERIZED:
            return self._parameterized_curve_spec
        raise ValueError(f"Unsupported curve type: {self.curve_type}")

    def _set_curve_spec(
        self, curve_spec: ExplicitCurveSpec | ParameterizedCurveSpec
    ) -> None:
        """Set the curve specification, and change the type of the curve accordingly.

        Args:
            curve_spec: Curve specification.
        """
        if isinstance(curve_spec, ExplicitCurveSpec):
            self._explicit_curve_spec = curve_spec
            self.curve_type = CurveType.EXPLICIT
        elif isinstance(curve_spec, ParameterizedCurveSpec):
            self._parameterized_curve_spec = curve_spec
            self.curve_type = CurveType.PARAMETERIZED
        else:
            raise TypeError(f"Unsupported curve specification: {curve_spec}")

    curve_spec = kivy.properties.AliasProperty(
        _get_curve_spec,
        _set_curve_spec,
        bind=("curve_type", "_explicit_curve_spec", "_parameterized_curve_spec"),
        cache=True,
    )
    """Curve specification of the current type."""

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
