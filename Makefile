CXX = g++
CXXFLAGS = -std=c++11 -m64 -g -Wall -w
SRCS = Cell.cpp CellFactory.cpp Render.cpp Screenshot.cpp GlutWindow.cpp main.cpp
FOLDER = src/
BUILD_FOLDER = build/
PROG = $(BUILD_FOLDER)main.exe
CPP_FILES := $(wildcard $(FOLDER)*.cpp)
OBJ_FILES := $(addprefix $(BUILD_FOLDER),$(notdir $(CPP_FILES:.cpp=.o)))

OPENCV = -I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
LIBS = -lglut -lGLU -lGL -lGLEW
LIBS += $(OPENCV)

$(PROG):$(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(PROG) $^ $(LIBS)

$(BUILD_FOLDER)%.o: $(FOLDER)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ $(LIBS)

run:
	$(PROG)

clean:
	rm -f $(PROG) $(BUILD_FOLDER)*.o
