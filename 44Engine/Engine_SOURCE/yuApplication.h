#pragma once
#include "yuEngine.h"
#include "yuGraphics.h"
#include "yuGraphicDevice_DX11.h"

namespace yu
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		// Running main engine loop
		void Run();
		void Release();

		void SetWindow(HWND hwnd, UINT width, UINT height);
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool initialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mHeight;
		UINT mWidth;
	};
}
