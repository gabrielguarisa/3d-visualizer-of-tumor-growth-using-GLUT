#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <time.h>
#include "Util.h"


namespace ogl {
	class Screenshot {
	private:
		GLubyte *bits_; //RGB bits
		GLint viewport_[4]; //current viewport
		GLint width_, height_;
		IplImage * capImg_;
		std::string type;
		std::string generateFileName();
	public:
		void newPicture(ImageFormat imageFormat = PNG);
	};
}