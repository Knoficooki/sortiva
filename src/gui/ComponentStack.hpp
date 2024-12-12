#pragma once
#include <vector>
#include <memory>
#include "GuiComponent.hpp"

class ComponentStack final
{
	inline static std::vector < std::shared_ptr<sva::GuiComponent> > s_Components;

public:
	inline static bool* s_WndRunning;
	inline static size_t s_WndWidth, s_WndHeight;

	template<typename T, typename ...Args> requires std::is_base_of_v<sva::GuiComponent, T>
	static std::shared_ptr<T> push(Args&&... args)
	{
		std::shared_ptr<T> comp = std::make_shared<T>(std::forward<Args>(args)...);

		s_Components.push_back(comp);
		comp->wndrsize(s_WndWidth, s_WndHeight);
		comp->attach(s_WndRunning);

		return comp;
	}

	static int run()
	{
		for (std::shared_ptr<sva::GuiComponent>& component : s_Components)
		{
			int r = component->input();
			if (r != 0) return r;
			r = component->draw();
			if (r != 0) return r;
		}
		return 0;
	}

	static void resize()
	{
		for (auto& comp : s_Components)
		{
			comp->wndrsize(s_WndWidth, s_WndHeight);
		}
	}
};