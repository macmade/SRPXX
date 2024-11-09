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

XSTest( String, ToLower )
{
    XSTestAssertTrue( SRP::String::toLower( "abcd" ) == "abcd" );
    XSTestAssertTrue( SRP::String::toLower( "ABCD" ) == "abcd" );
    XSTestAssertTrue( SRP::String::toLower( "AbCd" ) == "abcd" );
    XSTestAssertTrue( SRP::String::toLower( "1234" ) == "1234" );
    XSTestAssertTrue( SRP::String::toLower( "A1B2" ) == "a1b2" );
}

XSTest( String, ToUpper )
{
    XSTestAssertTrue( SRP::String::toUpper( "ABCD" ) == "ABCD" );
    XSTestAssertTrue( SRP::String::toUpper( "abcd" ) == "ABCD" );
    XSTestAssertTrue( SRP::String::toUpper( "AbCd" ) == "ABCD" );
    XSTestAssertTrue( SRP::String::toUpper( "1234" ) == "1234" );
    XSTestAssertTrue( SRP::String::toUpper( "a1b2" ) == "A1B2" );
}

XSTest( String, ToHex )
{
    XSTestAssertTrue( SRP::String::toHex( {},             SRP::String::HexFormat::Uppercase ) == "" );
    XSTestAssertTrue( SRP::String::toHex( {},             SRP::String::HexFormat::Lowercase ) == "" );
    XSTestAssertTrue( SRP::String::toHex( { 0x42 },       SRP::String::HexFormat::Uppercase ) == "42" );
    XSTestAssertTrue( SRP::String::toHex( { 0x42 },       SRP::String::HexFormat::Lowercase ) == "42" );
    XSTestAssertTrue( SRP::String::toHex( { 0x42, 0xFF }, SRP::String::HexFormat::Uppercase ) == "42FF" );
    XSTestAssertTrue( SRP::String::toHex( { 0x42, 0xFF }, SRP::String::HexFormat::Lowercase ) == "42ff" );
}

XSTest( String, HasPrefix )
{
    XSTestAssertTrue( SRP::String::hasPrefix( "abcd", "a" ) );
    XSTestAssertTrue( SRP::String::hasPrefix( "abcd", "ab" ) );
    XSTestAssertTrue( SRP::String::hasPrefix( "abcd", "abcd" ) );
    
    XSTestAssertFalse( SRP::String::hasPrefix( "abcd", "b" ) );
    XSTestAssertFalse( SRP::String::hasPrefix( "abcd", "abcde" ) );
}
