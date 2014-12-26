#include "sprite.h"

Sprite::Sprite( GLfloat startX, GLfloat startY, GLfloat width, GLfloat height,
				std::string TextureFileName, TextureManager *TexManager, GLSLProgram *shader )
{
	dest_x = 0.f;
	dest_y = 0.f;
	angle = 0.f;
	alpha = 1.f;
	scale = 1.f;

	GLfloat halfSizeX, halfSizeY;//x,y half-dimensions of the quad

	halfSizeX = width / 2.f;
	halfSizeY = height / 2.f;

	prog = shader;

	GLfloat imagewidth, imageheight;
	textureName = TextureFileName;
	texManager = TexManager;

	//load the texture via the texture manager
	texId = texManager->LoadTexture( TextureFileName );
	if ( texId == 0 )
	{
		assert( texId != 0 );
	}

	texManager->FetchDimensions( TextureFileName, imagewidth, imageheight );

	GLfloat u1 = startX / imagewidth;
	GLfloat u2 = ( startX + width ) / imagewidth;

	GLfloat v1 = 1.f - ( startY / imageheight );
	GLfloat v2 = 1.f - ( ( startY + height ) / imageheight );


	verts = new B3D::TVertex[4]; //make an array of Textured Vertices

	// generate a new VAO and get the associated ID
	glGenVertexArrays( 1, &vaoId ); // Create our Vertex Array Object  
	glBindVertexArray( vaoId ); // Bind our Vertex Array Object so we can use it  

	// generate a new VBO and get the associated ID
	glGenBuffers( 1, &vboId );

	// bind VBO in order to use
	glBindBuffer( GL_ARRAY_BUFFER, vboId );

	//set the vertex array points...we need 4 vertices, one for each corner of our sprite, 

	/*

	0-------3
	|       |
	|       |
	|       |
	1-------2
	*/

	//front side, counterclockwise
	//point 0
	verts[0].x = -halfSizeX;				verts[0].y = halfSizeY;			verts[0].z = 0.f;
	verts[0].u = u1;	verts[0].v = v1;
	//point 1
	verts[1].x = -halfSizeX;				verts[1].y = -halfSizeY;		verts[1].z = 0.f;
	verts[1].u = u1;	verts[1].v = v2;
	//point 2
	verts[2].x = halfSizeX;					verts[2].y = -halfSizeY;		verts[2].z = 0.f;
	verts[2].u = u2;	verts[2].v = v2;
	//point 3
	verts[3].x = halfSizeX;					verts[3].y = halfSizeY;			verts[3].z = 0.f;
	verts[3].u = u2;	verts[3].v = v1;

	// upload data to VBO
	glBufferData( GL_ARRAY_BUFFER, sizeof( B3D::TVertex ) * 4, verts, GL_STATIC_DRAW );

	// Set up our vertex attributes pointers
	///we don't really need normals for 2D, except maybe for special effects.
	//We send them anyway, as we don't have special shaders for 2d mode (YET!)
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( B3D::TVertex ), BUFFER_OFFSET( 0 ) ); //3 values (x,y,z) per point, start at 0 offset 	
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( B3D::TVertex ), BUFFER_OFFSET( sizeof( GLfloat ) * 3 ) ); //Start after x,y,z data 


	// activate attribute array
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 ); //don't use channel 2
	glDisableVertexAttribArray( 3 ); //don't use Color channel, we are textured


	glBindVertexArray( 0 ); // Disable our Vertex Array Object? 
	glBindBuffer( GL_ARRAY_BUFFER, 0 );// Disable our Vertex Buffer Object

	//free the memory once it's been uploaded
	delete[] verts;
}