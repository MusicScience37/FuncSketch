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

"""Test of FloatTextInput widget."""

import math

from func_sketch._gui.float_text_input import FloatTextInput


class TestFloatTextInput:
    """Test of FloatTextInput widget."""

    def test_initial_value(self):
        """Test that the initial value is set correctly."""
        float_text_input = FloatTextInput(value=1.25)

        assert float_text_input.value == 1.25
        assert float_text_input.text == "1.25"

    def test_update_value_from_text(self):
        """Test that the value is updated when the text is changed."""
        float_text_input = FloatTextInput(value=0.0)
        on_text_count = []
        float_text_input.bind(text=lambda instance, value: on_text_count.append(1))
        on_value_count = []
        float_text_input.bind(value=lambda instance, value: on_value_count.append(1))

        float_text_input.text = "2.5"

        assert float_text_input.value == 2.5
        assert float_text_input.text == "2.5"
        assert len(on_text_count) == 1
        assert len(on_value_count) == 1

    def test_update_value_via_value_property(self):
        """Test that the text is updated when the value is changed."""
        float_text_input = FloatTextInput(value=0.0)
        on_text_count = []
        float_text_input.bind(text=lambda instance, value: on_text_count.append(1))
        on_value_count = []
        float_text_input.bind(value=lambda instance, value: on_value_count.append(1))

        float_text_input.value = 3.75

        assert float_text_input.value == 3.75
        assert float_text_input.text == "3.75"
        assert len(on_text_count) == 1
        assert len(on_value_count) == 1

    def test_update_text_with_unparsable_string(self):
        """Test that the value is not updated when the text cannot be parsed as a float."""
        float_text_input = FloatTextInput(value=1.0)
        on_value_count = []
        float_text_input.bind(value=lambda instance, value: on_value_count.append(1))

        float_text_input.text = "abc"

        assert float_text_input.value == 1.0
        assert float_text_input.text == "abc"
        assert float_text_input.is_valid is False
        assert len(on_value_count) == 0

    def test_update_text_with_nan(self):
        """Test that the value is not updated when the text is "nan"."""
        float_text_input = FloatTextInput(value=1.0)
        on_value_count = []
        float_text_input.bind(value=lambda instance, value: on_value_count.append(1))

        float_text_input.text = "nan"

        assert float_text_input.value == 1.0
        assert float_text_input.text == "nan"
        assert float_text_input.is_valid is False
        assert len(on_value_count) == 0

    def test_update_text_with_infinity(self):
        """Test that the value is not updated when the text is "inf"."""
        float_text_input = FloatTextInput(value=1.0)
        on_value_count = []
        float_text_input.bind(value=lambda instance, value: on_value_count.append(1))

        float_text_input.text = "inf"

        assert float_text_input.value == 1.0
        assert float_text_input.text == "inf"
        assert float_text_input.is_valid is False
        assert len(on_value_count) == 0

    def test_update_value_with_nan(self):
        """Test that the text is not updated when the value is set to nan."""
        float_text_input = FloatTextInput(value=1.0)
        on_text_count = []
        float_text_input.bind(text=lambda instance, value: on_text_count.append(1))

        float_text_input.value = math.nan

        assert math.isnan(float_text_input.value)
        assert float_text_input.text == "1.0"
        assert float_text_input.is_valid is True
        assert len(on_text_count) == 0

    def test_update_value_with_infinity(self):
        """Test that the text is not updated when the value is set to infinity."""
        float_text_input = FloatTextInput(value=1.0)
        on_text_count = []
        float_text_input.bind(text=lambda instance, value: on_text_count.append(1))

        float_text_input.value = math.inf

        assert float_text_input.value == math.inf
        assert float_text_input.text == "1.0"
        assert float_text_input.is_valid is True
        assert len(on_text_count) == 0

    def test_update_text_to_invalid_value_and_then_valid_value(self):
        """Test that the value is updated correctly after an invalid text input followed by a valid one."""
        float_text_input = FloatTextInput(value=1.0)
        on_value_count = []
        float_text_input.bind(value=lambda instance, value: on_value_count.append(1))

        # Set an invalid text input
        float_text_input.text = "invalid"
        assert float_text_input.value == 1.0
        assert float_text_input.is_valid is False
        assert len(on_value_count) == 0

        # Now set a valid text input
        float_text_input.text = "2.5"
        assert float_text_input.value == 2.5
        assert float_text_input.is_valid is True
        assert len(on_value_count) == 1
