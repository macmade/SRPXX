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

XSTest( BigNum, FromString_Auto )
{
    {
        auto n1 = SRP::BigNum::fromString( "42",     SRP::BigNum::StringFormat::Auto );
        auto n2 = SRP::BigNum::fromString( "-1",     SRP::BigNum::StringFormat::Auto );
        auto n3 = SRP::BigNum::fromString( "42FF",   SRP::BigNum::StringFormat::Auto );
        auto n4 = SRP::BigNum::fromString( "FF42",   SRP::BigNum::StringFormat::Auto );
        auto n5 = SRP::BigNum::fromString( "42FFZZ", SRP::BigNum::StringFormat::Auto );
        auto n6 = SRP::BigNum::fromString( "ZZFF42", SRP::BigNum::StringFormat::Auto );
        
        XSTestAssertTrue(  n1 != nullptr );
        XSTestAssertTrue(  n2 != nullptr );
        XSTestAssertTrue(  n3 != nullptr );
        XSTestAssertFalse( n4 != nullptr );
        XSTestAssertTrue(  n5 != nullptr );
        XSTestAssertFalse( n6 != nullptr );
        
        XSTestAssertTrue( *( n1 ) == 42 );
        XSTestAssertTrue( *( n2 ) == -1 );
        XSTestAssertTrue( *( n3 ) == 42 );
        XSTestAssertTrue( *( n5 ) == 42 );
    }
    
    {
        auto n1 = SRP::BigNum::fromString( "0x42",     SRP::BigNum::StringFormat::Auto );
        auto n2 = SRP::BigNum::fromString( "-0x1",     SRP::BigNum::StringFormat::Auto );
        auto n3 = SRP::BigNum::fromString( "0x42FF",   SRP::BigNum::StringFormat::Auto );
        auto n4 = SRP::BigNum::fromString( "0xFF42",   SRP::BigNum::StringFormat::Auto );
        auto n5 = SRP::BigNum::fromString( "0x42FFZZ", SRP::BigNum::StringFormat::Auto );
        auto n6 = SRP::BigNum::fromString( "0xZZFF42", SRP::BigNum::StringFormat::Auto );
        
        XSTestAssertTrue(  n1 != nullptr );
        XSTestAssertTrue(  n2 != nullptr );
        XSTestAssertTrue(  n3 != nullptr );
        XSTestAssertTrue(  n4 != nullptr );
        XSTestAssertTrue(  n5 != nullptr );
        XSTestAssertFalse( n6 != nullptr );
        
        XSTestAssertTrue( *( n1 ) == 0x42 );
        XSTestAssertTrue( *( n2 ) == -1 );
        XSTestAssertTrue( *( n3 ) == 0x42FF );
        XSTestAssertTrue( *( n4 ) == 0xFF42 );
        XSTestAssertTrue( *( n5 ) == 0x42FF );
    }
    
    {
        auto n1 = SRP::BigNum::fromString( "0X42",     SRP::BigNum::StringFormat::Auto );
        auto n2 = SRP::BigNum::fromString( "-0X1",     SRP::BigNum::StringFormat::Auto );
        auto n3 = SRP::BigNum::fromString( "0X42FF",   SRP::BigNum::StringFormat::Auto );
        auto n4 = SRP::BigNum::fromString( "0XFF42",   SRP::BigNum::StringFormat::Auto );
        auto n5 = SRP::BigNum::fromString( "0X42FFZZ", SRP::BigNum::StringFormat::Auto );
        auto n6 = SRP::BigNum::fromString( "0XZZFF42", SRP::BigNum::StringFormat::Auto );
        
        XSTestAssertTrue(  n1 != nullptr );
        XSTestAssertTrue(  n2 != nullptr );
        XSTestAssertTrue(  n3 != nullptr );
        XSTestAssertTrue(  n4 != nullptr );
        XSTestAssertTrue(  n5 != nullptr );
        XSTestAssertFalse( n6 != nullptr );
        
        XSTestAssertTrue( *( n1 ) == 0x42 );
        XSTestAssertTrue( *( n2 ) == -1 );
        XSTestAssertTrue( *( n3 ) == 0x42FF );
        XSTestAssertTrue( *( n4 ) == 0xFF42 );
        XSTestAssertTrue( *( n5 ) == 0x42FF );
    }
}

