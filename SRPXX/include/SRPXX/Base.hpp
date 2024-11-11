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

#ifndef SRPXX_BASE_HPP
#define SRPXX_BASE_HPP

#include <SRPXX/HashAlgorithm.hpp>
#include <SRPXX/Hasher.hpp>
#include <SRPXX/BigNum.hpp>
#include <memory>
#include <vector>
#include <cstdint>

namespace SRP
{
    class Base
    {
        public:
        
            enum class GroupType
            {
                NG1024,
                NG1536,
                NG2048,
                NG3072,
                NG4096,
                NG6144,
                NG8192
            };
            
            Base( HashAlgorithm hashAlgorithm, GroupType groupType );
            virtual ~Base();
            
            Base( const Base & o )              = delete;
            Base & operator =( const Base & o ) = delete;
            
            std::vector< uint8_t > salt() const;
            
            void setSalt( const std::vector< uint8_t > & value );
            
            BigNum N() const;
            BigNum g() const;
            BigNum k() const;
            BigNum u() const;
            
            virtual BigNum A() const = 0;
            virtual BigNum B() const = 0;
            
            std::unique_ptr< Hasher > makeHasher()                                               const;
            std::vector< uint8_t >    hash( const std::vector< uint8_t > & data )                const;
            std::vector< uint8_t >    hash( const std::vector< std::vector< uint8_t > > & data ) const;
            std::vector< uint8_t >    pad(  const std::vector< uint8_t > & data )                const;
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* SRPXX_BASE_HPP */
