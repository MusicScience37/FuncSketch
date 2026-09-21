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

"""Class of the widget of the menu bar."""

import logging

import kivy.properties

from func_sketch._gui.common.menu_bar import MenuBar
from func_sketch._gui.plot_2d.commands import Commands

LOGGER = logging.getLogger(__name__)


class MenuWidget(MenuBar):
    """Class of the widget of the menu bar."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor.

        Args:
            **kwargs: Additional keyword arguments for the BoxLayout.
        """
        self._commands = Commands()
        super().__init__(
            menu_contents=[
                (
                    "File",
                    [
                        (
                            "Save plot as an image file",
                            self._commands.save_plot_as_image,
                        ),
                    ],
                ),
            ],
            **kwargs,
        )
        self.bind(shared_state=self._commands.setter("shared_state"))
