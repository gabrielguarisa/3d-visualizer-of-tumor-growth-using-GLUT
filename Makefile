CXX = g++
CXXFLAGS = -m64 -g -Wall -w
SRCS = Cell.cpp CellFactory.cpp Render.cpp Screenshot.cpp GlutWindow.cpp main.cpp
FOLDER = 3DViewer/
BUILD_FOLDER = build/
PROG = $(BUILD_FOLDER)main.exe
CPP_FILES := $(wildcard $(FOLDER)*.cpp)
OBJ_FILES := $(addprefix $(BUILD_FOLDER),$(notdir $(CPP_FILES:.cpp=.o)))

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = -lglut -lGLU -lGL
LIBS += $(OPENCV)

$(PROG):$(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(PROG) $^ $(LIBS)

$(BUILD_FOLDER)%.o: $(FOLDER)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ $(LIBS)

run:
	$(PROG)

clean:
	rm -f $(PROG) $(BUILD_FOLDER)*.o
