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

XSTest( String, ToBytes )
{
    std::vector< uint8_t > b1 = SRP::String::toBytes( "" );
    std::vector< uint8_t > b2 = SRP::String::toBytes( SRP::String::fromBytes( { 0 } ) );
    std::vector< uint8_t > b3 = SRP::String::toBytes( "Ab" );
    std::vector< uint8_t > b4 = SRP::String::toBytes( SRP::String::fromBytes( { 65, 98, 0 } ) );
    std::vector< uint8_t > b5 = SRP::String::toBytes( SRP::String::fromBytes( { 65, 98, 0, 65 } ) );
    
    XSTestAssertTrue( b1.size() == 0 );
    XSTestAssertTrue( b2.size() == 1 );
    XSTestAssertTrue( b3.size() == 2 );
    XSTestAssertTrue( b4.size() == 3 );
    XSTestAssertTrue( b5.size() == 4 );
    
    XSTestAssertTrue( b2[ 0 ] == 0 );
    
    XSTestAssertTrue( b3[ 0 ] == 65 );
    XSTestAssertTrue( b3[ 1 ] == 98 );
    
    XSTestAssertTrue( b4[ 0 ] == 65 );
    XSTestAssertTrue( b4[ 1 ] == 98 );
    XSTestAssertTrue( b4[ 2 ] == 0 );
    
    XSTestAssertTrue( b5[ 0 ] == 65 );
    XSTestAssertTrue( b5[ 1 ] == 98 );
    XSTestAssertTrue( b5[ 2 ] == 0 );
    XSTestAssertTrue( b5[ 3 ] == 65 );
}

XSTest( String, FromBytes )
{
    std::string s1 = SRP::String::fromBytes( {} );
    std::string s2 = SRP::String::fromBytes( { 0 } );
    std::string s3 = SRP::String::fromBytes( { 65, 98 } );
    std::string s4 = SRP::String::fromBytes( { 65, 98, 0 } );
    std::string s5 = SRP::String::fromBytes( { 65, 98, 0, 65 } );
    
    XSTestAssertTrue( s1.length() == 0 );
    XSTestAssertTrue( s2.length() == 1 );
    XSTestAssertTrue( s3.length() == 2 );
    XSTestAssertTrue( s4.length() == 3 );
    XSTestAssertTrue( s5.length() == 4 );
    
    XSTestAssertTrue( s2[ 0 ] == 0 );
    
    XSTestAssertTrue( s3[ 0 ] == 65 );
    XSTestAssertTrue( s3[ 1 ] == 98 );
    
    XSTestAssertTrue( s4[ 0 ] == 65 );
    XSTestAssertTrue( s4[ 1 ] == 98 );
    XSTestAssertTrue( s4[ 2 ] == 0 );
    
    XSTestAssertTrue( s5[ 0 ] == 65 );
    XSTestAssertTrue( s5[ 1 ] == 98 );
    XSTestAssertTrue( s5[ 2 ] == 0 );
    XSTestAssertTrue( s5[ 3 ] == 65 );
    
}

XSTest( String, HasPrefix )
{
    XSTestAssertTrue( SRP::String::hasPrefix( "abcd", "a" ) );
    XSTestAssertTrue( SRP::String::hasPrefix( "abcd", "ab" ) );
    XSTestAssertTrue( SRP::String::hasPrefix( "abcd", "abcd" ) );
    
    XSTestAssertFalse( SRP::String::hasPrefix( "abcd", "b" ) );
    XSTestAssertFalse( SRP::String::hasPrefix( "abcd", "abcde" ) );
}
