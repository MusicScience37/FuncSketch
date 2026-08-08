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

"""Class of sampled curves."""

import dataclasses

from func_sketch._cpp import PointList, RGBColor


@dataclasses.dataclass
class SampledCurve:
    """Class of sampled curves."""

    samples: PointList
    """List of sampled points."""

    color: RGBColor
    """Color of the curve."""
