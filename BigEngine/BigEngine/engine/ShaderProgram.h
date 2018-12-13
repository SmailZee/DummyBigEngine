#pragma once
#include "string"
namespace Big
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();
		enum ShaderType
		{Vertex,
		 Fragment
		};

		bool Create();
		void Destroy();
		void Use();
		bool LoadShader(const std::string& uri, ShaderType shaderType);

	private:
		unsigned int handle;
		bool CheckShadeError(unsigned int shader);
		bool CheckProgramError();

	};
}

