#ifndef EXPORTAPI_H
#define EXPORTAPI_H

#ifdef WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

#endif