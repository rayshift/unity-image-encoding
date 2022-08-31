// See https://aka.ms/new-console-template for more information

using BindingsGenerator;
using CppSharp;

var applicationName = "ETCEncodingDemo";

ConsoleDriver.Run(new UnityImageEncodingGeneratorLinux(applicationName));
ConsoleDriver.Run(new UnityImageEncodingGeneratorWindows(applicationName));
