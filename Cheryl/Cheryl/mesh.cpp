#include <sstream>
#include <atomic>

#include "mesh.h"
#include "global.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using std::stringstream;


mesh::mesh( GLSLProgram* prog, render_data info, bool isStripped )
{
	this->info = info;
	this->prog = prog;

	bStripped = isStripped;
	this->init();
}

mesh::~mesh()
{
	deinit();
	delete Vertices;
	delete Indices;
}

void mesh::init()
{
	tex_id = get_game_engine().txtr_mgr.GetID( texture_file );

	// Generate two Vertex Buffer Object IDs
	glGenBuffers( 2, this->vbo );

	// Bind first VBO id to its purpose (Vertex Data)
	glBindBuffer( GL_ARRAY_BUFFER, this->vbo[0] );
	// We need to upload the vertex data for the buffer
	glBufferData( GL_ARRAY_BUFFER, 8 * this->total_vertices * sizeof( float ), this->Vertices, GL_STATIC_DRAW );

	///###########################################
	// We don't know how to read our Vertex Data out of the VBO
	//This section will act as an instruction manual
	glGenVertexArrays( 1, &( this->vao ) );
	glBindVertexArray( this->vao );
	///=================================
	glEnableVertexAttribArray( 0 ); //enable position attribute
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 8, NULL );//position
	///+++++++++++++++++++++++++++++++++
	glEnableVertexAttribArray( 1 ); //enable normal attribute
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 8, BUFFER_OFFSET( sizeof( float ) * 3 ) );//normal
	///+++++++++++++++++++++++++++++++++
	glEnableVertexAttribArray( 2 ); //enable texture uv attribute
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( float ) * 8, BUFFER_OFFSET( sizeof( float ) * 6 ) );//uv
	///###########################################

	// Similar process as above, but for Index data - ( ie. the order in which to draw vertices of triangles )
	// We cannot setup the Indices until after the VAO
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->vbo[1] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->total_indices * sizeof( int ), this->Indices, GL_STATIC_DRAW );
}

void mesh::deinit()
{
	//free the vbo's
	glDeleteBuffers( 2, this->vbo );
	//free the vao
	glDeleteVertexArrays( 1, &( this->vao ) );
}

void mesh::draw( glm::mat4& modelMatrix )
{
	prog->use();
	prog->setUniform( "modelMatrix", modelMatrix );

	glBindVertexArray( this->vao );
	get_game_engine().txtr_mgr.BindTexture( tex_id );

	if ( bStripped )
	{
		glDrawElements( GL_TRIANGLE_STRIP, this->total_indices, GL_UNSIGNED_INT, BUFFER_OFFSET( 0 ) );
	}
	else
	{
		glDrawElements( GL_TRIANGLES, this->total_indices, GL_UNSIGNED_INT, BUFFER_OFFSET( 0 ) );
	}
	glBindVertexArray( 0 );
}