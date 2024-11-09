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

#include <SRPXX/PBKDF2.hpp>
#include <SRPXX/String.hpp>
#include <openssl/evp.h>

namespace SRP
{
    namespace PBKDF2
    {
        std::vector< uint8_t > HMAC( HashAlgorithm algorithm, const std::string & password, const std::vector< uint8_t > & salt, uint32_t iterations, size_t keyLength )
        {
            return HMAC( algorithm, String::toBytes( password ), salt, iterations, keyLength );
        }
        
        std::vector< uint8_t > HMAC( HashAlgorithm algorithm, const std::vector< uint8_t > & password, const std::vector< uint8_t > & salt, uint32_t iterations, size_t keyLength )
        {
            std::vector< uint8_t > key( keyLength );
            const EVP_MD         * digest = nullptr;
            
            switch( algorithm )
            {
                case HashAlgorithm::SHA1:   digest = EVP_sha1();   break;
                case HashAlgorithm::SHA224: digest = EVP_sha224(); break;
                case HashAlgorithm::SHA256: digest = EVP_sha256(); break;
                case HashAlgorithm::SHA384: digest = EVP_sha384(); break;
                case HashAlgorithm::SHA512: digest = EVP_sha512(); break;
            }
            
            if( digest == nullptr )
            {
                return {};
            }
            
            int result = PKCS5_PBKDF2_HMAC
            (
                reinterpret_cast< const char * >( password.data() ),
                password.size(),
                salt.data(),
                salt.size(),
                iterations,
                digest,
                keyLength,
                key.data()
            );
            
            if( result == 1 )
            {
                return key;
            }
            
            return {};
        }
    }
}
