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

struct SHA384Result
{
    std::vector< uint8_t > bytes;
    std::string            string;
    std::vector< uint8_t > hashBytes;
    std::string            hashStringUppercase;
    std::string            hashStringLowercase;
};

class SHA384: public XS::Test::Case
{
    protected:
        
        void SetUp() override;
        
        std::vector< SHA384Result > result;
};

XSTestFixture( SHA384, Bytes_Vector )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA384::bytes( r.bytes );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA384, Bytes_Data )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA384::bytes( r.bytes.data(), r.bytes.size() );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA384, Bytes_String )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > h = SRP::SHA384::bytes( r.string );
        
        XSTestAssertTrue( h == r.hashBytes );
    }
}

XSTestFixture( SHA384, String_Vector )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA384::string( r.bytes, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA384::string( r.bytes, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA384, String_Data )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA384::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA384::string( r.bytes.data(), r.bytes.size(), SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA384, String_String )
{
    for( const auto & r: this->result )
    {
        std::string h1 = SRP::SHA384::string( r.string, SRP::String::HexFormat::Uppercase );
        std::string h2 = SRP::SHA384::string( r.string, SRP::String::HexFormat::Lowercase );
        
        XSTestAssertTrue( h1 == r.hashStringUppercase );
        XSTestAssertTrue( h2 == r.hashStringLowercase );
    }
}

XSTestFixture( SHA384, Update_Vector )
{
    SRP::SHA384            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.update( bytes ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes ) );
}

XSTestFixture( SHA384, Update_Data )
{
    SRP::SHA384            hasher;
    std::vector< uint8_t > bytes = { 0x01, 0x02 };
    
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.update( bytes.data(), bytes.size() ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( bytes.data(), bytes.size() ) );
}

XSTestFixture( SHA384, Update_String )
{
    SRP::SHA384 hasher;
    std::string string = "hello, world";
    
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.update( string ) );
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.update( string ) );
}

XSTestFixture( SHA384, Finalize )
{
    SRP::SHA384 hasher;
    
    XSTestAssertTrue(  hasher.finalize() );
    XSTestAssertFalse( hasher.finalize() );
}

XSTestFixture( SHA384, GetBytes )
{
    for( const auto & r: this->result )
    {
        SRP::SHA384 hasher;
        
        XSTestAssertTrue( hasher.getBytes().size() == 0 );
        XSTestAssertTrue( hasher.update( r.bytes ) );
        XSTestAssertTrue( hasher.getBytes().size() == 0 );
        XSTestAssertTrue( hasher.finalize() );
        XSTestAssertTrue( hasher.getBytes().size() > 0 );
        XSTestAssertTrue( hasher.getBytes() == r.hashBytes );
    }
}

XSTestFixture( SHA384, GetString )
{
    for( const auto & r: this->result )
    {
        SRP::SHA384 hasher;
        
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

void SHA384::SetUp()
{
    this->result =
    {
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd' },
            "hello, world",
            {
                0x1F, 0xCD, 0xB6, 0x05, 0x9C, 0xE0, 0x51, 0x72, 0xA2, 0x6B,
                0xBE, 0x2A, 0x3C, 0xCC, 0x88, 0xED, 0x5A, 0x8C, 0xD5, 0xFC,
                0x53, 0xED, 0xFD, 0x90, 0x53, 0x30, 0x4D, 0x42, 0x92, 0x96,
                0xA6, 0xDA, 0x23, 0xB1, 0xCD, 0x9E, 0x5C, 0x9E, 0xD3, 0xBB,
                0x34, 0xF0, 0x04, 0x18, 0xA7, 0x0C, 0xDB, 0x7E
            },
            "1FCDB6059CE05172A26BBE2A3CCC88ED5A8CD5FC53EDFD9053304D429296A6DA23B1CD9E5C9ED3BB34F00418A70CDB7E",
            "1fcdb6059ce05172a26bbe2a3ccc88ed5a8cd5fc53edfd9053304d429296a6da23b1cd9e5c9ed3bb34f00418a70cdb7e"
        },
        {
            { 'h', 'e', 'l', 'l', 'o', ',', ' ', 'u', 'n', 'i', 'v', 'e', 'r', 's', 'e' },
            "hello, universe",
            {
                0x7C, 0xA9, 0xDF, 0xD2, 0xFB, 0x76, 0x1B, 0x5C, 0xE8, 0x19,
                0x87, 0x09, 0x18, 0x00, 0x0B, 0xB7, 0xC7, 0x19, 0x66, 0xB2,
                0xAB, 0x51, 0x16, 0xAD, 0x47, 0xD2, 0x84, 0x3F, 0x3B, 0x2B,
                0x5A, 0xDD, 0x3F, 0xB4, 0x66, 0x43, 0x7B, 0x9E, 0x53, 0x37,
                0x5C, 0xDD, 0x93, 0x3C, 0x3E, 0x4B, 0x29, 0x1D
            },
            "7CA9DFD2FB761B5CE819870918000BB7C71966B2AB5116AD47D2843F3B2B5ADD3FB466437B9E53375CDD933C3E4B291D",
            "7ca9dfd2fb761b5ce819870918000bb7c71966b2ab5116ad47d2843f3b2b5add3fb466437b9e53375cdd933c3e4b291d"
        }
    };
}
