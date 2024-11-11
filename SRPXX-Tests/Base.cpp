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

static std::string removeSpaces( std::string s );
static std::string removeSpaces( std::string s )
{
    s.erase( std::remove_if( s.begin(), s.end(), isspace ), s.end() );
    
    return s;
}

class ConcreteBase: public SRP::Base
{
    public:
        
        ConcreteBase( const Constants & constants, SRP::HashAlgorithm hashAlgorithm, SRP::Base::GroupType groupType ):
            SRP::Base( constants.identity(), hashAlgorithm, groupType ),
            _constants( constants )
        {}
        
        SRP::BigNum A() const override
        {
            return this->_constants.A();
        }
        
        SRP::BigNum B() const override
        {
            return this->_constants.B();
        }
        
        SRP::BigNum S() const override
        {
            return this->_constants.S();
        }
        
    private:
        
        Constants _constants;
};

XSTest( Base, u )
{
    for( const auto & constants: Constants::all() )
    {
        ConcreteBase base( constants, SRP::HashAlgorithm::SHA256, SRP::Base::GroupType::NG2048 );
        
        XSTestAssertTrue( base.u() == constants.u() );
    }
}

XSTest( Base, Salt )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA256, SRP::Base::GroupType::NG2048 );
    
    XSTestAssertTrue( base.salt().size() == 0 );
    
    std::vector< uint8_t > salt1 = SRP::Random::bytes( 16 );
    std::vector< uint8_t > salt2 = SRP::Random::bytes( 16 );
    
    XSTestAssertTrue( salt1 != salt2 );
    
    base.setSalt( salt1 );
    XSTestAssertTrue( base.salt() == salt1 );
    
    base.setSalt( salt2 );
    XSTestAssertTrue( base.salt() == salt2 );
    
    base.setSalt( {} );
    XSTestAssertTrue( base.salt().size() == 0 );
}

XSTest( Base, Hasher_SHA1 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG1024 );
    auto         hasher = base.makeHasher();
    
    hasher->update( "hello, world" );
    hasher->finalize();
    
    XSTestAssertEqual( hasher->string( SRP::String::HexFormat::Uppercase ), "B7E23EC29AF22B0B4E41DA31E868D57226121C84" );
    
    auto hash1 = hasher->bytes();
    auto hash2 = base.hash( SRP::String::toBytes( "hello, world" ) );
    auto hash3 = base.hash( { SRP::String::toBytes( "hello, " ), SRP::String::toBytes( "world" ) } );
    
    XSTestAssertTrue( hash1 == hash2 );
    XSTestAssertTrue( hash1 == hash3 );
    XSTestAssertTrue( SRP::String::toHex( hash1, SRP::String::HexFormat::Uppercase ) == hasher->string( SRP::String::HexFormat::Uppercase ) );
}

XSTest( Base, Hasher_SHA224 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA224, SRP::Base::GroupType::NG1024 );
    auto         hasher = base.makeHasher();
    
    hasher->update( "hello, world" );
    hasher->finalize();
    
    XSTestAssertEqual( hasher->string( SRP::String::HexFormat::Uppercase ), "6E1A93E32FB44081A401F3DB3EF2E6E108B7BBEEB5705AFDAF01FB27" );
    
    auto hash1 = hasher->bytes();
    auto hash2 = base.hash( SRP::String::toBytes( "hello, world" ) );
    auto hash3 = base.hash( { SRP::String::toBytes( "hello, " ), SRP::String::toBytes( "world" ) } );
    
    XSTestAssertTrue( hash1 == hash2 );
    XSTestAssertTrue( hash1 == hash3 );
    XSTestAssertTrue( SRP::String::toHex( hash1, SRP::String::HexFormat::Uppercase ) == hasher->string( SRP::String::HexFormat::Uppercase ) );
}

XSTest( Base, Hasher_SHA256 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA256, SRP::Base::GroupType::NG1024 );
    auto         hasher = base.makeHasher();
    
    hasher->update( "hello, world" );
    hasher->finalize();
    
    XSTestAssertEqual( hasher->string( SRP::String::HexFormat::Uppercase ), "09CA7E4EAA6E8AE9C7D261167129184883644D07DFBA7CBFBC4C8A2E08360D5B" );
    
    auto hash1 = hasher->bytes();
    auto hash2 = base.hash( SRP::String::toBytes( "hello, world" ) );
    auto hash3 = base.hash( { SRP::String::toBytes( "hello, " ), SRP::String::toBytes( "world" ) } );
    
    XSTestAssertTrue( hash1 == hash2 );
    XSTestAssertTrue( hash1 == hash3 );
    XSTestAssertTrue( SRP::String::toHex( hash1, SRP::String::HexFormat::Uppercase ) == hasher->string( SRP::String::HexFormat::Uppercase ) );
}

