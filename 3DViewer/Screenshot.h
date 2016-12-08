#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <time.h>
#include "Util.h"


namespace ogl {
	class Screenshot {
	private:
		GLubyte *bits_; //RGB bits
		GLint viewport_[4]; //current viewport
		GLint weidth_, height_;
		IplImage * capImg_;
		std::string type;
		std::string generateFileName()
		{
			time_t t = time(0);   // get time now
			struct tm * now = localtime(&t);

			char buffer[80];
			strftime(buffer, 80, "%Y-%m-%d-%I-%M-%S", now);
			return std::strcat(buffer, type.c_str());
		}
	public:
		void newPhoto(ImageFormat imageFormat)
		{
			//get current viewport
			glGetIntegerv(GL_VIEWPORT, this->viewport_);

			this->weidth_ = this->viewport_[2];
			this->height_ = this->viewport_[3];

			this->bits_ = new GLubyte[this->weidth_ * 3 * this->height_];

			//read pixel from frame buffer
			glFinish(); //finish all commands of OpenGL
			glPixelStorei(GL_PACK_ALIGNMENT,4);
			glPixelStorei(GL_PACK_ROW_LENGTH, 0);
			glPixelStorei(GL_PACK_SKIP_ROWS, 0);
			glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
			glReadPixels(0, 0, this->weidth_, this->height_, GL_BGR_EXT, GL_UNSIGNED_BYTE, this->bits_);

			capImg_ = cvCreateImage(cvSize(this->weidth_, this->height_), IPL_DEPTH_8U, 3);
			for (int i = 0; i < this->height_; ++i)
			{
				for (int j = 0; j < this->weidth_; ++j)
				{
					capImg_->imageData[i*capImg_->widthStep + j * 3 + 0] = (unsigned char)(this->bits_[(this->height_ - i - 1) * 3 * this->weidth_ + j * 3 + 0]);
					capImg_->imageData[i*capImg_->widthStep + j * 3 + 1] = (unsigned char)(this->bits_[(this->height_ - i - 1) * 3 * this->weidth_ + j * 3 + 1]);
					capImg_->imageData[i*capImg_->widthStep + j * 3 + 2] = (unsigned char)(this->bits_[(this->height_ - i - 1) * 3 * this->weidth_ + j * 3 + 2]);
				}
			}

			switch (imageFormat)
			{
			case PNG:
				type = ".png";
				break;
			case JPG:
				type = ".jpg";
				break;
			}

			cvSaveImage(this->generateFileName().c_str(), capImg_);
			cvReleaseImage(&capImg_);
			delete[] this->bits_;

		}
	};
}