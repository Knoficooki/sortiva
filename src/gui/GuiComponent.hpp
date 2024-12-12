#pragma once

namespace sva {

	class GuiComponent
	{
	public:
		void wndrsize(size_t width, size_t height) { m_WndWidth = width; m_WndHeight = height; onResize(); }
		virtual void onResize() {}
		virtual int draw() { if (!m_WndRunning) { return 1; } return 0; }
		virtual int input() { return 0; }

		virtual ~GuiComponent() = default;

		void attach(bool* wnd_running) { m_WndRunning = wnd_running; onAttach(); }
		virtual void onAttach() {}
	protected:
		bool* m_WndRunning = nullptr;
		size_t m_WndWidth = 0;
		size_t m_WndHeight = 0;
	};
}
