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

XSTest( SRP, Complete )
{
    // Server storage
    std::vector< uint8_t > salt;
    SRP::BigNum            verifier;
    
    /* Registration */
    {
        SRP::Client client( "milford@cubicle.org", SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048 );
        
        // User registers with a password
        client.setPassword( "1234" );
        
        // Client generates a salt
        client.setSalt( SRP::Random::bytes( 16 ) );
        
        // Client -> Server:
        // Server receives salt and verifier from Client
        salt     = client.salt();
        verifier = client.v();
    }
    
    /* Authentication */
    {
        SRP::Client client( "milford@cubicle.org", SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048 );
        SRP::Server server( "milford@cubicle.org", SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048 );
        
        // Server has stored salt and verifier during authentication (see above)
        server.setSalt( salt );
        server.setV( verifier );
        
        // Client -> Server:
        // Server receives A from Client
        server.setA( client.A() );
        
        // Server -> Client:
        // Client receives B and salt from Server
        client.setB( server.B() );
        client.setSalt( server.salt() );
        
        // User inputs a wrong password
        client.setPassword( "4321" );
        
        // Client and Server will not have matching M1 and M2, meaning the authentication failed
        XSTestAssertFalse( client.M1() == server.M1() );
        XSTestAssertFalse( client.M2() == server.M2() );
        
        // User inputs the correct password
        client.setPassword( "1234" );
        
        // With the correct password, Client and Server will have matching M1 and M2, meaning the authentication was successful
        XSTestAssertTrue( client.M1() == server.M1() );
        XSTestAssertTrue( client.M2() == server.M2() );
    }
}
