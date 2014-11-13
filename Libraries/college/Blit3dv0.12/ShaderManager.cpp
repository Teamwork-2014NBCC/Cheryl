#include "ShaderManager.h"

ShaderManager::~ShaderManager()
{
	for (auto item : ShaderMap)
	{
		delete item.second;
	}
}

GLSLProgram* ShaderManager::Load(const char* vertName, const char*fragName)
{
	GLSLProgram* prog = new GLSLProgram();
	
	if (!prog->compileShaderFromFile(vertName, GLSLShader::VERTEX))
	{
		printf("Vertex shader failed to compile!\n%s", prog->log().c_str());
		return NULL;
	}

	if (!prog->compileShaderFromFile(fragName, GLSLShader::FRAGMENT))
	{
		printf("Fragment shader failed to compile!\n%s", prog->log().c_str());
		return NULL;
	}

	if (!prog->link())
	{
		printf("Shader program failed to link!\n%s", prog->log().c_str());
		return NULL;
	}

	return prog;
}

GLSLProgram* ShaderManager::GetShader(const char* vertName, const char* fragName)
{
	std::string key = vertName;
	key += fragName;


	shaderIter = ShaderMap.find(key);
	if (shaderIter != ShaderMap.end())
	{
		return (shaderIter->second);
	}
	else
	{
		GLSLProgram* prog = Load(vertName, fragName);
		if (prog != NULL)
		{
			// successful loaded and linked shader program, added to map and return the result
			ShaderMap[key] = prog;
			return prog;
		}
	}

	// use default (first) shader
	return ShaderMap[0];
}

GLSLProgram* ShaderManager::UseShader(const char* vertName, const char* fragName)
{
	GLSLProgram* prog = GetShader(vertName, fragName);
	prog->use();
	return prog;
}