XSTest( BigNum, FromString_Decimal )
{
    auto n1 = SRP::BigNum::fromString( "42",   SRP::BigNum::StringFormat::Decimal );
    auto n2 = SRP::BigNum::fromString( "-1",   SRP::BigNum::StringFormat::Decimal );
    auto n3 = SRP::BigNum::fromString( "42FF", SRP::BigNum::StringFormat::Decimal );
    auto n4 = SRP::BigNum::fromString( "FF42", SRP::BigNum::StringFormat::Decimal );
    
    XSTestAssertTrue(  n1 != nullptr );
    XSTestAssertTrue(  n2 != nullptr );
    XSTestAssertTrue(  n3 != nullptr );
    XSTestAssertFalse( n4 != nullptr );
    
    XSTestAssertTrue( *( n1 ) == 42 );
    XSTestAssertTrue( *( n2 ) == -1 );
    XSTestAssertTrue( *( n3 ) == 42 );
}

XSTest( BigNum, FromString_Hexadecimal )
{
    auto n1 = SRP::BigNum::fromString( "42",     SRP::BigNum::StringFormat::Hexadecimal );
    auto n2 = SRP::BigNum::fromString( "-1",     SRP::BigNum::StringFormat::Hexadecimal );
    auto n3 = SRP::BigNum::fromString( "42FF",   SRP::BigNum::StringFormat::Hexadecimal );
    auto n4 = SRP::BigNum::fromString( "FF42",   SRP::BigNum::StringFormat::Hexadecimal );
    auto n5 = SRP::BigNum::fromString( "42FFZZ", SRP::BigNum::StringFormat::Hexadecimal );
    auto n6 = SRP::BigNum::fromString( "ZZFF42", SRP::BigNum::StringFormat::Hexadecimal );
    
    XSTestAssertTrue(  n1 != nullptr );
    XSTestAssertTrue(  n2 != nullptr );
    XSTestAssertTrue(  n3 != nullptr );
    XSTestAssertTrue(  n4 != nullptr );
    XSTestAssertTrue(  n5 != nullptr );
    XSTestAssertFalse( n6 != nullptr );
    
    XSTestAssertTrue( *( n1 ) == 0x42 );
    XSTestAssertTrue( *( n2 ) == -1 );
    XSTestAssertTrue( *( n3 ) == 0x42FF );
    XSTestAssertTrue( *( n4 ) == 0xFF42 );
    XSTestAssertTrue( *( n5 ) == 0x42FF );
}

XSTest( BigNum, Random )
{
    for( unsigned int i = 1; i < 10; i++ )
    {
        std::vector< SRP::BigNum > n;
        
        for( unsigned int j = 0; j < 10; j++ )
        {
            n.push_back( SRP::BigNum::random( i * 128 ) );
        }
        
        for( unsigned int j = 0; j < n.size(); j++ )
        {
            for( unsigned int k = 0; k < n.size(); k++ )
            {
                if( j == k )
                {
                    continue;
                }
                
                XSTestAssertTrue( n[ j ] != n[ k ] );
                XSTestAssertTrue( n[ j ].getBytes().size() == ( i * 128 ) / CHAR_BIT );
            }
        }
    }
}

XSTest( BigNum, CTOR )
{
    XSTestAssertTrue( SRP::BigNum() == 0 );
}

