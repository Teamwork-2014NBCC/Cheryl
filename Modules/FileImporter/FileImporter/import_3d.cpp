#include "import_3d.h"

/********************************************************
* Import method
* Imports obj files and stores it in a OBJMesh pointer
* Created by:	Mark Murphy		Date: Oct. 7, 2014
* Modified by:	Mark Murphy		Date: Oct. 14, 2014
*********************************************************/
Import::Import(std::string fileName, OBJMesh* mesh)
{
	std::string line;
	std::string newLine[3] = { "", "", "" };
	std::ifstream infile(fileName);
	float ftemp[3];
	int itemp[3];
	int smoothingGroup;

	//mesh->vertices.resize(300);
	//mesh->normals.resize(200);
	//mesh->UVs.resize(200);
	//mesh->indices.resize(300);

	if (infile.is_open())
	{
		while (!infile.eof())
		{
			infile >> line;
			//Ignore comments and white space
			if (line[0] == '#' || line[0] == ' ')
			{
				infile.ignore(256, '\n');
			}
			//Get vertices
			else if (line[0] == 'v' && line.size() == 1)
			{
				infile >> ftemp[0];
				infile >> ftemp[1];
				infile >> ftemp[2];
				mesh->vertices.push_back(new Coordinates(ftemp[0], ftemp[1], ftemp[2]));
			}
			//Get normals
			else if (line[0] == 'v' && line[1] == 'n')
			{
				infile >> ftemp[0];
				infile >> ftemp[1];
				infile >> ftemp[2];
				mesh->normals.push_back(new Coordinates(ftemp[0], ftemp[1], ftemp[2]));
			}
			//Get UVs
			else if (line[0] == 'v' && line[1] == 't')
			{
				infile >> ftemp[0];
				infile >> ftemp[1];
				infile >> ftemp[2];
				mesh->UVs.push_back(new Coordinates(ftemp[0], ftemp[1], ftemp[2]));
			}
			//Get indices
			else if (line[0] == 'f' && line.size() == 1)
			{
				//get first set of indices
				infile >> line;
				newLine[0] = "";
				newLine[1] = "";
				newLine[2] = "";
				int count = 0;
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == '/') count++;
					else newLine[count] += line[i];
				}
				itemp[0] = atoi(newLine[0].c_str()) - 1;
				itemp[1] = atoi(newLine[1].c_str()) - 1;
				itemp[2] = atoi(newLine[2].c_str()) - 1;
				mesh->indices.push_back(new Indices(mesh->vertices[itemp[0]], mesh->normals[itemp[2]], mesh->UVs[itemp[1]]));

				//get second set of indices
				infile >> line;
				newLine[0] = "";
				newLine[1] = "";
				newLine[2] = "";
				count = 0;
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == '/') count++;
					else newLine[count] += line[i];
				}
				itemp[0] = atoi(newLine[0].c_str()) - 1;
				itemp[1] = atoi(newLine[1].c_str()) - 1;
				itemp[2] = atoi(newLine[2].c_str()) - 1;
				mesh->indices.push_back(new Indices(mesh->vertices[itemp[0]], mesh->normals[itemp[2]], mesh->UVs[itemp[1]]));

				//get third set of indices
				infile >> line;
				newLine[0] = "";
				newLine[1] = "";
				newLine[2] = "";
				count = 0;
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == '/') count++;
					else newLine[count] += line[i];
				}
				itemp[0] = atoi(newLine[0].c_str()) - 1;
				itemp[1] = atoi(newLine[1].c_str()) - 1;
				itemp[2] = atoi(newLine[2].c_str()) - 1;
				mesh->indices.push_back(new Indices(mesh->vertices[itemp[0]], mesh->normals[itemp[2]], mesh->UVs[itemp[1]]));

				//get fourth set of indices
				infile.ignore();
				line = infile.peek();
				infile.unget();
				if ((line[0] >= '0') && (line[0] <= '9'))
				{
					infile >> line;
					newLine[0] = "";
					newLine[1] = "";
					newLine[2] = "";
					count = 0;
					for (int i = 0; i < line.length(); i++)
					{
						if (line[i] == '/') count++;
						else newLine[count] += line[i];
					}
					itemp[0] = atoi(newLine[0].c_str()) - 1;
					itemp[1] = atoi(newLine[1].c_str()) - 1;
					itemp[2] = atoi(newLine[2].c_str()) - 1;
					mesh->indices.push_back(new Indices(mesh->vertices[itemp[0]], mesh->normals[itemp[2]], mesh->UVs[itemp[1]]));
				}
			}

			//Get object's name
			else if (line[0] == 'g' && line.size() == 1)
			{
				infile >> line;
				mesh->objectName = line;
			}
			//Get name of material file
			else if (line[0] == 'm' && line[1] == 't')
			{
				infile >> line;
				mesh->materialName = line;
			}
			//Get material name
			else if (line[0] == 'u' && line[1] == 's')
			{
				infile >> line;
				mesh->textureName = line;
			}
		}
	}
	infile.close();
}

