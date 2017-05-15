#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"
#include "mge/Slider.hpp"

Slider * speedSlider;
Slider * intensitySlider;

WobbleMaterial* wobbleMaterial;

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() 
{
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    //CAMERA
    Camera* camera = new Camera ("camera", glm::vec3(0,0,10));
    _world->add(camera);
    _world->setMainCamera(camera);

    //MESHES
	Mesh* teapotMesh = Mesh::load(config::MGE_MODEL_PATH + "teapot_smooth.obj");

    //MATERIALS
	wobbleMaterial = new WobbleMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));

    //SCENE SETUP
	GameObject* teapot = new GameObject("teapot", glm::vec3(0, 1, 0));
	teapot->setMesh(teapotMesh);
	teapot->setMaterial(wobbleMaterial);
	_world->add(teapot);
  
	//SLIDERS
	speedSlider = new Slider(glm::vec2(20, 70),"", "speed",sf::Color::Blue, _window);
	speedSlider->setValue(0.15);
	_world->add(speedSlider);
	intensitySlider = new Slider(glm::vec2(20, 120), "", "intensity",sf::Color::Blue, _window);
	intensitySlider->setValue(0.4);
	_world->add(intensitySlider);

    camera->setBehaviour(new OrbitBehaviour (8,50,1.3f, teapot, _window));
}

void MGEDemo::_render() 
{
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_updateHud()
{
	//get values from sliders
	wobbleMaterial->speed = speedSlider->getValue() * 1.9 + 0.1; //value from 0.1 to 2
	wobbleMaterial->intensity = intensitySlider->getValue() * 0.35 + 0.05; //value from 0.05 to 0.4
	
	//update hud
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";
    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
