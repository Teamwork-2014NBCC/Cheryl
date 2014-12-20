#include <sstream>
#include <atomic>

#include "mesh.h"
#include "global.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using std::stringstream;


mesh::mesh( GLSLProgram* prog, mesh_data info, bool isStripped )
{
	this->info = info;

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
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc( GL_LESS ); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */
	float halfWidth = 10 * 0.5f;
	float halfHeight = 10 * 0.5f;

	glGenBuffers( 2, this->vbo ); //make two vbo's
	glBindBuffer( GL_ARRAY_BUFFER, this->vbo[0] ); //bind first vbo
	glBufferData( GL_ARRAY_BUFFER, 8 * this->total_vertices * sizeof( float ), this->Vertices, GL_STATIC_DRAW ); //upload data to vbo #1

	glGenVertexArrays( 1, &( this->vao ) );
	glBindVertexArray( vao );
	glEnableVertexAttribArray( 0 ); //enable position attribute
	glEnableVertexAttribArray( 1 ); //enable normal attribute
	glEnableVertexAttribArray( 2 ); //enable texture uv attribute
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 8, NULL );//position
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( float ) * 8, BUFFER_OFFSET( sizeof( float ) * 3 ) );//normal
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( float ) * 8, BUFFER_OFFSET( sizeof( float ) * 6 ) );//uv

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->vbo[1] ); //bind second vbo
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->total_indices * sizeof( int ), this->Indices, GL_STATIC_DRAW ); //upload data to vbo #2

	glBindVertexArray( 0 ); // Disable our Vertex Array Object?
	glBindBuffer( GL_ARRAY_BUFFER, 0 );// Disable our Vertex Buffer Object
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );// Disable our Vertex Buffer Object

	this->prog = get_blit3d()->sManager->UseShader( "lighting.vert", "lighting.frag" ); //load/compile/link

	//2d orthographic projection
	//blit3D->projectionMatrix *= glm::ortho(0.f, (GLfloat)(blit3D->screenWidth), 0.f, (GLfloat)(blit3D->screenHeight), 0.f, 1.f);
	//glDisable(GL_DEPTH_TEST);	// Disable Depth Testing for 2D!

	glm::vec3 Kd = glm::vec3( 1.0f, 1.0f, 0.2f ); //diffuse reflectivity
	glm::vec3 Ka = glm::vec3( 0.1f, 0.1f, 0.2f ); //ambient reflectivity
	glm::vec3 Ks = glm::vec3( 1.0f, 1.0f, 1.0f ); //Specular reflectivity
	GLfloat Shininess = 1.0f; //Specular shininess factor
	//send lighting info to the shader

	this->prog->setUniform( "Kd", Kd );
	this->prog->setUniform( "Ka", Ka );
	this->prog->setUniform( "Ks", Ks );
	this->prog->setUniform( "Shininess", Shininess );

	//send alpha to the shader
	this->prog->setUniform( "in_Alpha", 1.f );

	//attributes
	this->prog->bindAttribLocation( 0, "in_Position" );
	this->prog->bindAttribLocation( 1, "in_Normal" );
	this->prog->bindAttribLocation( 2, "in_Texcoord" );

	this->prog->printActiveUniforms();
	this->prog->printActiveAttribs();

	tex_id = get_game_engine().txtr_mgr.GetID( texture_file );

	//enable blending
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
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
	this->prog = get_blit3d()->sManager->UseShader( "lighting.vert", "lighting.frag" );
	this->prog->setUniform( "modelMatrix", modelMatrix );
	this->prog->setUniform( "projectionMatrix", get_blit3d()->projectionMatrix );
	this->prog->setUniform( "viewMatrix", get_blit3d()->viewMatrix );

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