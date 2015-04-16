/*	Copyright (C) 2012 Alexey Guseynov

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __STD_HEADER_RANGE_ACCESS_H
#define __STD_HEADER_RANGE_ACCESS_H

#pragma GCC system_header

// Free functions begin(container) and end(container) for
// any containers with begin and and methods and for arrays

namespace std {

// begin for non const container
template<class Container>
inline auto begin(Container& c) -> decltype(c.begin()) {
	return c.begin();
}

// begin for const container
template<class Container>
inline auto begin(const Container& c) -> decltype(c.begin()) {
	return c.begin();
}

// end for non const container
template<class Container>
inline auto end(Container& c) -> decltype(c.end()) {
	return c.end();
}

// end for const container
template<class Container>
inline auto end(const Container& c) -> decltype(c.end()) {
	return c.end();
}

/// Return an iterator pointing to the first element of the array.
template<class ValueType, size_t Size>
inline ValueType* begin(ValueType (&arr)[Size]) {
	return arr;
}

/// Return an iterator pointing to one past the last element
template<class ValueType, size_t Size>
inline ValueType* end(ValueType (&arr)[Size]) {
	return arr + Size;
}

} // namespace

#endif // __STD_HEADER_RANGE_ACCESS_H
