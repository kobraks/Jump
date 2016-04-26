	//kolizja pozioma
	if (vector.x != 0)
	{
		while (true)
		{
			auto tempPosition = rect.getPosition();

			if (vector.x > 0) x = 1;
			else if (vector.x < 0) x = -1;

			rect.move(x * speed * time.asSeconds(), 0);
			if (map->collision(rect) || rect.getPosition().x < 0)
			{
				rect.setPosition(tempPosition);
				vector.x = 0;
				break;
			}
			else sprite.move(x * speed * time.asSeconds(), 0);

			if (vector.x < 0) vector.x++;
			else if (vector.x > 0) vector.x--;

			if (vector.x == 0) break;
		}
	}

	//Kolizja pionowa
	if (vector.y != 0)
	{
		while (true)
		{
			auto tempPosition = rect.getPosition();

			if (vector.y > 0) y = 1;
			else if (vector.y < 0) y = -1;

			rect.move(0, y * speed * time.asSeconds());
			if (map->collision(rect))
			{
				rect.setPosition(tempPosition);
				//if (vector.y > 0) jump = false;
				//if (vector.y < 0) canJump = false;
				vector.y = 0;
				break;
			}
			else sprite.move(0, y * speed * time.asSeconds());

			if (vector.y < 0) vector.y++;
			else if (vector.y > 0) vector.y--;

			if (vector.y == 0) break;
		}
	}
