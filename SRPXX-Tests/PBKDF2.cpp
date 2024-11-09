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

#ifdef __APPLE__
#include <CommonCrypto/CommonCrypto.h>
#endif

struct PBKDF2Result
{
    SRP::HashAlgorithm     algorithm;
    std::string            password;
    std::vector< uint8_t > salt;
    uint32_t               iterations;
    size_t                 keyLength;
    std::vector< uint8_t > key;
};

class PBKDF2: public XS::Test::Case
{
    protected:
        
        void SetUp() override;
        
        std::vector< PBKDF2Result > result;
};

XSTestFixture( PBKDF2, HMAC )
{
    for( const auto & r: this->result )
    {
        std::vector< uint8_t > k1 = SRP::PBKDF2::HMAC( r.algorithm, r.password,                         r.salt, r.iterations, r.keyLength );
        std::vector< uint8_t > k2 = SRP::PBKDF2::HMAC( r.algorithm, SRP::String::toBytes( r.password ), r.salt, r.iterations, r.keyLength );
        
        XSTestAssertTrue( k1.size() == r.key.size() );
        XSTestAssertTrue( k2.size() == r.key.size() );
        
        XSTestAssertTrue( k1 == r.key );
        XSTestAssertTrue( k2 == r.key );
    }
}

XSTestFixture( PBKDF2, HMAC_AppleCC )
{
    #ifdef __APPLE__
    
    std::vector< uint32_t > sizes                                                      = { 128, 256, 512, 1024 };
    std::vector< std::pair< SRP::HashAlgorithm, CCPseudoRandomAlgorithm > > algorithms =
    {
        { SRP::HashAlgorithm::SHA1,   kCCPRFHmacAlgSHA1 },
        { SRP::HashAlgorithm::SHA224, kCCPRFHmacAlgSHA224 },
        { SRP::HashAlgorithm::SHA256, kCCPRFHmacAlgSHA256 },
        { SRP::HashAlgorithm::SHA384, kCCPRFHmacAlgSHA384 },
        { SRP::HashAlgorithm::SHA512, kCCPRFHmacAlgSHA512 }
    };
    
    for( const auto & algorithm: algorithms )
    {
        for( uint32_t iterations: sizes )
        {
            for( uint32_t keyLength: sizes )
            {
                for( size_t i = 0; i < 10; i++ )
                {
                    std::vector< uint8_t > password = SRP::Random::bytes( 5   * ( i + 1 ) );
                    std::vector< uint8_t > salt     = SRP::Random::bytes( 128 * ( i + 1 ) );
                    std::vector< uint8_t > k1       = SRP::PBKDF2::HMAC( algorithm.first, password, salt, iterations, keyLength );
                    std::vector< uint8_t > k2       = std::vector< uint8_t >( keyLength );
                    
                    int res = CCKeyDerivationPBKDF
                    (
                        kCCPBKDF2,
                        reinterpret_cast< const char * >( password.data() ),
                        password.size(),
                        salt.data(),
                        salt.size(),
                        algorithm.second,
                        iterations,
                        k2.data(),
                        keyLength
                    );
                    
                    XSTestAssertTrue( res       == 0 );
                    XSTestAssertTrue( k1.size() == k2.size() );
                    XSTestAssertTrue( k1        == k2 );
                }
            }
        }
    }
    
    #endif
}

void PBKDF2::SetUp()
{
    this->result =
    {
        {
            SRP::HashAlgorithm::SHA1,
            "hello, world",
            { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 },
            1024,
            10,
            { 0x11, 0x5E, 0x34, 0x6A, 0xCC, 0xB4, 0xEE, 0x62, 0x11, 0x5D }
        },
        {
            SRP::HashAlgorithm::SHA1,
            "hello, universe",
            { 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 },
            4096,
            16,
            { 0xDF, 0x98, 0xED, 0x0D, 0x0E, 0xD1, 0x3A, 0x23, 0x43, 0xEA, 0xEB, 0xD2, 0xCD, 0xEE, 0x2B, 0xD6 }
        },
        {
            SRP::HashAlgorithm::SHA224,
            "hello, world",
            { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 },
            1024,
            10,
            { 0x92, 0x06, 0x28, 0xFF, 0xC4, 0x86, 0x96, 0x41, 0xB1, 0xBA }
        },
        {
            SRP::HashAlgorithm::SHA224,
            "hello, universe",
            { 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 },
            4096,
            16,
            { 0x22, 0xD4, 0x44, 0x5C, 0xF2, 0xCB, 0xF5, 0x2A, 0x50, 0xEE, 0x52, 0x86, 0xDF, 0x11, 0x28, 0x76 }
        },
        {
            SRP::HashAlgorithm::SHA256,
            "hello, world",
            { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 },
            1024,
            10,
            { 0x9E, 0x0D, 0x40, 0x07, 0x7D, 0x4A, 0xE7, 0xE6, 0xAF, 0xE0 }
        },
        {
            SRP::HashAlgorithm::SHA256,
            "hello, universe",
            { 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 },
            4096,
            16,
            { 0x31, 0x9D, 0x2F, 0x05, 0xDC, 0x29, 0xA0, 0xE0, 0x14, 0xDE, 0x1B, 0x71, 0x30, 0xF1, 0x79, 0xB0 }
        },
        {
            SRP::HashAlgorithm::SHA384,
            "hello, world",
            { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 },
            1024,
            10,
            { 0x17, 0xB1, 0xA9, 0x5E, 0xFC, 0x9C, 0x38, 0x0B, 0xB6, 0x14 }
        },
        {
            SRP::HashAlgorithm::SHA384,
            "hello, universe",
            { 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 },
            4096,
            16,
            { 0x57, 0x5F, 0x47, 0x9D, 0x43, 0xBC, 0x49, 0x48, 0x62, 0xA5, 0xBC, 0xCD, 0x7B, 0x9B, 0xBB, 0x54 }
        },
        {
            SRP::HashAlgorithm::SHA512,
            "hello, world",
            { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 },
            1024,
            10,
            { 0x63, 0x3E, 0xAA, 0x51, 0x93, 0x82, 0x95, 0x77, 0x30, 0xDD }
        },
        {
            SRP::HashAlgorithm::SHA512,
            "hello, universe",
            { 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 },
            4096,
            16,
            { 0x92, 0x81, 0x63, 0xE8, 0x30, 0xA5, 0xD0, 0x30, 0xE1, 0x17, 0x05, 0x86, 0x61, 0x13, 0x80, 0x56 }
        }
    };
}
