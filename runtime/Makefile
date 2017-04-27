OBJECTS=\
  Reference.o \
  Array.o \
  Integer.o \
  Real.o \
  String.o \
  Sprite.o \
  Hash.o \
  Resource.o \
  ResourceManager.o \
  SuperSprite.o \
  MessageSprite.o \
  File.o \
  Window.o \
  InputFilter.o

TARGET=libCRT.so
CXXFLAGS=-fPIC -g

all: $(OBJECTS)
	g++ -g -shared -o $(TARGET) $(OBJECTS)

clean:
	-rm $(TARGET) $(OBJECTS)
