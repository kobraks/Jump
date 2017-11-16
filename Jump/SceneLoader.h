#pragma once
#include <string>

namespace jump
{
	namespace scene
	{
		class SceneManager;

		class SceneLoader
		{
		public:
			SceneLoader(SceneManager* manager, std::string& file_name);
			~SceneLoader();
		};
	}
}
