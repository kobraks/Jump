#pragma once
#include <string>

namespace jump
{
	namespace scene
	{
		class SceneManager;

		class SceneWriter
		{
		public:
			SceneWriter(SceneManager* manager, const std::string& file_name);
			~SceneWriter();
		};
	}
}

