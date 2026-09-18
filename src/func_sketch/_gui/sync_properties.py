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

"""Function to synchronize two properties."""

import kivy.event


def sync_properties(
    object1: kivy.event.EventDispatcher,  # type: ignore
    property_name1: str,
    object2: kivy.event.EventDispatcher,  # type: ignore
    property_name2: str,
    *,
    sync_initial: bool = True,
) -> None:
    """Synchronize two properties.

    Args:
        object1 (kivy.event.EventDispatcher): First object.
        property_name1 (str): Name of the property in the first object.
        object2 (kivy.event.EventDispatcher): Second object.
        property_name2 (str): Name of the property in the second object.
        sync_initial (bool): Whether to synchronize properties initially.
            The initial synchronization will set the second property's value
            to match the first property's value.
            Defaults to True.
    """
    syncing = False

    def on_object1_property_change(_instance: object, value: object) -> None:
        nonlocal syncing
        if syncing:
            return
        syncing = True
        try:
            setattr(object2, property_name2, value)
        finally:
            syncing = False

    def on_object2_property_change(_instance: object, value: object) -> None:
        nonlocal syncing
        if syncing:
            return
        syncing = True
        try:
            setattr(object1, property_name1, value)
        finally:
            syncing = False

    object1.bind(**{property_name1: on_object1_property_change})
    object2.bind(**{property_name2: on_object2_property_change})

    if sync_initial:
        setattr(object2, property_name2, getattr(object1, property_name1))
