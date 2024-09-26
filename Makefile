CPP=g++
CFLAGS = -Wall -Wextra -Werror -std=c++17

TARGET = drawBmp

all: $(TARGET)

$(TARGET):
	$(CPP) $(CFLAGS) main.cpp bmpimage.cpp -o $(TARGET)

test: $(TARGET)
	./$(TARGET) images/chess.bmp
	./$(TARGET) images/circle.bmp