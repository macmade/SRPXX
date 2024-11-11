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

### Usage

```cpp

/*******************************************************************************
 * 1 - Registration
 ******************************************************************************/

{
    // Create a SRP client for an identity, with a given hash algorithm and group type
    SRP::Client client( "milford@cubicle.org", SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048 );
    
    // Generate a random salt
    std::vector< uint8_t > salt( SRP::Random::bytes( 16 ) );
    
    // Set the salt and password
    client.setPassword( "1234" );
    client.setSalt( salt );
    
    // Generate the verifier
    std::vector< uint8_t > verifier = client.v().bytes( SRP::BigNum::Endianness::BigEndian );
    
    // Send the salt and verifier to the server
    // ...
}

/*******************************************************************************
 * 2 - Authentication
 ******************************************************************************/

{
    // TODO: ...
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
