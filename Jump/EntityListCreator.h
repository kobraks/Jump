#pragma once

namespace jump
{
	namespace utilities
	{
		class EntityListCreator
		{
		public:
			EntityListCreator();
			~EntityListCreator();
			void update();
			char** get_list() const;
			size_t get_count() const;

		private:
			char** list_;
			size_t count_;

			void clear();
		};
	}
}

