
# Copyright (C) Giuliano Catrambone (giuliano.catrambone@catrasoftware.it)

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License 
# as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later 
# version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

# Commercial use other than under the terms of the GNU General Public
# License is allowed only after express negotiation of conditions
# with the authors.

cmake_minimum_required(
	VERSION 2.8.12
)

project(
	C++ModernPills
)

SET(CMAKE_CXX_FLAGS "-std=c++14")

add_subdirectory(01_uniformInitialization/src)
add_subdirectory(02_autoType/src)
add_subdirectory(03_nullptr/src)
add_subdirectory(04_enumClass/src)
add_subdirectory(05_delegatingConstructor/src)
add_subdirectory(06_methodNewKeywords/src)
add_subdirectory(07_lambdaFunction/src)
add_subdirectory(08_rvalueAndLValue/src)
add_subdirectory(09_rvalueReference-movingSemantics/src)
add_subdirectory(10_rvalueReference-perfectForwarding/src)
add_subdirectory(11_compilerGeneratedFunctions/src)
add_subdirectory(12_sharedPointer/src)
add_subdirectory(13_weakPointer/src)
add_subdirectory(14_uniquePointer/src)
add_subdirectory(15_regularExpression/src)
add_subdirectory(16_chrono/src)
add_subdirectory(17_randomNumberEngine/src)
add_subdirectory(18_randomNumberDistribution/src)
add_subdirectory(19_tuple/src)
add_subdirectory(20_userDefinedLiterals/src)

add_subdirectory(50_stl-container-sequence-vector/src)
add_subdirectory(51_stl-container-sequence-deque/src)
add_subdirectory(52_stl-container-sequence-list/src)
add_subdirectory(53_stl-container-sequence-array/src)
add_subdirectory(54_stl-container-associative-set/src)
add_subdirectory(55_stl-container-associative-multiset/src)
add_subdirectory(56_stl-container-associative-map/src)
add_subdirectory(57_stl-container-associative-multimap/src)
add_subdirectory(58_stl-container-associative-unordered_set/src)
add_subdirectory(59_stl-container-associative-unordered_multiset/src)
add_subdirectory(60_stl-container-associative-unordered_map/src)
add_subdirectory(61_stl-container-associative-unordered_multimap/src)
add_subdirectory(62_stl-container-associative-array/src)
add_subdirectory(63_stl-container-adaptor/src)

add_subdirectory(mostFrequent/src)
