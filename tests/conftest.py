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

"""Configuration of pytest."""

import os
import pathlib
import shutil

import numpy
import pytest
import skimage.io
import skimage.metrics

# This must be set before importing Kivy.
os.environ["KIVY_NO_ARGS"] = "1"


class ImageApprover:
    """Class to check images as in ApprovalTests."""

    def __init__(
        self, data_dir: pathlib.Path, base_name: str, threshold: float
    ) -> None:
        """Constructor.

        Args:
            data_dir: Directory of data files.
            base_name: Base name of the image file.
            threshold: Threshold for comparison.
        """
        self._data_dir = data_dir
        self._base_name = base_name
        self._threshold = threshold

    @property
    def threshold(self) -> float:
        """Threshold for comparison."""
        return self._threshold

    @threshold.setter
    def threshold(self, value: float) -> None:
        """Set threshold for comparison.

        Args:
            value: Threshold for comparison.
        """
        self._threshold = value

    def verify(self, received: numpy.ndarray) -> None:
        """Verify the actual image.

        Args:
            received: Actual image.
        """
        approved_path = self._data_dir / f"{self._base_name}.approved.png"
        received_path = self._data_dir / f"{self._base_name}.received.png"
        diff_path = self._data_dir / f"{self._base_name}.diff.png"

        self._data_dir.mkdir(parents=True, exist_ok=True)

        if not approved_path.exists():
            skimage.io.imsave(str(received_path), received)
            shutil.copy(received_path, approved_path)
            pytest.fail(
                f"Approved image file does not exist: {approved_path}. "
                f"Created it from the received image. "
                "Please check and approve it."
            )

        approved = skimage.io.imread(str(approved_path))

        if received.shape != approved.shape:
            skimage.io.imsave(str(received_path), received)
            shutil.copy(received_path, approved_path)
            pytest.fail(
                f"Shape mismatch: received={received.shape}, approved={approved.shape}. "
                f"Received image: {received_path}, approved image: {approved_path}. "
                "Copied the received image to the approved image. "
                "Please check and approve it."
            )

        score, diff = skimage.metrics.structural_similarity(
            received, approved, channel_axis=2, full=True
        )
        diff = (diff * 255).astype(numpy.uint8)

        if score < self._threshold:
            skimage.io.imsave(str(received_path), received)
            skimage.io.imsave(str(diff_path), diff, check_contrast=False)
            shutil.copy(received_path, approved_path)
            pytest.fail(
                f"Image mismatch: score={score}, threshold={self._threshold}. "
                f"Received image: {received_path}, approved image: {approved_path}. "
                f"diff image: {diff_path}. "
                "Copied the received image to the approved image. "
                "Please check and approve it."
            )

        # Successful verification, remove the received and diff images.
        received_path.unlink(missing_ok=True)
        diff_path.unlink(missing_ok=True)


@pytest.fixture
def image_approver(request: pytest.FixtureRequest) -> ImageApprover:
    """Fixture to create an ImageApprover.

    Args:
        request: Request object.

    Returns:
        Created ImageApprover.
    """
    data_dir = pathlib.Path(request.path).parent / "approvals"
    base_name = f"{request.module.__name__}.{request.node.name}"
    threshold = 0.99
    return ImageApprover(data_dir, base_name, threshold)
