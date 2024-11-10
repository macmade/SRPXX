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

#ifndef SRPXX_TESTS_CONSTANTS_HPP
#define SRPXX_TESTS_CONSTANTS_HPP

#include <SRPXX.hpp>
#include <string>

namespace Constants
{
    inline std::string identity()
    {
        return "milford@cubicle.org";
    }
    
    inline std::string password()
    {
        return "1234";
    }
    
    inline std::vector< uint8_t > salt()
    {
        return
        {
                0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                0x16, 0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31,
                0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                0x48, 0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x62, 0x63,
                0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
                0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95,
                0x96, 0x97, 0x98, 0x99, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xB0, 0xB1,
                0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7
        };
    }
    
    inline SRP::BigNum a()
    {
        return
        {
            {
                0x71, 0x9C, 0xD0, 0x84, 0x80, 0x7E, 0x11, 0x81, 0x4F, 0x89, 0x63, 0x7B, 0x98, 0x44, 0xB2, 0x3C,
                0xA6, 0xCF, 0xC9, 0x56, 0xD0, 0xF7, 0x5F, 0xB6, 0x9D, 0x04, 0x82, 0x0D, 0x75, 0x84, 0x3A, 0xEB
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline SRP::BigNum b()
    {
        return
        {
            {
                0x1C, 0xCE, 0x3D, 0x04, 0x83, 0xE4, 0x7A, 0xB3, 0x36, 0xE3, 0x28, 0xF9, 0x8D, 0xB3, 0x77, 0xE5,
                0x3B, 0x35, 0xD4, 0x53, 0x0D, 0x06, 0x29, 0x89, 0x27, 0xCB, 0x30, 0x56, 0x6A, 0x57, 0x4C, 0x2B,
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline SRP::BigNum A()
    {
        return
        {
            {
                0x8E, 0x41, 0x51, 0xD3, 0xE6, 0xB1, 0x00, 0x95, 0x6E, 0x18, 0x84, 0x49, 0x61, 0xD5, 0xD0, 0x14,
                0xDA, 0x33, 0x08, 0xB7, 0x85, 0x18, 0xF4, 0x81, 0xCE, 0xB0, 0xEC, 0x12, 0xC3, 0x80, 0xB8, 0x69,
                0xB6, 0x41, 0x6D, 0xD9, 0x5C, 0xE5, 0x55, 0x55, 0x00, 0xA4, 0x24, 0x82, 0xA9, 0xFA, 0xC0, 0x2C,
                0x51, 0x98, 0xF6, 0xBA, 0xD7, 0x3C, 0x2A, 0xE1, 0xD5, 0x8D, 0x56, 0xE9, 0x94, 0x06, 0x2E, 0x88,
                0xCF, 0xAF, 0x4B, 0x4D, 0xA8, 0x85, 0x5A, 0x50, 0xCB, 0x66, 0xC2, 0x6D, 0x02, 0x94, 0xAC, 0x13,
                0x87, 0x28, 0xDC, 0x50, 0x0B, 0x2F, 0x4E, 0x79, 0xD0, 0xDA, 0x36, 0xA3, 0xBA, 0xD9, 0xB6, 0xCE,
                0xBC, 0x46, 0x45, 0x77, 0x64, 0xC2, 0xCE, 0xAE, 0xA5, 0x63, 0x3A, 0xD8, 0x8B, 0x84, 0x28, 0xAE,
                0x72, 0x03, 0x6B, 0xA1, 0x23, 0xC6, 0x17, 0x9B, 0xCD, 0xA4, 0xE9, 0x23, 0x92, 0x5B, 0xC9, 0x92,
                0x84, 0xC3, 0x35, 0x47, 0x2D, 0x7F, 0xC7, 0xA0, 0xFE, 0x75, 0xA9, 0x7B, 0xBA, 0x6F, 0x88, 0x23,
                0x22, 0xC0, 0xD5, 0x2C, 0xF5, 0xDE, 0x4B, 0x1A, 0xF0, 0x82, 0xF5, 0xC0, 0xAB, 0x0B, 0xC7, 0x11,
                0x7F, 0x16, 0x92, 0xBB, 0x3B, 0x4F, 0x25, 0x9D, 0xE8, 0xF6, 0x39, 0xC2, 0xE2, 0x4A, 0x97, 0xFD,
                0xEB, 0x34, 0xCC, 0x10, 0x66, 0x06, 0x82, 0x2D, 0xBB, 0x05, 0x8C, 0xEB, 0x75, 0xBD, 0xD2, 0x87,
                0x3D, 0x1A, 0x6C, 0x91, 0x4B, 0xE3, 0xC4, 0x33, 0xB6, 0x52, 0xE8, 0x7B, 0x63, 0x3B, 0x4D, 0x2F,
                0x12, 0xAB, 0xBE, 0xBD, 0xB6, 0x56, 0x8C, 0xB1, 0x42, 0x95, 0x76, 0x33, 0xAB, 0x25, 0x7C, 0xF0,
                0x53, 0x96, 0xD2, 0x80, 0xF7, 0x96, 0x6C, 0xF4, 0xE4, 0xE1, 0xD8, 0xE8, 0x3F, 0x79, 0x5E, 0xF8,
                0x59, 0xA5, 0xC6, 0x0A, 0xB1, 0x05, 0x41, 0x23, 0xE2, 0x36, 0xEE, 0x47, 0xC8, 0xD4, 0x63, 0x2C
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline SRP::BigNum B()
    {
        return
        {
            {
                0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
                0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
                0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
                0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
                0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
                0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
                0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90,
                0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80,
                0x7F, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70,
                0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60,
                0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58, 0x57, 0x56, 0x55, 0x54, 0x53, 0x52, 0x51, 0x50,
                0x4F, 0x4E, 0x4D, 0x4C, 0x4B, 0x4A, 0x49, 0x48, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40,
                0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30,
                0x2F, 0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20,
                0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10,
                0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline SRP::BigNum x()
    {
        return
        {
            {
                0x64, 0xBF, 0x4E, 0xB6, 0x98, 0xD0, 0x26, 0x6F, 0xE2, 0x09, 0x07, 0xAB, 0xDE, 0x97, 0x94, 0xFC,
                0x3A, 0xA7, 0x0F, 0xAB, 0xE3, 0x9F, 0x9F, 0xDF, 0xCB, 0x60, 0x4C, 0xB0, 0x70, 0x14, 0x71, 0xFF
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline SRP::BigNum u()
    {
        return
        {
            {
                0x2A, 0x33, 0x16, 0x24, 0xC8, 0x40, 0xF5, 0x44, 0x67, 0x2C, 0xFD, 0x96, 0x9D, 0x10, 0x34, 0xF0,
                0x00, 0xC9, 0xAD, 0x15, 0x81, 0x2F, 0x87, 0xB9, 0x20, 0x04, 0x2F, 0x68, 0x93, 0x78, 0xCE, 0x14
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline SRP::BigNum k()
    {
        return
        {
            {
                0x05, 0xB9, 0xE8, 0xEF, 0x05, 0x9C, 0x6B, 0x32, 0xEA, 0x59, 0xFC, 0x1D, 0x32, 0x2D, 0x37, 0xF0,
                0x4A, 0xA3, 0x0B, 0xAE, 0x5A, 0xA9, 0x00, 0x3B, 0x83, 0x21, 0xE2, 0x1D, 0xDB, 0x04, 0xE3, 0x00, 
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline SRP::BigNum S()
    {
        return
        {
            {
                0x69, 0xA4, 0xAF, 0x4A, 0xF7, 0xA9, 0xCA, 0x79, 0x8A, 0x6E, 0xE1, 0x0B, 0xC2, 0xB5, 0x1B, 0xF1,
                0xEA, 0x2A, 0x01, 0xCE, 0x0D, 0xAB, 0x13, 0xB4, 0xCF, 0xED, 0x7F, 0xFB, 0x48, 0x6F, 0xF8, 0xBD,
                0x2D, 0x85, 0xD5, 0x0A, 0x2C, 0x2B, 0x44, 0x81, 0x8E, 0xE3, 0x6E, 0x4B, 0xF8, 0xDA, 0x7B, 0x01,
                0xAB, 0xB3, 0x63, 0x05, 0x3A, 0xE2, 0xD3, 0x0E, 0x75, 0xC6, 0x76, 0x8C, 0x27, 0x11, 0x48, 0xB9,
                0x57, 0xFB, 0x4A, 0x15, 0xC9, 0x89, 0xB3, 0xA1, 0xC2, 0xB0, 0xD2, 0x39, 0x68, 0x6B, 0xBB, 0xB8,
                0xCD, 0x59, 0xEC, 0x92, 0x5C, 0x32, 0xED, 0x2D, 0x62, 0x8B, 0x44, 0xC2, 0x4C, 0x7B, 0xE8, 0x40,
                0xEE, 0x1E, 0xDC, 0x76, 0x99, 0x25, 0xF7, 0x53, 0xD6, 0x20, 0x03, 0xA3, 0x68, 0x50, 0xA0, 0x35,
                0xAD, 0x2E, 0x73, 0xBF, 0x56, 0x67, 0xB3, 0x91, 0xEC, 0xEF, 0x71, 0xFD, 0xFE, 0x76, 0x59, 0x87,
                0xAD, 0x74, 0x92, 0xE5, 0x43, 0xE5, 0x2B, 0xB8, 0x2D, 0x68, 0x6B, 0xBE, 0x01, 0xF8, 0xC5, 0x94,
                0x8E, 0xD4, 0xD2, 0x18, 0x17, 0x09, 0xB8, 0x8C, 0x05, 0xB8, 0xE6, 0x7E, 0x2D, 0x20, 0x03, 0x7B,
                0x1F, 0x5F, 0x0B, 0x85, 0x41, 0x66, 0x7C, 0xDF, 0xCD, 0x7C, 0xF3, 0x80, 0xFA, 0x85, 0xF2, 0x32,
                0x38, 0x1B, 0x97, 0x9E, 0x9E, 0xA5, 0xC5, 0x61, 0xF7, 0xBF, 0x7B, 0x7B, 0xA7, 0x0C, 0x01, 0xB1,
                0x19, 0x86, 0x22, 0x24, 0x99, 0xAB, 0xF0, 0x4C, 0x7F, 0x48, 0x83, 0xEB, 0x30, 0xCA, 0x08, 0xCA,
                0x87, 0x60, 0xAB, 0xD9, 0x92, 0x42, 0x2B, 0xD2, 0xA9, 0x72, 0x00, 0xDF, 0x4C, 0x45, 0xBE, 0x9A,
                0x81, 0x29, 0x21, 0xEB, 0x47, 0x1A, 0x43, 0x16, 0xDF, 0x0B, 0x16, 0x3B, 0x50, 0x7B, 0x50, 0x38,
                0x10, 0xDB, 0x02, 0xE3, 0xE5, 0xF7, 0xC5, 0x3C, 0x67, 0xE7, 0x6E, 0x22, 0x83, 0x30, 0xA7, 0x7B
            },
            SRP::BigNum::Endianness::BigEndian
        };
    }
    
    inline std::vector< uint8_t > K()
    {
        return
        {
            0x9D, 0x25, 0x80, 0x3B, 0xD2, 0xE1, 0x21, 0xF5, 0x1A, 0x41, 0x3D, 0xA7, 0x0C, 0xCD, 0x71, 0x95,
            0x30, 0x89, 0xA9, 0xC0, 0x59, 0xE5, 0x28, 0xB0, 0xF6, 0xBE, 0x12, 0x2F, 0xB8, 0x2B, 0xD0, 0x96
        };
    }
    
    inline std::vector< uint8_t > M1()
    {
        return
        {
            0xBB, 0xB1, 0xFB, 0x26, 0x69, 0xA2, 0xAE, 0x05, 0x31, 0xD8, 0x1A, 0x22, 0xF6, 0xE9, 0x10, 0x58,
            0x21, 0x4A, 0x15, 0x8D, 0x06, 0xD9, 0xF0, 0x62, 0x69, 0x8B, 0x71, 0x4E, 0x62, 0x43, 0xD1, 0x1D
        };
    }
    
    inline std::vector< uint8_t > M2()
    {
        return
        {
            0x5A, 0x8D, 0x2F, 0x65, 0x23, 0x95, 0x9F, 0x77, 0xFC, 0xC5, 0xD4, 0x40, 0x46, 0x8E, 0x15, 0x8F,
            0x55, 0x5D, 0xE8, 0x4E, 0x3B, 0x50, 0x2D, 0xE1, 0x57, 0xE7, 0xB0, 0x58, 0x1F, 0x35, 0xF6, 0xC6, 
        };
    }
    
    inline SRP::Client makeTestClient()
    {
        return { identity(), SRP::HashAlgorithm::SHA256, SRP::Client::GroupType::NG2048, a() };
    }
}

#endif /* SRPXX_TESTS_CONSTANTS_HPP */