XSTest( BigNum, CTOR_Bytes_Auto )
{
    if( SRP::Platform::isBigEndian() )
    {
        XSTestAssertTrue( SRP::BigNum( { 0x01, 0x02 }, SRP::BigNum::Endianness::Auto ) == 0x0102 );
        XSTestAssertTrue( SRP::BigNum( { 0xFF, 0x00 }, SRP::BigNum::Endianness::Auto ) == 0xFF00 );
    }
    else
    {
        XSTestAssertTrue( SRP::BigNum( { 0x01, 0x02 }, SRP::BigNum::Endianness::Auto ) == 0x0201 );
        XSTestAssertTrue( SRP::BigNum( { 0xFF, 0x00 }, SRP::BigNum::Endianness::Auto ) == 0x00FF );
    }
}

XSTest( BigNum, CTOR_Bytes_BigEndian )
{
    if( SRP::Platform::isBigEndian() )
    {
        XSTestAssertTrue( SRP::BigNum( { 0x01, 0x02 }, SRP::BigNum::Endianness::BigEndian ) == 0x0102 );
        XSTestAssertTrue( SRP::BigNum( { 0xFF, 0x00 }, SRP::BigNum::Endianness::BigEndian ) == 0xFF00 );
    }
    else
    {
        XSTestAssertTrue( SRP::BigNum( { 0x01, 0x02 }, SRP::BigNum::Endianness::BigEndian ) == 0x0102 );
        XSTestAssertTrue( SRP::BigNum( { 0xFF, 0x00 }, SRP::BigNum::Endianness::BigEndian ) == 0xFF00 );
    }
}

XSTest( BigNum, CTOR_Bytes_LittleEndian )
{
    if( SRP::Platform::isBigEndian() )
    {
        XSTestAssertTrue( SRP::BigNum( { 0x01, 0x02 }, SRP::BigNum::Endianness::LittleEndian ) == 0x0201 );
        XSTestAssertTrue( SRP::BigNum( { 0xFF, 0x00 }, SRP::BigNum::Endianness::LittleEndian ) == 0x00FF );
    }
    else
    {
        XSTestAssertTrue( SRP::BigNum( { 0x01, 0x02 }, SRP::BigNum::Endianness::LittleEndian ) == 0x0201 );
        XSTestAssertTrue( SRP::BigNum( { 0xFF, 0x00 }, SRP::BigNum::Endianness::LittleEndian ) == 0x00FF );
    }
}

XSTest( BigNum, CTOR_Int64 )
{
    XSTestAssertTrue( SRP::BigNum( 0 )         == 0 );
    XSTestAssertTrue( SRP::BigNum( 1 )         == 1 );
    XSTestAssertTrue( SRP::BigNum( -1 )        == -1 );
    XSTestAssertTrue( SRP::BigNum( INT64_MAX ) == INT64_MAX );
    XSTestAssertTrue( SRP::BigNum( INT64_MIN ) == INT64_MIN );
}

XSTest( BigNum, CCTOR )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( n1 );
    
    XSTestAssertTrue( n1 == 42 );
    XSTestAssertTrue( n2 == 42 );
}

XSTest( BigNum, MCTOR )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( std::move( n1 ) );
    
    XSTestAssertTrue( n2 == 42 );
}

XSTest( BigNum, OperatorAssign )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( 0 );
    
    XSTestAssertTrue( n1 == 42 );
    XSTestAssertTrue( n2 == 0 );
    
    n2 = n1;
    
    XSTestAssertTrue( n1 == 42 );
    XSTestAssertTrue( n2 == 42 );
}

XSTest( BigNum, OperatorEqual )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( 42 );
    SRP::BigNum n3( 0 );
    
    XSTestAssertTrue( n1 == n1 );
    XSTestAssertTrue( n2 == n2 );
    XSTestAssertTrue( n3 == n3 );
    
    XSTestAssertTrue( n1 == n2 );
    XSTestAssertTrue( n2 == n1 );
    
    XSTestAssertFalse( n1 == n3 );
    XSTestAssertFalse( n2 == n3 );
    XSTestAssertFalse( n3 == n1 );
    XSTestAssertFalse( n3 == n2 );
}

