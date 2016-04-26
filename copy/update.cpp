	bool kayboardWasUsed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = 1;

		kayboardWasUsed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -1;

		kayboardWasUsed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y = 1;

		kayboardWasUsed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (!this->collision(sf::Vector2f(0, -1), timeStep, map))
		{
			if (!this->isJumping())
			{
				acelerator -= 5;

				jumpStartHeight = this->getRectangle().getPosition().y + this->getRectangle().getSize().y;
				this->jumping(true);
			}
			else
			{
				if (this->CanJump()) acelerator--;
			}
		}
		kayboardWasUsed = true;
	}

	//Ograniczam wysokość skoku
	if (this->isJumping() &&
		this->getRectangle().getSize().y + this->getRectangle().getPosition().y < 
		jumpStartHeight - 32*2)
		this->CanJump(false);

	if (this->isJumping())
	{
		velocity.y += acelerator;

		if (velocity.y == 0) this->CanJump(false);
	}
	else
	{
		this->CanJump(true);
		acelerator = 0;
	}

	if (this->collision(sf::Vector2f(0, map->getGravityForce()), timeStep, map))
		this->CanJump(true);

	if (acelerator < -8 && acelerator < 0) acelerator = -8;
	if (acelerator > 8 && acelerator > 0) acelerator = 8;

	std::cout << "Velocity x: " << velocity.x << " y: " << velocity.y << std::endl;
	this->move(velocity, timeStep, map);

	//grawitacja
	if (this->getRectangle().getPosition().y + this->getRectangle().getSize().y < map->getGroundPosition())
	{
		if (!this->collision(sf::Vector2f(0, map->getGravityForce()), timeStep, map) &&
			!this->isJumping())
		{
			this->jumping(true);
			this->CanJump(false);
		}

		if (this->isJumping())
		{
			acelerator += map->getGravityForce();
		}
	}
	else
	{
		velocity.y = 0;
		this->jumping(false);
	}

	if (!kayboardWasUsed)
	{
		velocity.x = 0;
		this->stand();
	}
