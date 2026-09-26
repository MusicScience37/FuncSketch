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

"""Test of 2D plotting."""

import kivy.core.window
import pytest

from func_sketch._cpp import Point
from func_sketch._gui.common.collapsible_box import CollapsibleBox
from func_sketch._gui.common.constants import DEFAULT_PLOT_RANGE, NUM_CURVES
from func_sketch._gui.common.float_text_input import FloatTextInput
from func_sketch._gui.common.plain_text_input import PlainTextInput
from func_sketch._gui.common.switch_widget import SwitchWidget
from func_sketch._gui.plot_2d.curve_spec_list_widget import CurveSpecListWidget
from func_sketch._gui.plot_2d.curve_spec_widget import CurveSpecWidget
from func_sketch._gui.plot_2d.expression_text_input import ExpressionTextInput
from func_sketch._gui.plot_2d.expression_text_input_model import (
    ExpressionTextInputModel,
)
from func_sketch._gui.plot_2d.func_sketch_app import FuncSketchApp
from func_sketch._gui.plot_2d.image_size_widget import ImageSizeWidget
from func_sketch._gui.plot_2d.plot_widget import PlotWidget
from func_sketch._gui.plot_2d.range_config_widget import RangeConfigWidget
from func_sketch._gui.plot_2d.shared_state import SharedState
from func_sketch._gui.plot_2d.titles_config_widget import TitlesConfigWidget
from system_tests.screen_saver import ScreenshotSaver
from system_tests.util import wait_window_change


# Creating multiple application instances causes issues with Kivy,
# so scope "session" is required.
# Note that all tests share the same instance of the application.
@pytest.fixture(scope="session")
def func_sketch_plot_2d_app():
    """FuncSketch 2D plot application fixture.

    Yields:
        The instance of the application.
    """
    kivy.core.window.Window.size = (1300, 800)

    app = FuncSketchApp()
    app._run_prepare()
    wait_window_change()
    yield app
    app.stop()


def test_writing_expression(
    func_sketch_plot_2d_app: FuncSketchApp, screenshot_saver: ScreenshotSaver
) -> None:
    """Test of writing function expressions."""
    """Test of curves."""
    screenshot_saver.save("initial")

    curve_spec_list_widget = func_sketch_plot_2d_app.root.ids.curve_spec_list_widget
    assert isinstance(curve_spec_list_widget, CurveSpecListWidget)
    curve_spec_widgets = curve_spec_list_widget.ids.curve_spec_list_layout.children
    assert len(curve_spec_widgets) == NUM_CURVES

    curve_spec_1_widget = curve_spec_widgets[NUM_CURVES - 1]
    assert isinstance(curve_spec_1_widget, CurveSpecWidget)

    expression_text_input = curve_spec_1_widget.ids.expression_text_input
    assert isinstance(expression_text_input, ExpressionTextInput)
    expression_text_input_model = expression_text_input.model
    assert isinstance(expression_text_input_model, ExpressionTextInputModel)
    auto_complete_dropdown = expression_text_input._auto_complete_dropdown

    def add_character(character: str) -> None:
        expression_text_input.text = expression_text_input.text + character
        expression_text_input.cursor = (
            len(expression_text_input.text),
            0,
        )
        expression_text_input_model.on_key_type(character)
        expression_text_input._update_auto_completion()

    add_character("e")
    wait_window_change()
    screenshot_saver.save("e")
    screenshot_saver.save("e_auto_complete", auto_complete_dropdown)
    assert expression_text_input_model.token_candidates is not None
    assert expression_text_input_model.token_candidates[0] == "e"

    add_character("x")
    wait_window_change()
    screenshot_saver.save("ex")
    screenshot_saver.save("ex_auto_complete", auto_complete_dropdown)
    assert expression_text_input_model.token_candidates is not None
    assert expression_text_input_model.token_candidates[0] == "exp"

    auto_complete_dropdown.select("exp")
    wait_window_change()
    screenshot_saver.save("exp")
    assert expression_text_input.text == "exp"
    assert expression_text_input_model.token_candidates is None

    add_character("(")
    wait_window_change()
    screenshot_saver.save("exp(")
    assert expression_text_input_model.token_candidates is None

    add_character("x")
    wait_window_change()
    screenshot_saver.save("exp(x")
    screenshot_saver.save("exp(x)_auto_complete", auto_complete_dropdown)
    assert expression_text_input_model.token_candidates is not None
    assert expression_text_input_model.token_candidates[0] == "x"

    add_character(")")
    wait_window_change()
    screenshot_saver.save("exp(x)")
    assert expression_text_input_model.token_candidates is None


