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
        
        XSTestAssertTrue(  n1.has_value() );
        XSTestAssertTrue(  n2.has_value() );
        XSTestAssertTrue(  n3.has_value() );
        XSTestAssertFalse( n4.has_value() );
        XSTestAssertTrue(  n5.has_value() );
        XSTestAssertFalse( n6.has_value() );
        
        XSTestAssertTrue( n1 == 42 );
        XSTestAssertTrue( n2 == SRP::BigNum( 1 ).negative() );
        XSTestAssertTrue( n3 == 42 );
        XSTestAssertTrue( n5 == 42 );
    }
    
    {
        auto n1 = SRP::BigNum::fromString( "0x42",     SRP::BigNum::StringFormat::Auto );
        auto n2 = SRP::BigNum::fromString( "-0x1",     SRP::BigNum::StringFormat::Auto );
        auto n3 = SRP::BigNum::fromString( "0x42FF",   SRP::BigNum::StringFormat::Auto );
        auto n4 = SRP::BigNum::fromString( "0xFF42",   SRP::BigNum::StringFormat::Auto );
        auto n5 = SRP::BigNum::fromString( "0x42FFZZ", SRP::BigNum::StringFormat::Auto );
        auto n6 = SRP::BigNum::fromString( "0xZZFF42", SRP::BigNum::StringFormat::Auto );
        
        XSTestAssertTrue(  n1.has_value() );
        XSTestAssertTrue(  n2.has_value() );
        XSTestAssertTrue(  n3.has_value() );
        XSTestAssertTrue(  n4.has_value() );
        XSTestAssertTrue(  n5.has_value() );
        XSTestAssertFalse( n6.has_value() );
        
        XSTestAssertTrue( n1 == 0x42 );
        XSTestAssertTrue( n2 == SRP::BigNum( 0x1 ).negative() );
        XSTestAssertTrue( n3 == 0x42FF );
        XSTestAssertTrue( n4 == 0xFF42 );
        XSTestAssertTrue( n5 == 0x42FF );
    }
    
    {
        auto n1 = SRP::BigNum::fromString( "0X42",     SRP::BigNum::StringFormat::Auto );
        auto n2 = SRP::BigNum::fromString( "-0X1",     SRP::BigNum::StringFormat::Auto );
        auto n3 = SRP::BigNum::fromString( "0X42FF",   SRP::BigNum::StringFormat::Auto );
        auto n4 = SRP::BigNum::fromString( "0XFF42",   SRP::BigNum::StringFormat::Auto );
        auto n5 = SRP::BigNum::fromString( "0X42FFZZ", SRP::BigNum::StringFormat::Auto );
        auto n6 = SRP::BigNum::fromString( "0XZZFF42", SRP::BigNum::StringFormat::Auto );
        
        XSTestAssertTrue(  n1.has_value() );
        XSTestAssertTrue(  n2.has_value() );
        XSTestAssertTrue(  n3.has_value() );
        XSTestAssertTrue(  n4.has_value() );
        XSTestAssertTrue(  n5.has_value() );
        XSTestAssertFalse( n6.has_value() );
        
        XSTestAssertTrue( n1 == 0x42 );
        XSTestAssertTrue( n2 == SRP::BigNum( 0x1 ).negative() );
        XSTestAssertTrue( n3 == 0x42FF );
        XSTestAssertTrue( n4 == 0xFF42 );
        XSTestAssertTrue( n5 == 0x42FF );
    }
}

XSTest( BigNum, FromString_Decimal )
{
    auto n1 = SRP::BigNum::fromString( "42",   SRP::BigNum::StringFormat::Decimal );
    auto n2 = SRP::BigNum::fromString( "-1",   SRP::BigNum::StringFormat::Decimal );
    auto n3 = SRP::BigNum::fromString( "42FF", SRP::BigNum::StringFormat::Decimal );
    auto n4 = SRP::BigNum::fromString( "FF42", SRP::BigNum::StringFormat::Decimal );
    
    XSTestAssertTrue(  n1.has_value() );
    XSTestAssertTrue(  n2.has_value() );
    XSTestAssertTrue(  n3.has_value() );
    XSTestAssertFalse( n4.has_value() );
    
    XSTestAssertTrue( n1 == 42 );
    XSTestAssertTrue( n2 == SRP::BigNum( 1 ).negative() );
    XSTestAssertTrue( n3 == 42 );
}

