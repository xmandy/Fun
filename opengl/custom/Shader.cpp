#include "Shader.h"

GLuint Shader::CreateShader(const GLchar *path, GLuint shader_type)
{
    if (path == NULL)
        return 0;
    std::string code;
    
    std::ifstream shaderFile;
	std::string prefix;
    shaderFile.exceptions(std::ifstream::badbit);
	if (shader_type == GL_GEOMETRY_SHADER)
		prefix = "Geometry Shader: ";
	else if (shader_type == GL_VERTEX_SHADER)
		prefix = "Vertex Shader: ";
	else
		prefix = "Fragement Shader: ";

    
    try {
        shaderFile.open(path);
        std::stringstream stringStream;
        stringStream << shaderFile.rdbuf();
        
        shaderFile.close();
        code = stringStream.str();
    } catch (std::ifstream::failure e) {
        std::cout<< "ERROR: SHADER file read fail!" << path << std::endl;
        return 0;
    }
    
    if (code.length() == 0)
    {
        std::cout << "Shader path: " << path << " may be wrong!" << std::endl;
        return 0;
    }
    
    const GLchar *shaderCode = code.c_str();
	
    std::cout<< std::endl<< "*************** " << prefix << " ***************" << std::endl;
    std::cout<< shaderCode << std::endl;
    std::cout<<"******************************************"<< std::endl << std::endl;
//    std::cout << shaderCode << std::endl;
    
    GLuint shaderID;
    GLint success;
    shaderID = glCreateShader(shader_type);
    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout<< "ERROR compile shader source!" << path << "----" << infoLog << std::endl;
        return 0;
    }
    return shaderID;
}

Shader::Shader()
{
	std::cout << "kkkkkkkkkkkkkkkkkkkkkkkk" << std::endl;
}


Shader::Shader(const std::string &vertexPath, const std::string &fragPath, const std::string geoPath)
{
	Initialize(vertexPath == "" ? NULL : vertexPath.c_str(), 
		fragPath == "" ? NULL : fragPath.c_str(), 
		geoPath == "" ? NULL : geoPath.c_str());
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath)
{
	Initialize(vertexPath, fragmentPath, geometryPath);
}

void Shader::Initialize(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath)
{
//	std::string vertexCode;
//	std::string fragmentCode;
//
//	;std::ifstream vShaderFile;
//	std::ifstream fShaderFile;
//
//	vShaderFile.exceptions (std::ifstream::badbit);
//	fShaderFile.exceptions (std::ifstream::badbit);
//
//	try
//	{
//		vShaderFile.open(vertexPath);
//		fShaderFile.open(fragmentPath);
//		std::stringstream vShaderStream, fShaderStream;
//		vShaderStream << vShaderFile.rdbuf();
//		fShaderStream << fShaderFile.rdbuf();
//
//		vShaderFile.close();
//		fShaderFile.close();
//
//        vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cout << "ERROR::SHADER::FILE_READ" << std::endl;
//	}
//
//	const GLchar* vShaderCode = vertexCode.c_str();
//	const GLchar* fShaderCode = fragmentCode.c_str();
//    
//    std::cout << vShaderCode << std::endl;
//    std::cout << fShaderCode << std::endl;
//
//	GLuint vertex, fragment;
//	GLint success;
//	GLchar infoLog[512];
//
//	vertex = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex, 1, &vShaderCode, NULL);
//    glCompileShader(vertex);
//    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
//        std::cout<< "ERROR++ compile vertex shader: " << infoLog << std::endl;
//    }
//    
//    fragment = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment, 1, &fShaderCode, NULL);
//    glCompileShader(fragment);
//    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
//        std::cout << "ERROR.. compile fragment shader: " << infoLog << std::endl;
//    }
//
	Program = 0;
    GLuint vertex = CreateShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragment = CreateShader(fragmentPath, GL_FRAGMENT_SHADER);
    GLuint geometry = CreateShader(geometryPath, GL_GEOMETRY_SHADER);
    Program = glCreateProgram();
	std::cout << "11111111111111 " << this << " " << Program << std::endl;
    if (vertex > 0)
        glAttachShader(Program, vertex);
    if (fragment > 0)
        glAttachShader(Program, fragment);
    if (geometry > 0)
        glAttachShader(Program, geometry);
    glLinkProgram(Program);
    
    GLint success;
    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(Program, 512, NULL, infoLog);
        std::cout << "ERROR--link program: " << infoLog << std::endl;
    }
    if (vertex > 0)
        glDeleteShader(vertex);
    if (fragment > 0)
        glDeleteShader(fragment);
    if (geometry > 0)
        glDeleteShader(geometry);

	std::cout << "22222222222 " << this << " " <<  Program << std::endl;
}

void Shader::Use()
{
    glUseProgram(Program);
}
