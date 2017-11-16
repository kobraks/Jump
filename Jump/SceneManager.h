#pragma once
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>

namespace jump
{
	namespace entity
	{
		class Entity;
	}

	namespace scene
	{
		class SceneManager
		{
		public:
			SceneManager();
			~SceneManager();

			void add(entity::Entity* entity);

			entity::Entity* get_entity(const int& index);

			void clear();

			std::vector<entity::Entity*> get_entities() const;

			size_t size() const;
		private:
			std::vector<entity::Entity*> entities_;
		};
	}
}
