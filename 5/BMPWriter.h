#pragma once
#include "Color.h"

#include <fstream>
#include <cstdint>
#include <vector>


#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType{0x4D42};
    uint32_t bfSize{0};
    uint16_t bfReserved1{0};
    uint16_t bfReserved2{0};
    uint32_t bfOffBits{54};
};

struct BMPInfoHeader {
    uint32_t biSize{40};
    int32_t  biWidth{0};
    int32_t  biHeight{0};
    uint16_t biPlanes{1};
    uint16_t biBitCount{24};
    uint32_t biCompression{0};
    uint32_t biSizeImage{0};
    int32_t  biXPelsPerMeter{0};
    int32_t  biYPelsPerMeter{0};
    uint32_t biClrUsed{0};
    uint32_t biClrImportant{0};
};
#pragma pack(pop)

int WriteBMP(unsigned width, unsigned height, std::vector<Color> colorBuffer) {
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;

    int rowStride = (width * 3 + 3) & ~3;
    int imageDataSize = rowStride * height;
    
    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + imageDataSize;
    infoHeader.biSizeImage = imageDataSize;

    std::ofstream outFile("output.bmp", std::ios::binary);
    
    outFile.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint8_t red   = (uint8_t)(colorBuffer[y * width + x].R * 255);
            uint8_t green = (uint8_t)(colorBuffer[y * width + x].G * 255);
            uint8_t blue  = (uint8_t)(colorBuffer[y * width + x].B * 255);
            
            outFile.write(reinterpret_cast<const char*>(&blue), 1);
            outFile.write(reinterpret_cast<const char*>(&green), 1);
            outFile.write(reinterpret_cast<const char*>(&red), 1);
        }
        uint8_t padding[3] = {0, 0, 0};
        int paddingSize = rowStride - width * 3;
        if (paddingSize > 0) {
            outFile.write(reinterpret_cast<const char*>(padding), paddingSize);
        }
    }
    
    outFile.close();
    return 0;
}