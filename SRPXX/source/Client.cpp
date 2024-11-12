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

#ifdef _WIN32
#include <Windows.h>
#endif

namespace SRP
{
    class Client::IMPL
    {
        public:
            
            IMPL( const BigNum & a );
            ~IMPL();
            
            void clearPassword();
            
            BigNum                 _a;
            BigNum                 _B;
            std::vector< uint8_t > _password;
            uint64_t               _options;
    };
    
    Client::Client( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType ):
        Client( identity, hashAlgorithm, groupType, BigNum::random( 256 ) )
    {}
            
    Client::Client( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType, const BigNum & a ):
        Base( identity, hashAlgorithm, groupType ),
        impl( std::make_unique< IMPL >( a ) )
    {}
    
    Client::~Client()
    {}
    
    void Client::setPassword( const std::string & value )
    {
        this->setPassword( SRP::String::toBytes( value ) );
    }
    
    void Client::setPassword( const std::vector< uint8_t > & value )
    {
        this->impl->clearPassword();
        
        this->impl->_password = value;
    }
    
    void Client::setB( const BigNum & value )
    {
        this->impl->_B = value;
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
    
    /* ( g ^ a % N ) */
    BigNum Client::A() const
    {
        return this->g().modExp( this->impl->_a, this->N() );
    }
    
    /* From server */
    BigNum Client::B() const
    {
        return this->impl->_B;
    }
    
    BigNum Client::a() const
    {
        return this->impl->_a;
    }
    
    /* ( SHA( s | SHA( I | `:` | P ) ) ) */
    BigNum Client::x() const
    {
        std::vector< std::vector< uint8_t > > data =
        {
            String::toBytes( this->identity() ),
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
                this->salt(),
                this->hash( data )
            }
        );
        
        return { hash, BigNum::Endianness::BigEndian };
    }
    
    /* g ^ x % N */
    BigNum Client::v() const
    {
        return this->g().modExp( this->x(), this->N() );
    }
    
    /* ( ( B - ( k * g ^ x ) ) ^ ( a + ( u * x ) ) % N ) */
    BigNum Client::S() const
    {
        BigNum left  = this->B() - ( this->k() * this->g().modExp( this->x(), this->N() ) );
        BigNum right = this->a() + ( this->u() * this->x() );

        return left.modExp( right, this->N() );
    }
    
    Client::IMPL::IMPL( const BigNum & a ):
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
            #ifdef _WIN32
            SecureZeroMemory( this->_password.data(), this->_password.size() );
            #else
            memset_s( this->_password.data(), this->_password.size(), 0, this->_password.size() );
            #endif
        }
    }
}
