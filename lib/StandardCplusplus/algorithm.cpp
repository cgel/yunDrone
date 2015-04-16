/*	Copyright (C) 2004 Garrett A. Kajmowicz
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


#include <algorithm>


namespace std{

	char* __copy(char* first, char* last, char* result) {
        #ifdef __AVR__
        // This is 1/3 shorter than code produced by GCC
        asm (
            "   movw    r30, r24\n"     // Move first to index register Z
            "   movw    r26, r20\n"     // Move result to index register X
            "   rjmp    forward_loop_middle\n"
            "forward_loop_start: ld r18, Z+\n"  // Copy data
            "   st      X+, r18\n"
            "forward_loop_middle: cp    r22, r30\n" // first != last
            "   cpc     r23, r31\n" 
            "   brne    forward_loop_start\n"
            "   movw    r24, r30\n"
        );
        #else
		while(first != last){
			*(result++) = *(first++);
		}
		return result;
        #endif
	}

	char* __copy_backward(char* first, char* last, char* result) {
        #ifdef __AVR__
        // This is 1/3 shorter than code produced by GCC
        asm (
            "   movw    r30, r22\n"     // Move first to index register Z
            "   movw    r26, r20\n"     // Move result to index register X
            "   rjmp    backward_loop_middle\n"
            "backward_loop_start: ld r18, -Z\n"  // Copy data
            "   st      -X, r18\n"
            "backward_loop_middle: cp    r24, r30\n" // first != last
            "   cpc     r25, r31\n" 
            "   brne    backward_loop_start\n"
            "   movw    r24, r30\n"
        );
        #else
		while(first != last){
			*(--result) = *(--last);
		}
		return result;
        #endif
	}
}