XSTest( BigNum, FromString_Hexadecimal )
{
    auto n1 = SRP::BigNum::fromString( "42",     SRP::BigNum::StringFormat::Hexadecimal );
    auto n2 = SRP::BigNum::fromString( "-1",     SRP::BigNum::StringFormat::Hexadecimal );
    auto n3 = SRP::BigNum::fromString( "42FF",   SRP::BigNum::StringFormat::Hexadecimal );
    auto n4 = SRP::BigNum::fromString( "FF42",   SRP::BigNum::StringFormat::Hexadecimal );
    auto n5 = SRP::BigNum::fromString( "42FFZZ", SRP::BigNum::StringFormat::Hexadecimal );
    auto n6 = SRP::BigNum::fromString( "ZZFF42", SRP::BigNum::StringFormat::Hexadecimal );
    
    XSTestAssertTrue(  n1.has_value() );
    XSTestAssertTrue(  n2.has_value() );
    XSTestAssertTrue(  n3.has_value() );
    XSTestAssertTrue(  n4.has_value() );
    XSTestAssertTrue(  n5.has_value() );
    XSTestAssertFalse( n6.has_value() );
    
    XSTestAssertTrue( n1 == 0x42 );
    XSTestAssertTrue( n2 == SRP::BigNum( 0x1 ).negative() );
    XSTestAssertTrue( n3 == 0x42FF );
    XSTestAssertTrue( n4 == 0xFF42 );
    XSTestAssertTrue( n5 == 0x42FF );
}

XSTest( BigNum, CTOR )
{
    XSTestAssertTrue( SRP::BigNum() == 0 );
}

XSTest( BigNum, CTOR_UInt64 )
{
    XSTestAssertTrue( SRP::BigNum( 0 ) == 0 );
    XSTestAssertTrue( SRP::BigNum( 1 ) == 1 );
    XSTestAssertTrue( SRP::BigNum( INT64_MAX ) == INT64_MAX );
    XSTestAssertTrue( SRP::BigNum( static_cast< uint64_t >( -1 ) ) == static_cast< uint64_t >( -1 ) );
}

XSTest( BigNum, CCTOR )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( n1 );
    
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

XSTest( BigNum, OperatorAssign_UInt64 )
{
    SRP::BigNum n( 0 );
    
    XSTestAssertTrue( n == 0 );
    
    n = 42;
    
    XSTestAssertTrue( n == 42 );
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

XSTest( BigNum, OperatorEqual_UInt64 )
{
    SRP::BigNum n( 42 );
    
    XSTestAssertTrue(  n == 42 );
    XSTestAssertFalse( n == 0 );
}

XSTest( BigNum, OperatorEqual_String )
{
    XSTestAssertFalse( SRP::BigNum( 42 ) == "" );
    XSTestAssertFalse( SRP::BigNum( 0 )  == "" );
    XSTestAssertFalse( SRP::BigNum()     == "" );
    
    XSTestAssertTrue( SRP::BigNum( 42 )                == "42" );
    XSTestAssertTrue( SRP::BigNum( 42 ).negative()     == "-42" );
    XSTestAssertTrue( SRP::BigNum( 0x42 )              == "0x42" );
    XSTestAssertTrue( SRP::BigNum( 0x42 ).negative()   == "-0x42" );
    XSTestAssertTrue( SRP::BigNum( 0x42 )              == "0X42" );
    XSTestAssertTrue( SRP::BigNum( 0x42 ).negative()   == "-0X42" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )            == "0X42FF" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF ).negative() == "-0X42FF" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )            == "0x42FF" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF ).negative() == "-0x42FF" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )            == "0x42ff" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF ).negative() == "-0x42ff" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF )            == "0X42ff" );
    XSTestAssertTrue( SRP::BigNum( 0x42FF ).negative() == "-0X42ff" );
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

