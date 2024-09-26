#include <iostream>
#include "bmpimage.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_bmp_file>" << std::endl;
        return 1;
    }

    BMPImage bmpImage;
    if (!bmpImage.openBMP(argv[1]))
    {
        return 1;
    }

    bmpImage.displayBMP();
    bmpImage.closeBMP();

    return 0;
}