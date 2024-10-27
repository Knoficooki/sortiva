#include "ViewManager.h"

ViewManager::ViewManager()
{
	m_viewportSize = { GetScreenWidth(), GetScreenHeight() };
	m_mainView = new View({ 0, 0, m_viewportSize.x, m_viewportSize.y });
}

void ViewManager::update()
{
	if (IsWindowResized())
	{
		m_viewportSize = { GetScreenWidth(), GetScreenHeight() };
		m_mainView->onResize({ static_cast<float>(m_viewportSize.x), static_cast<float>(m_viewportSize.y) });
	}
	m_mainView->update();
}

void ViewManager::draw()
{
}
