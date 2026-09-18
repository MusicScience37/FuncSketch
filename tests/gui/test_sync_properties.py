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

"""Test of sync_properties."""

import kivy.event
import kivy.properties

from func_sketch._gui.sync_properties import sync_properties


class _ObjectA(kivy.event.EventDispatcher):
    """Dummy event dispatcher with a property named "foo" for testing."""

    foo = kivy.properties.NumericProperty(0.0)


class _ObjectB(kivy.event.EventDispatcher):
    """Dummy event dispatcher with a property named "bar" for testing."""

    bar = kivy.properties.NumericProperty(0.0)


class _ObjectC(kivy.event.EventDispatcher):
    """Dummy event dispatcher with a property named "baz" for testing."""

    baz = kivy.properties.NumericProperty(0.0)


class TestSyncProperties:
    """Test of sync_properties."""

    def test_sync_properties(self) -> None:
        """Test that two properties are kept in sync in both directions."""
        object1 = _ObjectA(foo=1.0)
        object2 = _ObjectB(bar=2.0)

        sync_properties(object1, "foo", object2, "bar")

        # object2 is initialized from object1.
        assert object1.foo == 1.0
        assert object2.bar == 1.0

        object1.foo = 3.0
        assert object2.bar == 3.0

        object2.bar = 5.0
        assert object1.foo == 5.0

    def test_sync_properties_in_chain(self) -> None:
        """Test that properties can be synchronized in a chain."""
        object1 = _ObjectA(foo=1.0)
        object2 = _ObjectB(bar=2.0)
        object3 = _ObjectC(baz=3.0)

        sync_properties(object1, "foo", object2, "bar")
        sync_properties(object2, "bar", object3, "baz")

        # object2 and object3 are initialized in order.
        assert object1.foo == 1.0
        assert object2.bar == 1.0
        assert object3.baz == 1.0

        object1.foo = 10.0
        assert object2.bar == 10.0
        assert object3.baz == 10.0

        object3.baz = 20.0
        assert object2.bar == 20.0
        assert object1.foo == 20.0
