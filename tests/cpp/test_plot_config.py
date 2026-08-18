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

    def test_margin(self) -> None:
        """Test of margin property."""
        config = PlotConfig()

        # Configuration of margins can be changed in place.
        config.margin.left = 12
        config.margin.right = 34
        config.margin.top = 56
        config.margin.bottom = 78

        assert config.margin.left == 12
        assert config.margin.right == 34
        assert config.margin.top == 56
        assert config.margin.bottom == 78

    def test_axes(self) -> None:
        """Test of axes property."""
        config = PlotConfig()
        color = RGBColor(0x11, 0x22, 0x33)

        # Configuration of axes can be changed in place.
        config.axes.tick_label_font_size = 12
        config.axes.line_width = 3
        config.axes.color = color
        config.axes.num_pixels_per_tick_in_x_axis = 150
        config.axes.num_pixels_per_tick_in_y_axis = 100

        assert config.axes.tick_label_font_size == 12
        assert config.axes.line_width == 3
        assert config.axes.color.r == color.r
        assert config.axes.color.g == color.g
        assert config.axes.color.b == color.b
        assert config.axes.num_pixels_per_tick_in_x_axis == 150
        assert config.axes.num_pixels_per_tick_in_y_axis == 100

    def test_grid_line_width(self) -> None:
        """Test of grid_line_width property."""
        config = PlotConfig()
        config.grid_line_width = 3
        assert config.grid_line_width == 3

    def test_zero_line_width(self) -> None:
        """Test of zero_line_width property."""
        config = PlotConfig()
        config.zero_line_width = 3
        assert config.zero_line_width == 3

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

    def test_grid_color(self) -> None:
        """Test of grid_color property."""
        config = PlotConfig()
        color = RGBColor(0x11, 0x22, 0x33)
        config.grid_color = color
        assert config.grid_color.r == color.r
        assert config.grid_color.g == color.g
        assert config.grid_color.b == color.b

    def test_initial_num_sample_points(self) -> None:
        """Test of initial_num_sample_points property."""
        config = PlotConfig()
        config.initial_num_sample_points = 200
        assert config.initial_num_sample_points == 200

    def test_max_num_sample_points(self) -> None:
        """Test of max_num_sample_points property."""
        config = PlotConfig()
        config.max_num_sample_points = 3000
        assert config.max_num_sample_points == 3000

    def test_max_coordinate_change_rate(self) -> None:
        """Test of max_coordinate_change_rate property."""
        config = PlotConfig()
        config.max_coordinate_change_rate = 0.05
        assert config.max_coordinate_change_rate == 0.05

    def test_slope_change_threshold(self) -> None:
        """Test of slope_change_threshold property."""
        config = PlotConfig()
        config.slope_change_threshold = 0.5
        assert config.slope_change_threshold == 0.5

    def test_min_param_change_rate(self) -> None:
        """Test of min_param_change_rate property."""
        config = PlotConfig()
        config.min_param_change_rate = 0.01
        assert config.min_param_change_rate == 0.01
