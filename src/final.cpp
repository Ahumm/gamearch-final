#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <GL/glew.h> //MUST come before GLFW!
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp> //feel free to use your own math library!
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model/model.h"
#include "emitter/emitter.h"
#include "utils/utils.h"

int current_width = 800,
	current_height = 450;
    
sf::Window* window = NULL;
sf::Clock* wclock = NULL;

string window_title_base = "Fun Fun Fun";
string window_title = window_title_base + " - Model0";
string window_title_old = window_title;

vector<model> models;
vector<emitter> emitters;

double thistime, oldtime, dt, starttime;

glm::vec3 camera_positions[30] = { glm::vec3(2.0f,2.0f,2.0f), glm::vec3(5.0f,5.0f,5.0f),
                                   glm::vec3(10.0f,10.0f,10.0f), glm::vec3(2.0f,-2.0f,2.0f),
                                   glm::vec3(5.0f,-5.0f,5.0f),glm::vec3(10.0f,-10.0f,10.0f), 
                                   glm::vec3(-2.0f,2.0f,2.0f), glm::vec3(-5.0f,5.0f,5.0f),
                                   glm::vec3(-10.0f,10.0f,10.0f), glm::vec3(2.0f,2.0f,-2.0f),
                                   glm::vec3(5.0f,5.0f,-5.0f), glm::vec3(10.0f,10.0f,-10.0f), 
                                   glm::vec3(-2.0f,-2.0f,2.0f), glm::vec3(-5.0f,-5.0f,5.0f),
                                   glm::vec3(-10.0f,-10.0f,10.0f), glm::vec3(-2.0f,2.0f,-2.0f), 
                                   glm::vec3(-5.0f,5.0f,-5.0f), glm::vec3(-10.0f,10.0f,-10.0f), 
                                   glm::vec3(2.0f,-2.0f,-2.0f), glm::vec3(5.0f,-5.0f,-5.0f),
                                   glm::vec3(10.0f,-10.0f,-10.0f), glm::vec3(-2.0f,-2.0f,-2.0f),
                                   glm::vec3(-5.0f,-5.0f,-5.0f), glm::vec3(-10.0f,-10.0f,-10.0f),
                                   glm::vec3(5.0f,0.0f,0.0f), glm::vec3(5.0f,5.0f,0.0f), 
                                   glm::vec3(0.0f,5.0f,0.0f), glm::vec3(0.0f,5.0f,5.0f), 
                                   glm::vec3(0.0f,0.0f,5.0f), glm::vec3(5.0f,0.0f,5.0f) };
      /*                             
glm::vec3(0.0,-10.0,15.0), glm::vec3(0.0,  0.0,15.0),
                                glm::vec3(0.0,  0.0,25.0), glm::vec3(0.0,-10.0,25.0),
                                glm::vec3(10.0,  0.0,5.0), glm::vec3(-10.0,-10.0,-10.0),
                                glm::vec3(-5.0,-5.0,-5.0), glm::vec3(2.0,2.0,2.0),
                                glm::vec3(-10.0,  0.0,5.0), glm::vec3(10.0,10.0,10.0) };
      */
uint32_t selected_camera = 2;
uint32_t num_cams = 30;

//glm::vec3 campos = glm::vec3(0.0,-10.0,15.0);
glm::vec3 campos = camera_positions[selected_camera];//glm::vec3(0.0,-10.0,15.0);
glm::vec3 tarpos = glm::vec3(0.0,0.0,0.0);
glm::vec3 upworl = glm::vec3(0.0,1.0,0.0);

//glm::mat4 projection_matrix = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.f);
glm::mat4 projection_matrix = glm::perspective(60.0f, (float)current_width / (float)current_height, 0.1f, 100.f);
glm::mat4 view_matrix = glm::mat4(1.0f);

void initialize(int& argc,char* argv[]);
void init_window();
void resize_function(const sf::Event& event);
void destroy_window();
void update_function(const double& delta_time);
void render_function();
void game_loop();
bool handle_keys(const sf::Event& event);
void spawn_panda(const char* model_file);
void spawn_emitter(const char* particle_texture_file, const double& lifespan, const uint32_t& spawn_speed);
void deactivate_unused();


// Some values for switching between models/emitters
bool on_models = true;
size_t model_index = -1;
size_t emitter_index = -1;