def test_curves(
    func_sketch_plot_2d_app: FuncSketchApp, screenshot_saver: ScreenshotSaver
) -> None:
    """Test of curves."""
    screenshot_saver.save("initial")

    curve_spec_list_widget = func_sketch_plot_2d_app.root.ids.curve_spec_list_widget
    assert isinstance(curve_spec_list_widget, CurveSpecListWidget)
    curve_spec_widgets = curve_spec_list_widget.ids.curve_spec_list_layout.children
    assert len(curve_spec_widgets) == NUM_CURVES

    show_legend_switch = curve_spec_list_widget.ids.show_legend_switch
    assert isinstance(show_legend_switch, SwitchWidget)

    curve_spec_1_widget = curve_spec_widgets[NUM_CURVES - 1]
    assert isinstance(curve_spec_1_widget, CurveSpecWidget)
    curve_spec_2_widget = curve_spec_widgets[NUM_CURVES - 2]
    assert isinstance(curve_spec_2_widget, CurveSpecWidget)
    curve_spec_3_widget = curve_spec_widgets[NUM_CURVES - 3]
    assert isinstance(curve_spec_3_widget, CurveSpecWidget)
    curve_spec_4_widget = curve_spec_widgets[NUM_CURVES - 4]
    assert isinstance(curve_spec_4_widget, CurveSpecWidget)
    curve_spec_5_widget = curve_spec_widgets[NUM_CURVES - 5]
    assert isinstance(curve_spec_5_widget, CurveSpecWidget)

    curve_spec_1_widget.ids.expression_text_input.text = "gamma(x)"
    wait_window_change()
    screenshot_saver.save("curve1_set")

    show_legend_switch.active = True
    wait_window_change()
    screenshot_saver.save("show_legend_enabled")

    # Add other curves randomly.

    curve_spec_4_widget.ids.expression_text_input.text = "gamma(x+0.5i)"
    wait_window_change()
    screenshot_saver.save("curve4_set")

    curve_spec_2_widget.ids.expression_text_input.text = "-1/x"
    wait_window_change()
    screenshot_saver.save("curve2_set")

    curve_spec_5_widget.ids.expression_text_input.text = "x**100"
    wait_window_change()
    screenshot_saver.save("curve5_set")

    curve_spec_3_widget.ids.expression_text_input.text = "log10(x)"
    wait_window_change()
    screenshot_saver.save("curve3_set")


def test_fix_image_size(
    func_sketch_plot_2d_app: FuncSketchApp, screenshot_saver: ScreenshotSaver
) -> None:
    """Test to fix the image size."""
    screenshot_saver.save("initial")

    curves_collapsible_box = func_sketch_plot_2d_app.root.ids.curves_collapsible_box
    assert isinstance(curves_collapsible_box, CollapsibleBox)
    range_collapsible_box = func_sketch_plot_2d_app.root.ids.range_collapsible_box
    assert isinstance(range_collapsible_box, CollapsibleBox)
    image_size_collapsible_box = (
        func_sketch_plot_2d_app.root.ids.image_size_collapsible_box
    )
    assert isinstance(image_size_collapsible_box, CollapsibleBox)
    titles_collapsible_box = func_sketch_plot_2d_app.root.ids.titles_collapsible_box
    assert isinstance(titles_collapsible_box, CollapsibleBox)

    curves_collapsible_box.collapsed = True
    range_collapsible_box.collapsed = True
    image_size_collapsible_box.collapsed = False
    titles_collapsible_box.collapsed = True
    wait_window_change()
    screenshot_saver.save("show_image_size_section")

    image_size_widget = func_sketch_plot_2d_app.root.ids.image_size_widget
    assert isinstance(image_size_widget, ImageSizeWidget)
    fix_size_switch = image_size_widget.ids.fix_size_switch
    assert isinstance(fix_size_switch, SwitchWidget)
    fixed_width_input = image_size_widget.ids.fixed_width_input
    assert isinstance(fixed_width_input, PlainTextInput)
    fixed_height_input = image_size_widget.ids.fixed_height_input
    assert isinstance(fixed_height_input, PlainTextInput)
    shared_state = func_sketch_plot_2d_app.root.shared_state
    assert isinstance(shared_state, SharedState)

    image_buffer = shared_state.image_buffer
    assert image_buffer is not None
    assert image_buffer.shape[0] != int(fixed_height_input.text)
    assert image_buffer.shape[1] != int(fixed_width_input.text)

    fix_size_switch.active = True
    wait_window_change()
    screenshot_saver.save("fix_size_enabled")
    image_buffer = shared_state.image_buffer
    assert image_buffer is not None
    assert image_buffer.shape[0] == int(fixed_height_input.text)
    assert image_buffer.shape[1] == int(fixed_width_input.text)

    fixed_width_input.text = "800"
    fixed_height_input.text = "600"
    wait_window_change()
    screenshot_saver.save("fixed_size_changed")
    image_buffer = shared_state.image_buffer
    assert image_buffer is not None
    assert image_buffer.shape[0] == int(fixed_height_input.text)
    assert image_buffer.shape[1] == int(fixed_width_input.text)

    fix_size_switch.active = False
    wait_window_change()
    screenshot_saver.save("fix_size_disabled")
    image_buffer = shared_state.image_buffer
    assert image_buffer is not None
    assert image_buffer.shape[0] != int(fixed_height_input.text)
    assert image_buffer.shape[1] != int(fixed_width_input.text)


