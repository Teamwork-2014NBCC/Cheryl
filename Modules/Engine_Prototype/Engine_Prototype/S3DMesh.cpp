#include "S3DMesh.h"
#include "global.h"

/****************************************************
* Import method
* Imports a S3D file
* Created by:	Mark Murphy		Date: Oct. 8, 2014
* Modified by:	Mark Murphy		Date: Oct. 14, 2014
*****************************************************
void S3DMesh::Import(std::string fileName)
{
meshName = fileName;
std::string line;

auto file_map = File_Manager::Get_Files(".s3d");
auto file_ref = file_map.find(fileName);
if ( file_ref != file_map.end() )
{
std::ifstream infile(file_ref->second + file_ref->first);
if ( infile.is_open() )
{
infile >> line;
numVerts = atoi(line.c_str());
verts = new float[numVerts*8];

for ( int i = 0; i < numVerts * 8; i++ )
{
infile >> verts[i];
}

infile >> line;
numIndices = atoi(line.c_str());
indices = new int[numIndices];
for ( int i = 0; i < numIndices; i++ )
{
infile >> indices[i];
}

infile >> line;
textureName = line;
infile.close();
}
}
}*/

/****************************************************
* Update method
* Updates mesh
* Created by:	Mark Murphy		Date: Oct. 8, 2014
* Modified by:	Mark Murphy		Date: Oct. 8, 2014
*****************************************************/
void S3DMesh::Update( double milliseconds )
{
}

/****************************************************
* Draw method
* Draws to screen
* Created by:	Mark Murphy		Date: Oct. 8, 2014
* Modified by:	Josh Cooper		Date: Dec. 4, 2014
*****************************************************/
void S3DMesh::Draw()
{
	float time = ( float )glfwGetTime();

	glBindVertexArray( vao );

	modelMatrix = glm::mat4( 1.f ) * translation_Matrix * rotation_Matrix * scale_Matrix;
	//prog = blit3D->sManager->UseShader("shader.vert", "shader.frag");
	prog->setUniform( "modelMatrix", modelMatrix );

	prog->setUniform( "Kd", Kd );
	prog->setUniform( "Ka", Ka );
	prog->setUniform( "Ks", Ks );
	prog->setUniform( "Shininess", Shininess );

	get_game_engine().txtr_mgr.BindTexture( texID );
	// draw points 0-4 from the currently bound VAO with current in-use shader
	if ( bStripped ) glDrawElements( GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_INT, BUFFER_OFFSET( 0 ) );
	else glDrawElements( GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, BUFFER_OFFSET( 0 ) );
	//=================================
}

/****************************************************
* Transform method
* Used to translate model
* Created by:	Mark Murphy		Date: Oct. 30, 2014
* Modified by:	Mark Murphy		Date: Oct. 30, 2014
*****************************************************/
void S3DMesh::Transform( float x, float y, float z )
{
	translation_Matrix = glm::translate( glm::mat4( 1.f ), glm::vec3( x, y, z ) );
}

/****************************************************
* Rotate method
* Used to rotate model
* Created by:	Mark Murphy		Date: Oct. 30, 2014
* Modified by:	Mark Murphy		Date: Oct. 30, 2014
*****************************************************/
void S3DMesh::Rotate( float angle, float x, float y, float z )
{
	rotation_Matrix = glm::rotate( glm::mat4( 1.f ), angle, glm::vec3( x, y, z ) );
}

/****************************************************
* Scale method
* Used to scale model
* Created by:	Mark Murphy		Date: Oct. 30, 2014
* Modified by:	Mark Murphy		Date: Nov. 4, 2014
*****************************************************/
void S3DMesh::Scale( float x, float y, float z )
{
	scale_Matrix = glm::scale( glm::mat4( 1.f ), glm::vec3( x, y, z ) );
}

/****************************************************
* S3DMesh constructer
* Sets initial values
* Created by:	Mark Murphy		Date: Oct. 8, 2014
* Modified by:	Josh Cooper		Date: Dec. 4, 2014
*****************************************************/
S3DMesh::S3DMesh( Texture_Manager& txt_mgr, GLSLProgram* prog, mesh_data info, bool isStripped )
{
	this->prog = prog;

	numVerts = info.numVerts;
	numIndices = info.numIndices;
	verts = info.verts;
	indices = info.indices;
	textureName = info.textureName;

	bStripped = isStripped;

	modelMatrix = glm::mat4( 1.f );
	scale_Matrix = glm::mat4( 1.f );
	rotation_Matrix = glm::mat4( 1.f );
	translation_Matrix = glm::mat4( 1.f );

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc( GL_LESS ); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */
	//float halfWidth = blit3D->screenWidth * 0.5f;
	//float halfHeight = blit3D->screenHeight * 0.5f;
	float halfWidth = 10 * 0.5f;
	float halfHeight = 10 * 0.5f;

	glGenBuffers( 2, vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, numVerts * 8 * sizeof( float ), verts, GL_STATIC_DRAW );

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( float )* 8, NULL );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( float )* 8, BUFFER_OFFSET( sizeof( float )* 3 ) );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( float )* 8, BUFFER_OFFSET( sizeof( float )* 6 ) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo[1] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof( GLuint ), indices, GL_STATIC_DRAW );
	//unbind vao + both vbo

	glBindVertexArray( 0 ); // Disable our Vertex Array Object?
	glBindBuffer( GL_ARRAY_BUFFER, 0 );// Disable our Vertex Buffer Object
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );// Disable our Vertex Buffer Object

	Kd = glm::vec3( 1.0f, 1.0f, 0.2f ); //diffuse reflectivity
	Ka = glm::vec3( 0.1f, 0.1f, 0.2f ); //ambient reflectivity
	Ks = glm::vec3( 1.0f, 1.0f, 1.0f ); //Specular reflectivity
	Shininess = 1.0f; //Specular shininess factor

	//modelMatrix = glm::mat4(1.f);

	//2d orthographic projection
	//blit3D->projectionMatrix *= glm::ortho(0.f, (GLfloat)(blit3D->screenWidth), 0.f, (GLfloat)(blit3D->screenHeight), 0.f, 1.f);
	//glDisable(GL_DEPTH_TEST);	// Disable Depth Testing for 2D!
	//3d perspective projection

	//send alpha to the shader
	this->prog->setUniform( "in_Alpha", 1.f );

	//attributes
	this->prog->bindAttribLocation( 0, "in_Position" );
	this->prog->bindAttribLocation( 1, "in_Normal" );
	this->prog->bindAttribLocation( 2, "in_Texcoord" );

	this->prog->printActiveUniforms();
	this->prog->printActiveAttribs();

	texID = txt_mgr.GetID( textureName );

	//enable blending
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

/****************************************************
* S3DMesh deconstructor
* Releases memory
* Created by:	Mark Murphy		Date: Oct. 8, 2014
* Modified by:	Mark Murphy		Date: Oct. 8, 2014
*****************************************************/
S3DMesh::~S3DMesh()
{
	delete[] verts;
	delete[] indices;

	get_game_engine().txtr_mgr.FreeTexture( texID );
	//free the vbo's
	glDeleteBuffers( 2, vbo );
	//free the vao
	glDeleteVertexArrays( 1, &vao );
}