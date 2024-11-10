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

struct SHA256Result
{
    std::vector< uint8_t > bytes;
    std::string            string;
    std::vector< uint8_t > hashBytes;
    std::string            hashStringUppercase;
    std::string            hashStringLowercase;
};

class SHA256: public XS::Test::Case
{
    protected:
        
        void SetUp() override;
        
        std::vector< SHA256Result > result;
};

XSTestFixture( SHA256, Bytes_Vector )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA256::bytes( r.bytes );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA256, Bytes_Data )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA256::bytes( r.bytes.data(), r.bytes.size() );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA256, Bytes_String )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA256::bytes( r.string );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA256, String_Vector )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA256::string( r.bytes, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA256::string( r.bytes, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA256, String_Data )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA256::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA256::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA256, String_String )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA256::string( r.string, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA256::string( r.string, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA256, Update_Vector )
{
    SRP::SHA256            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes ) );
}

XSTestFixture( SHA256, Update_Data )
{
    SRP::SHA256            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes.data(), bytes.size() ) );
}

XSTestFixture( SHA256, Update_String )
{
    SRP::SHA256 hasher;
    std::string string = "hello, world";
    
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( string ) );
}

XSTestFixture( SHA256, Finalize )
{
    SRP::SHA256 hasher;
    
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.finalize() );
}

XSTestFixture( SHA256, GetBytes )
{
    for( const auto & r: this->result )
    {
        SRP::SHA256 hasher;
        
        XSTestAssertTrue( hasher.bytes().size() == 0 );
        XSTestAssertTrue( hasher.update( r.bytes ) );
        XSTestAssertTrue( hasher.bytes().size() == 0 );
        XSTestAssertTrue( hasher.finalize() );
        XSTestAssertTrue( hasher.bytes().size() > 0 );
        XSTestAssertTrue( hasher.bytes() == r.hashBytes );
    }
}

XSTestFixture( SHA256, GetString )
{
    for( const auto & r: this->result )
    {
        SRP::SHA256 hasher;
        
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Uppercase ).size() == 0 );
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Lowercase ).size() == 0 );
        XSTestAssertTrue( hasher.update( r.bytes ) );
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Uppercase ).size() == 0 );
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Lowercase ).size() == 0 );
        XSTestAssertTrue( hasher.finalize() );
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Uppercase ).size() > 0 );
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Lowercase ).size() > 0 );
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Uppercase ) == r.hashStringUppercase );
        XSTestAssertTrue( hasher.string( SRP::String::HexFormat::Lowercase ) == r.hashStringLowercase );
    }
}

void SHA256::SetUp()
{
    this->result =
    {
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd' },
            "hello, world",
            {
                0x09, 0xCA, 0x7E, 0x4E, 0xAA, 0x6E, 0x8A, 0xE9, 0xC7, 0xD2,
                0x61, 0x16, 0x71, 0x29, 0x18, 0x48, 0x83, 0x64, 0x4D, 0x07,
                0xDF, 0xBA, 0x7C, 0xBF, 0xBC, 0x4C, 0x8A, 0x2E, 0x08, 0x36,
                0x0D, 0x5B
            },
            "09CA7E4EAA6E8AE9C7D261167129184883644D07DFBA7CBFBC4C8A2E08360D5B",
            "09ca7e4eaa6e8ae9c7d261167129184883644d07dfba7cbfbc4c8a2e08360d5b"
        },
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'u', 'n', 'i', 'v', 'e', 'r', 's', 'e' },
            "hello, universe",
            {
                0x21, 0xF0, 0x24, 0x3B, 0x16, 0x8D, 0xE0, 0xFC, 0x4B, 0x3E,
                0x29, 0x80, 0xBA, 0xC1, 0xD8, 0xE7, 0xE7, 0xE6, 0x0D, 0xC0,
                0xB7, 0x7A, 0x7C, 0x1C, 0x19, 0x9D, 0x94, 0x28, 0x6D, 0xCE,
                0x1D, 0x42
            },
            "21F0243B168DE0FC4B3E2980BAC1D8E7E7E60DC0B77A7C1C199D94286DCE1D42",
            "21f0243b168de0fc4b3e2980bac1d8e7e7e60dc0b77a7c1c199d94286dce1d42"
        }
    };
}
