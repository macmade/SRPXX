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

#ifndef SRPXX_TESTS_CONSTANTS_HPP
#define SRPXX_TESTS_CONSTANTS_HPP

#include <SRPXX.hpp>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

class TestVectors
{
    public:
        
        TestVectors( SRP::HashAlgorithm hashAlgorithm, SRP::Base::GroupType groupType, std::string identity, std::string password, std::vector< uint8_t > salt, std::vector< uint8_t > v, std::vector< uint8_t > a, std::vector< uint8_t > A, std::vector< uint8_t > b, std::vector< uint8_t > B, std::vector< uint8_t > u, std::vector< uint8_t > k, std::vector< uint8_t > S, std::vector< uint8_t > x, std::vector< uint8_t > K, std::vector< uint8_t > M1, std::vector< uint8_t > M2 );
        TestVectors( const TestVectors & o );
        ~TestVectors();
        
        TestVectors & operator =( TestVectors o );
        
        friend void swap( TestVectors & o1, TestVectors & o2 );
        
        std::unique_ptr< SRP::Client > makeClient() const;
        std::unique_ptr< SRP::Server > makeServer() const;
        
        SRP::HashAlgorithm     hashAlgorithm() const;
        SRP::Base::GroupType   groupType()     const;
        std::string            identity()      const;
        std::string            password()      const;
        std::vector< uint8_t > salt()          const;
        SRP::BigNum            v()             const;
        SRP::BigNum            a()             const;
        SRP::BigNum            A()             const;
        SRP::BigNum            b()             const;
        SRP::BigNum            B()             const;
        SRP::BigNum            u()             const;
        SRP::BigNum            k()             const;
        SRP::BigNum            S()             const;
        SRP::BigNum            x()             const;
        std::vector< uint8_t > K()             const;
        std::vector< uint8_t > M1()            const;
        std::vector< uint8_t > M2()            const;
        
        static std::vector< TestVectors > all();
        
    private:
        
        class IMPL;
        
        std::unique_ptr< IMPL > impl;
};

#endif /* SRPXX_TESTS_CONSTANTS_HPP */
