#include "Player.h"

#include "Items.h"
#include "Log.h"
#include "hud.h"
#include "Position.h"

#pragma region functions

namespace jump
{
	namespace objects
	{
		namespace characters
		{
			sf::Vector2f& operator/ (const sf::Vector2f& vector, const sf::Vector2f& vector2)
			{
				sf::Vector2f returned(0, 0);

				returned.x = vector.x / vector2.x;
				returned.y = vector.y / vector2.y;

				return returned;
			}

			sf::Vector2f operator/ (const sf::Vector2f& vector, const int& i)
			{
				sf::Vector2f returned;
				returned.x = vector.x / i;
				returned.y = vector.y / i;

				return returned;
			}

			const sf::Vector2f rectSize(28, 60);
			const sf::Vector2f imageSize(32, 64);
			const sf::Vector2f animationFrameSize(16, 24);
		}
	}
}

#pragma endregion

using namespace jump;
using namespace objects;
using namespace characters;

Player::Player(system::Configuration* config) : Character()
{
	this->config = config;
	this->speed = 200.f;
	this->rect.setSize(rectSize);
	this->body = NULL;

	//this->rect.setOrigin(rectSize/2);
	//this->sprite.setOrigin(imageSize/2);

	this->rect.setFillColor(sf::Color::Red);
	this->score = 0;

	lives = 3;

	numFootContacts = 0;
	jumpTimeout = 0;
}

Player::~Player()
{
}

void Player::create(b2World* world)
{
	FILE_LOG(logINFO) << "Create player";
	float32 x = this->rect.getPosition().x / map::PIXELS_IN_METERS;
	float32 y = this->rect.getPosition().y / map::PIXELS_IN_METERS;

	FILE_LOG(logDEBUG4) << "player position x: " << x << " y: " << y;
	FILE_LOG(logDEBUG4) << "SFML player position x: " << rect.getPosition().x << " y: " << rect.getPosition().y;

	//Stworzenie cia³a
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; //Dynamiczne cia³o
	bodyDef.fixedRotation = true;		   //Zakaz obracania siê
	bodyDef.allowSleep = false;		   //Nie pozwul na wy³¹czenie tego
	
	bodyDef.position.Set(x, y);

	body = world->CreateBody(&bodyDef);
	b2MassData mass;
	mass.mass = 40;
	mass.center(0);

	body->SetMassData(&mass);

	//Górna kolizja
	b2CircleShape bodyShape;
	bodyShape.m_radius = (rect.getSize().x / 2) / map::PIXELS_IN_METERS;
	bodyShape.m_p.Set(0, -(rect.getSize().x / 2) / map::PIXELS_IN_METERS);

	b2FixtureDef bodyFixDef;
	bodyFixDef.shape = &bodyShape;
	bodyFixDef.density = 1.0f;
	bodyFixDef.friction = 0.01f;

	body->CreateFixture(&bodyFixDef);

	//Dolna kolizja
	bodyShape.m_radius = (rect.getSize().x / 2) / map::PIXELS_IN_METERS;
	bodyShape.m_p.Set(0, (rect.getSize().x / 2 + 3) / map::PIXELS_IN_METERS);

	bodyFixDef.shape = &bodyShape;
	bodyFixDef.density = 1.0f;
	bodyFixDef.friction = 0.01f;

	body->CreateFixture(&bodyFixDef);

	//Kolizja nadole
	b2PolygonShape foot;
	foot.SetAsBox(0.3, 0.3, b2Vec2(0, (rect.getSize().y / 2) / map::PIXELS_IN_METERS), 0);
	bodyFixDef.isSensor = true;
	bodyFixDef.shape = &foot;

	b2Fixture* footSensorFixture = body->CreateFixture(&bodyFixDef);
	footSensorFixture->SetUserData((void*)map::Type::PLAYER_FOOT_SENSOR);

	FILE_LOG(logDEBUG4) << "Player weight: " << body->GetMass();

	body->SetUserData((void*)map::Type::PLAYER);
}

int Player::getLives()
{
	return this->lives;
}

void Player::setPosition(sf::Vector2f position)
{
	position.x *= 32;
	position.y *= 32;
	position.y -= 32;

	system::Position tmp(position);

	this->rect.setPosition(tmp.getSFPosition());
	this->sprite.setPosition(tmp.getSFPosition());
	if (this->body) this->body->SetTransform(tmp.getBox2dPosition(), this->body->GetAngle());
}

