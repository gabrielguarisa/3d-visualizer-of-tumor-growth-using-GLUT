#pragma once

#include <opencv2/highgui/highgui.hpp>
#include "Util.h"

namespace ogl {
	class Screenshot
	{
	public:
		static void takeScreenshot(std::string filename);
	};
}