XSTest( Base, Hasher_SHA384 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA384, SRP::Base::GroupType::NG1024 );
    auto         hasher = base.makeHasher();
    
    hasher->update( "hello, world" );
    hasher->finalize();
    
    XSTestAssertEqual( hasher->string( SRP::String::HexFormat::Uppercase ), "1FCDB6059CE05172A26BBE2A3CCC88ED5A8CD5FC53EDFD9053304D429296A6DA23B1CD9E5C9ED3BB34F00418A70CDB7E" );
    
    auto hash1 = hasher->bytes();
    auto hash2 = base.hash( SRP::String::toBytes( "hello, world" ) );
    auto hash3 = base.hash( { SRP::String::toBytes( "hello, " ), SRP::String::toBytes( "world" ) } );
    
    XSTestAssertTrue( hash1 == hash2 );
    XSTestAssertTrue( hash1 == hash3 );
    XSTestAssertTrue( SRP::String::toHex( hash1, SRP::String::HexFormat::Uppercase ) == hasher->string( SRP::String::HexFormat::Uppercase ) );
}

XSTest( Base, Hasher_SHA512 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA512, SRP::Base::GroupType::NG1024 );
    auto         hasher = base.makeHasher();
    
    hasher->update( "hello, world" );
    hasher->finalize();
    
    XSTestAssertEqual( hasher->string( SRP::String::HexFormat::Uppercase ), "8710339DCB6814D0D9D2290EF422285C9322B7163951F9A0CA8F883D3305286F44139AA374848E4174F5AADA663027E4548637B6D19894AEC4FB6C46A139FBF9" );
    
    auto hash1 = hasher->bytes();
    auto hash2 = base.hash( SRP::String::toBytes( "hello, world" ) );
    auto hash3 = base.hash( { SRP::String::toBytes( "hello, " ), SRP::String::toBytes( "world" ) } );
    
    XSTestAssertTrue( hash1 == hash2 );
    XSTestAssertTrue( hash1 == hash3 );
    XSTestAssertTrue( SRP::String::toHex( hash1, SRP::String::HexFormat::Uppercase ) == hasher->string( SRP::String::HexFormat::Uppercase ) );
}

XSTest( Base, NG1024_Pad )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG1024 );
    size_t       size = 1024 / 8;
    
    XSTestAssertTrue( base.pad( std::vector< uint8_t >(        0 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size - 1 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size     ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size + 1 ) ).size() == size + 1 );
}

XSTest( Base, NG1536_Pad )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG1536 );
    size_t       size = 1536 / 8;
    
    XSTestAssertTrue( base.pad( std::vector< uint8_t >(        0 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size - 1 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size     ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size + 1 ) ).size() == size + 1 );
}

XSTest( Base, NG2048_Pad )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG2048 );
    size_t       size = 2048 / 8;
    
    XSTestAssertTrue( base.pad( std::vector< uint8_t >(        0 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size - 1 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size     ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size + 1 ) ).size() == size + 1 );
}

XSTest( Base, NG3072_Pad )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG3072 );
    size_t       size = 3072 / 8;
    
    XSTestAssertTrue( base.pad( std::vector< uint8_t >(        0 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size - 1 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size     ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size + 1 ) ).size() == size + 1 );
}

XSTest( Base, NG4096_Pad )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG4096 );
    size_t       size = 4096 / 8;
    
    XSTestAssertTrue( base.pad( std::vector< uint8_t >(        0 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size - 1 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size     ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size + 1 ) ).size() == size + 1 );
}

XSTest( Base, NG6144_Pad )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG6144 );
    size_t       size = 6144 / 8;
    
    XSTestAssertTrue( base.pad( std::vector< uint8_t >(        0 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size - 1 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size     ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size + 1 ) ).size() == size + 1 );
}

XSTest( Base, NG8192_Pad )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG8192 );
    size_t       size = 8192 / 8;
    
    XSTestAssertTrue( base.pad( std::vector< uint8_t >(        0 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size - 1 ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size     ) ).size() == size );
    XSTestAssertTrue( base.pad( std::vector< uint8_t >( size + 1 ) ).size() == size + 1 );
}

