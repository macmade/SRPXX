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
#include "TestVectors.hpp"

XSTest( Client, SetB )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setB( test.B() );
        XSTestAssertTrue( client->B() == test.B() );
    }
}

XSTest( Client, v )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        XSTestAssertTrue( client->v() == test.v() );
    }
}

XSTest( Client, a )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        XSTestAssertTrue( client->a() == test.a() );
    }
}

XSTest( Client, A )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        XSTestAssertTrue( client->A() == test.A() );
    }
}

XSTest( Client, u )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        client->setB( test.B() );
        
        XSTestAssertTrue( client->u() == test.u() );
    }
}

XSTest( Client, k )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        client->setB( test.B() );
        
        XSTestAssertTrue( client->k() == test.k() );
    }
}

XSTest( Client, S )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        client->setB( test.B() );
        
        XSTestAssertTrue( client->S() == test.S() );
    }
}

XSTest( Client, X )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        XSTestAssertTrue( client->x() == test.x() );
    }
}

XSTest( Client, K )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        client->setB( test.B() );
        
        XSTestAssertTrue( client->K() == test.K() );
    }
}

XSTest( Client, M1 )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        client->setB( test.B() );
        
        XSTestAssertTrue( client->M1() == test.M1() );
    }
}

XSTest( Client, M2 )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        client->setPassword( test.password() );
        client->setSalt( test.salt() );
        client->setB( test.B() );
        
        XSTestAssertTrue( client->M2() == test.M2() );
    }
}

XSTest( Client, SetOptions )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        XSTestAssertFalse( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
        client->setOptions( static_cast< uint64_t >( SRP::Client::Options::NoUsernameInX ) );
        XSTestAssertTrue( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
        client->setOptions( 0 );
        XSTestAssertFalse( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
    }
}
    
XSTest( Client, AddOption )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        XSTestAssertFalse( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
        client->addOption( SRP::Client::Options::NoUsernameInX );
        XSTestAssertTrue( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
    }
}
    
XSTest( Client, RemoveOption )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        XSTestAssertFalse( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
        client->addOption( SRP::Client::Options::NoUsernameInX );
        XSTestAssertTrue( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
        client->removeOption( SRP::Client::Options::NoUsernameInX );
        XSTestAssertFalse( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
    }
}
    
XSTest( Client, HasOption )
{
    for( const auto & test: TestVectors::all() )
    {
        auto client = test.makeClient();
        
        XSTestAssertFalse( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
        client->addOption( SRP::Client::Options::NoUsernameInX );
        XSTestAssertTrue( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
        client->removeOption( SRP::Client::Options::NoUsernameInX );
        XSTestAssertFalse( client->hasOption( SRP::Client::Options::NoUsernameInX ) );
    }
}
