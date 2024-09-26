#include "bmpimage.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <windows.h>

using namespace std;

BMPImage::BMPImage() : size(0), width(0), height(0), bitsCount(0) {}

BMPImage::~BMPImage()
{
    closeBMP();
}

bool BMPImage::openBMP(const string &fileName)
{
    ifstream file(fileName, ios::binary);
    if (!file.is_open())
    {
        cout << "File " << fileName << " not found!" << endl;
        return false;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    file.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != 0x4D42)
    {
        cerr << "Not a BMP file" << endl;
        return false;
    }

    file.read(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32)
    {
        cerr << "Unsupported bit depth" << endl;
        return false;
    }

    width = infoHeader.biWidth;
    height = infoHeader.biHeight;
    bitsCount = infoHeader.biBitCount;

    if (infoHeader.biSizeImage == 0)
    {
        size = ((width * bitsCount + 31) / 32) * 4 * height;
    }
    else
    {
        size = infoHeader.biSizeImage;
    }

    bmpdata.resize(size);

    file.seekg(fileHeader.bfOffBits, ios::beg);

    file.read(reinterpret_cast<char *>(bmpdata.data()), size);

    file.close();
    return true;
}

void BMPImage::closeBMP()
{

    bmpdata.clear();
}

void BMPImage::displayBMP() const
{
    if (bmpdata.empty())
    {
        cout << "Bitmap is not open" << endl;
        return;
    }

    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            const size_t index = (y * width + x) * (bitsCount / 8);
            const uint8_t blue = bmpdata[index];
            const uint8_t green = bmpdata[index + 1];
            const uint8_t red = bmpdata[index + 2];

            if (red == 0 && green == 0 && blue == 0)
            {
                cout << '#';
            }
            else if (red == 255 && green == 255 && blue == 255)
            {
                cout << ' ';
            }
            else
            {
                cout << '?';
            }
        }
        cout << endl;
    }
}