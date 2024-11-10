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

/* For memset_s */
#define __STDC_WANT_LIB_EXT1__ 1

#include <SRPXX/Client.hpp>
#include <string.h>

namespace SRP
{
    class Client::IMPL
    {
        public:
            
            IMPL( const std::string & identity, const BigNum & a );
            ~IMPL();
            
            void clearPassword();
            void clearSalt();
            
            std::string            _identity;
            BigNum                 _a;
            std::vector< uint8_t > _password;
            std::vector< uint8_t > _salt;
    };
    
    Client::Client( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType ):
        Client( identity, hashAlgorithm, groupType, BigNum::random( 256 ) )
    {}
            
    Client::Client( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType, const BigNum & a ):
        Base( hashAlgorithm, groupType ),
        impl( std::make_unique< IMPL >( identity, a ) )
    {}
    
    Client::~Client()
    {}
    
    void Client::setPassword( const std::string & password )
    {
        this->setPassword( SRP::String::toBytes( password ) );
    }
    
    void Client::setPassword( const std::vector< uint8_t > & password )
    {
        this->impl->clearPassword();
        
        this->impl->_password = password;
    }
    
    void Client::setSalt( const std::vector< uint8_t > & salt )
    {
        this->impl->clearSalt();
        
        this->impl->_salt = salt;
    }
    
    BigNum Client::A() const
    {
        return this->g().modExp( this->impl->_a, this->N() );
    }
    
    BigNum Client::X() const
    {
        return {};
    }
    
    Client::IMPL::IMPL( const std::string & identity, const BigNum & a ):
        _identity( identity ),
        _a( a )
    {}
    
    Client::IMPL::~IMPL()
    {
        this->clearPassword();
    }
    
    void Client::IMPL::clearPassword()
    {
        if( this->_password.size() > 0 )
        {
            memset_s( this->_password.data(), this->_password.size(), 0, this->_password.size() );
        }
    }
    
    void Client::IMPL::clearSalt()
    {
        if( this->_salt.size() > 0 )
        {
            memset_s( this->_salt.data(), this->_salt.size(), 0, this->_salt.size() );
        }
    }
}
