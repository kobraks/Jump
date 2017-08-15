#pragma once

namespace jump
{
	namespace system
	{
		class Console
		{
		public:
			~Console();

			static Console* get_instance();
			static void draw(const char* title, const bool* const p_open);
		private:
			Console();
			Console(Console&) = delete;
		};
	}
}
