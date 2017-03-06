#pragma once

#include <opencv2/highgui/highgui.hpp>
#include "Util.h"

namespace ogl {

	class Viewport
	{
	public:
		GLubyte *bits; //RGB bits
		GLint viewport[4]; //current viewport
		GLint width, height;

		Viewport();
		~Viewport();
	};

	class Screenshot
	{
	private:
		std::vector<Viewport*> viewports;
		bool longScreenshot_;
		std::string path;

		void takeScreenshot(Viewport* viewport, std::string fileName);

	public:
		Screenshot(bool longScreenshotInit = false) : longScreenshot_(longScreenshotInit) { }
		void startLongScreenshot();
		void stopLongScreenshot();
		void longScreenshotWatch();
		void screenshot(ImageFormat imageFormat);
	};
}
