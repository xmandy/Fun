#ifndef PLATFORMUTILS_H
#define PLATFORMUTILS_H

#include <string>

// 定义平台相关的一些参数
namespace common {
#ifdef MAC_OS_X
	const char* TEXTURE_PATH = "/Users/yangxue/workspace/MyRoad/opengl/textures/";
	const char* SHADERS_PATH = "/Users/yangxue/workspace/MyRoad/opengl/shaders/";
	const char* MODEL_PATH = "/Users/yangxue/workspace/MyRoad/opengl/models/";
	const char *PATH_SEPARATOR = "/";
#endif // MAC_OS_X

#ifdef WIN32
	const char* TEXTURE_PATH = "C:\\Workspace\\code\\money\\opengl\\textures\\";
	const char* SHADERS_PATH = "C:\\Workspace\\code\\money\\opengl\\shaders\\";
	const char* MODEL_PATH = "C:\\Workspace\\code\\money\\opengl\\models\\";
	const char *PATH_SEPARATOR = "\\";
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

void GetModelPath(std::string &path, const char *modelName)
{
#ifdef WIN32
	std::string name(modelName);
	while (name.find("/") != std::string::npos)
	{
		std::string::size_type pos = name.find("/");
		name.replace(pos, 1, "\\");
	}
	path.assign(MODEL_PATH);
	path.append(name);

#endif // WIN32

#ifdef MAC_OSX
	path.assign(MODEL_PATH);
	path.append(modelName);

#endif


}


}





#endif
