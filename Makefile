CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
INCLUDES = -I/opt/homebrew/include -I/opt/homebrew/opt/glew/include -I/opt/homebrew/opt/glfw/include -I/opt/homebrew/opt/glm/include
LDFLAGS = -L/opt/homebrew/lib -L/opt/homebrew/opt/glew/lib -L/opt/homebrew/opt/glfw/lib
LIBS = -lGLEW -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

TARGET = black_hole_2D
SOURCE = black_hole_2D.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCE) -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean 