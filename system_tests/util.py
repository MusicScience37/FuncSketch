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

"""Utility functions for system tests."""

import kivy.base


def wait_window_change(num_ticks: int = 20) -> None:
    """Wait for window change.

    Args:
        num_ticks (int, optional): Number of ticks wait in the Kivy event loop. Defaults to 20.
    """
    for _ in range(num_ticks):
        kivy.base.EventLoop.idle()
