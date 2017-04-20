#ifndef PLATFORMUTILS_H
#define PLATFORMUTILS_H

#include <string>

// 定义平台相关的一些参数
namespace common {
#ifdef MAC_OS_X
	const char* TEXTURE_PATH = "/Users/yangxue/workspace/MyRoad/opengl/textures/";
	const char* SHADERS_PATH = "/Users/yangxue/workspace/MyRoad/opengl/shaders/";
#endif // MAC_OS_X

#ifdef WIN32
	const char* TEXTURE_PATH = "C:\\Workspace\\code\\money\\opengl\\textures\\";
	const char* SHADERS_PATH = "C:\\Workspace\\code\\money\\opengl\\shaders\\";
#endif // WIN32

void GetTexturePath(std::string &path, const char* filename)
{
	path.assign(TEXTURE_PATH);
	path.append(filename);
}

void GetShaderPath(std::string &path, const char* filename)
{
	path.assign(SHADERS_PATH);
	path.append(filename);
}
}





#endif
