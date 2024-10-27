#pragma once
#include "raylib.h"
#include <types.hpp>

class View
{
	friend class ViewManager;
public:
	View(rectu rect) : m_rect(rect) {}
	virtual ~View() = default;
	virtual void draw();
	virtual void update();
	virtual void onMouseDown(vec2d mousePos) {}
	virtual void onMouseUp(vec2d mousePos) {}
	virtual void onMouseMove(vec2d mousePos) {}
	virtual void onKeyDown(int key) {}
	virtual void onKeyUp(int key) {}
	virtual void onKeyPress(int key) {}
	virtual void onFocus() {}
	virtual void onBlur() {}
	
	virtual void onResize(vec2d factor)
	{
		m_rect.width = static_cast<rectu::type>(static_cast<float>(m_rect.width) * factor.x);
		m_rect.height = static_cast<rectu::type>(static_cast<float>(m_rect.height) * factor.y);
	}

	
	
	vec2u getPosition() const { return {m_rect.x, m_rect.y}; }
	vec2u getSize() const { return {m_rect.width, m_rect.height}; }
	const rectu& getRect() const { return m_rect; }
	void setPosition(vec2u pos) { m_rect.x = pos.x; m_rect.y = pos.y; }
	void setSize(vec2u size) { m_rect.width = size.x; m_rect.height = size.y; }
	void setRect(rectu &rect) { m_rect = rect; }
	virtual void Resize(float multiplier)
	{
		m_rect.width = static_cast<rectu::type>(static_cast<float>(m_rect.width) * multiplier);
		m_rect.height = static_cast<rectu::type>(static_cast<float>(m_rect.height) * multiplier);
	}
private:
	rectu m_rect;
};
