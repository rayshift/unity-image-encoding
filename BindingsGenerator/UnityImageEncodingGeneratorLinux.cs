using System.Reflection;
using CppSharp;
using CppSharp.AST;
using CppSharp.Generators;

namespace BindingsGenerator;

public class UnityImageEncodingGeneratorLinux : ILibrary
{
    private readonly string _libraryName;

    public UnityImageEncodingGeneratorLinux(string libraryName)
    {
        _libraryName = libraryName;
    }
    public void Preprocess(Driver driver, ASTContext ctx)
    {
        
    }

    public void Postprocess(Driver driver, ASTContext ctx)
    {
    }

    public void Setup(Driver driver)
    {
        var options = driver.Options;
        driver.ParserOptions.TargetTriple = "x86_64-linux-gnu";

        options.GeneratorKind = GeneratorKind.CSharp;
        options.OutputDir = $"../../../../{_libraryName}/Native/Linux64";
        //options.OutputDir = "../../../Bindings/Linux64";

        var module = options.AddModule("UnityImageEncodingLinux");
        
        module.OutputNamespace = $"{_libraryName}.Native.Linux64";
        module.IncludeDirs.Add("../../../../UnityImageEncoding.Native/src/include");
        module.Headers.Add("UnityImageEncoders.h");

        module.LibraryDirs.Add("../../../../UnityImageEncoding.Native/out/build/x64-linux/");
        module.Libraries.Add("libUnityImageEncoding.Native.so");

        // adjust image name
        module.SharedLibraryName = "UnityImageEncoding.Native";


        options.Verbose = true;

        Directory.CreateDirectory($"../../../../{_libraryName}/Native/");
        Directory.CreateDirectory($"../../../../{_libraryName}/Native/Linux64");

        File.Copy(Path.Combine("../../../../UnityImageEncoding.Native/out/build/x64-linux/", "libUnityImageEncoding.Native.so"), 
            Path.Combine($"../../../../{_libraryName}/Native/Linux64", "libUnityImageEncoding.Native.so"), true);
    }

    public void SetupPasses(Driver driver)
    {
    }

    public void GenerateCode(Driver driver, List<GeneratorOutput> outputs)
    {
    }
}