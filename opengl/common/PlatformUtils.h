#ifndef PLATFORMUTILS_H
#define PLATFORMUTILS_H

#include <string>

// 定义平台相关的一些参数
namespace common {

	extern const char *TEXTURE_PATH;
	extern const char *SHADERS_PATH;
	extern const char *MODEL_PATH;
	extern const char *PATH_SEPARATOR;

	void GetTexturePath(std::string &path, const char* filename);
	void GetShaderPath(std::string &path, const char* filename);
	void GetModelPath(std::string &path, const char *modelName);
}
#endif
