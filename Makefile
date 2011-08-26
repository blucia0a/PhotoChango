SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

%.o : %.cpp
	g++ -Wno-deprecated -m32 -march=i386 -c -o $@ $< -I./OpenCV.framework/Headers

all: $(OBJS)
	g++ -m32 -march=i386 -o PhotoChango $^ -L./OpenCV.framework -lOpenCV -framework CoreAudio

clean:
	-rm *.o
	-rm PhotoChango
