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

"""Package of the GUI of FuncSketch."""

import pathlib

import kivy.resources

# Add this directory to the resource paths of Kivy so that
# `#:include xxx.kv` directives in the .kv files of this package can be
# resolved regardless of the current working directory or sys.argv[0].
kivy.resources.resource_add_path(str(pathlib.Path(__file__).absolute().parent))
