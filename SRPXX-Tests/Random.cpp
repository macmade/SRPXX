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

#include <SRPXX.hpp>
#include <XSTest/XSTest.hpp>

XSTest( Random, Bytes )
{
    std::vector< std::size_t > sizes = { 128, 256, 512, 1024, 2048, 4096 };
    
    for( const auto & size: sizes )
    {
        std::vector< std::vector< uint8_t > > data;
        
        for( int i = 0; i < 100; i++ )
        {
            data.push_back( SRP::Random::bytes( size ) );
        }
        
        for( size_t i = 0; i < data.size(); i++ )
        {
            XSTestAssertEqual( data[ i ].size(), size );
            
            for( size_t j = 0; j < data.size(); j++ )
            {
                if( j == i )
                {
                    continue;
                }
                
                XSTestAssertTrue( data[ i ] != data[ j ] );
            }
        }
    }
}
