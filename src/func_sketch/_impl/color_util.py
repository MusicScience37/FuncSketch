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

"""Utilities of colors."""

# cspell: ignore RRGGBB, RRGGBBAA


def hex_to_rgba(hex: str) -> tuple[float, float, float, float]:
    """Convert a hex color string to an RGBA tuple.

    Args:
        hex: Hex color string (e.g., "#RRGGBB" or "#RRGGBBAA").

    Returns:
        RGBA tuple with values in the range [0.0, 1.0].
    """
    hex = hex.lstrip("#")
    if len(hex) == 6:
        r, g, b = int(hex[0:2], 16), int(hex[2:4], 16), int(hex[4:6], 16)
        a = 255
    elif len(hex) == 8:
        r, g, b, a = (
            int(hex[0:2], 16),
            int(hex[2:4], 16),
            int(hex[4:6], 16),
            int(hex[6:8], 16),
        )
    else:
        raise ValueError("Invalid hex color format")
    return (r / 255.0, g / 255.0, b / 255.0, a / 255.0)