uint32_t my_controller = 0;

int main(int argc, char* argv[])
{
	initialize(argc, argv);

    spawn_panda("models/panda-model.egg");
    
    spawn_emitter("textures/particle.png", 100, 50);    // 0
    spawn_emitter("textures/particle.png", 10, 50);     // 1
    spawn_emitter("textures/particle.png", 300, 20);    // 2
    spawn_emitter("textures/particle.png", 300, 60);   // 3
    
    game_loop();
	
	exit(EXIT_SUCCESS);
}

void initialize(int& argc, char* argv[])
{
    srand( time( NULL ) );
    
	GLenum glew_init_result;

	init_window();
	on_gl_error("Init window");

	glewExperimental = GL_TRUE;
    glew_init_result = glewInit();
    on_gl_error("GLEW init");

	if (GLEW_OK != glew_init_result) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(glew_init_result)
		);
		exit(EXIT_FAILURE);
	}
	on_gl_error("GLEW string");
	
	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);
	on_gl_error("Get string");
	
    fprintf(
		stdout,
		"INFO: GLEW Version: %s\n",
		glewGetString(GLEW_VERSION) 
	);

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	on_gl_error("Clear color");
	glEnable(GL_DEPTH_TEST);
	on_gl_error("Depth test");
	glDepthFunc(GL_LESS);
	on_gl_error("Depth Func");
	glEnable(GL_CULL_FACE);
	on_gl_error("Enable cull face");
	glCullFace(GL_BACK);
	on_gl_error("Cull face");
	glFrontFace(GL_CCW);
	on_gl_error("Front face");
    //ViewMatrix = glm::lookAt(glm::vec3(0.0, -10.0,15.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    view_matrix = glm::lookAt(campos, tarpos, upworl);
    //ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0,0,-2));
}

void init_window()
{
	// Create the window and select it as active
    window = new sf::Window(sf::VideoMode(current_width,current_height, 32), window_title);
    wclock = new sf::Clock();
    window->setActive();
    window->display();
    window->setFramerateLimit(30);
}

void destroy_window()
{
    delete window;
    delete wclock;
}

void game_loop(){
    bool exiting = 0;
    oldtime = wclock->getElapsedTime().asMilliseconds();
    while(window->isOpen())
    {
        thistime = wclock->getElapsedTime().asMilliseconds();
        dt = thistime - oldtime;
        
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
                exiting = true;
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                exiting = handle_keys(event);
            }
            else if(event.type == sf::Event::Resized)
            {
                resize_function(event);
            }
            if(exiting)
                break;
        }
        if(exiting)
            break;
       
        // Update
        update_function(dt);
       
        // Display
        render_function();
        window->display();
        oldtime = thistime;
    }
}

bool handle_keys(const sf::Event& event)
{
    if(event.key.code == sf::Keyboard::Escape)
    {
        window->close();
        return true;
    }
    else if(event.key.code == sf::Keyboard::A)
    {
        if(on_models)
        {
            --model_index;
        }
        else
        {
            --emitter_index;
        }
    }
    else if(event.key.code == sf::Keyboard::S)
    {
        if(on_models)
        {
            ++model_index;
        }
        else
        {
            ++emitter_index;
        }
    }
    else if(event.key.code == sf::Keyboard::D)
    {
        on_models = !on_models;
    }
    else if(event.key.code == sf::Keyboard::R)
    {
        if(!on_models && !(emitter_index < 0))
        {
            emitters[emitter_index].clear_all_particles();
        }
    }
    else if(event.key.code == sf::Keyboard::Left)
    {
        if(!on_models && !(emitter_index < 0) && (base_emitter_control_types)my_controller != NO_CONTROLLER)
        {
            --my_controller;
            emitters[emitter_index].switch_controller((base_emitter_control_types)my_controller);
        }
    }
    else if(event.key.code == sf::Keyboard::Right)
    {
        if(!on_models && !(emitter_index < 0) && (base_emitter_control_types)(my_controller + 1) != ENUM_END)
        {
            ++my_controller;
            emitters[emitter_index].switch_controller((base_emitter_control_types)my_controller);
        }
    }
    else if(event.key.code == sf::Keyboard::Tab)
    {
        selected_camera = (selected_camera + 1) % num_cams;
        campos = camera_positions[selected_camera];
    }
    else if(event.key.code == sf::Keyboard::Tilde)
    {
        selected_camera = (selected_camera - 1 + num_cams) % num_cams;
        campos = camera_positions[selected_camera];
    }
    else if(event.key.code == sf::Keyboard::RShift)
    {
        if(on_models)
        {
            if(!(model_index < 0 || model_index >= models.size()))
            {
                models[model_index].rotate = !models[model_index].rotate;
            }
        }
    }
    
    return false;
}