def test_change_range(
    func_sketch_plot_2d_app: FuncSketchApp, screenshot_saver: ScreenshotSaver
) -> None:
    """Test to change the range of the plot.

    This includes interaction in plots.
    """
    screenshot_saver.save("initial")

    curves_collapsible_box = func_sketch_plot_2d_app.root.ids.curves_collapsible_box
    assert isinstance(curves_collapsible_box, CollapsibleBox)
    range_collapsible_box = func_sketch_plot_2d_app.root.ids.range_collapsible_box
    assert isinstance(range_collapsible_box, CollapsibleBox)
    image_size_collapsible_box = (
        func_sketch_plot_2d_app.root.ids.image_size_collapsible_box
    )
    assert isinstance(image_size_collapsible_box, CollapsibleBox)
    titles_collapsible_box = func_sketch_plot_2d_app.root.ids.titles_collapsible_box
    assert isinstance(titles_collapsible_box, CollapsibleBox)

    curves_collapsible_box.collapsed = True
    range_collapsible_box.collapsed = False
    image_size_collapsible_box.collapsed = True
    titles_collapsible_box.collapsed = True
    wait_window_change()
    screenshot_saver.save("show_range_section")

    range_config_widget = func_sketch_plot_2d_app.root.ids.range_config_widget
    assert isinstance(range_config_widget, RangeConfigWidget)
    x_min_text_input = range_config_widget.ids.x_min_text_input
    assert isinstance(x_min_text_input, FloatTextInput)
    x_max_text_input = range_config_widget.ids.x_max_text_input
    assert isinstance(x_max_text_input, FloatTextInput)
    y_min_text_input = range_config_widget.ids.y_min_text_input
    assert isinstance(y_min_text_input, FloatTextInput)
    y_max_text_input = range_config_widget.ids.y_max_text_input
    assert isinstance(y_max_text_input, FloatTextInput)
    shared_state = func_sketch_plot_2d_app.root.shared_state
    assert isinstance(shared_state, SharedState)

    x_min_text_input.text = "-2.0"
    x_max_text_input.text = "3.0"
    y_min_text_input.text = "-1.0"
    y_max_text_input.text = "4.0"
    wait_window_change()
    screenshot_saver.save("range_changed")
    plot_range = shared_state.plot_range
    assert plot_range.x_range[0] == pytest.approx(-2.0)
    assert plot_range.x_range[1] == pytest.approx(3.0)
    assert plot_range.y_range[0] == pytest.approx(-1.0)
    assert plot_range.y_range[1] == pytest.approx(4.0)

    plot_widget = func_sketch_plot_2d_app.root.ids.plot_widget
    assert isinstance(plot_widget, PlotWidget)
    plot_widget_model = plot_widget._model

    def plot_to_image(x: float, y: float) -> tuple[float, float]:
        point_in_plot = Point(x, y)
        point_in_image_int = (
            plot_widget_model._plotter.point_converter.convert_plot_to_image(
                point_in_plot
            )
        )
        image_height = plot_widget_model._plotter.actual_size[0]
        # y-coordinate in Kivy is inverted compared to the coordinate in the image.
        return (
            float(point_in_image_int[0]),
            float(image_height - point_in_image_int[1]),
        )

    # Move mouse first.
    mouse_pos_in_plot = (0.0, 1.0)
    relative_mouse_position = plot_to_image(*mouse_pos_in_plot)
    plot_widget_model.on_mouse_pos_in_widget(relative_mouse_position)
    wait_window_change()
    screenshot_saver.save("mouse_moved")
    coordinate_tolerance = 0.05
    assert shared_state.mouse_pos_in_plot.x == pytest.approx(
        mouse_pos_in_plot[0], abs=coordinate_tolerance
    )
    assert shared_state.mouse_pos_in_plot.y == pytest.approx(
        mouse_pos_in_plot[1], abs=coordinate_tolerance
    )

    # Zoom in.
    plot_widget_model.on_mouse_scroll(is_scroll_down=True)
    wait_window_change()
    screenshot_saver.save("zoomed_in")
    plot_range = shared_state.plot_range
    assert plot_range.x_range[0] == pytest.approx(-1.0, abs=coordinate_tolerance)
    assert plot_range.x_range[1] == pytest.approx(1.5, abs=coordinate_tolerance)
    assert plot_range.y_range[0] == pytest.approx(0.0, abs=coordinate_tolerance)
    assert plot_range.y_range[1] == pytest.approx(2.5, abs=coordinate_tolerance)
    assert float(x_min_text_input.text) == pytest.approx(
        plot_range.x_range[0], abs=coordinate_tolerance
    )
    assert float(x_max_text_input.text) == pytest.approx(
        plot_range.x_range[1], abs=coordinate_tolerance
    )
    assert float(y_min_text_input.text) == pytest.approx(
        plot_range.y_range[0], abs=coordinate_tolerance
    )
    assert float(y_max_text_input.text) == pytest.approx(
        plot_range.y_range[1], abs=coordinate_tolerance
    )

    # Zoom out.
    plot_widget_model.on_mouse_scroll(is_scroll_down=False)
    wait_window_change()
    screenshot_saver.save("zoomed_out")
    plot_range = shared_state.plot_range
    assert plot_range.x_range[0] == pytest.approx(-2.0, abs=coordinate_tolerance)
    assert plot_range.x_range[1] == pytest.approx(3.0, abs=coordinate_tolerance)
    assert plot_range.y_range[0] == pytest.approx(-1.0, abs=coordinate_tolerance)
    assert plot_range.y_range[1] == pytest.approx(4.0, abs=coordinate_tolerance)
    assert float(x_min_text_input.text) == pytest.approx(
        plot_range.x_range[0], abs=coordinate_tolerance
    )
    assert float(x_max_text_input.text) == pytest.approx(
        plot_range.x_range[1], abs=coordinate_tolerance
    )
    assert float(y_min_text_input.text) == pytest.approx(
        plot_range.y_range[0], abs=coordinate_tolerance
    )
    assert float(y_max_text_input.text) == pytest.approx(
        plot_range.y_range[1], abs=coordinate_tolerance
    )

    # Pan.
    image_height = plot_widget_model._plotter.actual_size[0]
    image_width = plot_widget_model._plotter.actual_size[1]
    plot_widget_model.on_mouse_left_button_down(
        relative_pos=relative_mouse_position, current_touch_modifiers=[]
    )
    relative_mouse_position = (
        relative_mouse_position[0] + image_width * 0.1,
        relative_mouse_position[1] + image_height * 0.1,
    )
    plot_widget_model.on_mouse_left_button_dragging(
        relative_pos=relative_mouse_position
    )
    plot_widget_model.on_mouse_left_button_up(relative_pos=relative_mouse_position)
    plot_widget_model.on_mouse_pos_in_widget(relative_mouse_position)
    wait_window_change()
    screenshot_saver.save("panned")
    # Mouse position should remain consistent after panning.
    assert shared_state.mouse_pos_in_plot.x == pytest.approx(
        mouse_pos_in_plot[0], abs=coordinate_tolerance
    )
    assert shared_state.mouse_pos_in_plot.y == pytest.approx(
        mouse_pos_in_plot[1], abs=coordinate_tolerance
    )
    plot_range = shared_state.plot_range
    assert (plot_range.x_range[1] - plot_range.x_range[0]) == pytest.approx(
        5.0, abs=coordinate_tolerance
    )
    assert (plot_range.y_range[1] - plot_range.y_range[0]) == pytest.approx(
        5.0, abs=coordinate_tolerance
    )
    assert float(x_min_text_input.text) == pytest.approx(
        plot_range.x_range[0], abs=coordinate_tolerance
    )
    assert float(x_max_text_input.text) == pytest.approx(
        plot_range.x_range[1], abs=coordinate_tolerance
    )
    assert float(y_min_text_input.text) == pytest.approx(
        plot_range.y_range[0], abs=coordinate_tolerance
    )
    assert float(y_max_text_input.text) == pytest.approx(
        plot_range.y_range[1], abs=coordinate_tolerance
    )

    # Select another range.
    mouse_pos_in_plot = (-1.0, 2.0)
    relative_mouse_position = plot_to_image(*mouse_pos_in_plot)
    plot_widget_model.on_mouse_pos_in_widget(relative_mouse_position)
    plot_widget_model.on_mouse_left_button_down(
        relative_pos=relative_mouse_position, current_touch_modifiers=["ctrl"]
    )
    mouse_pos_in_plot = (1.0, 0.0)
    relative_mouse_position = plot_to_image(*mouse_pos_in_plot)
    plot_widget_model.on_mouse_pos_in_widget(relative_mouse_position)
    plot_widget_model.on_mouse_left_button_dragging(
        relative_pos=relative_mouse_position
    )
    plot_widget_model.on_mouse_left_button_up(relative_pos=relative_mouse_position)
    wait_window_change()
    screenshot_saver.save("selected_range")
    plot_range = shared_state.plot_range
    assert plot_range.x_range[0] == pytest.approx(-1.0, abs=coordinate_tolerance)
    assert plot_range.x_range[1] == pytest.approx(1.0, abs=coordinate_tolerance)
    assert plot_range.y_range[0] == pytest.approx(0.0, abs=coordinate_tolerance)
    assert plot_range.y_range[1] == pytest.approx(2.0, abs=coordinate_tolerance)
    assert float(x_min_text_input.text) == pytest.approx(
        plot_range.x_range[0], abs=coordinate_tolerance
    )
    assert float(x_max_text_input.text) == pytest.approx(
        plot_range.x_range[1], abs=coordinate_tolerance
    )
    assert float(y_min_text_input.text) == pytest.approx(
        plot_range.y_range[0], abs=coordinate_tolerance
    )
    assert float(y_max_text_input.text) == pytest.approx(
        plot_range.y_range[1], abs=coordinate_tolerance
    )

    # Reset the range.
    shared_state.update_plot_range(None, DEFAULT_PLOT_RANGE.copy())
    wait_window_change()
    screenshot_saver.save("reset_range")
    plot_range = shared_state.plot_range
    assert float(x_min_text_input.text) == pytest.approx(
        plot_range.x_range[0], abs=coordinate_tolerance
    )
    assert float(x_max_text_input.text) == pytest.approx(
        plot_range.x_range[1], abs=coordinate_tolerance
    )
    assert float(y_min_text_input.text) == pytest.approx(
        plot_range.y_range[0], abs=coordinate_tolerance
    )
    assert float(y_max_text_input.text) == pytest.approx(
        plot_range.y_range[1], abs=coordinate_tolerance
    )


