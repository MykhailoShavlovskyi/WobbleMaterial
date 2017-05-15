#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>


KeysBehaviour::KeysBehaviour(float pMoveSpeed, float pTurnSpeed): AbstractBehaviour(), _moveSpeed(pMoveSpeed), _turnSpeed(pTurnSpeed)
{
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update( float pStep )
{
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) 
	{
		_owner->translate(glm::vec3(0,0,-1));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_owner->translate(glm::vec3(0, 0, 1));
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_owner->rotate(glm::radians(-1.), glm::vec3(0, 1, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_owner->rotate(glm::radians(1.), glm::vec3(0, 1, 0));
	}
}
