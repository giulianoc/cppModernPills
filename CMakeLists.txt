
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

add_subdirectory(000_foreach/src)
add_subdirectory(001_uniformInitialization/src)
add_subdirectory(002_autoType/src)
add_subdirectory(003_nullptr/src)
add_subdirectory(004_enumClass/src)
add_subdirectory(005_delegatingConstructor/src)
add_subdirectory(006_methodNewKeywords/src)
add_subdirectory(007_lambdaFunction/src)
add_subdirectory(008_rvalueAndLValue/src)
add_subdirectory(009_rvalueReference-movingSemantics/src)
add_subdirectory(010_rvalueReference-perfectForwarding/src)
add_subdirectory(011_compilerGeneratedFunctions/src)
add_subdirectory(012_sharedPointer/src)
add_subdirectory(013_weakPointer/src)
add_subdirectory(014_uniquePointer/src)
add_subdirectory(015_regularExpression/src)
add_subdirectory(016_chrono/src)
add_subdirectory(017_randomNumberEngine/src)
add_subdirectory(018_randomNumberDistribution/src)
add_subdirectory(019_tuple/src)
add_subdirectory(020_userDefinedLiterals/src)
add_subdirectory(021_constructorOrder/src)

add_subdirectory(100_stl-container-sequence-vector/src)
add_subdirectory(101_stl-container-sequence-deque/src)
add_subdirectory(102_stl-container-sequence-list/src)
add_subdirectory(103_stl-container-sequence-array/src)
add_subdirectory(104_stl-container-associative-set/src)
add_subdirectory(105_stl-container-associative-multiset/src)
add_subdirectory(106_stl-container-associative-map/src)
add_subdirectory(107_stl-container-associative-multimap/src)
add_subdirectory(108_stl-container-associative-unordered_set/src)
add_subdirectory(109_stl-container-associative-unordered_multiset/src)
add_subdirectory(110_stl-container-associative-unordered_map/src)
add_subdirectory(111_stl-container-associative-unordered_multimap/src)
add_subdirectory(112_stl-container-associative-array/src)
add_subdirectory(113_stl-container-adaptor/src)
add_subdirectory(114_stl-iteratorsAndAlgorithms/src)
add_subdirectory(115_stl-functors/src)
add_subdirectory(116_stl-string/src)
add_subdirectory(117_stl-stream/src)

add_subdirectory(200_mostFrequent/src)
