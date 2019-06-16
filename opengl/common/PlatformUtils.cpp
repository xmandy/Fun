#include "PlatformUtils.h"

// ����ƽ̨��ص�һЩ����
namespace common {

void GetTexturePath(std::string &path, const char* filename)
{
	path.assign(TEXTURE_PATH);
	path.append(filename);
}

std::string GetTexturePath(const char* filename)
{
	std::string path(TEXTURE_PATH);
	path.append(filename);
	return path;
}

void GetShaderPath(std::string &path, const char* filename)
{
	path.assign(SHADERS_PATH);
	path.append(filename);
}

std::string GetShaderPath(const char* filename)
{
	std::string path(SHADERS_PATH);
	path.append(filename);
	return path;
}

std::string GetModelDir(const char *modelName)
{
	std::string path("");
	path.assign(MODEL_PATH);
	path += modelName;
	path += "/";
	return path;
}

std::string GetModelFilePath(const char *modelName)
{
	std::string path("");
	path.assign(MODEL_PATH);
	path += modelName;
	path += "/";
	path += modelName;
	path += ".obj";
	return path;
}

}




