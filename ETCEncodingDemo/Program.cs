using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Drawing;
using SixLabors.ImageSharp.PixelFormats;
using SixLabors.ImageSharp.Processing;
using SixLabors.ImageSharp.Drawing.Processing;
using SixLabors.ImageSharp.Formats.Jpeg;

namespace ETCEncodingDemo
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Running ETC demo.");

            using var image = new Image<Rgba32>(512, 256);

            // Example drawing
            image.Mutate(x => x.BackgroundColor(new Rgba32(255, 255, 255, 50))); // fill with white background
            DrawingOptions options = new()
            {
                GraphicsOptions = new()
                {
                    ColorBlendingMode = PixelColorBlendingMode.Multiply
                }
            };

            var grad = new LinearGradientBrush(new PointF(0f, 0f), new PointF(0f, 128f), GradientRepetitionMode.None,
                new ColorStop[]
                {
                    new ColorStop(0f, Color.Red),
                    new ColorStop(0.5f, Color.Green),
                    new ColorStop(1.0f, Color.Blue)
                });

            image.Mutate(m => m.Draw(options, grad, 128, RectangleF.FromLTRB(0, 0, 512, 128)));


            IBrush brush = Brushes.Horizontal(Color.Red, Color.Blue);
            IPen pen = Pens.DashDot(Color.Green, 5);
            IPath yourPolygon = new Star(x: 61f, y: 60.0f, prongs: 3, innerRadii: 25.0f, outerRadii: 55.0f);

            // Draws a star with horizontal red and blue hatching with a dash dot pattern outline.
            image.Mutate(x => x.Fill(options, brush, yourPolygon)
                .Draw(options, pen, yourPolygon));

            // Draw taiga
            var taiga = SixLabors.ImageSharp.Image.Load(File.OpenRead("images/taiga.jpg"),
                new JpegDecoder());

            taiga.Mutate(o => o.Resize(390, 256, KnownResamplers.Lanczos3));
            image.Mutate(m => m.DrawImage(taiga, new Point(512-390, 0), 1f));


            // Save as .png
            image.SaveAsPng("demo_output_png.png");

            // write ETC1
            Console.WriteLine("Encoding ETC1.");
            var file = File.OpenWrite("demo_output_etc1.pkm");
            ETCEncoder<Rgba32> encoder = new ETCEncoder<Rgba32>(image);
            encoder.ConvertToETC1(file, true, true); 
            file.Close();

            // write ETC2 alpha
            Console.WriteLine("Encoding ETC2 (alpha).");
            var file2 = File.OpenWrite("demo_output_etc2a.pkm");
            encoder.ConvertToETC2Alpha(file2, true);
            file2.Close();

            // write ETC2
            Console.WriteLine("Encoding ETC2.");
            var file3 = File.OpenWrite("demo_output_etc2.pkm");
            encoder.ConvertToETC2(file3, true);
            file3.Close();

            Console.WriteLine("Finished.");
        }
    }
}