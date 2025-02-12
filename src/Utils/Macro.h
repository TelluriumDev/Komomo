#pragma once

#ifndef KMMAPI
#ifdef KMM_EXPORT
#define KMMAPI __declspec(dllexport)
#else
#define KMMAPI __declspec(dllimport)
#endif
#endif