void resize_function(const sf::Event& event)
{
    current_width = event.size.width;
    current_height = event.size.height;
    glViewport(0, 0, current_width, current_height);
}

void update_function(const double& delta_time)
{
    // CHECK THAT THE "SELECTED" MODEL IS VALID
    if(model_index < 0 && models.size() > 0) model_index = 0;
    else if(models.size() <= 0) model_index = -1;
    else if(model_index >= models.size()) model_index = models.size() - 1;
    // CHECK THAT THE "SELECTED" EMITTER IS VALID
    if(emitter_index < 0 && emitters.size() > 0) emitter_index = 0;
    else if(emitters.size() <= 0) emitter_index = -1;
    else if(emitter_index >= emitters.size()) emitter_index = emitters.size() - 1;
    
    // UPDATE WINDOW TITLE
    if(on_models)
    {
        if(!(model_index < 0))
        {
            fprintf(stdout, "1: %f ::: 2: %f ::: 3: %f \n", campos.x,campos.y,campos.z);
            string co_ord = "( " + float_to_string(campos.x) + " , " + float_to_string(campos.y) + " , " + float_to_string(campos.z) + " )";
//string co_ord = "";//"( " + int_to_string(((int)campos[0])) + " , " + int_to_string(((int)campos[1])) + " , " + int_to_string(((int)campos[3])) + " )";
            window_title = window_title_base + " - " + co_ord + " - Model" + int_to_string(model_index);
            if(!models[model_index].active) window_title = window_title + " - InActive";
        }
        else window_title = window_title_base;
    }
    else
    {
        if(!(emitter_index < 0))
        {
            string co_ord = "( " + float_to_string(campos.x) + " , " + float_to_string(campos.y) + " , " + float_to_string(campos.z) + " )";
            window_title = window_title_base + " - " + co_ord + " - Emitter" + int_to_string(emitter_index) + " - " + emitters[emitter_index].current_controller_name;
            if(!emitters[emitter_index].active) window_title = window_title + " - InActive";
        }
        else window_title = window_title_base;
    }
    
    if(window_title != window_title_old)
    {
        window->setTitle(window_title);
        window_title_old = window_title;
    }
    
    deactivate_unused();
    
    // UPDATE THE VIEW_MATRIX (FOR CHANGED CAMERA ANGLES)
    view_matrix = glm::lookAt(campos, tarpos, upworl);
    
    // UPDATE ANY ACTIVE MODELS
    for(size_t i = 0; on_models && i < models.size(); ++i)
    {
        models[i].update(delta_time);
    }
    // DRAW ANY ACTIVE EMITTERS
    for(size_t i = 0; !on_models && i < emitters.size(); ++i)
    {
        emitters[i].update(delta_time);
    }
}

void render_function()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw any active models
    for(size_t i = 0; on_models && i < models.size(); ++i)
    {
        models[i].draw(view_matrix, projection_matrix);
    }
    // Draw any active emitters
    for(size_t i = 0; !on_models && i < emitters.size(); ++i)
    {
        emitters[i].draw(view_matrix, projection_matrix);
    }
}

void spawn_panda(const char* model_file)
{
    // SPAWN A PANDA
    model p(model_file);
    p.scale(0.01f);
    models.push_back(p);
}

// SPAWN A PARTICLE EMITTER
void spawn_emitter(const char* particle_texture_file, const double& lifespan, const uint32_t& spawn_speed)
{
    // SPAWN AN EMITTER (NO CONTROL FUNCTIONS)
    emitter e(particle_texture_file, lifespan, spawn_speed);
    e.set_spawn_radius(4.0f);
    emitters.push_back(e);
}

void deactivate_unused()
{
    for(size_t i = 0 ; i < emitters.size(); ++i)
    {
        if(i != emitter_index)
            emitters[i].active_off();
        else
            emitters[i].active_on();
    }
}



