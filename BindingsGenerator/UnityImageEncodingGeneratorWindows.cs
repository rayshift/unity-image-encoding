using System.Reflection;
using CppSharp;
using CppSharp.AST;
using CppSharp.Generators;

namespace BindingsGenerator;

public class UnityImageEncodingGeneratorWindows : ILibrary
{

    private readonly string _libraryName;

    public UnityImageEncodingGeneratorWindows(string libraryName)
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

        var releaseType = "release";

        options.GeneratorKind = GeneratorKind.CSharp;
        options.OutputDir = $"../../../../{_libraryName}/Native/Win64";
        //options.OutputDir = "../../../Bindings/Win64";
        
        var module = options.AddModule("UnityImageEncodingWindows");
        
        module.OutputNamespace = $"{_libraryName}.Native.Win64";
        module.IncludeDirs.Add("../../../../UnityImageEncoding.Native/src/include");
        module.Headers.Add("UnityImageEncoders.h");

        module.LibraryDirs.Add($"../../../../UnityImageEncoding.Native/out/build/x64-{releaseType}/");
        module.Libraries.Add("UnityImageEncoding.Native.dll");

        module.SharedLibraryName = "UnityImageEncoding.Native.dll";

        options.Verbose = true;

        Directory.CreateDirectory($"../../../../{_libraryName}/Native/");
        Directory.CreateDirectory($"../../../../{_libraryName}/Native/Win64");

        File.Copy(Path.Combine($"../../../../UnityImageEncoding.Native/out/build/x64-{releaseType}/", "UnityImageEncoding.Native.dll"),
            Path.Combine($"../../../../{_libraryName}/Native/Win64", "UnityImageEncoding.Native.dll"), true);
    }

    public void SetupPasses(Driver driver)
    {
    }

    public void GenerateCode(Driver driver, List<GeneratorOutput> outputs)
    {
    }
}