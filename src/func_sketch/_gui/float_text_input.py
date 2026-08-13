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

"""Class of text input field for floating point numbers."""

import logging
import math

import kivy.properties

from func_sketch._gui.plain_text_input import PlainTextInput

LOGGER = logging.getLogger(__name__)


class FloatTextInput(PlainTextInput):
    """Class of text input field for floating point numbers."""

    value = kivy.properties.NumericProperty(0.0)
    """Value of the floating-point number represented by the text input field."""

    is_valid = kivy.properties.BooleanProperty(True)
    """Whether the current text is a valid float."""

    def __init__(self, **kwargs):
        """Initialize the text input field.

        Args:
            **kwargs: Keyword arguments passed to the base class.
        """

        self._syncing = False
        super().__init__(**kwargs)
        self.text = str(self.value)

        self.bind(text=self._on_text_changed)
        self.bind(value=self._on_value_changed)
        self.bind(is_valid=self._update_error_color)

    def _update_error_color(self, _instance: object, is_valid: bool) -> None:
        """Change the background color depending on the validity.

        Args:
            _instance (object): Instance of the event.
            is_valid (bool): Whether the current text is a valid float.
        """
        self.is_error = not is_valid

    def _on_text_changed(self, _instance: object, text: str) -> None:
        """Update the value when the text is changed to a valid float.

        Args:
            _instance (object): Instance of the event.
            text (str): New text.
        """

        if self._syncing:
            return
        try:
            value = float(text)
        except ValueError:
            self.is_valid = False
            return
        if not math.isfinite(value):
            self.is_valid = False
            return
        self.is_valid = True
        self._syncing = True
        try:
            self.value = value
        finally:
            self._syncing = False

    def _on_value_changed(self, _instance: object, value: float) -> None:
        """Update the text when the value is changed.

        Args:
            _instance (object): Instance of the event.
            value (float): New value.
        """

        if self._syncing:
            return
        if not math.isfinite(value):
            LOGGER.warning(
                "Tried to set non-finite value %s from implementation.", value
            )
            return
        self._syncing = True
        try:
            self.text = str(value)
        finally:
            self._syncing = False
        self.is_valid = True
