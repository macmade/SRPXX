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

struct SHA224Result
{
    std::vector< uint8_t > bytes;
    std::string            string;
    std::vector< uint8_t > hashBytes;
    std::string            hashStringUppercase;
    std::string            hashStringLowercase;
};

class SHA224: public XS::Test::Case
{
    protected:
        
        void SetUp() override;
        
        std::vector< SHA224Result > result;
};

XSTestFixture( SHA224, Bytes_Vector )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA224::bytes( r.bytes );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA224, Bytes_Data )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA224::bytes( r.bytes.data(), r.bytes.size() );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA224, Bytes_String )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA224::bytes( r.string );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA224, String_Vector )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA224::string( r.bytes, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA224::string( r.bytes, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA224, String_Data )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA224::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA224::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA224, String_String )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA224::string( r.string, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA224::string( r.string, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA224, Update_Vector )
{
    SRP::SHA224            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes ) );
}

XSTestFixture( SHA224, Update_Data )
{
    SRP::SHA224            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes.data(), bytes.size() ) );
}

XSTestFixture( SHA224, Update_String )
{
    SRP::SHA224 hasher;
    std::string string = "hello, world";
    
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( string ) );
}

XSTestFixture( SHA224, Finalize )
{
    SRP::SHA224 hasher;
    
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.finalize() );
}

XSTestFixture( SHA224, GetBytes )
{
    for( const auto & r: this->result )
    {
        SRP::SHA224 hasher;
        
        XSTestAssertTrue( hasher.bytes().size() == 0 );
        XSTestAssertTrue( hasher.update( r.bytes ) );
        XSTestAssertTrue( hasher.bytes().size() == 0 );
        XSTestAssertTrue( hasher.finalize() );
        XSTestAssertTrue( hasher.bytes().size() > 0 );
        XSTestAssertTrue( hasher.bytes() == r.hashBytes );
    }
}

XSTestFixture( SHA224, GetString )
{
    for( const auto & r: this->result )
    {
        SRP::SHA224 hasher;
        
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

void SHA224::SetUp()
{
    this->result =
    {
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd' },
            "hello, world",
            {
                0x6E, 0x1A, 0x93, 0xE3, 0x2F, 0xB4, 0x40, 0x81, 0xA4, 0x01,
                0xF3, 0xDB, 0x3E, 0xF2, 0xE6, 0xE1, 0x08, 0xB7, 0xBB, 0xEE,
                0xB5, 0x70, 0x5A, 0xFD, 0xAF, 0x01, 0xFB, 0x27
            },
            "6E1A93E32FB44081A401F3DB3EF2E6E108B7BBEEB5705AFDAF01FB27",
            "6e1a93e32fb44081a401f3db3ef2e6e108b7bbeeb5705afdaf01fb27"
        },
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'u', 'n', 'i', 'v', 'e', 'r', 's', 'e' },
            "hello, universe",
            {
                0x2A, 0xB1, 0x03, 0xBA, 0x1F, 0xF5, 0x96, 0xC3, 0xE0, 0x52,
                0xC7, 0xF6, 0xD1, 0x33, 0x07, 0x61, 0xF7, 0xA6, 0x27, 0x99,
                0x58, 0x7F, 0x67, 0xF6, 0x88, 0x52, 0xEB, 0xF7
            },
            "2AB103BA1FF596C3E052C7F6D1330761F7A62799587F67F68852EBF7",
            "2ab103ba1ff596c3e052c7f6d1330761f7a62799587f67f68852ebf7"
        }
    };
}
