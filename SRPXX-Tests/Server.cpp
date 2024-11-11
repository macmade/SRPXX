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
#include "Constants.hpp"

XSTest( Server, SetV )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        XSTestAssertTrue( server.v() == SRP::BigNum() );
        server.setV( SRP::BigNum( 42 ) );
        XSTestAssertTrue( server.v() == SRP::BigNum( 42 ) );
    }
}

XSTest( Server, SetA )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        XSTestAssertTrue( server.A() == SRP::BigNum() );
        server.setA( SRP::BigNum( 42 ) );
        XSTestAssertTrue( server.A() == SRP::BigNum( 42 ) );
    }
}

XSTest( Server, b )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.b() == constants.b() );
    }
}

XSTest( Server, B )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.B() == constants.B() );
    }
}

XSTest( Server, u )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.u() == constants.u() );
    }
}

XSTest( Server, k )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.k() == constants.k() );
    }
}

XSTest( Server, S )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.S() == constants.S() );
    }
}

XSTest( Server, K )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.K() == constants.K() );
    }
}

XSTest( Server, M1 )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.M1() == constants.M1() );
    }
}

XSTest( Server, M2 )
{
    for( const auto & constants: Constants::all() )
    {
        SRP::Server server = constants.makeServer();
        
        server.setV( constants.v() );
        server.setSalt( constants.salt() );
        server.setA( constants.A() );
        XSTestAssertTrue( server.M2() == constants.M2() );
    }
}
