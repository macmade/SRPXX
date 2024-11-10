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

struct SHA1Result
{
    std::vector< uint8_t > bytes;
    std::string            string;
    std::vector< uint8_t > hashBytes;
    std::string            hashStringUppercase;
    std::string            hashStringLowercase;
};

class SHA1: public XS::Test::Case
{
    protected:
        
        void SetUp() override;
        
        std::vector< SHA1Result > result;
};

XSTestFixture( SHA1, Bytes_Vector )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA1::bytes( r.bytes );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA1, Bytes_Data )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA1::bytes( r.bytes.data(), r.bytes.size() );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA1, Bytes_String )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA1::bytes( r.string );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA1, String_Vector )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA1::string( r.bytes, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA1::string( r.bytes, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA1, String_Data )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA1::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA1::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA1, String_String )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA1::string( r.string, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA1::string( r.string, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA1, Update_Vector )
{
    SRP::SHA1              hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes ) );
}

XSTestFixture( SHA1, Update_Data )
{
    SRP::SHA1              hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes.data(), bytes.size() ) );
}

XSTestFixture( SHA1, Update_String )
{
    SRP::SHA1   hasher;
    std::string string = "hello, world";
    
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( string ) );
}

XSTestFixture( SHA1, Finalize )
{
    SRP::SHA1 hasher;
    
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.finalize() );
}

XSTestFixture( SHA1, GetBytes )
{
    for( const auto & r: this->result )
    {
        SRP::SHA1 hasher;
        
        XSTestAssertTrue( hasher.bytes().size() == 0 );
        XSTestAssertTrue( hasher.update( r.bytes ) );
        XSTestAssertTrue( hasher.bytes().size() == 0 );
        XSTestAssertTrue( hasher.finalize() );
        XSTestAssertTrue( hasher.bytes().size() > 0 );
        XSTestAssertTrue( hasher.bytes() == r.hashBytes );
    }
}

XSTestFixture( SHA1, GetString )
{
    for( const auto & r: this->result )
    {
        SRP::SHA1 hasher;
        
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

void SHA1::SetUp()
{
    this->result =
    {
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd' },
            "hello, world",
            {
                0xB7, 0xE2, 0x3E, 0xC2, 0x9A, 0xF2, 0x2B, 0x0B, 0x4E, 0x41,
                0xDA, 0x31, 0xE8, 0x68, 0xD5, 0x72, 0x26, 0x12, 0x1C, 0x84
            },
            "B7E23EC29AF22B0B4E41DA31E868D57226121C84",
            "b7e23ec29af22b0b4e41da31e868d57226121c84"
        },
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'u', 'n', 'i', 'v', 'e', 'r', 's', 'e' },
            "hello, universe",
            {
                0xC7, 0x58, 0xD6, 0xDD, 0xA4, 0x50, 0x3F, 0xEE, 0x91, 0xA1,
                0x99, 0x61, 0x91, 0x5E, 0x2B, 0xA7, 0x50, 0x00, 0xC4, 0x55
            },
            "C758D6DDA4503FEE91A19961915E2BA75000C455",
            "c758d6dda4503fee91a19961915e2ba75000c455"
        }
    };
}
