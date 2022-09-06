// Copyright 2009 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef OPENGLSTUB_H
#define OPENGLSTUB_H

namespace OpenGLStub
{
	#define ETC_PKM_HEADER_SIZE 16

    typedef unsigned char etc1_byte;
    typedef int etc1_bool;
    typedef unsigned int etc1_uint32;

    static constexpr char kMagic[] = { 'P', 'K', 'M', ' ', '1', '0' };
    static constexpr char kMagic2[] = { 'P', 'K', 'M', ' ', '2', '0' };
    static constexpr etc1_uint32 ETC1_PKM_FORMAT_OFFSET = 6;
    static constexpr etc1_uint32 ETC1_PKM_ENCODED_WIDTH_OFFSET = 8;
    static constexpr etc1_uint32 ETC1_PKM_ENCODED_HEIGHT_OFFSET = 10;
    static constexpr etc1_uint32 ETC1_PKM_WIDTH_OFFSET = 12;
    static constexpr etc1_uint32 ETC1_PKM_HEIGHT_OFFSET = 14;

    // ETC1_RGB_NO_MIPMAPS                  0                 GL_ETC1_RGB8_OES
	// ETC2_RGB_NO_MIPMAPS                  1                 GL_COMPRESSED_RGB8_ETC2
	// ETC2_RGBA_NO_MIPMAPS_OLD             2, not used       -
	// ETC2_RGBA_NO_MIPMAPS                 3                 GL_COMPRESSED_RGBA8_ETC2_EAC
	// ETC2_RGBA1_NO_MIPMAPS                4                 GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
	// ETC2_R_NO_MIPMAPS                    5                 GL_COMPRESSED_R11_EAC
	// ETC2_RG_NO_MIPMAPS                   6                 GL_COMPRESSED_RG11_EAC
	// ETC2_R_SIGNED_NO_MIPMAPS             7                 GL_COMPRESSED_SIGNED_R11_EAC
	// ETC2_RG_SIGNED_NO_MIPMAPS            8                 GL_COMPRESSED_SIGNED_RG11_EAC
    static constexpr etc1_uint32 ETC1_RGB_NO_MIPMAPS = 0;
    static constexpr etc1_uint32 ETC2_RGB_NO_MIPMAPS = 1;
    static constexpr etc1_uint32 ETC2_RGBA_NO_MIPMAPS = 3;

    // https://android.googlesource.com/platform/frameworks/native/+/master/opengl/libs/ETC1/etc1.cpp
    static void writeBEUint16(etc1_byte* pOut, etc1_uint32 data) {
        pOut[0] = static_cast<etc1_byte>(data >> 8);
        pOut[1] = static_cast<etc1_byte>(data);
    }

    // Format a PKM header
    inline void etc1_pkm_format_header(etc1_byte* pHeader, etc1_uint32 width, etc1_uint32 height) {
        memcpy(pHeader, kMagic, sizeof(kMagic));
        const etc1_uint32 encodedWidth = (width + 3) & ~3;
        const etc1_uint32 encodedHeight = (height + 3) & ~3;
        writeBEUint16(pHeader + ETC1_PKM_FORMAT_OFFSET, ETC1_RGB_NO_MIPMAPS);
        writeBEUint16(pHeader + ETC1_PKM_ENCODED_WIDTH_OFFSET, encodedWidth);
        writeBEUint16(pHeader + ETC1_PKM_ENCODED_HEIGHT_OFFSET, encodedHeight);
        writeBEUint16(pHeader + ETC1_PKM_WIDTH_OFFSET, width);
        writeBEUint16(pHeader + ETC1_PKM_HEIGHT_OFFSET, height);
    }

    inline void etc2_rgba_pkm_format_header(etc1_byte* pHeader, etc1_uint32 width, etc1_uint32 height)
    {
        memcpy(pHeader, kMagic2, sizeof(kMagic2));
        writeBEUint16(pHeader + ETC1_PKM_FORMAT_OFFSET, ETC2_RGBA_NO_MIPMAPS);
        writeBEUint16(pHeader + ETC1_PKM_ENCODED_WIDTH_OFFSET, width);
        writeBEUint16(pHeader + ETC1_PKM_ENCODED_HEIGHT_OFFSET, height);
        writeBEUint16(pHeader + ETC1_PKM_WIDTH_OFFSET, width);
        writeBEUint16(pHeader + ETC1_PKM_HEIGHT_OFFSET, height);
    }

    inline void etc2_rgb_pkm_format_header(etc1_byte* pHeader, etc1_uint32 width, etc1_uint32 height)
    {
        memcpy(pHeader, kMagic2, sizeof(kMagic2));
        const etc1_uint32 encodedWidth = (width + 3) & ~3;
        const etc1_uint32 encodedHeight = (height + 3) & ~3;
        writeBEUint16(pHeader + ETC1_PKM_FORMAT_OFFSET, ETC2_RGB_NO_MIPMAPS);
        writeBEUint16(pHeader + ETC1_PKM_ENCODED_WIDTH_OFFSET, encodedWidth);
        writeBEUint16(pHeader + ETC1_PKM_ENCODED_HEIGHT_OFFSET, encodedHeight);
        writeBEUint16(pHeader + ETC1_PKM_WIDTH_OFFSET, width);
        writeBEUint16(pHeader + ETC1_PKM_HEIGHT_OFFSET, height);
    }

}


#endif