XSTest( BigNum, OperatorNotEqual_UInt64 )
{
    SRP::BigNum n( 42 );
    
    XSTestAssertFalse( n != 42 );
    XSTestAssertTrue(  n != 0 );
}

XSTest( BigNum, OperatorNotEqual_String )
{
    XSTestAssertTrue( SRP::BigNum( 42 ) != "" );
    XSTestAssertTrue( SRP::BigNum( 0 )  != "" );
    XSTestAssertTrue( SRP::BigNum()     != "" );
    
    XSTestAssertFalse( SRP::BigNum( 42 )                != "42" );
    XSTestAssertFalse( SRP::BigNum( 42 ).negative()     != "-42" );
    XSTestAssertFalse( SRP::BigNum( 0x42 )              != "0x42" );
    XSTestAssertFalse( SRP::BigNum( 0x42 ).negative()   != "-0x42" );
    XSTestAssertFalse( SRP::BigNum( 0x42 )              != "0X42" );
    XSTestAssertFalse( SRP::BigNum( 0x42 ).negative()   != "-0X42" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )            != "0X42FF" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF ).negative() != "-0X42FF" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )            != "0x42FF" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF ).negative() != "-0x42FF" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )            != "0x42ff" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF ).negative() != "-0x42ff" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF )            != "0X42ff" );
    XSTestAssertFalse( SRP::BigNum( 0x42FF ).negative() != "-0X42ff" );
}

XSTest( BigNum, ToString )
{
    XSTestAssertTrue( SRP::BigNum( 42 ).toString()            == "42" );
    XSTestAssertTrue( SRP::BigNum( 42 ).negative().toString() == "-42" );
    
    XSTestAssertTrue( SRP::BigNum( 42 ).toString( SRP::BigNum::StringFormat::Auto )            == "42" );
    XSTestAssertTrue( SRP::BigNum( 42 ).negative().toString( SRP::BigNum::StringFormat::Auto ) == "-42" );
    
    XSTestAssertTrue( SRP::BigNum( 42 ).toString( SRP::BigNum::StringFormat::Decimal )            == "42" );
    XSTestAssertTrue( SRP::BigNum( 42 ).negative().toString( SRP::BigNum::StringFormat::Decimal ) == "-42" );
    
    XSTestAssertTrue( SRP::BigNum( 0x42 ).toString( SRP::BigNum::StringFormat::Hexadecimal )            == "0x42" );
    XSTestAssertTrue( SRP::BigNum( 0x42 ).negative().toString( SRP::BigNum::StringFormat::Hexadecimal ) == "-0x42" );
    
    XSTestAssertTrue( SRP::BigNum( 0xFF ).toString( SRP::BigNum::StringFormat::Hexadecimal )            == "0xff" );
    XSTestAssertTrue( SRP::BigNum( 0xFF ).negative().toString( SRP::BigNum::StringFormat::Hexadecimal ) == "-0xff" );
}

XSTest( BigNum, Negative )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( n1.negative() );
    
    XSTestAssertFalse( n1.isNegative() );
    XSTestAssertTrue(  n2.isNegative() );
    
    XSTestAssertTrue( n1 == 42 );
    XSTestAssertTrue( n2.positive() == 42 );
}

XSTest( BigNum, Positive )
{
    SRP::BigNum n1( SRP::BigNum( 42 ).negative() );
    SRP::BigNum n2( n1.positive() );
    
    XSTestAssertTrue(  n1.isNegative() );
    XSTestAssertFalse( n2.isNegative() );
    
    XSTestAssertTrue( n1 == SRP::BigNum( 42 ).negative() );
    XSTestAssertTrue( n2 == 42 );
}

XSTest( BigNum, IsNegative )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( n1.negative() );
    
    XSTestAssertFalse( n1.isNegative() );
    XSTestAssertTrue(  n2.isNegative() );
}

XSTest( BigNum, IsPositive )
{
    SRP::BigNum n1( 42 );
    SRP::BigNum n2( n1.negative() );
    
    XSTestAssertTrue(  n1.isPositive() );
    XSTestAssertFalse( n2.isPositive() );
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
