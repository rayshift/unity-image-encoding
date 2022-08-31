using System.Runtime.CompilerServices;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

#if Windows
using ETCEncodingDemo.Native.Win64;
#else
using ETCEncodingDemo.Native.Linux64;
#endif

namespace ETCEncodingDemo;

public class ETCEncoder<TPixel> where TPixel : unmanaged, IPixel<TPixel>
{
    private readonly byte[] _image;
    private readonly int _width;
    private readonly int _height;

    public ETCEncoder(Image<TPixel> sourceImage)
    {
        _width = sourceImage.Width;
        _height = sourceImage.Height;
        byte[] pixels = new byte[_width * _height * Unsafe.SizeOf<Bgra32>()];

        if (typeof(TPixel) != typeof(Bgra32)) // no need to duplicate if correct type
        {
            var bgraPixels = sourceImage.CloneAs<Bgra32>();
            bgraPixels.CopyPixelDataTo(pixels);
            bgraPixels.Dispose();
        }
        else
        {
            sourceImage.CopyPixelDataTo(pixels);
        }


        _image = pixels;
    }

    public unsafe void ConvertToETC1(Stream outputStream, bool dither, bool writePkmHeader)
    {
        byte[] outputBuffer = new byte[(_width * _height / 2) + (int)(writePkmHeader ? UnityImageEncoding.PkmHeaderSize : 0)];
        byte[] inputBuffer = _image;

        fixed (byte* outputPtr = outputBuffer)
        {
            fixed (byte* inputPtr = inputBuffer)
            {
                var code = UnityImageEncoding.EncodeETC1(inputPtr, outputPtr, (uint)_width, (uint)_height, dither, writePkmHeader);
                if (code != 0)
                    throw new Exception($"ETC1 Encoder returned status code {code}.");
            }
        }

        outputStream.Write(outputBuffer);
    }

    public unsafe void ConvertToETC2Alpha(Stream outputStream, bool writePkmHeader)
    {
        byte[] outputBuffer = new byte[(_width * _height) + (int)(writePkmHeader ? UnityImageEncoding.PkmHeaderSize : 0)];
        byte[] inputBuffer = _image;

        fixed (byte* outputPtr = outputBuffer)
        {
            fixed (byte* inputPtr = inputBuffer)
            {
                var code = UnityImageEncoding.EncodeETC2Alpha(inputPtr, outputPtr, (uint)_width, (uint)_height, writePkmHeader);
                if (code != 0)
                    throw new Exception($"ETC2A Encoder returned status code {code}.");
            }
        }

        outputStream.Write(outputBuffer);
    }

    public unsafe void ConvertToETC2(Stream outputStream, bool writePkmHeader)
    {
        byte[] outputBuffer = new byte[(_width * _height / 2) + (int)(writePkmHeader ? UnityImageEncoding.PkmHeaderSize : 0)];
        byte[] inputBuffer = _image;

        fixed (byte* outputPtr = outputBuffer)
        {
            fixed (byte* inputPtr = inputBuffer)
            {
                var code = UnityImageEncoding.EncodeETC2(inputPtr, outputPtr, (uint)_width, (uint)_height, writePkmHeader);
                if (code != 0)
                    throw new Exception($"ETC2 Encoder returned status code {code}.");
            }
        }

        outputStream.Write(outputBuffer);
    }
}