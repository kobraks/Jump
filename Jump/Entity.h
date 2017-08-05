#pragma once

#include <map>
#include <typeindex>

namespace jump
{
	namespace component
	{
		class Component;
	}

	class Entity
	{
	public:
		Entity();
		~Entity();

		void add_component(std::type_index _type_index, component::Component* _component);

		template<class T>
		T* get_component()
		{
			auto& component = components_.find(std::type_index(typeid(T)));
			if (component != components_.end())
				return dynamic_cast<T*>(component->second);

			return nullptr;
		}

		template<class T>
		void remove_component()
		{
			auto& component = components_.find(typeid(T));
			if (component != components_.end())
			{
				delete component->second;
				//TODO remove components
			}
		}

	private:
		std::map<std::type_index, component::Component*> components_;
	};

}
