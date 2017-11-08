
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

add_subdirectory(mostFrequent/src)
add_subdirectory(userDefinedLiterals/src)
add_subdirectory(uniformInitialization/src)
add_subdirectory(autoType/src)
add_subdirectory(nullptr/src)
add_subdirectory(enumClass/src)
add_subdirectory(delegatingConstructor/src)
add_subdirectory(methodNewKeywords/src)
add_subdirectory(lambdaFunction/src)
add_subdirectory(rvalueAndLValue/src)
add_subdirectory(rvalueReference-movingSemantics/src)
add_subdirectory(rvalueReference-perfectForwarding/src)
add_subdirectory(compilerGeneratedFunctions/src)
add_subdirectory(sharedPointer/src)

