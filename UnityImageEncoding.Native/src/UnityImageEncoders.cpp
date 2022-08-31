#include "include/UnityImageEncoders.h"

#include <cassert>
#include <cstring>
#include <cstdlib>
#include <malloc.h>

#include "lib/opengl_stub.h"
#include "lib/etcpak/ProcessRGB.hpp"

UnityImageEncoding::UnityImageEncoding() = default;

enum EncodeType
{
	ETC1_RGB,
	ETC2_RGB,
	ETC2_RGBA
};

int EncodeETC(EncodeType type,
	const unsigned char* sourceBgra32,
	unsigned char* dest,
	unsigned int width,
	unsigned int height,
	bool addPkmHeader,
	bool dither)
{
	// safety check
	if (width > (65536) || height > (65536) || width % 4 != 0 || height % 4 != 0 || width + height < 8) return Fail;

	const size_t dataOffset = addPkmHeader ? UnityImageEncoding::GetPkmHeaderSize() : 0;

	// write header
	if (addPkmHeader) {
		switch (type)
		{
		case ETC1_RGB:
			OpenGLStub::etc1_pkm_format_header(dest, width, height);
			break;
		case ETC2_RGB:
			OpenGLStub::etc2_rgb_pkm_format_header(dest, width, height);
			break;
		case ETC2_RGBA:
			OpenGLStub::etc2_rgba_pkm_format_header(dest, width, height);
			break;
		}
	}

	const auto blockSize = width * height * 4;

	const auto blocksMultiplier = type == ETC2_RGBA ? 4 : 8;

	if (blockSize <= 0) return Fail;

	const auto srcPtr = std::malloc(blockSize);
	const auto dstPtr = std::malloc(blockSize / blocksMultiplier);

	if (srcPtr == nullptr || dstPtr == nullptr) return Fail;

	std::memcpy(srcPtr, sourceBgra32, blockSize);

	const auto srcAligned = static_cast<const uint32_t*>(srcPtr);
	const auto dstAligned = static_cast<uint64_t*>(dstPtr);

	switch (type)
	{
	case ETC1_RGB:
		if (dither) {
			CompressEtc1RgbDither(srcAligned, dstAligned, height * width / 16, width);
		}
		else
		{
			CompressEtc1Rgb(srcAligned, dstAligned, height * width / 16, width);
		}
		break;
	case ETC2_RGB:
		CompressEtc2Rgb(srcAligned, dstAligned, height * width / 16, width, false);
		break;
	case ETC2_RGBA:
		CompressEtc2Rgba(srcAligned, dstAligned, height * width / 16, width, false);
		break;
	}


	std::memcpy(dest + dataOffset, dstAligned, blockSize / blocksMultiplier);

	std::free(srcPtr);
	std::free(dstPtr);

	return Success;

}


int UnityImageEncoding::EncodeETC1(const unsigned char* sourceBgra32, 
	unsigned char* destRgb24, 
	unsigned int width, 
	unsigned int height, 
	bool dither, 
	bool addPkmHeader)
{
	return EncodeETC(EncodeType::ETC1_RGB,
		sourceBgra32,
		destRgb24,
		width,
		height,
		addPkmHeader,
		dither
		);
}

int UnityImageEncoding::EncodeETC2Alpha(const unsigned char* sourceBgra32, 
	unsigned char* destRgba32, 
	unsigned int width, 
	unsigned int height,
	bool addPkmHeader)
{
	return EncodeETC(EncodeType::ETC2_RGBA,
		sourceBgra32,
		destRgba32,
		width,
		height,
		addPkmHeader,
		false
	);
}

int UnityImageEncoding::EncodeETC2(const unsigned char* sourceBgra32,
	unsigned char* destRgb24,
	unsigned int width,
	unsigned int height,
	bool addPkmHeader)
{
	return EncodeETC(EncodeType::ETC2_RGB,
		sourceBgra32,
		destRgb24,
		width,
		height,
		addPkmHeader,
		false
	);
}



size_t UnityImageEncoding::GetPkmHeaderSize() 
{
    return ETC_PKM_HEADER_SIZE;
}