XSTest( BigNum, OperatorEqual_Int64 )
{
    SRP::BigNum n1( 0 );
    SRP::BigNum n2( 1 );
    SRP::BigNum n3( -1 );
    SRP::BigNum n4( INT_MAX );
    SRP::BigNum n5( INT_MIN );
    
    XSTestAssertTrue(  n1 == 0 );
    XSTestAssertFalse( n1 == 1 );
    XSTestAssertTrue(  n2 == 1 );
    XSTestAssertFalse( n2 == 0 );
    XSTestAssertTrue(  n3 == -1 );
    XSTestAssertFalse( n3 == 0 );
    XSTestAssertTrue(  n4 == INT_MAX );
    XSTestAssertFalse( n4 == 0 );
    XSTestAssertTrue(  n5 == INT_MIN );
    XSTestAssertFalse( n5 == 0 );
}

XSTest( BigNum, OperatorEqual_String )
{
    XSTestAssertFalse( SRP::BigNum( 42 ) == "" );
    XSTestAssertFalse( SRP::BigNum( 0 )  == "" );
    XSTestAssertFalse( SRP::BigNum()     == "" );
    
    XSTestAssertTrue( SRP::BigNum( 42 )      == "42" );
    XSTestAssertTrue( SRP::BigNum( -42 )     == "-42" );
    XSTestAssertTrue( SRP::BigNum( 0x42 )    == "0x42" );
    XSTestAssertTrue( SRP::BigNum( -0x42 )   == "-0x42" );
    XSTestAssertTrue( SRP::BigNum( 0x42 )    == "0X42" );
    XSTestAssertTrue( SRP::BigNum( -0x42 )   == "-0X42" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )  == "0X42FF" );
    XSTestAssertTrue( SRP::BigNum( -0x42FF ) == "-0X42FF" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )  == "0x42FF" );
    XSTestAssertTrue( SRP::BigNum( -0x42FF ) == "-0x42FF" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )  == "0x42ff" );
    XSTestAssertTrue( SRP::BigNum( -0x42FF ) == "-0x42ff" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )  == "0X42ff" );
    XSTestAssertTrue( SRP::BigNum( -0x42FF ) == "-0X42ff" );
}

XSTest( BigNum, OperatorNotEqual )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( 42 );
    SRP::BigNum n3( 0 );
    
    XSTestAssertFalse( n1 != n1 );
    XSTestAssertFalse( n2 != n2 );
    XSTestAssertFalse( n3 != n3 );
    
    XSTestAssertFalse( n1 != n2 );
    XSTestAssertFalse( n2 != n1 );
    
    XSTestAssertTrue( n1 != n3 );
    XSTestAssertTrue( n2 != n3 );
    XSTestAssertTrue( n3 != n1 );
    XSTestAssertTrue( n3 != n2 );
}

XSTest( BigNum, OperatorNotEqual_Int64 )
{
    SRP::BigNum n1( 0 );
    SRP::BigNum n2( 1 );
    SRP::BigNum n3( -1 );
    SRP::BigNum n4( INT_MAX );
    SRP::BigNum n5( INT_MIN );
    
    XSTestAssertFalse( n1 != 0 );
    XSTestAssertTrue(  n1 != 1 );
    XSTestAssertFalse( n2 != 1 );
    XSTestAssertTrue(  n2 != 0 );
    XSTestAssertFalse( n3 != -1 );
    XSTestAssertTrue(  n3 != 0 );
    XSTestAssertFalse( n4 != INT_MAX );
    XSTestAssertTrue(  n4 != 0 );
    XSTestAssertFalse( n5 != INT_MIN );
    XSTestAssertTrue(  n5 != 0 );
}

