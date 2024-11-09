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

#include <SRPXX/SHA384.hpp>
#include <openssl/sha.h>

namespace SRP
{
    class SHA384::IMPL
    {
        public:
            
            IMPL();
            ~IMPL();
            
            bool       _finalized;
            SHA512_CTX _context;
            uint8_t    _hash[ SHA384_DIGEST_LENGTH ];
    };
    
    std::vector< uint8_t > SHA384::bytes( const std::vector< uint8_t > & data )
    {
        return SHA384::bytes( data.data(), data.size() );
    }
    
    std::vector< uint8_t > SHA384::bytes( const uint8_t * data, size_t length )
    {
        SHA384 hasher;
        
        hasher.update( data, length );
        hasher.finalize();
        
        return hasher.getBytes();
    }
    
    std::vector< uint8_t > SHA384::bytes( const std::string & data )
    {
        return SHA384::bytes( reinterpret_cast< const uint8_t * >( data.c_str() ), data.length() );
    }
    
    std::string SHA384::string( const std::vector< uint8_t > & data, String::HexFormat format )
    {
        return SHA384::string( data.data(), data.size(), format );
    }
    
    std::string SHA384::string( const uint8_t * data, size_t length, String::HexFormat format )
    {
        return String::toHex( SHA384::bytes( data, length ), format );
    }
    
    std::string SHA384::string( const std::string & data, String::HexFormat format )
    {
        return SHA384::string( reinterpret_cast< const uint8_t * >( data.c_str() ), data.length(), format );
    }
    
    SHA384::SHA384():
        impl( std::make_unique< IMPL >() )
    {}
    
    SHA384::~SHA384()
    {}
    
    bool SHA384::update( const std::vector< uint8_t > & data )
    {
        return this->update( data.data(), data.size() );
    }
    
    bool SHA384::update( const uint8_t * data, size_t length )
    {
        if( this->impl->_finalized )
        {
            return false;
        }
        
        return SHA384_Update( &( this->impl->_context ), data, length ) == 1;
    }
    
    bool SHA384::update( const std::string & data )
    {
        return this->update( reinterpret_cast< const uint8_t * >( data.c_str() ), data.length() );
    }
    
    bool SHA384::finalize()
    {
        if( this->impl->_finalized )
        {
            return false;
        }
        
        if( SHA384_Final( this->impl->_hash, &( this->impl->_context ) ) == 1 )
        {
            this->impl->_finalized = true;
            
            return true;
        }
        
        return false;
    }
    
    std::vector< uint8_t > SHA384::getBytes()
    {
        if( this->impl->_finalized == false )
        {
            return {};
        }
        
        std::vector< uint8_t > bytes( sizeof( this->impl->_hash ) );
        
        memcpy( bytes.data(), this->impl->_hash, sizeof( this->impl->_hash ) );
        
        return bytes;
    }
    
    std::string SHA384::getString( String::HexFormat format )
    {
        return String::toHex( this->getBytes(), format );
    }
    
    SHA384::IMPL::IMPL():
        _finalized( false )
    {
        SHA384_Init( &( this->_context ) );
        memset( this->_hash, 0, sizeof( this->_hash ) );
    }
    
    SHA384::IMPL::~IMPL()
    {}
}
