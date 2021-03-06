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

int current_width = 1200,
	current_height = 675;
    
sf::Window* window = NULL;
sf::Clock* wclock = NULL;

string window_title = "Fun Fun Fun";
string window_title_base = "Fun Fun Fun";

vector<model> models;
vector<emitter> emitters;

double thistime, oldtime, dt, starttime;

// MASS OF CAMERA LOCATIONS (PROBABLY SHOULD JUST ADD CAMERA CONTROLS)
glm::vec3 camera_positions[25] = { glm::vec3(-2.0f,-2.0f,-2.0f), glm::vec3(-2.0f,-2.0f, 0.0f),
                                   glm::vec3(-2.0f,-2.0f, 2.0f), glm::vec3(-2.0f, 0.0f,-2.0f),
                                   glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(-2.0f, 0.0f, 2.0f),
                                   glm::vec3(-2.0f, 2.0f,-2.0f), glm::vec3(-2.0f, 2.0f, 0.0f),
                                   glm::vec3(-2.0f, 2.0f, 2.0f), glm::vec3( 0.0f,-2.0f,-2.0f),
                                   glm::vec3( 0.0f,-2.0f, 2.0f), glm::vec3( 0.0f, 0.0f,-2.0f), 
                                   glm::vec3( 0.0f, 0.0f, 2.0f), glm::vec3( 0.0f, 2.0f,-2.0f),
                                   glm::vec3( 2.0f,-2.0f,-2.0f), glm::vec3( 2.0f,-2.0f, 0.0f),
                                   glm::vec3( 2.0f,-2.0f, 2.0f), glm::vec3( 2.0f, 0.0f,-2.0f),
                                   glm::vec3( 2.0f, 0.0f, 0.0f), glm::vec3( 2.0f, 0.0f, 2.0f),
                                   glm::vec3( 2.0f, 2.0f,-2.0f), glm::vec3( 2.0f, 2.0f, 0.0f),
                                   glm::vec3( 2.0f, 2.0f, 2.0f), glm::vec3( 0.0f, 2.0f, 2.0f)  };

uint32_t selected_camera = 0;
uint32_t num_cams = 25;
uint32_t home_cam = 12;

float camera_scale = 5.0f, camera_scale_2 = 1.0f;

//glm::vec3 campos = glm::vec3(0.0,-10.0,15.0);
glm::vec3 campos = camera_positions[selected_camera] * camera_scale * camera_scale_2;//glm::vec3(0.0,-10.0,15.0);
glm::vec3 tarpos = glm::vec3(0.0,0.0,0.0);
glm::vec3 upworl = glm::vec3(0.0,1.0,0.0);

//glm::mat4 projection_matrix = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.f);
glm::mat4 projection_matrix = glm::perspective(60.0f, (float)current_width / (float)current_height, 0.1f, 1000.f);
glm::mat4 view_matrix = glm::mat4(1.0f);


// Some values for switching between models/emitters
bool on_models = true;
bool flanking = false;
int model_index = -1;
int emitter_index = -1;

uint32_t my_controller = 0;


void initialize(int& argc,char* argv[]);
void init_window();
void resize_function(const sf::Event& event);
void destroy_window();
void update_function(const double& delta_time);
void render_function();
void game_loop();
bool handle_keys(const sf::Event& event);
void spawn_panda(const char* model_file);
void spawn_emitter(const char* particle_texture_file, const double& lifespan, const uint32_t& count_or_speed, const bool& is_count);
void deactivate_unused();