XSTest( BigNum, OperatorNotEqual_String )
{
    XSTestAssertTrue( SRP::BigNum( 42 ) != "" );
    XSTestAssertTrue( SRP::BigNum( 0 )  != "" );
    XSTestAssertTrue( SRP::BigNum()     != "" );
    
    XSTestAssertFalse( SRP::BigNum( 42 )      != "42" );
    XSTestAssertFalse( SRP::BigNum( -42 )     != "-42" );
    XSTestAssertFalse( SRP::BigNum( 0x42 )    != "0x42" );
    XSTestAssertFalse( SRP::BigNum( -0x42 )   != "-0x42" );
    XSTestAssertFalse( SRP::BigNum( 0x42 )    != "0X42" );
    XSTestAssertFalse( SRP::BigNum( -0x42 )   != "-0X42" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )  != "0X42FF" );
    XSTestAssertFalse( SRP::BigNum( -0x42FF ) != "-0X42FF" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )  != "0x42FF" );
    XSTestAssertFalse( SRP::BigNum( -0x42FF ) != "-0x42FF" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )  != "0x42ff" );
    XSTestAssertFalse( SRP::BigNum( -0x42FF ) != "-0x42ff" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )  != "0X42ff" );
    XSTestAssertFalse( SRP::BigNum( -0x42FF ) != "-0X42ff" );
}

XSTest( BigNum, OperatorGreatorOrEqual )
{
    XSTestAssertTrue(  SRP::BigNum( 42 ) >= SRP::BigNum( 42 ) );
    XSTestAssertTrue(  SRP::BigNum( 43 ) >= SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( 42 ) >= SRP::BigNum( 43 ) );
    
    XSTestAssertTrue( SRP::BigNum( 42 ) >= SRP::BigNum( -42 ) );
    XSTestAssertTrue( SRP::BigNum( 43 ) >= SRP::BigNum( -42 ) );
    XSTestAssertTrue( SRP::BigNum( 42 ) >= SRP::BigNum( -43 ) );
    
    XSTestAssertFalse( SRP::BigNum( -42 ) >= SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( -43 ) >= SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( -42 ) >= SRP::BigNum( 43 ) );
}

XSTest( BigNum, OperatorLessOrEqual )
{
    XSTestAssertTrue(  SRP::BigNum( 42 ) <= SRP::BigNum( 42 ) );
    XSTestAssertTrue(  SRP::BigNum( 41 ) <= SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( 42 ) <= SRP::BigNum( 41 ) );
    
    XSTestAssertFalse( SRP::BigNum( 42 ) <= SRP::BigNum( -42 ) );
    XSTestAssertFalse( SRP::BigNum( 41 ) <= SRP::BigNum( -42 ) );
    XSTestAssertFalse( SRP::BigNum( 42 ) <= SRP::BigNum( -41 ) );
    
    XSTestAssertTrue( SRP::BigNum( -42 ) <= SRP::BigNum( 42 ) );
    XSTestAssertTrue( SRP::BigNum( -41 ) <= SRP::BigNum( 42 ) );
    XSTestAssertTrue( SRP::BigNum( -42 ) <= SRP::BigNum( 41 ) );
}

XSTest( BigNum, OperatorGreater )
{
    XSTestAssertFalse( SRP::BigNum( 42 ) > SRP::BigNum( 42 ) );
    XSTestAssertTrue(  SRP::BigNum( 43 ) > SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( 42 ) > SRP::BigNum( 43 ) );
    
    XSTestAssertTrue( SRP::BigNum( 42 ) > SRP::BigNum( -42 ) );
    XSTestAssertTrue( SRP::BigNum( 43 ) > SRP::BigNum( -42 ) );
    XSTestAssertTrue( SRP::BigNum( 42 ) > SRP::BigNum( -43 ) );
    
    XSTestAssertFalse( SRP::BigNum( -42 ) > SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( -43 ) > SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( -42 ) > SRP::BigNum( 43 ) );
}

