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

#include <SRPXX/String.hpp>

namespace SRP
{
    namespace String
    {
        std::string toLower( const std::string & str )
        {
            std::string ret( str );
            
            std::transform( ret.begin(), ret.end(), ret.begin(), ::tolower );
            
            return ret;
        }
        
        std::string toUpper( const std::string & str )
        {
            std::string ret( str );
            
            std::transform( ret.begin(), ret.end(), ret.begin(), ::toupper );
            
            return ret;
        }
        
        std::string toHex( const std::vector< uint8_t > & data, HexFormat format )
        {
            std::string s;
            
            for( uint8_t b: data )
            {
                char c[ 3 ];
                
                if( format == HexFormat::Uppercase )
                {
                    std::snprintf( c, 3, "%02X", b );
                }
                else
                {
                    std::snprintf( c, 3, "%02x", b );
                }
                
                s.append( c );
            }
            
            return s;
        }
        
        std::vector< uint8_t > toBytes( const std::string & str )
        {
            return std::vector< uint8_t >( str.begin(), str.end() );
        }
        
        std::string fromBytes( const std::vector< uint8_t > & str )
        {
            return std::string( reinterpret_cast< const char * >( str.data() ), str.size() );
        }
        
        bool hasPrefix( const std::string & str, const std::string & prefix )
        {
            if( str.length() < prefix.length() )
            {
                return false;
            }
            
            return str.substr( 0, prefix.length() ) == prefix;
        }
    }
}
