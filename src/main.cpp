#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <GL/glew.h> //MUST come before GLFW!
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp> //feel free to use your own math library!
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "model.h"

int CurrentWidth = 800,
	CurrentHeight = 450,
	WindowHandle = 0;
    
sf::Window* window = NULL;
sf::Clock* wclock = NULL;

vector<model> models;
//vector<emitter> emitters;

double thistime, oldtime, dt, starttime;

glm::vec3 campos = glm::vec3(0.0,-10.0,15.0);
glm::vec3 tarpos = glm::vec3(0.0,0.0,0.0);
glm::vec3 upworl = glm::vec3(0.0,1.0,0.0);

glm::mat4 projection_matrix = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.f);
glm::mat4 view_matrix = glm::mat4(1.0f);

void Initialize(int, char*[]);
void InitWindow(void);
void DestroyWindow(void);
void update_function(double & delta_time);
void RenderFunction(void);
void game_loop(void);
bool handlekeys(sf::Event event);
void OnGLError(const char* error_message);

int main(int argc, char* argv[])
{
	Initialize(argc, argv);

    game_loop();
	
	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[])
{
	GLenum GlewInitResult;

	InitWindow();
	OnGLError("Init window");

	glewExperimental = GL_TRUE;
    GlewInitResult = glewInit();
    OnGLError("GLEW init");

	if (GLEW_OK != GlewInitResult) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(GlewInitResult)
		);
		exit(EXIT_FAILURE);
	}
	OnGLError("GLEW string");
	
	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);
	OnGLError("Get string");
	
    fprintf(
		stdout,
		"INFO: GLEW Version: %s\n",
		glewGetString(GLEW_VERSION) 
	);

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	OnGLError("Clear color");
	glEnable(GL_DEPTH_TEST);
	OnGLError("Depth test");
	glDepthFunc(GL_LESS);
	OnGLError("Depth Func");
	glEnable(GL_CULL_FACE);
	OnGLError("Enable cull face");
	glCullFace(GL_BACK);
	OnGLError("Cull face");
	glFrontFace(GL_CCW);
	OnGLError("Front face");
    //ViewMatrix = glm::lookAt(glm::vec3(0.0, -10.0,15.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    ViewMatrix = glm::lookAt(campos, tarpos, upworl);
    //ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0,0,-2));
    
    // Spawn a panda
    model p = model("models/panda-model.egg");
    models.push_back(p);
}

void InitWindow(void)
{
	// Create the window and select it as active
    window = new sf::Window(sf::VideoMode(CurrentWidth,CurrentHeight, 32), "Fun Fun Fun");
    wclock = new sf::Clock();
    window->SetActive();
    window->Display();
    window->SetFramerateLimit(60);
}

void DestroyWindow(void)
{
    delete window;
    delete wclock;
}

void game_loop(void){
    bool exiting = 0;
    oldtime = wclock->GetElapsedTime().AsMilliseconds();
    while(window->IsOpen())
    {
        thistime = wclock->GetElapsedTime().AsMilliseconds();
        dt = thistime - oldtime;
        
        sf::Event event;
        while(window->PollEvent(event))
        {
            if(event.Type == sf::Event::Closed)
            {
                window->Close();
                exiting = true;
            }
            else if(event.Type == sf::Event::KeyPressed)
            {
                exiting = handlekeys(event);
            }
            if(exiting)
                break;
        }
        if(exiting)
            break;
       
        // Update
        update_function();
       
        // Display
        RenderFunction();
        window->Display();
        oldtime = thistime;
    }
}

bool handlekeys(sf::Event event)
{
    if(event.Key.Code == sf::Keyboard::Escape)
    {
        window->Close();
        return true;
    }
    if(event.Key.Code == sf::Keyboard::S)
    {
        used_program = (used_program + 1) % 2;
        if(used_program == 1) {
            glUseProgram(uberlight);
        }
        else {
            glUseProgram(nolight);
        }
        OnGLError("ERROR: Could not switch shaders");
    }
    
    return false;
}

void update_function(double & delta_time)
{
    for(size_t i = 0; i < models.size(); ++i)
    {
        models[i].update(delta_time);
    }
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(size_t i = 0; i < models.size(); ++i)
    {
        models[i].draw(view_matrix, projection_matrix);
    }
}

void OnGLError(const char* error_message)
{
	const GLenum ErrorValue = glGetError();

	if (ErrorValue != GL_NO_ERROR)
	{
		const char* APPEND_DETAIL_STRING = ": %s\n";
		const size_t APPEND_LENGTH = strlen(APPEND_DETAIL_STRING) + 1;
		const size_t message_length = strlen(error_message);
		char* display_message = (char*)malloc(message_length + APPEND_LENGTH);

		memcpy(display_message, error_message, message_length);
		memcpy(&display_message[message_length], APPEND_DETAIL_STRING, APPEND_LENGTH);

		fprintf(stderr, display_message, "");//gluErrorString(ErrorValue));
		fprintf(stdout, display_message, "");//gluErrorString(ErrorValue));

		free(display_message);
	}
}