XSTest( BigNum, OperatorLess )
{
    XSTestAssertFalse( SRP::BigNum( 42 ) < SRP::BigNum( 42 ) );
    XSTestAssertTrue(  SRP::BigNum( 41 ) < SRP::BigNum( 42 ) );
    XSTestAssertFalse( SRP::BigNum( 42 ) < SRP::BigNum( 41 ) );
    
    XSTestAssertFalse( SRP::BigNum( 42 ) < SRP::BigNum( -42 ) );
    XSTestAssertFalse( SRP::BigNum( 41 ) < SRP::BigNum( -42 ) );
    XSTestAssertFalse( SRP::BigNum( 42 ) < SRP::BigNum( -41 ) );
    
    XSTestAssertTrue( SRP::BigNum( -42 ) < SRP::BigNum( 42 ) );
    XSTestAssertTrue( SRP::BigNum( -41 ) < SRP::BigNum( 42 ) );
    XSTestAssertTrue( SRP::BigNum( -42 ) < SRP::BigNum( 41 ) );
}

XSTest( BigNum, OperatorPrefixIncrement )
{
    for( int64_t i = INT8_MIN; i <= INT8_MAX; i++ )
    {
        SRP::BigNum n( i );
        
        XSTestAssertTrue( ++n == i + 1 );
        XSTestAssertTrue( n   == i + 1 );
    }
}

XSTest( BigNum, OperatorPrefixDecrement )
{
    for( int64_t i = INT8_MIN; i <= INT8_MAX; i++ )
    {
        SRP::BigNum n( i );
        
        XSTestAssertTrue( --n == i - 1 );
        XSTestAssertTrue( n   == i - 1 );
    }
}

XSTest( BigNum, OperatorPostfixIncrement )
{
    for( int64_t i = INT8_MIN; i <= INT8_MAX; i++ )
    {
        SRP::BigNum n( i );
        
        XSTestAssertTrue( n++ == i );
        XSTestAssertTrue( n   == i + 1 );
    }
}

XSTest( BigNum, OperatorPostfixDecrement )
{
    for( int64_t i = INT8_MIN; i <= INT8_MAX; i++ )
    {
        SRP::BigNum n( i );
        
        XSTestAssertTrue( n-- == i );
        XSTestAssertTrue( n   == i - 1 );
    }
}

XSTest( BigNum, OperatorPlusEqual )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            
            n1 += n2;
            
            XSTestAssertTrue( n1 == a + b );
            XSTestAssertTrue( n2 == b );
        }
    }
}

XSTest( BigNum, OperatorMinusEqual )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
            {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            
            n1 -= n2;
            
            XSTestAssertTrue( n1 == a - b );
            XSTestAssertTrue( n2 == b );
        }
    }
}

XSTest( BigNum, OperatorMultiplyEqual )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            
            n1 *= n2;
            
            XSTestAssertTrue( n1 == a * b );
            XSTestAssertTrue( n2 == b );
        }
    }
}

XSTest( BigNum, OperatorDivideEqual )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            
            n1 /= n2;
            
            if( b == 0 )
            {
                XSTestAssertTrue( n1 == a );
            }
            else
            {
                XSTestAssertTrue( n1 == a / b );
            }
            
            XSTestAssertTrue( n2 == b );
        }
    }
}

XSTest( BigNum, OperatorModEqual )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            
            n1 %= n2;
            
            if( b == 0 )
            {
                XSTestAssertTrue( n1 == a );
            }
            else
            {
                XSTestAssertTrue( n1 == a % b );
            }
            
            XSTestAssertTrue( n2 == b );
        }
    }
}

XSTest( BigNum, OperatorExpEqual )
{
    for( int64_t a = -10; a <= 10; a++ )
    {
        for( int64_t b = -10; b <= 10; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            double      r = pow( static_cast< double >( a ), static_cast< double >( std::abs( b ) ) );
            
            n1 ^= n2;
            
            XSTestAssertTrue( n1 == static_cast< int64_t >( r ) );
            XSTestAssertTrue( n2 == b );
        }
    }
}

