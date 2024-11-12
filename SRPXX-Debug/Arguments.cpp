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

#include "Arguments.hpp"
#include <stdexcept>

class Arguments::IMPL
{
    public:
        
        IMPL( int argc, const char * argv[] );
        IMPL( const IMPL & o );
        ~IMPL();
        
        std::string          _identity;
        std::string          _password;
        SRP::HashAlgorithm   _hashAlgorithm;
        SRP::Base::GroupType _groupType;
};

Arguments::Arguments( int argc, const char * argv[] ):
    impl( std::make_unique< IMPL >( argc, argv ) )
{}

Arguments::Arguments( const Arguments & o ):
    impl( std::make_unique< IMPL >( *( o.impl ) ) )
{}

Arguments::~Arguments()
{}

Arguments & Arguments::operator =( Arguments o )
{
    swap( *( this ), o );
    
    return *( this );
}

void swap( Arguments & o1, Arguments & o2 )
{
    using std::swap;
    
    swap( o1.impl, o2.impl );
}

std::string Arguments::identity() const
{
    return this->impl->_identity;
}

std::string Arguments::password() const
{
    return this->impl->_password;
}

SRP::HashAlgorithm Arguments::hashAlgorithm() const
{
    return this->impl->_hashAlgorithm;
}

SRP::Base::GroupType Arguments::groupType() const
{
    return this->impl->_groupType;
}

Arguments::IMPL::IMPL( int argc, const char * argv[] )
{
    if( argc != 5 )
    {
        throw std::runtime_error
        (
            "Usage: srp <identity> <password> <hash algorithm> <group parameter>\n"
            "\n"
            "    - Supported hash algorithms:  sha1 sha224 sha256 sha384 sha512\n"
            "    - Supported group parameters: 1024 1536 2048 3072 4096 6144 8192"
        );
    }
    
    this->_identity = argv[ 1 ];
    this->_password = argv[ 2 ];
    
    std::string hash  = argv[ 3 ];
    std::string group = argv[ 4 ];
    
         if( hash == "sha1"   ) { this->_hashAlgorithm = SRP::HashAlgorithm::SHA1; }
    else if( hash == "sha224" ) { this->_hashAlgorithm = SRP::HashAlgorithm::SHA224; }
    else if( hash == "sha256" ) { this->_hashAlgorithm = SRP::HashAlgorithm::SHA256; }
    else if( hash == "sha384" ) { this->_hashAlgorithm = SRP::HashAlgorithm::SHA384; }
    else if( hash == "sha512" ) { this->_hashAlgorithm = SRP::HashAlgorithm::SHA512; }
    else
    {
        throw std::runtime_error( "Unsupported hash algorithm: " + hash );
    }
    
         if( group == "1024" ) { this->_groupType = SRP::Base::GroupType::NG1024; }
    else if( group == "1536" ) { this->_groupType = SRP::Base::GroupType::NG1536; }
    else if( group == "2048" ) { this->_groupType = SRP::Base::GroupType::NG2048; }
    else if( group == "3072" ) { this->_groupType = SRP::Base::GroupType::NG3072; }
    else if( group == "4096" ) { this->_groupType = SRP::Base::GroupType::NG4096; }
    else if( group == "6144" ) { this->_groupType = SRP::Base::GroupType::NG6144; }
    else if( group == "8192" ) { this->_groupType = SRP::Base::GroupType::NG8192; }
    else
    {
        throw std::runtime_error( "Unsupported group parameter: " + group );
    }
}

Arguments::IMPL::IMPL( const IMPL & o ):
    _identity(      o._identity ),
    _password(      o._password ),
    _hashAlgorithm( o._hashAlgorithm ),
    _groupType(     o._groupType )
{}

Arguments::IMPL::~IMPL()
{}
