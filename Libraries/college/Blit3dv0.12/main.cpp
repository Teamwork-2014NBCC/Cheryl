#include "Blit3D.h"

#include <stdio.h>
#include <conio.h>
#include <thread>

#ifdef _WIN32
	#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
		#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
		#define new DEBUG_NEW
	#endif
#endif

//GLOBAL DATA 
GLFWwindow* window;
extern Blit3D *blit3D;

extern void PreInit(void);
extern void Init();
extern void Update(float milliseconds);
extern void Draw(void);
extern void DeInit(void);
extern void DoInput(int key, int scancode, int action, int mods);
extern void Sync(void);


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
	else DoInput(key, scancode, action, mods);
}

int main () 
{
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit ()) 
	{
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 

	// uncomment these lines if on Apple OS X
	/*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	GLint samples = 8;
	glGetIntegerv(GL_SAMPLES, &samples);
	if (samples)
		printf("Context reports FSAA is available with %i samples\n", samples);
	else
		printf("Context reports FSAA is unavailable\n");

	if (samples)
	{
		printf("Requesting FSAA with %i samples\n", samples);
		glEnable(GL_MULTISAMPLE);
	}
	else
		printf("Requesting that FSAA not be available\n");

	glfwWindowHint(GLFW_SAMPLES, samples);

	PreInit();
 
	GLFWmonitor** monitors;
	int count;
  
	monitors = glfwGetMonitors(&count);
	if(count > 1) printf("%i monitors detected, running on primary one.\n", count);
	else printf("1 monitor detected.\n", count);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	if (blit3D->fullScreen) window = glfwCreateWindow (mode->width, mode->height, "Blit3D", glfwGetPrimaryMonitor(), NULL);
	else window = glfwCreateWindow(blit3D->screenWidth, blit3D->screenHeight, "Blit3D", NULL, NULL);
  
	if (!window)  
	{
    
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent (window);

	glfwSetKeyCallback(window, key_callback);
                                  
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	blit3D->Init();
	blit3D->screenHeight = mode->height;
	blit3D->screenWidth = mode->width;

	Init();

//#ifndef GL_BACK_LEFT
//	#define GL_FRONT_LEFT 0x0400
//	#define GL_FRONT_RIGHT 0x0401
//	#define GL_BACK_LEFT 0x0402
//	#define GL_BACK_RIGHT 0x0403
//	#define GL_FRONT 0x0404
//	#define GL_BACK 0x0405
//#endif
//	glDrawBuffer(GL_BACK);

	glEnable(GL_CULL_FACE); // enables face culling    
	glCullFace(GL_BACK); // tells OpenGL to cull back faces (the sane default setting)
	glFrontFace(GL_CCW); // tells OpenGL which faces are considered 'front' (use GL_CW or GL_CCW)

	glClearColor(0.0f, 0.0f , 0.0f, 0.0f);	//clear colour: r,g,b,a 
	
	double time = glfwGetTime();
	double prevTime = time;
	double elapsedTime = 0;

	glfwSwapInterval(1); //cap FPS
	//event loop
	while (!glfwWindowShouldClose (window)) 
	{
		time = (float)glfwGetTime();
		elapsedTime = time - prevTime;
		prevTime = time;

		//prog.setUniform("iGlobalTime",time);

		std::thread t1(Update, (float)elapsedTime);
		//Update((float)elapsedTime);
		
		Draw();		

		t1.join();	

		Sync();
		
		// update other events like input handling 
		glfwPollEvents ();
	}

	DeInit();

	
	// close GL context and any other GLFW resources
	glfwTerminate();
	_getch();
	return 0;
}