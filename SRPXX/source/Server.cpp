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

#include <SRPXX/Server.hpp>

namespace SRP
{
    class Server::IMPL
    {
        public:
            
            IMPL( const std::string & identity, const BigNum & b );
            ~IMPL();
            
            std::string _identity;
            BigNum      _v;
            BigNum      _b;
            BigNum      _A;
    };
    
    Server::Server( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType ):
        Server( identity, hashAlgorithm, groupType, BigNum::random( 256 ) )
    {}
    
    Server::Server( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType, const BigNum & b ):
        Base( hashAlgorithm, groupType ),
        impl( std::make_unique< IMPL >( identity, b ) )
    {}
    
    Server::~Server()
    {}
            
    void Server::setV( const BigNum & value )
    {
        this->impl->_v = value;
    }
    
    void Server::setA( const BigNum & value )
    {
        this->impl->_A = value;
    }
            
    BigNum Server::A() const
    {
        return this->impl->_A;
    }
    
    /* k * v + g ^ b % N */
    BigNum Server::B() const
    {
        BigNum left  = this->k().modMul( this->v(), this->N() );
        BigNum right = this->g().modExp( this->b(), this->N() );
        
        return left.modAdd( right, this->N() );
    }
    
    BigNum Server::S() const
    {
        return {};
    }
    
    BigNum Server::v() const
    {
        return this->impl->_v;
    }
    
    BigNum Server::b() const
    {
        return this->impl->_b;
    }
    
    Server::IMPL::IMPL( const std::string & identity, const BigNum & b ):
        _identity( identity ),
        _b( b )
    {}
    
    Server::IMPL::~IMPL()
    {}
}
