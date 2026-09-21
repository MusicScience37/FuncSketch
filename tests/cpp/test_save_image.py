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

"""Test of save_image function."""

import pathlib

import cv2
import numpy
import pytest

from func_sketch._cpp import (
    CurveSampler,
    ExplicitCurveSpec,
    PlotRange,
    Plotter,
    save_image,
)
from func_sketch._gui.common.constants import CURVE_COLORS, DEFAULT_PLOT_CONFIG

THIS_DIR = pathlib.Path(__file__).absolute().parent


def _create_test_image() -> numpy.ndarray:
    """Create a test image.

    Returns:
        Test image as a numpy.ndarray.
    """
    height = 600
    width = 800

    config = DEFAULT_PLOT_CONFIG
    range = PlotRange((-3.0, 3.0), (-3.0, 3.0))
    sampler = CurveSampler(range, config.sampling)
    plotter = Plotter(range, config)

    curve_spec = ExplicitCurveSpec(
        name="Test Curve",
        function_expression_str="gamma(x)",
        color=CURVE_COLORS[0],
    )
    sampled_curve = sampler(curve_spec)

    image = numpy.ndarray((height, width, 3), dtype=numpy.uint8)
    plotter.write([sampled_curve], image)

    return image


@pytest.mark.parametrize("suffix", ["jpg", "png", "tiff", "webp"])
def test_save_image(suffix: str) -> None:
    """Test of save_image function."""
    image = _create_test_image()
    output_path = THIS_DIR / "outputs" / f"test_image.{suffix}"
    if output_path.exists():
        output_path.unlink()

    wrote = save_image(image, str(output_path))

    assert wrote
    assert output_path.exists()
    read_image = cv2.imread(str(output_path), cv2.IMREAD_UNCHANGED)
    assert read_image is not None
    assert read_image.shape == (600, 800, 3)