XSTest( Base, NG1024 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG1024 );
    
    XSTestAssertEqual( base.g(), "2" );
    XSTestAssertEqual
    (
        base.N(),
        removeSpaces
        (
            "0x"
            "EEAF0AB9 ADB38DD6 9C33F80A FA8FC5E8 60726187 75FF3C0B 9EA2314C"
            "9C256576 D674DF74 96EA81D3 383B4813 D692C6E0 E0D5D8E2 50B98BE4"
            "8E495C1D 6089DAD1 5DC7D7B4 6154D6B6 CE8EF4AD 69B15D49 82559B29"
            "7BCF1885 C529F566 660E57EC 68EDBC3C 05726CC0 2FD4CBF4 976EAA9A"
            "FD5138FE 8376435B 9FC61D2F C0EB06E3"
        )
    );
}

XSTest( Base, NG1536 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG1536 );
    
    XSTestAssertEqual( base.g(), "2" );
    XSTestAssertEqual
    (
        base.N(),
        removeSpaces
        (
            "0x"
            "9DEF3CAF B939277A B1F12A86 17A47BBB DBA51DF4 99AC4C80 BEEEA961"
            "4B19CC4D 5F4F5F55 6E27CBDE 51C6A94B E4607A29 1558903B A0D0F843"
            "80B655BB 9A22E8DC DF028A7C EC67F0D0 8134B1C8 B9798914 9B609E0B"
            "E3BAB63D 47548381 DBC5B1FC 764E3F4B 53DD9DA1 158BFD3E 2B9C8CF5"
            "6EDF0195 39349627 DB2FD53D 24B7C486 65772E43 7D6C7F8C E442734A"
            "F7CCB7AE 837C264A E3A9BEB8 7F8A2FE9 B8B5292E 5A021FFF 5E91479E"
            "8CE7A28C 2442C6F3 15180F93 499A234D CF76E3FE D135F9BB"
        )
    );
}

XSTest( Base, NG2048 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG2048 );
    
    XSTestAssertEqual( base.g(), "2" );
    XSTestAssertEqual
    (
        base.N(),
        removeSpaces
        (
            "0x"
            "AC6BDB41 324A9A9B F166DE5E 1389582F AF72B665 1987EE07 FC319294"
            "3DB56050 A37329CB B4A099ED 8193E075 7767A13D D52312AB 4B03310D"
            "CD7F48A9 DA04FD50 E8083969 EDB767B0 CF609517 9A163AB3 661A05FB"
            "D5FAAAE8 2918A996 2F0B93B8 55F97993 EC975EEA A80D740A DBF4FF74"
            "7359D041 D5C33EA7 1D281E44 6B14773B CA97B43A 23FB8016 76BD207A"
            "436C6481 F1D2B907 8717461A 5B9D32E6 88F87748 544523B5 24B0D57D"
            "5EA77A27 75D2ECFA 032CFBDB F52FB378 61602790 04E57AE6 AF874E73"
            "03CE5329 9CCC041C 7BC308D8 2A5698F3 A8D0C382 71AE35F8 E9DBFBB6"
            "94B5C803 D89F7AE4 35DE236D 525F5475 9B65E372 FCD68EF2 0FA7111F"
            "9E4AFF73"
        )
    );
}

XSTest( Base, NG3072 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG3072 );
    
    XSTestAssertEqual( base.g(), "5" );
    XSTestAssertEqual
    (
        base.N(),
        removeSpaces
        (
            "0x"
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
            "E0FD108E 4B82D120 A93AD2CA FFFFFFFF FFFFFFFF"
        )
    );
}

XSTest( Base, NG4096 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG4096 );
    
    XSTestAssertEqual( base.g(), "5" );
    XSTestAssertEqual
    (
        base.N(),
        removeSpaces
        (
            "0x"
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
            "FFFFFFFF FFFFFFFF"
        )
    );
}

XSTest( Base, NG6144 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG6144 );
    
    XSTestAssertEqual( base.g(), "5" );
    XSTestAssertEqual
    (
        base.N(),
        removeSpaces
        (
            "0x"
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
            "6DCC4024 FFFFFFFF FFFFFFFF"
        )
    );
}

XSTest( Base, NG8192 )
{
    ConcreteBase base( Constants::all().front(), SRP::HashAlgorithm::SHA1, SRP::Base::GroupType::NG8192 );
    
    XSTestAssertEqual( base.g(), "19" );
    XSTestAssertEqual
    (
        base.N(),
        removeSpaces
        (
            "0x"
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
            "60C980DD 98EDD3DF FFFFFFFF FFFFFFFF"
        )
    );
}
