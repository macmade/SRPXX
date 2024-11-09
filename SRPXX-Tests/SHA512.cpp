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

struct Result
{
    std::vector< uint8_t > bytes;
    std::string            string;
    std::vector< uint8_t > hashBytes;
    std::string            hashStringUppercase;
    std::string            hashStringLowercase;
};

class SHA512: public XS::Test::Case
{
    protected:
        
        void SetUp() override;
        
        std::vector< Result > result;
};

XSTestFixture( SHA512, Bytes_Vector )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA512::bytes( r.bytes );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA512, Bytes_Data )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA512::bytes( r.bytes.data(), r.bytes.size() );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA512, Bytes_String )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA512::bytes( r.string );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA512, String_Vector )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA512::string( r.bytes, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA512::string( r.bytes, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA512, String_Data )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA512::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA512::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA512, String_String )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA512::string( r.string, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA512::string( r.string, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA512, Update_Vector )
{
    SRP::SHA512            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes ) );
}

XSTestFixture( SHA512, Update_Data )
{
    SRP::SHA512            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes.data(), bytes.size() ) );
}

XSTestFixture( SHA512, Update_String )
{
    SRP::SHA512 hasher;
    std::string string = "hello, world";
    
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( string ) );
}

XSTestFixture( SHA512, Finalize )
{
    SRP::SHA512 hasher;
    
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.finalize() );
}

XSTestFixture( SHA512, GetBytes )
{
    for( const auto & r: this->result )
    {
        SRP::SHA512 hasher;
        
        XSTestAssertTrue( hasher.getBytes().size() == 0 );
        XSTestAssertTrue( hasher.update( r.bytes ) );
        XSTestAssertTrue( hasher.getBytes().size() == 0 );
        XSTestAssertTrue( hasher.finalize() );
        XSTestAssertTrue( hasher.getBytes().size() > 0 );
        XSTestAssertTrue( hasher.getBytes() == r.hashBytes );
    }
}

XSTestFixture( SHA512, GetString )
{
    for( const auto & r: this->result )
    {
        SRP::SHA512 hasher;
        
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Uppercase ).size() == 0 );
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Lowercase ).size() == 0 );
        XSTestAssertTrue( hasher.update( r.bytes ) );
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Uppercase ).size() == 0 );
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Lowercase ).size() == 0 );
        XSTestAssertTrue( hasher.finalize() );
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Uppercase ).size() > 0 );
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Lowercase ).size() > 0 );
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Uppercase ) == r.hashStringUppercase );
        XSTestAssertTrue( hasher.getString( SRP::String::HexFormat::Lowercase ) == r.hashStringLowercase );
    }
}

void SHA512::SetUp()
{
    this->result =
    {
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd' },
            "hello, world",
            {
                0x87, 0x10, 0x33, 0x9D, 0xCB, 0x68, 0x14, 0xD0, 0xD9, 0xD2,
                0x29, 0x0E, 0xF4, 0x22, 0x28, 0x5C, 0x93, 0x22, 0xB7, 0x16,
                0x39, 0x51, 0xF9, 0xA0, 0xCA, 0x8F, 0x88, 0x3D, 0x33, 0x05,
                0x28, 0x6F, 0x44, 0x13, 0x9A, 0xA3, 0x74, 0x84, 0x8E, 0x41,
                0x74, 0xF5, 0xAA, 0xDA, 0x66, 0x30, 0x27, 0xE4, 0x54, 0x86,
                0x37, 0xB6, 0xD1, 0x98, 0x94, 0xAE, 0xC4, 0xFB, 0x6C, 0x46,
                0xA1, 0x39, 0xFB, 0xF9
            },
            "8710339DCB6814D0D9D2290EF422285C9322B7163951F9A0CA8F883D3305286F44139AA374848E4174F5AADA663027E4548637B6D19894AEC4FB6C46A139FBF9",
            "8710339dcb6814d0d9d2290ef422285c9322b7163951f9a0ca8f883d3305286f44139aa374848e4174f5aada663027e4548637b6d19894aec4fb6c46a139fbf9"
        },
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'u', 'n', 'i', 'v', 'e', 'r', 's', 'e' },
            "hello, universe",
            {
                0xB9, 0xE4, 0x5B, 0xB8, 0xD2, 0x6C, 0x21, 0x6F, 0xD6, 0x3E,
                0x18, 0x37, 0x8D, 0xE2, 0x35, 0x8C, 0x12, 0xE1, 0xB4, 0xFB,
                0x31, 0x98, 0x6B, 0x65, 0x94, 0xC2, 0x2A, 0x9D, 0xCE, 0x8D,
                0xDE, 0x8A, 0xB3, 0x0C, 0x70, 0x21, 0xE0, 0xE3, 0xB6, 0xDF,
                0x9F, 0x53, 0x21, 0x77, 0x32, 0xB0, 0x21, 0xAF, 0x8F, 0x1C,
                0xAF, 0x80, 0xA1, 0xD0, 0x1D, 0xB2, 0xB7, 0xBB, 0xE2, 0x40,
                0x7F, 0x67, 0xDE, 0xD5
            },
            "B9E45BB8D26C216FD63E18378DE2358C12E1B4FB31986B6594C22A9DCE8DDE8AB30C7021E0E3B6DF9F53217732B021AF8F1CAF80A1D01DB2B7BBE2407F67DED5",
            "b9e45bb8d26c216fd63e18378de2358c12e1b4fb31986b6594c22a9dce8dde8ab30c7021e0e3b6df9f53217732b021af8f1caf80a1d01db2b7bbe2407f67ded5"
        }
    };
}
