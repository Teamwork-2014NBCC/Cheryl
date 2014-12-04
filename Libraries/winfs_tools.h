#include <dirent.h>
#include <assert.h>
#include <string>
#include <map>
#include <unordered_map>

using std::string;
using std::wstring;
using file_extension = string;
using stringmap = std::map<string, string>;

class dir_lister
{
	protected:
		DIR* Directory;
		string sDirpath;
		//std::vector<std::string> File_List;
		std::unordered_map<file_extension, stringmap> File_List;

		bool dirExists(string dirName_in)
		{
			DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
			if ( ftyp == INVALID_FILE_ATTRIBUTES )
				return false;  //something is wrong with your path!

			if ( ftyp & FILE_ATTRIBUTE_DIRECTORY )
				return true;   // this is a directory!

			return false;    // this is not a directory!
		}

	public:
		dir_lister(){}
		dir_lister(string path)
		{
			if ( (Directory = opendir(path.c_str())) == NULL )
			{
				//you done fucked it up
				assert("You done fucked it up. Directory is invalid");
			}
			else
			{
				this->sDirpath = path;
			}
		}

		void Set_Path(string path)
		{
			if ( (Directory = opendir(path.c_str())) == NULL )
			{
				//you done fucked it up
				assert("You done fucked it up. Directory is invalid");
			}
			else
			{
				this->sDirpath = path;
			}
		}

/*
		void Set_Path(wstring path)
		{
			if ( (Directory = opendir((char*)path.c_str())) == NULL )
			{
				//you done fucked it up
				assert("You done fucked it up. Directory is invalid");
			}
			else
			{
				this->sDirpath = std::string((char*)path.c_str());
			}
		}
/**/

		void Find_Files()
		{
			if ( Directory != NULL )
			{
				dirent *X;
				while ( (X = readdir(Directory)) != NULL )
				{
					string file_name(X->d_name);
					size_t pos = file_name.find_last_of('.');
					if ( pos != string::npos )
					{
						string file_ext(file_name.begin() + pos, file_name.end());
						File_List[file_ext][file_name] = sDirpath;
					}
					else
					{
						if ( dirExists(sDirpath + file_name) )
							File_List["directories"][file_name] = sDirpath;
						else
							File_List["file_no_ext"][file_name] = sDirpath;
					}
				}
				closedir(Directory);
			}
		}

		std::map<string, string>& Get_Files_List(string extension)
		{
			if ( File_List.size() == 0 )
			{
				Find_Files();
			}
			return File_List[extension];
		}
};