/********************************************************
* Import method
* Imports obj files and stores it in a OBJMesh reference
* Created by:	Mark Murphy		Date: Oct. 7, 2014
* Modified by:	Mark Murphy		Date: Oct. 14, 2014
*********************************************************/
Import::Import(std::string fileName, OBJMesh& mesh)
{
	std::string line;
	std::string newLine[3] = { "", "", "" };
	std::ifstream infile(fileName);
	float ftemp[3];
	int itemp[3];
	int smoothingGroup;

	if (infile.is_open())
	{
		while (!infile.eof())
		{
			infile >> line;
			//Ignore comments and white space
			if (line[0] == '#' || line[0] == ' ')
			{
				infile.ignore(256, '\n');
			}
			//Get vertices
			else if (line[0] == 'v' && line.size() == 1)
			{
				infile >> line;
				ftemp[0] = atof(line.c_str());
				infile >> line;
				ftemp[1] = atof(line.c_str());
				infile >> line;
				ftemp[2] = atof(line.c_str());
				mesh.vertices.push_back(new Coordinates(ftemp[0], ftemp[1], ftemp[2]));
			}
			//Get normals
			else if (line[0] == 'v' && line[1] == 'n')
			{
				infile >> line;
				ftemp[0] = atof(line.c_str());
				infile >> line;
				ftemp[1] = atof(line.c_str());
				infile >> line;
				ftemp[2] = atof(line.c_str());
				mesh.normals.push_back(new Coordinates(ftemp[0], ftemp[1], ftemp[2]));
			}
			//Get UVs
			else if (line[0] == 'v' && line[1] == 't')
			{
				infile >> line;
				ftemp[0] = atof(line.c_str());
				infile >> line;
				ftemp[1] = atof(line.c_str());
				infile >> line;
				ftemp[2] = atof(line.c_str());
				mesh.UVs.push_back(new Coordinates(ftemp[0], ftemp[1], ftemp[2]));
			}
			//Get indices
			else if (line[0] == 'f' && line.size() == 1)
			{
				//get first set of indices
				infile >> line;
				newLine[0] = "";
				newLine[1] = "";
				newLine[2] = "";
				int count = 0;
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == '/') count++;
					else newLine[count] += line[i];
				}
				itemp[0] = atoi(newLine[0].c_str()) - 1;
				itemp[1] = atoi(newLine[1].c_str()) - 1;
				itemp[2] = atoi(newLine[2].c_str()) - 1;
				mesh.indices.push_back(new Indices(mesh.vertices[itemp[0]], mesh.normals[itemp[2]], mesh.UVs[itemp[1]]));

				//get second set of indices
				infile >> line;
				newLine[0] = "";
				newLine[1] = "";
				newLine[2] = "";
				count = 0;
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == '/') count++;
					else newLine[count] += line[i];
				}
				itemp[0] = atoi(newLine[0].c_str()) - 1;
				itemp[1] = atoi(newLine[1].c_str()) - 1;
				itemp[2] = atoi(newLine[2].c_str()) - 1;
				mesh.indices.push_back(new Indices(mesh.vertices[itemp[0]], mesh.normals[itemp[2]], mesh.UVs[itemp[1]]));

				//get third set of indices
				infile >> line;
				newLine[0] = "";
				newLine[1] = "";
				newLine[2] = "";
				count = 0;
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == '/') count++;
					else newLine[count] += line[i];
				}
				itemp[0] = atoi(newLine[0].c_str()) - 1;
				itemp[1] = atoi(newLine[1].c_str()) - 1;
				itemp[2] = atoi(newLine[2].c_str()) - 1;
				mesh.indices.push_back(new Indices(mesh.vertices[itemp[0]], mesh.normals[itemp[2]], mesh.UVs[itemp[1]]));
			}
			//Get object's name
			else if (line[0] == 'g' && line.size() == 1)
			{
				infile >> line;
				mesh.objectName = line;
			}
			//Get name of material file
			else if (line[0] == 'm' && line[1] == 't')
			{
				infile >> line;
				mesh.materialName = line;
			}
			//Get material name
			else if (line[0] == 'u' && line[1] == 's')
			{
				infile >> line;
				mesh.textureName = line;
			}
		}
	}
	infile.close();
}
Import::~Import()
{
}