OBJECTS=\
  Sprite.o \
  Resource.o \
  ResourceManager.o \
  SuperSprite.o \
  MessageSprite.o \
  File.o \
  Window.o \
  InputFilter.o \
  Cotopha.o

TARGET=libCRT.so
CXXFLAGS=-fPIC -g -std=c++14

all: $(OBJECTS)
	g++ -g -shared -o $(TARGET) $(OBJECTS)

clean:
	-rm $(TARGET) $(OBJECTS)
