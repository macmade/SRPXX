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

#ifndef SRPXX_BIG_NUM_HPP
#define SRPXX_BIG_NUM_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <optional>
#include <vector>

namespace SRP
{
    class BigNum
    {
        public:
            
            enum class StringFormat
            {
                Auto,
                Decimal,
                Hexadecimal
            };
            
            enum class Endianness
            {
                Auto,
                BigEndian,
                LittleEndian
            };
            
            static std::optional< BigNum > fromString( const std::string & value, StringFormat format = StringFormat::Auto );
        
            BigNum();
            BigNum( const std::vector< uint8_t > & bytes, Endianness endianness = Endianness::Auto );
            BigNum( uint64_t value );
            BigNum( const BigNum & o );
            BigNum( BigNum && o ) noexcept;
            ~BigNum();
            
            BigNum & operator =( BigNum o );
            BigNum & operator =( uint64_t value );
            
            bool operator ==( const BigNum & o )          const;
            bool operator ==( uint64_t value )            const;
            bool operator ==( const std::string & value ) const;
            
            bool operator !=( const BigNum & o )          const;
            bool operator !=( uint64_t value )            const;
            bool operator !=( const std::string & value ) const;
            
            std::string toString( StringFormat format = StringFormat::Auto ) const;
            
            BigNum negative() const;
            BigNum positive() const;
            
            bool isNegative() const;
            bool isPositive() const;
            bool isOdd()      const;
            bool isEven()     const;
            
            friend void swap( BigNum & o1, BigNum & o2 ) noexcept;
            
        private:
            
            class IMPL;
            
            std::unique_ptr< IMPL > impl;
    };
}

#endif /* SRPXX_BIG_NUM_HPP */
