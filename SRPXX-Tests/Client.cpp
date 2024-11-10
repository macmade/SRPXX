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

XSTest( Client, a )
{
    SRP::Client client = Constants::makeTestClient();
    
    XSTestAssertTrue( client.a() == Constants::a() );
}

XSTest( Client, A )
{
    SRP::Client client = Constants::makeTestClient();
    
    XSTestAssertTrue( client.A() == Constants::A() );
}

XSTest( Client, SetOptions )
{
    SRP::Client client = Constants::makeTestClient();
    
    XSTestAssertFalse( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
    client.setOptions( static_cast< uint64_t >( SRP::Client::Options::NoUsernameInX ) );
    XSTestAssertTrue( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
    client.setOptions( 0 );
    XSTestAssertFalse( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
}
    
XSTest( Client, AddOption )
{
    SRP::Client client = Constants::makeTestClient();
    
    XSTestAssertFalse( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
    client.addOption( SRP::Client::Options::NoUsernameInX );
    XSTestAssertTrue( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
}
    
XSTest( Client, RemoveOption )
{
    SRP::Client client = Constants::makeTestClient();
    
    XSTestAssertFalse( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
    client.addOption( SRP::Client::Options::NoUsernameInX );
    XSTestAssertTrue( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
    client.removeOption( SRP::Client::Options::NoUsernameInX );
    XSTestAssertFalse( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
}
    
XSTest( Client, HasOption )
{
    SRP::Client client = Constants::makeTestClient();
    
    XSTestAssertFalse( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
    client.addOption( SRP::Client::Options::NoUsernameInX );
    XSTestAssertTrue( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
    client.removeOption( SRP::Client::Options::NoUsernameInX );
    XSTestAssertFalse( client.hasOption( SRP::Client::Options::NoUsernameInX ) );
}
