/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2024 Jean-David Gadina - www.xs-labs.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

#include <SRPXX.hpp>
#include <XSTest/XSTest.hpp>

XSTest( Integer, Bytes )
{
    std::vector< uint8_t > bytesU8  { 0x01 };
    std::vector< uint8_t > bytesU16 { 0x01, 0x02 };
    std::vector< uint8_t > bytesU32 { 0x01, 0x02, 0x03, 0x04 };
    std::vector< uint8_t > bytesU64 { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    
    if( SRP::Platform::isBigEndian() )
    {
        XSTestAssertEqual( SRP::Integer::bytes< uint8_t  >( 0x01               ), bytesU8 );
        XSTestAssertEqual( SRP::Integer::bytes< uint16_t >( 0x0102             ), bytesU16 );
        XSTestAssertEqual( SRP::Integer::bytes< uint32_t >( 0x01020304         ), bytesU32 );
        XSTestAssertEqual( SRP::Integer::bytes< uint64_t >( 0x0102030405060708 ), bytesU64 );
    }
    else
    {
        
        XSTestAssertEqual( SRP::Integer::bytes< uint8_t  >( 0x01               ), bytesU8 );
        XSTestAssertEqual( SRP::Integer::bytes< uint16_t >( 0x0201             ), bytesU16 );
        XSTestAssertEqual( SRP::Integer::bytes< uint32_t >( 0x04030201         ), bytesU32 );
        XSTestAssertEqual( SRP::Integer::bytes< uint64_t >( 0x0807060504030201 ), bytesU64 );
    }
}
