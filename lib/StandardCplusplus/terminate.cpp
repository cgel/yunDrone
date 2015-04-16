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

#include <exception>
#include <cstdlib>

namespace {
	std::terminate_handler __terminate_handler = std::abort;
}

void std::terminate () throw() {
	#ifdef __UCLIBCXX_EXCEPTION_SUPPORT__
	try {
		__terminate_handler ();
	} catch(...) {}
	#else
	__terminate_handler ();
	#endif
	std::abort ();
}

std::terminate_handler std::set_terminate (std::terminate_handler func) throw() {
	std::terminate_handler old = __terminate_handler;
	__terminate_handler = func;
	return old;
}
