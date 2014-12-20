#ifndef S3DMESH_H_
#define S3DMESH_H_
#include <vector>
#include <fstream>
#include <mutex>
#include <debug_toolset.h>
#include <blit3d\Blit3D.h>

using std::string;
using std::ifstream;

struct mesh_data
{
	GLuint total_vertices = 0;
	GLuint total_indices = 0;
	float* Vertices = nullptr;
	unsigned int* Indices = nullptr;
	std::string texture_file;

	mesh_data(){}
	mesh_data( int nv, int ni, float* verts, unsigned int* indices, std::string tx )
	{
		total_vertices = nv;
		total_indices = ni;
		this->Vertices = verts;
		this->Indices = indices;
		texture_file = tx;
	}
	mesh_data( const mesh_data& ref )
	{
		total_vertices = ref.total_vertices;
		total_indices = ref.total_indices;
		this->Vertices = ref.Vertices;
		this->Indices = ref.Indices;
		texture_file = ref.texture_file;
	}
};

class mesh
{
private:
	GLSLProgram*	prog = nullptr;
	bool bStripped = false;

	mesh_data		info;
	GLuint				&total_vertices = info.total_vertices;
	GLuint				&total_indices = info.total_indices;
	float*				&Vertices = info.Vertices;
	unsigned int*	&Indices = info.Indices;
	std::string		&texture_file = info.texture_file;

	//make TWO vbo's, so we can upload indices as a seperate vbo
	GLuint vbo[2];
	GLuint vao = 0;
	GLuint tex_id = 0;

protected:
	void Load( string file_path );
	void init();
	void deinit();

	bool deleteme = false;

public:
	mesh( GLSLProgram* prog, mesh_data info, bool isStripped = true );
	~mesh();
	bool isHidden() const { return deleteme; }

	void draw( glm::mat4& modelMatrix );
};

#endif
