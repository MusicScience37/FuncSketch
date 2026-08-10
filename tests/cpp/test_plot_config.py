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

"""Test of PlotConfig."""

from func_sketch._cpp import PlotConfig, RGBColor


class TestPlotConfig:
    """Test of PlotConfig."""

    def test_left_margin(self) -> None:
        """Test of left_margin property."""
        config = PlotConfig()
        config.left_margin = 12
        assert config.left_margin == 12

    def test_right_margin(self) -> None:
        """Test of right_margin property."""
        config = PlotConfig()
        config.right_margin = 12
        assert config.right_margin == 12

    def test_top_margin(self) -> None:
        """Test of top_margin property."""
        config = PlotConfig()
        config.top_margin = 12
        assert config.top_margin == 12

    def test_bottom_margin(self) -> None:
        """Test of bottom_margin property."""
        config = PlotConfig()
        config.bottom_margin = 12
        assert config.bottom_margin == 12

    def test_tick_label_font_size(self) -> None:
        """Test of tick_label_font_size property."""
        config = PlotConfig()
        config.tick_label_font_size = 12
        assert config.tick_label_font_size == 12

    def test_axes_line_width(self) -> None:
        """Test of axes_line_width property."""
        config = PlotConfig()
        config.axes_line_width = 3
        assert config.axes_line_width == 3

    def test_grid_line_width(self) -> None:
        """Test of grid_line_width property."""
        config = PlotConfig()
        config.grid_line_width = 3
        assert config.grid_line_width == 3

    def test_curve_line_width(self) -> None:
        """Test of curve_line_width property."""
        config = PlotConfig()
        config.curve_line_width = 3
        assert config.curve_line_width == 3

    def test_background_color(self) -> None:
        """Test of background_color property."""
        config = PlotConfig()
        color = RGBColor(0x11, 0x22, 0x33)
        config.background_color = color
        assert config.background_color.r == color.r
        assert config.background_color.g == color.g
        assert config.background_color.b == color.b

    def test_axes_color(self) -> None:
        """Test of axes_color property."""
        config = PlotConfig()
        color = RGBColor(0x11, 0x22, 0x33)
        config.axes_color = color
        assert config.axes_color.r == color.r
        assert config.axes_color.g == color.g
        assert config.axes_color.b == color.b

    def test_grid_color(self) -> None:
        """Test of grid_color property."""
        config = PlotConfig()
        color = RGBColor(0x11, 0x22, 0x33)
        config.grid_color = color
        assert config.grid_color.r == color.r
        assert config.grid_color.g == color.g
        assert config.grid_color.b == color.b