XSTest( BigNum, OperatorPlus )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            SRP::BigNum n3( n1 + n2 );
            
            XSTestAssertTrue( n1 == a );
            XSTestAssertTrue( n2 == b );
            XSTestAssertTrue( n3 == a + b );
        }
    }
}

XSTest( BigNum, OperatorMinus )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            SRP::BigNum n3( n1 - n2 );
            
            XSTestAssertTrue( n1 == a );
            XSTestAssertTrue( n2 == b );
            XSTestAssertTrue( n3 == a - b );
        }
    }
}

XSTest( BigNum, OperatorMultiply )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            SRP::BigNum n3( n1 * n2 );
            
            XSTestAssertTrue( n1 == a );
            XSTestAssertTrue( n2 == b );
            XSTestAssertTrue( n3 == a * b );
        }
    }
}

XSTest( BigNum, OperatorDivide )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            SRP::BigNum n3( n1 / n2 );
            
            XSTestAssertTrue( n1 == a );
            XSTestAssertTrue( n2 == b );
            
            if( b == 0 )
            {
                XSTestAssertTrue( n3 == a );
            }
            else
            {
                XSTestAssertTrue( n3 == a / b );
            }
        }
    }
}

XSTest( BigNum, OperatorMod )
{
    for( int64_t a = INT8_MIN; a <= INT8_MAX; a++ )
    {
        for( int64_t b = INT8_MIN; b <= INT8_MAX; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            SRP::BigNum n3( n1 % n2 );
            
            XSTestAssertTrue( n1 == a );
            XSTestAssertTrue( n2 == b );
            
            if( b == 0 )
            {
                XSTestAssertTrue( n3 == a );
            }
            else
            {
                XSTestAssertTrue( n3 == a % b );
            }
        }
    }
}

XSTest( BigNum, OperatorExp )
{
    for( int64_t a = -10; a <= 10; a++ )
    {
        for( int64_t b = -10; b <= 10; b++ )
        {
            SRP::BigNum n1( a );
            SRP::BigNum n2( b );
            SRP::BigNum n3( n1 ^ n2 );
            double      r = pow( static_cast< double >( a ), static_cast< double >( std::abs( b ) ) );
            
            XSTestAssertTrue( n1 == a );
            XSTestAssertTrue( n2 == b );
            XSTestAssertTrue( n3 == static_cast< int64_t >( r ) );
        }
    }
}

XSTest( BigNum, ToString )
{
    XSTestAssertTrue( SRP::BigNum( 42 ).toString()  == "42" );
    XSTestAssertTrue( SRP::BigNum( -42 ).toString() == "-42" );
    
    XSTestAssertTrue( SRP::BigNum( 42 ).toString( SRP::BigNum::StringFormat::Auto )  == "42" );
    XSTestAssertTrue( SRP::BigNum( -42 ).toString( SRP::BigNum::StringFormat::Auto ) == "-42" );
    
    XSTestAssertTrue( SRP::BigNum( 42 ).toString( SRP::BigNum::StringFormat::Decimal )  == "42" );
    XSTestAssertTrue( SRP::BigNum( -42 ).toString( SRP::BigNum::StringFormat::Decimal ) == "-42" );
    
    XSTestAssertTrue( SRP::BigNum( 0x42 ).toString( SRP::BigNum::StringFormat::Hexadecimal )  == "0x42" );
    XSTestAssertTrue( SRP::BigNum( -0x42 ).toString( SRP::BigNum::StringFormat::Hexadecimal ) == "-0x42" );
    
    XSTestAssertTrue( SRP::BigNum( 0xFF ).toString( SRP::BigNum::StringFormat::Hexadecimal )  == "0xff" );
    XSTestAssertTrue( SRP::BigNum( -0xFF ).toString( SRP::BigNum::StringFormat::Hexadecimal ) == "-0xff" );
}

