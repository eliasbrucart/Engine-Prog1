#ifndef EXPORT_H

#ifdef ENGINE_EXPORT

#define ENGINE_API __declspec(dllimport)

#else

#define ENGINE_API __declspec(dllexport)

#endif // ENGINE_EXPORT

#endif // !EXPORT_H
