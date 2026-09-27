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

"""Test of commands."""

import logging
import pathlib

import cv2
import numpy
import pytest
import pytest_mock

from func_sketch._gui.plot_2d.commands import Commands
from func_sketch._gui.plot_2d.shared_state import SharedState


class TestSavePlotAsImage:
    """Test of save_plot_as_image function."""

    def _create_test_image(self) -> numpy.ndarray:
        height = 60
        width = 80
        image = numpy.zeros((height, width, 3), dtype=numpy.uint8)
        image[:, :, 0] = numpy.linspace(0, 255, width, dtype=numpy.uint8)[
            numpy.newaxis, :
        ]
        image[:, :, 1] = numpy.linspace(0, 255, height, dtype=numpy.uint8)[
            :, numpy.newaxis
        ]
        image[:, :, 2] = 128
        return image

    def test_save_image(
        self, tmp_path: pathlib.Path, mocker: pytest_mock.MockerFixture
    ) -> None:
        """Test saving a plot as an image."""
        image = self._create_test_image()
        shared_state = SharedState()
        shared_state.update_image_buffer(None, image)
        commands = Commands(shared_state=shared_state)
        output_path = tmp_path / "test_image.png"

        mock_tk = mocker.patch("tkinter.Tk")
        mock_asksaveasfilename = mocker.patch(
            "tkinter.filedialog.asksaveasfilename", return_value=str(output_path)
        )

        commands.save_plot_as_image()

        mock_tk.return_value.withdraw.assert_called_once()
        mock_asksaveasfilename.assert_called_once()
        mock_tk.return_value.destroy.assert_called_once()
        assert output_path.exists()
        read_image = cv2.imread(str(output_path), cv2.IMREAD_UNCHANGED)
        assert read_image is not None
        read_image = cv2.cvtColor(read_image, cv2.COLOR_BGR2RGB)
        assert (read_image == image).all()

    def test_cancel(
        self, tmp_path: pathlib.Path, mocker: pytest_mock.MockerFixture
    ) -> None:
        """Test cancelling saving a plot."""
        image = self._create_test_image()
        shared_state = SharedState()
        shared_state.update_image_buffer(None, image)
        commands = Commands(shared_state=shared_state)

        mock_tk = mocker.patch("tkinter.Tk")
        mock_asksaveasfilename = mocker.patch(
            "tkinter.filedialog.asksaveasfilename", return_value=""
        )

        commands.save_plot_as_image()

        mock_tk.return_value.withdraw.assert_called_once()
        mock_asksaveasfilename.assert_called_once()
        mock_tk.return_value.destroy.assert_called_once()
        assert list(tmp_path.iterdir()) == []

    def test_no_shared_state(
        self,
        tmp_path: pathlib.Path,
        mocker: pytest_mock.MockerFixture,
        caplog: pytest.LogCaptureFixture,
    ) -> None:
        """Test saving a plot without shared state."""
        commands = Commands()
        output_path = tmp_path / "test_image.png"

        mocker.patch("tkinter.Tk")
        mocker.patch(
            "tkinter.filedialog.asksaveasfilename", return_value=str(output_path)
        )

        with caplog.at_level(logging.ERROR):
            commands.save_plot_as_image()

        assert not output_path.exists()
        assert "Shared state is None" in caplog.text

    @pytest.mark.parametrize(
        "file_name", ["test_image", "test_image.", "test_image.txt"]
    )
    def test_fail_to_save(
        self,
        file_name: str,
        tmp_path: pathlib.Path,
        mocker: pytest_mock.MockerFixture,
        caplog: pytest.LogCaptureFixture,
    ) -> None:
        """Test failure in saving a plot."""
        image = self._create_test_image()
        shared_state = SharedState()
        shared_state.update_image_buffer(None, image)
        commands = Commands(shared_state=shared_state)
        output_path = tmp_path / file_name

        mocker.patch("tkinter.Tk")
        mocker.patch(
            "tkinter.filedialog.asksaveasfilename", return_value=str(output_path)
        )

        with caplog.at_level(logging.ERROR):
            commands.save_plot_as_image()

        assert not output_path.exists()
        assert "Failed to save the current plot" in caplog.text
