#ifndef _TEXTURE_MGR_H_
#define _TEXTURE_MGR_H_

#define TEXTURE_MANAGER_MAX_TEXTURES 31

//Platform Specific
#include <Windows.h>

//Third Party / Tool box
#include <winfs_tools.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FreeImage.h>

//C++ STL
#include <unordered_set>
#include <map>

using texid = GLuint;
extern std::wstring execution_path;

namespace coope
{
	struct tex
	{
		texid ID;
		bool unload;
		unsigned int refcount;
		unsigned int width, height;
	};
}

class File_Manager
{
	private:
		static dir_lister& Get()
		{
			static dir_lister Singleton_Dir_Lister;
			return Singleton_Dir_Lister;
		}
		static std::unordered_set<std::string>& Get_Loaded()
		{
			static std::unordered_set<std::string> Singleton_Loaded_List;
			return Singleton_Loaded_List;
		}

	protected:
	public:
		/*static void Register_Directory(std::wstring path)
		{
			if ( Get_Loaded().emplace(path).second )
			{
				Get().Set_Path(path);
				Get().Find_Files();
			}
		}*/
		static void Register_Directory(std::string path)
		{
			if ( Get_Loaded().emplace(path).second )
			{
				Get().Set_Path(path);
				Get().Find_Files();
			}
		}
		static stringmap& Get_Files(std::string extension)
		{
			return Get().Get_Files_List(extension);
		}
};

class Texture_Manager
{
	private:
		std::map<std::string, texid> file_map;
		std::map<std::string, texid>::iterator file_itor;

		std::map<texid, coope::tex*> texture_map;
		std::map<texid, coope::tex*>::iterator texture_itor;

		GLuint Bound_IDs[TEXTURE_MANAGER_MAX_TEXTURES];// = { -1 }; //currently bound texture
		bool useMipMaps = true;

	public:
		Texture_Manager()
		{
			//nothing
		}
		~Texture_Manager()
		{
			for ( auto itor : texture_map )
			{
				delete itor.second;
			}
		}
		void Init();
		//void Unload_DirFiles(std::string path);
		void LoadAll();
		void LoadTexture(std::string file, std::string path);
		GLuint GetID(std::string File, bool count_increase = true);

		void FreeTexture(GLuint texid);
		void BindTexture(GLuint texid, GLuint texture_unit = GL_TEXTURE0);
};

#endif