int main(int argc, char* argv[])
{
	initialize(argc, argv);
    
    spawn_panda("models/panda-model.egg");
    
    // NUM PARTICLES = lifespan (seconds) * spawnspeed (particles / second)
    
    spawn_emitter("textures/particle.png", 10   , 50  , false); // 0
    spawn_emitter("textures/particle.png", 20   , 60  , false); // 1
    spawn_emitter("textures/particle.png", 30   , 70  , false); // 2
    spawn_emitter("textures/particle.png", 30   , 80  , false); // 3
    spawn_emitter("textures/particle.png", 30   , 90  , false); // 4
    spawn_emitter("textures/particle.png", 15   , 60  , false); // 5
    spawn_emitter("textures/particle.png", 30   , 60  , false); // 6
    spawn_emitter("textures/particle.png", 30   , 6000, false); // 6
    spawn_emitter("textures/particle.png", 30000, 60  , false); // 7
    
    //spawn_emitter("textures/particle.png", 10   , 10    , true); // 0
    //spawn_emitter("textures/particle.png", 10   , 100   , true); // 1
    //spawn_emitter("textures/particle.png", 10   , 1000  , true); // 2
    //spawn_emitter("textures/particle.png", 10   , 10000 , true); // 3
    //spawn_emitter("textures/particle.png", 10   , 100000, true); // 4
    
    emitters[0].set_base_color(1.0f,1.0f,1.0f,1.0f); // WHITE    (EMITTER0)
    emitters[1].set_base_color(0.0f,1.0f,0.0f,1.0f); // GREEN    (EMITTER1)
    emitters[2].set_base_color(0.0f,0.0f,1.0f,1.0f); // BLUE     (EMITTER2)
    emitters[3].set_base_color(1.0f,1.0f,0.0f,1.0f); // YELLOW   (EMITTER3)
    emitters[4].set_base_color(1.0f,0.0f,1.0f,1.0f); // Magenta  (EMITTER4)
    emitters[5].set_base_color(1.0f,1.0f,1.0f,1.0f); // WHITE    (EMITTER5)
    emitters[6].set_base_color(0.0f,1.0f,1.0f,1.0f); // CYAN     (EMITTER6)
    emitters[7].set_base_color(1.0f,1.0f,1.0f,1.0f); // WHITE    (EMITTER7)
    emitters[7].set_base_color(1.0f,1.0f,1.0f,1.0f); // WHITE    (EMITTER8)
    emitter_index = 0;
    
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	else if(event.key.code == sf::Keyboard::P)
	{
		if(!on_models && !(emitter_index < 0))
        {
            emitters[emitter_index].fade = !emitters[emitter_index].fade;
            emitters[emitter_index].switch_controller((base_emitter_control_types)my_controller);
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
    else if(event.key.code == sf::Keyboard::F)
    {
        flanking = !flanking;
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
        if(!on_models && !(emitter_index < 0) && my_controller != 0)
        {
            --my_controller;
            fprintf(stdout, "%i\n",  my_controller);
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
        campos = camera_positions[selected_camera] * camera_scale * camera_scale_2;
    }
    else if(event.key.code == sf::Keyboard::Home) {
        selected_camera = home_cam;
        campos = camera_positions[selected_camera] * camera_scale * camera_scale_2;
    }
    else if(event.key.code == sf::Keyboard::Tilde)
    {
        selected_camera = (selected_camera - 1 + num_cams) % num_cams;
        campos = camera_positions[selected_camera] * camera_scale * camera_scale_2;
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
    else if(event.key.code == sf::Keyboard::RControl)
    {
        camera_scale = (camera_scale == 5.0f) ? 10.0f : (camera_scale == 10.0f) ? 1.0f : (camera_scale == 1.0f) ? 3.0f : 5.0f;
        campos = camera_positions[selected_camera] * camera_scale * camera_scale_2;
    }
    else if(event.key.code == sf::Keyboard::BackSlash)
    {
        camera_scale_2 = (camera_scale_2 == 5.0f) ? 10.0f : (camera_scale_2 == 10.0f) ? 1.0f : (camera_scale_2 == 1.0f) ? 3.0f : 5.0f;
        campos = camera_positions[selected_camera] * camera_scale * camera_scale_2;
    }
    else if(event.key.code == sf::Keyboard::Equal)
    {
        if(!on_models)
        {
            if(!(emitter_index < 0 || emitter_index >= emitters.size()))
            {
                if(emitters[emitter_index].thickness < 8.0f) emitters[emitter_index].thickness *= 2.0f;
            }
        }
    }
    else if(event.key.code == sf::Keyboard::Dash)
    {
        if(!on_models)
        {
            if(!(emitter_index < 0 || emitter_index >= emitters.size()))
            {
                if(emitters[emitter_index].thickness > 1.0f) emitters[emitter_index].thickness /= 2.0f;
            }
        }
    }
    else if(event.key.code == sf::Keyboard::Num1)
    {
        if(!on_models && (!(emitter_index < 0 || emitter_index >= emitters.size())))
        {
            emitters[emitter_index].prev_spawn_controller();
        }
    }
    else if(event.key.code == sf::Keyboard::Num2)
    {
        if(!on_models && (!(emitter_index < 0 || emitter_index >= emitters.size())))
        {
            emitters[emitter_index].next_spawn_controller();
        }
    }
    else if(event.key.code == sf::Keyboard::Num0)
    {
        if(!on_models && (!(emitter_index < 0 || emitter_index >= emitters.size())))
        {
            //emitters[emitter_index].print_status(std::cout);
            emitters[emitter_index].print_status(std::cout, emitter_index);
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
    if(model_index < 0 && models.size() > 0) model_index = models.size() - 1;
    else if(models.size() <= 0) model_index = -1;
    else if(model_index >= models.size()) model_index = 0;
    // CHECK THAT THE "SELECTED" EMITTER IS VALID
    if(emitter_index < 0 && emitters.size() > 0) emitter_index = emitters.size() - 1;
    else if(emitters.size() <= 0) emitter_index = -1;
    else if(emitter_index >= emitters.size()) emitter_index = 0;
    
    // UPDATE WINDOW TITLE
    if(on_models)
    {
        if(!(model_index < 0))
        {
            string co_ord = "( " + float_to_string(campos.x) + " , " + float_to_string(campos.y) + " , " + float_to_string(campos.z) + " )";
            if(!models[model_index].active) window_title = window_title + " - InActive";
        }
    }
    else
    {
        if(!(emitter_index < 0))
        {
            string co_ord = "( " + float_to_string(campos.x) + " , " + float_to_string(campos.y) + " , " + float_to_string(campos.z) + " )";
            window_title = window_title_base + " - " + co_ord + " - " + int_to_string(emitter_index) + " - " + emitters[emitter_index].current_controller_name + " - " + int_to_string(emitters[emitter_index].spawn_controller);
            if(!emitters[emitter_index].active) window_title = window_title + " - InActive";
        }
    }
    
    window->setTitle(window_title);
    
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
        emitters[i].draw(view_matrix, projection_matrix, campos);
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
void spawn_emitter(const char* particle_texture_file, const double& lifespan, const uint32_t& count_or_speed, const bool& is_count)
{
    // SPAWN AN EMITTER (NO CONTROL FUNCTIONS)
    emitter e(particle_texture_file, lifespan, count_or_speed, is_count);
    e.set_spawn_radius(4.0f);
    emitters.push_back(e);
}

void deactivate_unused()
{
    int left = -1, right = -1;
    for(size_t i = 0 ; i < emitters.size(); ++i)
    {
        if(i == emitter_index)
        {
            emitters[i].active_on();
            if(flanking)
            {
                left = i - 1; right = i + 1;
                if(left < 0) left = emitters.size() - 1;
                if(right >= emitters.size()) right = 0;
            }
        }
        else
            emitters[i].active_off();
    }
    
    if(flanking)
    {
        emitters[left].active_on();
        emitters[right].active_on();
    }
}