void Player::update(sf::Time& timeStep, map::Map* map)
{
	if (!busts.empty())
	{
		std::vector<int> bustsToDelete;

		for (int i = 0; i < busts.size(); i++)
		{
			busts[i]->update();
			if (!busts[i]->isStarted())
			{
				bustsToDelete.push_back(i);
			}
		}

		if (!bustsToDelete.empty()) 
		{
			for (auto element : bustsToDelete)
			{
				delete busts[element];
				busts.erase(busts.begin() + element);
			}

			bustsToDelete.clear();
		}
	}

	if (lives < 0)
	{
		this->status = Status::death;
		return;
	}

	bool keyboardWasUsed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		keyboardWasUsed = true;
		velocity.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		keyboardWasUsed = true;
		velocity.x = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		keyboardWasUsed = true;

		if (!(numFootContacts < 1) &&
			!(jumpTimeout > 0))
		{
			jumpTimeout = 15;

			velocity.y = -5;
		}

		if (jumpTimeout > 0)
			velocity.y = -5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		keyboardWasUsed = true;
		velocity.y = 1;
	}

	if (jumpTimeout >-1) jumpTimeout--;

	move(velocity, timeStep);
	if (!keyboardWasUsed) stand();

	b2Vec2 pos = body->GetPosition();

	rect.setPosition(pos.x * map::PIXELS_IN_METERS, pos.y * map::PIXELS_IN_METERS);
	sprite.setPosition(pos.x * map::PIXELS_IN_METERS, pos.y * map::PIXELS_IN_METERS);

	if (rect.getPosition().y > map->getGroundPosition())
	{
		lives--;

		this->setPosition(map->getStartPosition());
	}
}

void Player::move(sf::Vector2f& vector, sf::Time time)
{
	animation(vector, time);

	b2Vec2 v;
	v.x = vector.x * time.asSeconds() * speed;
	v.y = vector.y * time.asSeconds() * speed;

	//body->ApplyLinearImpulse(v, body->GetWorldCenter(), true);
	if (body->GetPosition().x > 0.45 || v.x >0) body->SetLinearVelocity(v);
	else if (v.y != 0) body->SetLinearVelocity(b2Vec2(0, v.y));
	vector = sf::Vector2f(0, 0);
}

void Player::animation(sf::Vector2f& vector, sf::Time& time)
{
	frameCounter += frameSpeed * time.asSeconds();

	if (frameCounter >= switchFrame)
	{
		frameCounter = 0;

		if (direction == 0 && vector.x > 0 ||
			direction == 1 && vector.x < 0 ||
			vector.x == 0)
		{
			animationStep++;
			if (animationStep * animationFrameSize.x >= texture.getSize().x) animationStep = 1;
		}

		if (direction == 0 && vector.x < 0 || direction == 1 && vector.x > 0)
		{
			if (direction == 0) direction = 1;
			else if (direction == 1) direction = 0;

			animationStep = 0;
		}
	}

	sprite.setTextureRect(sf::IntRect(animationFrameSize.x * animationStep, direction * animationFrameSize.y, animationFrameSize.x, animationFrameSize.y));
}

void Player::stand()
{
	animationStep = 0;
	sprite.setTextureRect(sf::IntRect(animationFrameSize.x * animationStep, direction * animationFrameSize.y, animationFrameSize.x, animationFrameSize.y));
}

void Player::LoadTextureFromFile(std::string fileName)
{
	if (texture.loadFromFile(fileName))
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, animationFrameSize.x, animationFrameSize.y));
		sprite.scale(sf::Vector2f(imageSize/animationFrameSize));
	}
	else
	{
		//TODO
	}
}

void Player::draw(sf::RenderWindow& window)
{
	//window.draw(rect);
	window.draw(sprite);
}

void Player::contact(map::Type typeA, map::Type typeB, b2Body* body)
{
	if (typeB == map::Type::BOX)
	{
		if (typeA == map::Type::PLAYER_FOOT_SENSOR)
		{
			numFootContacts++;
		}
	} 
	else if (typeB == map::Type::ENEMY)
	{
		lives--;
	}
	else if (typeB == map::Type::ITEM)
	{
		if (!body) return;
		other::Items* item = (other::Items*)body->GetUserData();
		switch (item->getType())
		{
		case other::Items::Type::HEART:
			if (lives < 3) lives++;
			break;
		case other::Items::Type::SPIKES:
			if (this->status != Status::imortal)
				if (canBeKilled()) lives--;
			break;
		case other::Items::Type::STAR:
			break;

		default:
			this->score += item->getValue();
			break;
		}
	}
}

bool Player::canBeKilled()
{
	if (busts.empty()) return true;
	else
	{
		for (auto bust : busts)
		{
			if (bust->getType() == system::Bust::Type::INMORTAL) return true;
		}
	}

	return false;
}

void Player::endContact(map::Type typeA, map::Type typeB, b2Body* body)
{
	if (typeB == map::Type::BOX)
	{
		if (typeA == map::Type::PLAYER_FOOT_SENSOR)
		{
			numFootContacts--;
		}
	}
}

int Player::getPoints()
{
	return this->score;
}