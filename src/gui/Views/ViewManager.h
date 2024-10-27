#pragma once
#include "View.h"
#include <vector>
#include <types.hpp>

class ViewManager
{
	vec2u m_viewportSize;
public:
	ViewManager();
	~ViewManager();
	void update();
	void draw();
private:
	View* m_mainView;
};
