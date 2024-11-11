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

#include <SRPXX/Base64.hpp>
#include <memory>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#ifdef __clang__
#pragma clang diagnostic pop
#endif

namespace SRP
{
    namespace Base64
    {
        struct BIOFreeAll
        {
            void operator()( BIO * p )
            {
                BIO_free_all( p );
            }
        };
        
        std::string encode( const std::vector< uint8_t > & value )
        {
            if( value.size() > INT_MAX )
            {
                return {};
            }
            
            std::unique_ptr< BIO, BIOFreeAll > base64( BIO_new( BIO_f_base64( ) ) );
            BIO                              * memory( BIO_new( BIO_s_mem() ) );
            
            BIO_push( base64.get(), memory );
            BIO_set_flags( base64.get(), BIO_FLAGS_BASE64_NO_NL );
            
            BIO_write( base64.get(), value.data(), static_cast< int >( value.size() ) );
            BIO_flush( base64.get() );
            
            char * encoded = nullptr;
            long   size    = BIO_get_mem_data( memory, &encoded );
            
            if( encoded == nullptr || size < 0 )
            {
                return {};
            }
            
            return std::string( encoded, static_cast< unsigned long >( size ) );
        }
        
        std::vector< uint8_t > decode( const std::string & value )
        {
            std::vector< uint8_t > decoded( ( ( value.length() / 4 ) * 3 ) + 1 );
            
            if( decoded.size() > INT_MAX )
            {
                return {};
            }
            
            std::unique_ptr< BIO, BIOFreeAll > base64( BIO_new( BIO_f_base64() ) );
            BIO                              * memory( BIO_new_mem_buf( value.c_str(), -1 ) );
            
            BIO_push( base64.get(), memory );
            BIO_set_flags( base64.get(), BIO_FLAGS_BASE64_NO_NL );
            
            int size = BIO_read( base64.get(), decoded.data(), static_cast< int >( decoded.size() ) );
            
            if( size < 0 )
            {
                return {};
            }
            
            decoded.resize( static_cast< size_t >( size ) );
            
            return decoded;
        }
    }
}
