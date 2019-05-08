#pragma once

typedef void(*buildfunc)(void);

#ifdef ROCKET_LIVE_RELOADED_CODE_EXPORTS
#define ROCKET_LIVE_RELOADED_CODE_API __declspec(dllexport)
#else
#define ROCKET_LIVE_RELOADED_CODE_API __declspec(dllimport)
#endif

extern "C" ROCKET_LIVE_RELOADED_CODE_API void live_shader_rebuild(buildfunc build);
