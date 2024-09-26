#ifndef BMPIMAGE_H
#define BMPIMAGE_H
#include <string>
#include <cstdint>
#include <vector>
class BMPImage
{
public:
    BMPImage();
    ~BMPImage();
    bool openBMP(const std::string &fileName);
    void displayBMP() const;
    void closeBMP();

private:
    std::vector<uint8_t> bmpdata;
    size_t size;
    int width;
    int height;
    uint16_t bitsCount;
};
#endif