#ifndef UNITYIMAGEENCODERS_H
#define UNITYIMAGEENCODERS_H

#include "ExportAPI.h"
#include <stddef.h>

class EXPORT_API UnityImageEncoding
{
public:
	UnityImageEncoding();
	static int EncodeETC1(const unsigned char* sourceBgra32,
		unsigned char* destRgb24, 
		unsigned int width,
		unsigned int height, 
		bool dither = true, 
		bool addPkmHeader = false);

	static int EncodeETC2Alpha(const unsigned char* sourceBgra32, 
		unsigned char* destRgba32, 
		unsigned int width, 
		unsigned int height,
		bool addPkmHeader = false);

	static int EncodeETC2(const unsigned char* sourceBgra32,
		unsigned char* destRgb24,
		unsigned int width,
		unsigned int height,
		bool addPkmHeader = false);

	static size_t GetPkmHeaderSize();
};

enum EncodeReturnCode
{
	Fail = -1,
	Success = 0
};
#endif