XSTest( BigNum, GetBytes_Auto )
{
    SRP::BigNum n1( { 0x42, 0xFF }, SRP::BigNum::Endianness::BigEndian );
    
    if( SRP::Platform::isBigEndian() )
    {
        XSTestAssertTrue( n1.getBytes( SRP::BigNum::Endianness::Auto ) == std::vector< uint8_t >( { 0x42, 0xFF } ) );
    }
    else
    {
        XSTestAssertTrue( n1.getBytes( SRP::BigNum::Endianness::Auto ) == std::vector< uint8_t >( { 0xFF, 0x42 } ) );
    }
}

XSTest( BigNum, GetBytes_BigEndian )
{
    SRP::BigNum n1( { 0x42, 0xFF }, SRP::BigNum::Endianness::BigEndian );
    
    XSTestAssertTrue( n1.getBytes( SRP::BigNum::Endianness::BigEndian ) == std::vector< uint8_t >( { 0x42, 0xFF } ) );
}

XSTest( BigNum, GetBytes_LittleEndian )
{
    SRP::BigNum n1( { 0x42, 0xFF }, SRP::BigNum::Endianness::BigEndian );
    
    XSTestAssertTrue( n1.getBytes( SRP::BigNum::Endianness::LittleEndian ) == std::vector< uint8_t >( { 0xFF, 0x42 } ) );
}

XSTest( BigNum, Negative )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( n1.negative() );
    SRP::BigNum n3( n1.negative().negative() );
    
    XSTestAssertFalse( n1.isNegative() );
    XSTestAssertTrue(  n2.isNegative() );
    XSTestAssertTrue(  n3.isNegative() );
    
    XSTestAssertTrue( n1 == 42 );
    XSTestAssertTrue( n2 == -42 );
    XSTestAssertTrue( n3 == -42 );
}

XSTest( BigNum, Positive )
{
    SRP::BigNum n1( SRP::BigNum( -42 ) );
    SRP::BigNum n2( n1.positive() );
    SRP::BigNum n3( n1.positive().positive() );
    
    XSTestAssertTrue(  n1.isNegative() );
    XSTestAssertFalse( n2.isNegative() );
    XSTestAssertFalse( n3.isNegative() );
    
    XSTestAssertTrue( n1 == -42 );
    XSTestAssertTrue( n2 == 42 );
    XSTestAssertTrue( n3 == 42 );
}

XSTest( BigNum, IsNegative )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( n1.negative() );
    SRP::BigNum n3( n1.negative().negative() );
    
    XSTestAssertFalse( n1.isNegative() );
    XSTestAssertTrue(  n2.isNegative() );
    XSTestAssertTrue(  n3.isNegative() );
}

XSTest( BigNum, IsPositive )
{
    SRP::BigNum n1( -42 );
    SRP::BigNum n2( n1.positive() );
    SRP::BigNum n3( n1.positive().positive() );
    
    XSTestAssertFalse( n1.isPositive() );
    XSTestAssertTrue(  n2.isPositive() );
    XSTestAssertTrue(  n3.isPositive() );
}

XSTest( BigNum, IsOdd )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( 43 );
    
    XSTestAssertFalse( n1.isOdd() );
    XSTestAssertTrue(  n2.isOdd() );
}

XSTest( BigNum, IsEven )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( 43 );
    
    XSTestAssertTrue(  n1.isEven() );
    XSTestAssertFalse( n2.isEven() );
}

XSTest( BigNum, Swap )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( 0 );
    
    XSTestAssertTrue( n1 == 42 );
    XSTestAssertTrue( n2 == 0 );
    
    swap( n1, n2 );
    
    XSTestAssertTrue( n1 == 0 );
    XSTestAssertTrue( n2 == 42 );
}
