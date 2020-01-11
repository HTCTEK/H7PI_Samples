/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "RingBuffer.h"
#include <string.h>

RingBuffer::RingBuffer( void )
{
    _iHead=0 ;
    _iTail=0 ;
		_iCount=0;
}

void RingBuffer::store_char( uint8_t c )
{
  int i = (uint32_t)(_iHead + 1) % SERIAL_BUFFER_SIZE ;

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if ( i != _iTail )
  {
    _aucBuffer[_iHead] = c ;
    _iHead = i ;
		_iCount++;
  }
}

int RingBuffer::read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
  if (_iCount==0)
    return -1 ;

  uint8_t uc = _aucBuffer[_iTail] ;
  _iTail = (unsigned int)(_iTail + 1) % SERIAL_BUFFER_SIZE ;
	_iCount--;
  return uc ;
}

int RingBuffer::peek(void)
{
	if ( _iHead == _iTail )
    return -1 ;

  return _aucBuffer[_iTail] ;
}

//return if there have any char,if has,return true.
//else ,return false;
bool RingBuffer::avaliable(void)
{
	return (_iCount>0);
}

//clean all the buffer
void RingBuffer::clean(void)
{
	_iHead=0;
	_iTail=0;
	_iCount=0;
}