def test_add_title(
    func_sketch_plot_2d_app: FuncSketchApp, screenshot_saver: ScreenshotSaver
) -> None:
    """Test to add a title."""
    screenshot_saver.save("initial")

    curves_collapsible_box = func_sketch_plot_2d_app.root.ids.curves_collapsible_box
    assert isinstance(curves_collapsible_box, CollapsibleBox)
    range_collapsible_box = func_sketch_plot_2d_app.root.ids.range_collapsible_box
    assert isinstance(range_collapsible_box, CollapsibleBox)
    image_size_collapsible_box = (
        func_sketch_plot_2d_app.root.ids.image_size_collapsible_box
    )
    assert isinstance(image_size_collapsible_box, CollapsibleBox)
    titles_collapsible_box = func_sketch_plot_2d_app.root.ids.titles_collapsible_box
    assert isinstance(titles_collapsible_box, CollapsibleBox)

    curves_collapsible_box.collapsed = True
    range_collapsible_box.collapsed = True
    image_size_collapsible_box.collapsed = True
    titles_collapsible_box.collapsed = False
    wait_window_change()
    screenshot_saver.save("show_titles_section")

    titles_config_widget = func_sketch_plot_2d_app.root.ids.titles_config_widget
    assert isinstance(titles_config_widget, TitlesConfigWidget)
    plot_title_text_input = titles_config_widget.ids.plot_title_text_input
    assert isinstance(plot_title_text_input, PlainTextInput)
    shared_state = func_sketch_plot_2d_app.root.shared_state
    assert isinstance(shared_state, SharedState)

    plot_title_text_input.text = "Test Plot"
    wait_window_change()
    screenshot_saver.save("added_title")
    assert shared_state.plot_config.plot_title == "Test Plot"
