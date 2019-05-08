#include "R3_ShaderBuild.h"

#include <cstdio>

#include "../Rocket3d/ShaderManager.h"


void live_shader_rebuild(buildfunc build)
{
	buildfunc buildShaders;
	printf("Hot Compiling Shaders...\n");
	buildShaders = build;
	buildShaders();
}