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

"""Test of Margin."""

from func_sketch._cpp import Margin


class TestMargin:
    """Test of Margin."""

    def test_left(self) -> None:
        """Test of left property."""
        margin = Margin()
        margin.left = 12
        assert margin.left == 12

    def test_right(self) -> None:
        """Test of right property."""
        margin = Margin()
        margin.right = 12
        assert margin.right == 12

    def test_top(self) -> None:
        """Test of top property."""
        margin = Margin()
        margin.top = 12
        assert margin.top == 12

    def test_bottom(self) -> None:
        """Test of bottom property."""
        margin = Margin()
        margin.bottom = 12
        assert margin.bottom == 12
