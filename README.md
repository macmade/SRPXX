SRPXX
=====

[![Build Status](https://img.shields.io/github/actions/workflow/status/macmade/SRPXX/ci-mac.yaml?label=macOS&logo=apple)](https://github.com/macmade/SRPXX/actions/workflows/ci-mac.yaml)
[![Issues](http://img.shields.io/github/issues/macmade/SRPXX.svg?logo=github)](https://github.com/macmade/SRPXX/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?logo=git)
![License](https://img.shields.io/badge/license-mit-brightgreen.svg?logo=open-source-initiative)  
[![Contact](https://img.shields.io/badge/follow-@macmade-blue.svg?logo=twitter&style=social)](https://twitter.com/macmade)
[![Sponsor](https://img.shields.io/badge/sponsor-macmade-pink.svg?logo=github-sponsors&style=social)](https://github.com/sponsors/macmade)

### About

C++ implementation of the Secure Remote Password protocol (SRP) - RFC 5054.

**Supported Hash Algorithms:**

 - SHA-1
 - SHA-224
 - SHA-256
 - SHA-384
 - SHA-512

**Supported Group Parameters:**

 - 1024 bits
 - 1536 bits
 - 2048 bits
 - 3072 bits
 - 4096 bits
 - 6144 bits
 - 8192 bits

### Example Usage

```cpp

#include <SRPXX.hpp>

// Server storage
std::vector< uint8_t > salt;
std::vector< uint8_t > verifier;

/* Registration */
{
    // Create a SRP client for an identity, with a given hash algorithm and group type
    SRP::Client client( "milford@cubicle.org", SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048 );
    
    // User registers with a password
    client.setPassword( "1234" );
    
    // Client generates a salt
    client.setSalt( SRP::Random::bytes( 16 ) );
    
    // Client -> Server:
    // Server receives salt and verifier from Client
    // Client can then discard them
    salt     = client.salt();
    verifier = client.v().bytes( SRP::BigNum::Endianness::BigEndian );
}

/* Authentication */
{
    SRP::Client client( "milford@cubicle.org", SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048 );
    SRP::Server server( "milford@cubicle.org", SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048 );
    
    // Server has stored salt and verifier during registration (see above)
    server.setSalt( salt );
    server.setV( SRP::BigNum( verifier, SRP::BigNum::Endianness::BigEndian ) );
    
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
    AssertFalse( client.M1() == server.M1() );
    AssertFalse( client.M2() == server.M2() );
    
    // User inputs the correct password
    client.setPassword( "1234" );
    
    // With the correct password, Client and Server will have matching M1 and M2, meaning the authentication was successful
    AssertTrue( client.M1() == server.M1() );
    AssertTrue( client.M2() == server.M2() );
}

```

Requirements
------------

This project requires OpenSSL.  
A pre-built version of BoringSSL is provided for macOS and Windows in the `Submodules/BoringSSL/lib` directory.

Debug Tool
----------

A debug CLI tool is provided in the `SRPXX-Debug` directory:

```
Usage: srp <identity> <password> <hash algorithm> <group parameter>

    - Supported hash algorithms:  sha1 sha224 sha256 sha384 sha512
    - Supported group parameters: 1024 1536 2048 3072 4096 6144 8192
```

When invoked, it will output test data representing all values used during the SRP session, similar to files in the `SRPXX-Tests/Constants` directory:

```cpp
SRP::HashAlgorithm::SHA1,
SRP::Base::GroupType::NG1024,
"milford@cubicle.org",
"1234",
{
    /* Salt */
    0xC8, 0x2B, 0x40, 0xC5, 0xB9, 0x6A, 0x38, 0x2C, 0x84, 0x0D, 0xA8, 0xD2, 0x04, 0x83, 0x8A, 0xAB, ...
},
{
    /* Verifier */
    0xAD, 0x4F, 0xAB, 0x4A, 0x68, 0x89, 0x9A, 0x18, 0x6C, 0x38, 0x1B, 0xC4, 0x20, 0x55, 0x02, 0xB3, ...
},
{
    /* a */
    0x43, 0xC7, 0xA0, 0xDD, 0x9A, 0xE4, 0x2B, 0x34, 0x52, 0x0D, 0xDC, 0xCE, 0xE8, 0x68, 0xB6, 0x8E, ...
},
{
    /* A */
    0x18, 0x25, 0x6F, 0xED, 0x07, 0xD6, 0xA1, 0xB2, 0x91, 0x58, 0xDB, 0xFC, 0x49, 0x2F, 0x23, 0xCC, ...
},
{
    /* b */
    0xD7, 0x17, 0x11, 0x2D, 0x6F, 0x02, 0xCD, 0xB4, 0x92, 0x0D, 0xBD, 0x42, 0x94, 0x15, 0xCA, 0xB0, ...
},
{
    /* B */
    0xEE, 0x7E, 0xE2, 0x67, 0x18, 0x1D, 0x3A, 0x0E, 0x05, 0x83, 0x86, 0x27, 0x78, 0x30, 0x18, 0xE2, ...
},
{
    /* u */
    0xA3, 0x5E, 0x6C, 0xF9, 0x44, 0xC2, 0x93, 0xC9, 0x2D, 0x70, 0x51, 0x77, 0xD9, 0xCF, 0x54, 0xD7, ...
},
{
    /* k */
    0x75, 0x56, 0xAA, 0x04, 0x5A, 0xEF, 0x2C, 0xDD, 0x07, 0xAB, 0xAF, 0x0F, 0x66, 0x5C, 0x3E, 0x81, ...
},
{
    /* S */
    0xEA, 0xD5, 0x20, 0xA6, 0xD1, 0x9C, 0x34, 0xEB, 0x94, 0x3E, 0xAA, 0x5E, 0x03, 0x51, 0xA7, 0x48, ...
},
{
    /* x */
    0xBC, 0x07, 0xB5, 0x14, 0xB8, 0xF9, 0x86, 0xC2, 0xA5, 0x19, 0xC2, 0x80, 0x99, 0x81, 0xB6, 0x90, ...
},
{
    /* K */
    0x28, 0xE9, 0x54, 0xDC, 0xDC, 0x50, 0x6A, 0xBA, 0x2D, 0x64, 0xEF, 0xB2, 0x04, 0xB0, 0xCC, 0x5D, ...
},
{
    /* M1 */
    0x5D, 0x09, 0x99, 0x64, 0x42, 0xF3, 0x27, 0x2B, 0xA1, 0x48, 0x82, 0x0C, 0xE7, 0x87, 0x8C, 0x36, ...
},
{
    /* M2 */
    0xDB, 0xE4, 0xF8, 0x2E, 0xE7, 0x06, 0x28, 0x5D, 0x60, 0x0C, 0x66, 0xB1, 0xA7, 0xD0, 0xB5, 0x53, ...
}
```


License
-------

Project is released under the terms of the MIT License.

Repository Infos
----------------

    Owner:          Jean-David Gadina - XS-Labs
    Web:            www.xs-labs.com
    Blog:           www.noxeos.com
    Twitter:        @macmade
    GitHub:         github.com/macmade
    LinkedIn:       ch.linkedin.com/in/macmade/
    StackOverflow:  stackoverflow.com/users/182676/macmade
