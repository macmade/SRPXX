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

/* For memset_s */
#define __STDC_WANT_LIB_EXT1__ 1

#include <SRPXX/Base.hpp>
#include <SRPXX/SHA1.hpp>
#include <SRPXX/SHA224.hpp>
#include <SRPXX/SHA256.hpp>
#include <SRPXX/SHA384.hpp>
#include <SRPXX/SHA512.hpp>
#include <string>
#include <cctype>
#include <stdexcept>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace SRP
{
    class Base::IMPL
    {
        public:
            
            IMPL( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType );
            ~IMPL();
            
            HashAlgorithm          _hashAlgorithm;
            GroupType              _groupType;
            BigNum                 _N;
            BigNum                 _g;
            std::string            _identity;
            std::vector< uint8_t > _salt;
            
            void clearSalt();
            
            static BigNum getN( GroupType groupType );
            static BigNum getG( GroupType groupType );
            
            static std::pair< std::string, std::string > getNG( GroupType groupType );
            
            struct NGGroup
            {
                const char * N;
                const char * g;
            };
            
            static struct NGGroup RFCGroups[];
    };
    
    Base::Base( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType ):
        impl( std::make_unique< IMPL >( identity, hashAlgorithm, groupType ) )
    {}
    
    Base::~Base()
    {}
    
    std::string Base::identity() const
    {
        return this->impl->_identity;
    }
    
    std::vector< uint8_t > Base::salt() const
    {
        return this->impl->_salt;
    }
    
    void Base::setSalt( const std::vector< uint8_t > & value )
    {
        this->impl->clearSalt();
        
        this->impl->_salt = value;
    }
    
    BigNum Base::N() const
    {
        return this->impl->_N;
    }
    
    BigNum Base::g() const
    {
        return this->impl->_g;
    }
    
    /* H( N | PAD( g ) ) */
    BigNum Base::k() const
    {
        return BigNum
        (
            this->hash
            (
                {
                    this->N().bytes( SRP::BigNum::Endianness::BigEndian ),
                    this->pad( this->g().bytes( SRP::BigNum::Endianness::BigEndian ) ),
                }
            ),
            BigNum::Endianness::BigEndian
        );
    }
    
    /* H( PAD( A ) | PAD( B ) ) */
    BigNum Base::u() const
    {
        return BigNum
        (
            this->hash
            (
                {
                    this->pad( this->A().bytes( SRP::BigNum::Endianness::BigEndian ) ),
                    this->pad( this->B().bytes( SRP::BigNum::Endianness::BigEndian ) ),
                }
            ),
            BigNum::Endianness::BigEndian
        );
    }
    
    /* H( S ) */
    std::vector< uint8_t > Base::K() const
    {
        return this->hash( this->S().bytes( BigNum::Endianness::BigEndian ) );
    }
    
    /* H( H( N ) xor H( g ), H( I ), s, A, B, K ) */
    std::vector< uint8_t > Base::M1() const
    {
        std::vector< uint8_t > hn = this->hash( this->N().bytes( BigNum::Endianness::BigEndian ) );
        std::vector< uint8_t > hg = this->hash( this->pad( this->g().bytes( BigNum::Endianness::BigEndian ) ) );
        std::vector< uint8_t > ng;
        
        for( size_t i = 0; i < hn.size(); i++ )
        {
            ng.push_back( hn[ i ] ^ hg[ i ] );
        }
        
        return this->hash
        (
            {
                ng,
                this->hash( String::toBytes( this->identity() ) ),
                this->salt(),
                this->A().bytes( BigNum::Endianness::BigEndian ),
                this->B().bytes( BigNum::Endianness::BigEndian ),
                this->K()
            }
        );
    }
    
    /* H( A | M | K ) */
    std::vector< uint8_t > Base::M2() const
    {
        return this->hash
        (
            {
                this->A().bytes( BigNum::Endianness::BigEndian ),
                this->M1(),
                this->K()
            }
        );
    }
    
    std::unique_ptr< Hasher > Base::makeHasher() const
    {
        switch( this->impl->_hashAlgorithm )
        {
            case HashAlgorithm::SHA1:   return std::make_unique< SHA1 >();
            case HashAlgorithm::SHA224: return std::make_unique< SHA224 >();
            case HashAlgorithm::SHA256: return std::make_unique< SHA256 >();
            case HashAlgorithm::SHA384: return std::make_unique< SHA384 >();
            case HashAlgorithm::SHA512: return std::make_unique< SHA512 >();
            
            #ifdef _WIN32
            default: return {};
            #endif
        }
    }
    
    std::vector< uint8_t > Base::hash( const std::vector< uint8_t > & data ) const
    {
        return this->hash( std::vector< std::vector< uint8_t > >{ data } );
    }
    
    std::vector< uint8_t > Base::hash( const std::vector< std::vector< uint8_t > > & data ) const
    {
        auto hasher = this->makeHasher();
        
        for( const auto & d: data )
        {
            hasher->update( d );
        }
        
        hasher->finalize();
        
        return hasher->bytes();
    }
    
    std::vector< uint8_t > Base::pad( const std::vector< uint8_t > & data ) const
    {
        size_t length = this->N().bytes( BigNum::Endianness::BigEndian ).size();
        
        if( data.size() < length )
        {
            std::vector< uint8_t > padded( length - data.size(), 0 );
            
            padded.insert( std::end( padded ), std::begin( data ), std::end( data ) );
            
            return padded;
        }
        
        return data;
    }
    
    Base::IMPL::IMPL( const std::string & identity, HashAlgorithm hashAlgorithm, GroupType groupType ):
        _hashAlgorithm( hashAlgorithm ),
        _groupType( groupType ),
        _N( IMPL::getN( groupType ) ),
        _g( IMPL::getG( groupType ) ),
        _identity( identity )
    {}
    
    Base::IMPL::~IMPL()
    {
        this->clearSalt();
    }
    
    void Base::IMPL::clearSalt()
    {
        if( this->_salt.size() > 0 )
        {
            #ifdef _WIN32
            SecureZeroMemory( this->_salt.data(), this->_salt.size() );
            #else
            memset_s( this->_salt.data(), this->_salt.size(), 0, this->_salt.size() );
            #endif
        }
    }
            
    BigNum Base::IMPL::getN( GroupType groupType )
    {
        std::unique_ptr< BigNum > N = BigNum::fromString( IMPL::getNG( groupType ).first, BigNum::StringFormat::Hexadecimal );
        
        if( N == nullptr )
        {
            throw std::runtime_error( "Invalid N value" );
        }
        
        return *( N );
    }
    
    BigNum Base::IMPL::getG( GroupType groupType )
    {
        std::unique_ptr< BigNum > g = BigNum::fromString( IMPL::getNG( groupType ).second, BigNum::StringFormat::Decimal );
        
        if( g == nullptr )
        {
            throw std::runtime_error( "Invalid g value" );
        }
        
        return *( g );
    }
    
    std::pair< std::string, std::string > Base::IMPL::getNG( GroupType groupType )
    {
        struct NGGroup ng;
        
        switch( groupType )
        {
            case GroupType::NG1024: ng = RFCGroups[ 0 ]; break;
            case GroupType::NG1536: ng = RFCGroups[ 1 ]; break;
            case GroupType::NG2048: ng = RFCGroups[ 2 ]; break;
            case GroupType::NG3072: ng = RFCGroups[ 3 ]; break;
            case GroupType::NG4096: ng = RFCGroups[ 4 ]; break;
            case GroupType::NG6144: ng = RFCGroups[ 5 ]; break;
            case GroupType::NG8192: ng = RFCGroups[ 6 ]; break;
        }
        
        std::string N = ng.N;
        std::string g = ng.g;
        
        N.erase( std::remove_if( N.begin(), N.end(), isspace ), N.end() );
        g.erase( std::remove_if( g.begin(), g.end(), isspace ), g.end() );
        
        return { N, g };
    }
    
    struct Base::IMPL::NGGroup Base::IMPL::RFCGroups[] =
    {
        /* 1024-bit Group */
        {
            "EEAF0AB9 ADB38DD6 9C33F80A FA8FC5E8 60726187 75FF3C0B 9EA2314C"
            "9C256576 D674DF74 96EA81D3 383B4813 D692C6E0 E0D5D8E2 50B98BE4"
            "8E495C1D 6089DAD1 5DC7D7B4 6154D6B6 CE8EF4AD 69B15D49 82559B29"
            "7BCF1885 C529F566 660E57EC 68EDBC3C 05726CC0 2FD4CBF4 976EAA9A"
            "FD5138FE 8376435B 9FC61D2F C0EB06E3",
            "2"
        },
        
        /* 1536-bit Group */
        {
            "9DEF3CAF B939277A B1F12A86 17A47BBB DBA51DF4 99AC4C80 BEEEA961"
            "4B19CC4D 5F4F5F55 6E27CBDE 51C6A94B E4607A29 1558903B A0D0F843"
            "80B655BB 9A22E8DC DF028A7C EC67F0D0 8134B1C8 B9798914 9B609E0B"
            "E3BAB63D 47548381 DBC5B1FC 764E3F4B 53DD9DA1 158BFD3E 2B9C8CF5"
            "6EDF0195 39349627 DB2FD53D 24B7C486 65772E43 7D6C7F8C E442734A"
            "F7CCB7AE 837C264A E3A9BEB8 7F8A2FE9 B8B5292E 5A021FFF 5E91479E"
            "8CE7A28C 2442C6F3 15180F93 499A234D CF76E3FE D135F9BB",
            "2"
        },
        
        /* 2048-bit Group */
        {
            "AC6BDB41 324A9A9B F166DE5E 1389582F AF72B665 1987EE07 FC319294"
            "3DB56050 A37329CB B4A099ED 8193E075 7767A13D D52312AB 4B03310D"
            "CD7F48A9 DA04FD50 E8083969 EDB767B0 CF609517 9A163AB3 661A05FB"
            "D5FAAAE8 2918A996 2F0B93B8 55F97993 EC975EEA A80D740A DBF4FF74"
            "7359D041 D5C33EA7 1D281E44 6B14773B CA97B43A 23FB8016 76BD207A"
            "436C6481 F1D2B907 8717461A 5B9D32E6 88F87748 544523B5 24B0D57D"
            "5EA77A27 75D2ECFA 032CFBDB F52FB378 61602790 04E57AE6 AF874E73"
            "03CE5329 9CCC041C 7BC308D8 2A5698F3 A8D0C382 71AE35F8 E9DBFBB6"
            "94B5C803 D89F7AE4 35DE236D 525F5475 9B65E372 FCD68EF2 0FA7111F"
            "9E4AFF73",
            "2"
        },
        
        /* 3072-bit Group */
        {
            "FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08"
            "8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B"
            "302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9"
            "A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6"
            "49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8"
            "FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D"
            "670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C"
            "180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718"
            "3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D"
            "04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D"
            "B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226"
            "1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C"
            "BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC"
            "E0FD108E 4B82D120 A93AD2CA FFFFFFFF FFFFFFFF",
            "5"
        },

        /* 4096-bit Group */
        {
            "FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08"
            "8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B"
            "302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9"
            "A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6"
            "49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8"
            "FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D"
            "670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C"
            "180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718"
            "3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D"
            "04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D"
            "B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226"
            "1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C"
            "BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC"
            "E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7 88719A10 BDBA5B26"
            "99C32718 6AF4E23C 1A946834 B6150BDA 2583E9CA 2AD44CE8 DBBBC2DB"
            "04DE8EF9 2E8EFC14 1FBECAA6 287C5947 4E6BC05D 99B2964F A090C3A2"
            "233BA186 515BE7ED 1F612970 CEE2D7AF B81BDD76 2170481C D0069127"
            "D5B05AA9 93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34063199"
            "FFFFFFFF FFFFFFFF",
            "5"
        },
        
        /* 6144-bit Group */
        {
            "FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08"
            "8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B"
            "302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9"
            "A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6"
            "49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8"
            "FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D"
            "670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C"
            "180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718"
            "3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D"
            "04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D"
            "B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226"
            "1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C"
            "BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC"
            "E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7 88719A10 BDBA5B26"
            "99C32718 6AF4E23C 1A946834 B6150BDA 2583E9CA 2AD44CE8 DBBBC2DB"
            "04DE8EF9 2E8EFC14 1FBECAA6 287C5947 4E6BC05D 99B2964F A090C3A2"
            "233BA186 515BE7ED 1F612970 CEE2D7AF B81BDD76 2170481C D0069127"
            "D5B05AA9 93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34028492"
            "36C3FAB4 D27C7026 C1D4DCB2 602646DE C9751E76 3DBA37BD F8FF9406"
            "AD9E530E E5DB382F 413001AE B06A53ED 9027D831 179727B0 865A8918"
            "DA3EDBEB CF9B14ED 44CE6CBA CED4BB1B DB7F1447 E6CC254B 33205151"
            "2BD7AF42 6FB8F401 378CD2BF 5983CA01 C64B92EC F032EA15 D1721D03"
            "F482D7CE 6E74FEF6 D55E702F 46980C82 B5A84031 900B1C9E 59E7C97F"
            "BEC7E8F3 23A97A7E 36CC88BE 0F1D45B7 FF585AC5 4BD407B2 2B4154AA"
            "CC8F6D7E BF48E1D8 14CC5ED2 0F8037E0 A79715EE F29BE328 06A1D58B"
            "B7C5DA76 F550AA3D 8A1FBFF0 EB19CCB1 A313D55C DA56C9EC 2EF29632"
            "387FE8D7 6E3C0468 043E8F66 3F4860EE 12BF2D5B 0B7474D6 E694F91E"
            "6DCC4024 FFFFFFFF FFFFFFFF",
            "5"
        },
        
        /* 8192-bit Group */
        {
            "FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08"
            "8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B"
            "302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9"
            "A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6"
            "49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8"
            "FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D"
            "670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C"
            "180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718"
            "3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D"
            "04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D"
            "B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226"
            "1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C"
            "BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC"
            "E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7 88719A10 BDBA5B26"
            "99C32718 6AF4E23C 1A946834 B6150BDA 2583E9CA 2AD44CE8 DBBBC2DB"
            "04DE8EF9 2E8EFC14 1FBECAA6 287C5947 4E6BC05D 99B2964F A090C3A2"
            "233BA186 515BE7ED 1F612970 CEE2D7AF B81BDD76 2170481C D0069127"
            "D5B05AA9 93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34028492"
            "36C3FAB4 D27C7026 C1D4DCB2 602646DE C9751E76 3DBA37BD F8FF9406"
            "AD9E530E E5DB382F 413001AE B06A53ED 9027D831 179727B0 865A8918"
            "DA3EDBEB CF9B14ED 44CE6CBA CED4BB1B DB7F1447 E6CC254B 33205151"
            "2BD7AF42 6FB8F401 378CD2BF 5983CA01 C64B92EC F032EA15 D1721D03"
            "F482D7CE 6E74FEF6 D55E702F 46980C82 B5A84031 900B1C9E 59E7C97F"
            "BEC7E8F3 23A97A7E 36CC88BE 0F1D45B7 FF585AC5 4BD407B2 2B4154AA"
            "CC8F6D7E BF48E1D8 14CC5ED2 0F8037E0 A79715EE F29BE328 06A1D58B"
            "B7C5DA76 F550AA3D 8A1FBFF0 EB19CCB1 A313D55C DA56C9EC 2EF29632"
            "387FE8D7 6E3C0468 043E8F66 3F4860EE 12BF2D5B 0B7474D6 E694F91E"
            "6DBE1159 74A3926F 12FEE5E4 38777CB6 A932DF8C D8BEC4D0 73B931BA"
            "3BC832B6 8D9DD300 741FA7BF 8AFC47ED 2576F693 6BA42466 3AAB639C"
            "5AE4F568 3423B474 2BF1C978 238F16CB E39D652D E3FDB8BE FC848AD9"
            "22222E04 A4037C07 13EB57A8 1A23F0C7 3473FC64 6CEA306B 4BCBC886"
            "2F8385DD FA9D4B7F A2C087E8 79683303 ED5BDD3A 062B3CF5 B3A278A6"
            "6D2A13F8 3F44F82D DF310EE0 74AB6A36 4597E899 A0255DC1 64F31CC5"
            "0846851D F9AB4819 5DED7EA1 B1D510BD 7EE74D73 FAF36BC3 1ECFA268"
            "359046F4 EB879F92 4009438B 481C6CD7 889A002E D5EE382B C9190DA6"
            "FC026E47 9558E447 5677E9AA 9E3050E2 765694DF C81F56E8 80B96E71"
            "60C980DD 98EDD3DF FFFFFFFF FFFFFFFF",
            "19"
        }
    };
}
