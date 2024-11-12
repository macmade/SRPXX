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

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <SRPXX.hpp>
#include "Arguments.hpp"

static std::string stringFromHashAlgorithm( SRP::HashAlgorithm algorithm );
static std::string stringFromGroupType( SRP::Base::GroupType groupType );
static std::string stringFromString( const std::string & string );
static std::string stringFromBigNum( const std::string & name, const SRP::BigNum & number );
static std::string stringFromData( const std::string & name, const std::vector< uint8_t > & data );

int main( int argc, const char * argv[] )
{
    try
    {
        Arguments              args( argc, argv );
        std::vector< uint8_t > salt;
        std::vector< uint8_t > verifier;
        
        {
            SRP::Client client( args.identity(), args.hashAlgorithm(), args.groupType() );
            
            client.setPassword( args.password() );
            client.setSalt( SRP::Random::bytes( 16 ) );
            
            salt     = client.salt();
            verifier = client.v().bytes( SRP::BigNum::Endianness::BigEndian );
        }
        
        {
            SRP::Client client( args.identity(), args.hashAlgorithm(), args.groupType() );
            SRP::Server server( args.identity(), args.hashAlgorithm(), args.groupType() );
            
            server.setSalt( salt );
            server.setV( SRP::BigNum( verifier, SRP::BigNum::Endianness::BigEndian ) );
            server.setA( client.A() );
            client.setB( server.B() );
            client.setSalt( server.salt() );
            client.setPassword( args.password() );
            
            if( client.M1() != server.M1() || client.M2() != server.M2() )
            {
                throw std::runtime_error( "Invalid M1/M2" );
            }
            
            std::cout << stringFromHashAlgorithm( args.hashAlgorithm() ) << "," << std::endl;
            std::cout << stringFromGroupType( args.groupType() )         << "," << std::endl;
            std::cout << stringFromString( args.identity() )             << "," << std::endl;
            std::cout << stringFromString( args.password() )             << "," << std::endl;
            std::cout << stringFromData( "Salt", salt )                  << "," << std::endl;
            std::cout << stringFromData( "Verifier", verifier )          << "," << std::endl;
            std::cout << stringFromBigNum( "a", client.a() )             << "," << std::endl;
            std::cout << stringFromBigNum( "A", client.A() )             << "," << std::endl;
            std::cout << stringFromBigNum( "b", server.b() )             << "," << std::endl;
            std::cout << stringFromBigNum( "B", server.B() )             << "," << std::endl;
            std::cout << stringFromBigNum( "u", client.u() )             << "," << std::endl;
            std::cout << stringFromBigNum( "k", client.k() )             << "," << std::endl;
            std::cout << stringFromBigNum( "S", client.S() )             << "," << std::endl;
            std::cout << stringFromBigNum( "x", client.x() )             << "," << std::endl;
            std::cout << stringFromData( "K", client.K() )               << "," << std::endl;
            std::cout << stringFromData( "M1", client.M1() )             << "," << std::endl;
            std::cout << stringFromData( "M2", client.M2() )                    << std::endl;
        }
    }
    catch( const std::exception & e )
    {
        std::cout << e.what() << std::endl;
        
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

static std::string stringFromHashAlgorithm( SRP::HashAlgorithm algorithm )
{
    switch( algorithm )
    {
        case SRP::HashAlgorithm::SHA1:   return "SRP::HashAlgorithm::SHA1";
        case SRP::HashAlgorithm::SHA224: return "SRP::HashAlgorithm::SHA224";
        case SRP::HashAlgorithm::SHA256: return "SRP::HashAlgorithm::SHA256";
        case SRP::HashAlgorithm::SHA384: return "SRP::HashAlgorithm::SHA384";
        case SRP::HashAlgorithm::SHA512: return "SRP::HashAlgorithm::SHA512";
    }
}

static std::string stringFromGroupType( SRP::Base::GroupType groupType )
{
    switch( groupType )
    {
        case SRP::Base::GroupType::NG1024: return "SRP::Base::GroupType::NG1024";
        case SRP::Base::GroupType::NG1536: return "SRP::Base::GroupType::NG1536";
        case SRP::Base::GroupType::NG2048: return "SRP::Base::GroupType::NG2048";
        case SRP::Base::GroupType::NG3072: return "SRP::Base::GroupType::NG3072";
        case SRP::Base::GroupType::NG4096: return "SRP::Base::GroupType::NG4096";
        case SRP::Base::GroupType::NG6144: return "SRP::Base::GroupType::NG6144";
        case SRP::Base::GroupType::NG8192: return "SRP::Base::GroupType::NG8192";
    }
}

static std::string stringFromString( const std::string & string )
{
    return "\"" + string + "\"";
}

static std::string stringFromBigNum( const std::string & name, const SRP::BigNum & number )
{
    return stringFromData( name, number.bytes( SRP::BigNum::Endianness::BigEndian ) );
}

static std::string stringFromData( const std::string & name, const std::vector< uint8_t > & data )
{
    std::stringstream ss;
    
    ss << "{"                        << std::endl;
    ss << "    /* " << name << " */" << std::endl;
    
    for( size_t i = 0; i < data.size(); i++ )
    {
        if( i == 0 || ( i + 1 ) % 16 == 1 )
        {
            ss <<  "    ";
        }
        
        ss << "0x" << std::uppercase << std::hex << std::setw( 2 ) << std::setfill( '0' ) << static_cast< unsigned int >( data[ i ] );
        
        if( i != ( data.size() - 1 ) )
        {
            if( ( i + 1 ) % 16 == 0 )
            {
                ss << "," << std::endl;
            }
            else
            {
                ss << ", ";
            }
        }
    }
    
    ss << std::endl << "}";
    
    return ss.str();
}
