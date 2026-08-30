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

"""Constants for the GUI."""

from func_sketch._cpp import PlotConfig, PlotRange, RGBColor
from func_sketch._impl.color_util import (
    hex_to_rgba,
    rgba_to_rgb_color,
)

# Colors

_PRIMARY99 = hex_to_rgba("#FEFBF9")
_PRIMARY65 = hex_to_rgba("#CB7739")
_PRIMARY50 = hex_to_rgba("#8E5225")

_GRAY99 = hex_to_rgba("#FCFCFB")
_GRAY97 = hex_to_rgba("#F6F5F4")
_GRAY90 = hex_to_rgba("#E2DDDA")
_GRAY85 = hex_to_rgba("#D3CCC8")
_GRAY50 = hex_to_rgba("#6A615C")
_GRAY30 = hex_to_rgba("#312D2A")

_ERROR95 = hex_to_rgba("#FEE9E9")
_ERROR50 = hex_to_rgba("#B9043A")

_WHITE = hex_to_rgba("#FFFFFF")

# Colors in GUI elements

NORMAL_TEXT_COLOR = _GRAY30
"""Color for normal text."""

SPLITTER_COLOR = _GRAY85
"""Color for the splitter between the navigation and main content areas."""

TEXT_INPUT_NORMAL_BACKGROUND_COLOR = _GRAY99
"""Background color for text input fields."""

TEXT_INPUT_FOCUSED_BACKGROUND_COLOR = _PRIMARY99
"""Background color for text input fields in focused state."""

TEXT_INPUT_ERROR_BACKGROUND_COLOR = _ERROR95
"""Background color for text input fields in error state."""

TEXT_INPUT_NORMAL_BORDER_COLOR = _GRAY50
"""Border color for text input fields in normal state."""

TEXT_INPUT_FOCUSED_BORDER_COLOR = _PRIMARY65
"""Border color for text input fields in focused state."""

TEXT_INPUT_ERROR_BORDER_COLOR = _ERROR50
"""Border color for text input fields in error state."""

ERROR_MESSAGE_COLOR = _ERROR50
"""Color for error messages."""

# Colors in navigation area

NAVIGATION_BACKGROUND_COLOR = _GRAY97
"""Background color for the navigation area."""

# Colors in plot area

PLOT_BACKGROUND_COLOR = _WHITE
"""Background color for the plot area."""

CURVE_COLORS = [
    # Colors in https://jfly.uni-koeln.de/color/#pallet
    RGBColor(0, 114, 178),  # Blue
    RGBColor(204, 121, 167),  # Reddish purple
    RGBColor(86, 180, 233),  # Sky blue
    RGBColor(213, 94, 0),  # Vermilion
    RGBColor(230, 159, 0),  # Orange
]
"""Colors for curves in the plot area."""

# Font sizes

FONT_SIZE_DEFAULT = 15
"""Default font size in Kivy."""

FONT_SIZE_HEADER1 = 25
"""Font size for level 1 headers."""

FONT_SIZE_HEADER2 = 20
"""Font size for level 2 headers."""

FONT_SIZE_TEXT = 15
"""Font size for normal text."""

# Spacing

SPACING_DEFAULT = 10
"""Default spacing between widgets."""

SPACING_HEADER1 = 35
"""Spacing for level 1 headers."""

SPACING_HEADER2 = 15
"""Spacing for level 2 headers."""

PADDING_NAVIGATION = 15
"""Padding for the navigation area."""

# Curves

NUM_CURVES = len(CURVE_COLORS)
"""Number of curves supported in the application."""

# Plotting

DEFAULT_PLOT_RANGE = PlotRange((-3.0, 3.0), (-3.0, 3.0))
"""Default range for the plot area."""


def _default_plot_config() -> PlotConfig:
    """Create a default PlotConfig object.

    Returns:
        PlotConfig: Default plot configuration object.
    """
    config = PlotConfig()
    config.background_color = rgba_to_rgb_color(PLOT_BACKGROUND_COLOR)
    config.grid.color = rgba_to_rgb_color(_GRAY90)
    config.axes.color = rgba_to_rgb_color(NORMAL_TEXT_COLOR)
    config.plot_title_color = rgba_to_rgb_color(NORMAL_TEXT_COLOR)
    return config


DEFAULT_PLOT_CONFIG = _default_plot_config()
"""Default plot configuration object."""
