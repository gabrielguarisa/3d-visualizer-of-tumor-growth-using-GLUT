#include "Screenshot.h"

// VIEWPORT
ogl::Viewport::Viewport()
{
	//get current viewport
	glGetIntegerv(GL_VIEWPORT, this->viewport);

	this->width = this->viewport[2];
	this->height = this->viewport[3];

	this->bits = new GLubyte[this->width * 3 * this->height];

	//read pixel from frame buffer
	glFinish(); //finish all commands of OpenGL

	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glReadPixels(0, 0, this->width, this->height, GL_BGR_EXT, GL_UNSIGNED_BYTE, this->bits);
}

ogl::Viewport::~Viewport()
{
	delete[] this->bits;
}

// SCREENSHOT
void ogl::Screenshot::takeScreenshot(Viewport* viewport, std::string fileName)
{
	IplImage* _img;



	_img = cvCreateImage(cvSize(viewport->width, viewport->height), IPL_DEPTH_8U, 3);
	for (int i = 0; i < viewport->height; ++i)
	{
		for (int j = 0; j < viewport->width; ++j)
		{
			_img->imageData[i*_img->widthStep + j * 3 + 0] = (unsigned char)(viewport->bits[(viewport->height - i - 1) * 3 * viewport->width + j * 3 + 0]);
			_img->imageData[i*_img->widthStep + j * 3 + 1] = (unsigned char)(viewport->bits[(viewport->height - i - 1) * 3 * viewport->width + j * 3 + 1]);
			_img->imageData[i*_img->widthStep + j * 3 + 2] = (unsigned char)(viewport->bits[(viewport->height - i - 1) * 3 * viewport->width + j * 3 + 2]);
		}
	}

	cvSaveImage(fileName.c_str(), _img);
	cvReleaseImage(&_img);
}

void ogl::Screenshot::startLongScreenshot()
{
	if (!longScreenshot_)
	{
		longScreenshot_ = true;
	}
}

void ogl::Screenshot::stopLongScreenshot()
{
	if (longScreenshot_)
	{
		longScreenshot_ = false;
		path = "out/" + Util::getCurrentTime() + "/";
		for (int i = 0; i < viewports.size(); i++) {
			this->takeScreenshot(viewports[i], Util::generateImageFileName(static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str(), path, JPG));
		}
		viewports.clear();
	}
}

void ogl::Screenshot::longScreenshotWatch()
{
	if (longScreenshot_)
	{
		viewports.push_back(new Viewport());
	}
}

void ogl::Screenshot::screenshot(ImageFormat imageFormat)
{
	this->takeScreenshot(new Viewport(), Util::generateImageFileName(Util::getCurrentTime(), "out/", imageFormat));
}
