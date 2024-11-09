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

#ifndef SRPXX_SHA_1_HPP
#define SRPXX_SHA_1_HPP

#include <SRPXX/Hasher.hpp>

namespace SRP
{
    class SHA1: public Hasher
    {
        public:
        
            static std::vector< uint8_t > bytes( const std::vector< uint8_t > & data );
            static std::vector< uint8_t > bytes( const uint8_t * data, size_t length );
            static std::vector< uint8_t > bytes( const std::string & data );
            
            static std::string string( const std::vector< uint8_t > & data, String::HexFormat format = String::HexFormat::Uppercase );
            static std::string string( const uint8_t * data, size_t length, String::HexFormat format = String::HexFormat::Uppercase );
            static std::string string( const std::string & data,            String::HexFormat format = String::HexFormat::Uppercase );
            
            SHA1();
            ~SHA1() override;
            
            SHA1( const SHA1 & o )              = delete;
            SHA1 & operator =( const SHA1 & o ) = delete;
            
            bool update( const std::vector< uint8_t > & data ) override;
            bool update( const uint8_t * data, size_t length ) override;
            bool update( const std::string & data            ) override;
            bool finalize()                                    override;
            
            std::vector< uint8_t > getBytes()                            override;
            std::string            getString( String::HexFormat format ) override;
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* SRPXX_SHA_1_HPP */
