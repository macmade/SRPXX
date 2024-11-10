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
            uint64_t               _options;
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
    
    void Client::setOptions( uint64_t options )
    {
        this->impl->_options = options;
    }
    
    void Client::addOption( Options option )
    {
        this->impl->_options |= static_cast< uint64_t >( option );
    }
    
    void Client::removeOption( Options option )
    {
        this->impl->_options &= ~static_cast< uint64_t >( option );
    }
    
    bool Client::hasOption( Options option ) const
    {
        return ( this->impl->_options & static_cast< uint64_t >( option ) ) != 0;
    }
    
    BigNum Client::a() const
    {
        return this->impl->_a;
    }
    
    /* ( g ^ a % N ) */
    BigNum Client::A() const
    {
        return this->g().modExp( this->impl->_a, this->N() );
    }
    
    /* ( SHA( s | SHA( I | `:` | P ) ) ) */
    BigNum Client::X() const
    {
        std::vector< std::vector< uint8_t > > data =
        {
            String::toBytes( this->impl->_identity ),
            String::toBytes( ":" ),
            this->impl->_password
        };
        
        if( this->hasOption( Options::NoUsernameInX ) )
        {
            data.erase( data.begin() );
        }
        
        std::vector< uint8_t > hash = this->hash
        (
            {
                this->impl->_salt,
                this->hash( data )
            }
        );
        
        return { hash, BigNum::Endianness::BigEndian };
    }
    
    Client::IMPL::IMPL( const std::string & identity, const BigNum & a ):
        _identity( identity ),
        _a( a ),
        _options( 0 )
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
