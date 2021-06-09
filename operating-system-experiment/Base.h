#ifndef HEADER_BASE_H
#define HEADER_BASE_H

#ifdef _WIN32
#define CRU_WINDOWS 1
#endif

#ifdef CRU_WINDOWS
#ifdef CRU_EXPORT_API
#define CRU_API __declspec(dllexport)
#else
#define CRU_API __declspec(dllimport)
#endif
#else
#define CRU_API
#endif

#endif