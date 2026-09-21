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

"""Class of commands."""

import logging
import tkinter
import tkinter.filedialog

import kivy.event
import kivy.properties

from func_sketch._cpp import save_image

LOGGER = logging.getLogger(__name__)


class Commands(kivy.event.EventDispatcher):
    """Class of commands."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def save_plot_as_image(self) -> None:
        """Save the current plot as an image file."""
        LOGGER.debug("Saving the current plot as an image file.")

        root = tkinter.Tk()
        root.withdraw()  # Hide the root window
        file_path = tkinter.filedialog.asksaveasfilename(
            defaultextension=".png",
            filetypes=[("PNG files", "*.png")],
        )
        root.destroy()

        if not file_path:
            LOGGER.debug("Cancelled saving the plot.")
            return

        LOGGER.debug("Saving the current plot to %s", file_path)
        if self.shared_state is None:
            LOGGER.error("Shared state is None. Cannot save the plot.")
            return
        if not save_image(self.shared_state.image_buffer, file_path):
            LOGGER.error("Failed to save the current plot to %s", file_path)
            return
        LOGGER.debug("Wrote the current plot to %s", file_path)
