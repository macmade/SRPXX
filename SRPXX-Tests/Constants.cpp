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

#include "Constants.hpp"
#include <algorithm>

class Constants::IMPL
{
    public:
        
        IMPL( SRP::HashAlgorithm hashAlgorithm, SRP::Base::GroupType groupType, std::string identity, std::string password, std::vector< uint8_t > salt, std::vector< uint8_t > v, std::vector< uint8_t > a, std::vector< uint8_t > A, std::vector< uint8_t > b, std::vector< uint8_t > B, std::vector< uint8_t > u, std::vector< uint8_t > k, std::vector< uint8_t > S, std::vector< uint8_t > x, std::vector< uint8_t > K, std::vector< uint8_t > M1, std::vector< uint8_t > M2 );
        IMPL( const IMPL & o );
        ~IMPL();
        
        SRP::HashAlgorithm     _hashAlgorithm;
        SRP::Base::GroupType   _groupType;
        std::string            _identity;
        std::string            _password;
        std::vector< uint8_t > _salt;
        SRP::BigNum            _v;
        SRP::BigNum            _a;
        SRP::BigNum            _A;
        SRP::BigNum            _b;
        SRP::BigNum            _B;
        SRP::BigNum            _u;
        SRP::BigNum            _k;
        SRP::BigNum            _S;
        SRP::BigNum            _x;
        std::vector< uint8_t > _K;
        std::vector< uint8_t > _M1;
        std::vector< uint8_t > _M2;
};

Constants::Constants( SRP::HashAlgorithm hashAlgorithm, SRP::Base::GroupType groupType, std::string identity, std::string password, std::vector< uint8_t > salt, std::vector< uint8_t > v, std::vector< uint8_t > a, std::vector< uint8_t > A, std::vector< uint8_t > b, std::vector< uint8_t > B, std::vector< uint8_t > u, std::vector< uint8_t > k, std::vector< uint8_t > S, std::vector< uint8_t > x, std::vector< uint8_t > K, std::vector< uint8_t > M1, std::vector< uint8_t > M2 ):
    impl( std::make_unique< IMPL >( hashAlgorithm, groupType, identity, password, salt, v, a, A, b, B, u, k, S, x, K, M1, M2 ) )
{}

Constants::Constants( const Constants & o ):
    impl( std::make_unique< IMPL >( *( o.impl ) ) )
{}

Constants::~Constants()
{}

Constants & Constants::operator =( Constants o )
{
    swap( *( this ), o );
    
    return *( this );
}

void swap( Constants & o1, Constants & o2 )
{
    using std::swap;
    
    swap( o1.impl, o2.impl );
}

SRP::Client Constants::makeClient() const
{
    return SRP::Client( this->identity(), this->impl->_hashAlgorithm, this->impl->_groupType, this->a() );
}

SRP::Server Constants::makeServer() const
{
    return SRP::Server( this->identity(), this->impl->_hashAlgorithm, this->impl->_groupType, this->b() );
}

SRP::HashAlgorithm Constants::hashAlgorithm() const
{
    return this->impl->_hashAlgorithm;
}

SRP::Base::GroupType Constants::groupType() const
{
    return this->impl->_groupType;
}

std::string Constants::identity() const
{
    return this->impl->_identity;
}

std::string Constants::password() const
{
    return this->impl->_password;
}

std::vector< uint8_t > Constants::salt() const
{
    return this->impl->_salt;
}

SRP::BigNum Constants::v() const
{
    return this->impl->_v;
}

SRP::BigNum Constants::a() const
{
    return this->impl->_a;
}

SRP::BigNum Constants::A() const
{
    return this->impl->_A;
}

SRP::BigNum Constants::b() const
{
    return this->impl->_b;
}

SRP::BigNum Constants::B() const
{
    return this->impl->_B;
}

SRP::BigNum Constants::u() const
{
    return this->impl->_u;
}

SRP::BigNum Constants::k() const
{
    return this->impl->_k;
}

SRP::BigNum Constants::S() const
{
    return this->impl->_S;
}

SRP::BigNum Constants::x() const
{
    return this->impl->_x;
}

std::vector< uint8_t > Constants::K() const
{
    return this->impl->_K;
}

std::vector< uint8_t > Constants::M1() const
{
    return this->impl->_M1;
}

std::vector< uint8_t > Constants::M2() const
{
    return this->impl->_M2;
}

Constants::IMPL::IMPL( SRP::HashAlgorithm hashAlgorithm, SRP::Base::GroupType groupType, std::string identity, std::string password, std::vector< uint8_t > salt, std::vector< uint8_t > v, std::vector< uint8_t > a, std::vector< uint8_t > A, std::vector< uint8_t > b, std::vector< uint8_t > B, std::vector< uint8_t > u, std::vector< uint8_t > k, std::vector< uint8_t > S, std::vector< uint8_t > x, std::vector< uint8_t > K, std::vector< uint8_t > M1, std::vector< uint8_t > M2 ):
    _hashAlgorithm( hashAlgorithm ),
    _groupType(     groupType ),
    _identity(      identity ),
    _password(      password ),
    _salt(          salt ),
    _v(             SRP::BigNum( v, SRP::BigNum::Endianness::BigEndian ) ),
    _a(             SRP::BigNum( a, SRP::BigNum::Endianness::BigEndian ) ),
    _A(             SRP::BigNum( A, SRP::BigNum::Endianness::BigEndian ) ),
    _b(             SRP::BigNum( b, SRP::BigNum::Endianness::BigEndian ) ),
    _B(             SRP::BigNum( B, SRP::BigNum::Endianness::BigEndian ) ),
    _u(             SRP::BigNum( u, SRP::BigNum::Endianness::BigEndian ) ),
    _k(             SRP::BigNum( k, SRP::BigNum::Endianness::BigEndian ) ),
    _S(             SRP::BigNum( S, SRP::BigNum::Endianness::BigEndian ) ),
    _x(             SRP::BigNum( x, SRP::BigNum::Endianness::BigEndian ) ),
    _K(             K ),
    _M1(            M1 ),
    _M2(            M2 )
{}

Constants::IMPL::IMPL( const IMPL & o ):
    _hashAlgorithm( o._hashAlgorithm ),
    _groupType(     o._groupType ),
    _identity(      o._identity ),
    _password(      o._password ),
    _salt(          o._salt ),
    _v(             o._v ),
    _a(             o._a ),
    _A(             o._A ),
    _b(             o._b ),
    _B(             o._B ),
    _u(             o._u ),
    _k(             o._k ),
    _S(             o._S ),
    _x(             o._x ),
    _K(             o._K ),
    _M1(            o._M1 ),
    _M2(            o._M2 )
{}

Constants::IMPL::~IMPL()
{}

std::vector< Constants > Constants::all()
{
    return
    {
        #include "Constants/SHA1/All.txt"
        ,
        #include "Constants/SHA224/All.txt"
        ,
        #include "Constants/SHA256/All.txt"
        ,
        #include "Constants/SHA384/All.txt"
        ,
        #include "Constants/SHA512/All.txt"
    };
}
