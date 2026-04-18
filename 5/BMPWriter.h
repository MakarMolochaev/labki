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

int WriteBMP(unsigned width, unsigned height, const std::vector<Color>& colorBuffer) {
    if (colorBuffer.size() != static_cast<size_t>(width) * height) {
        return -1;
    }

    std::cout << "Writing to file\n";

    int rowStride = ((width * 3 + 3) & ~3);
    size_t imageDataSize = static_cast<size_t>(rowStride) * height;

    BMPFileHeader fileHeader{};
    BMPInfoHeader infoHeader{};

    infoHeader.biWidth = static_cast<int32_t>(width);
    infoHeader.biHeight = static_cast<int32_t>(height);
    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + static_cast<uint32_t>(imageDataSize);
    infoHeader.biSizeImage = static_cast<uint32_t>(imageDataSize);

    std::vector<uint8_t> imageData(imageDataSize, 0);

    uint8_t* dst = imageData.data();

    for (unsigned y = 0; y < height; ++y) {
        const Color* srcRow = colorBuffer.data() + y * width;
        uint8_t* dstRow = dst + y * rowStride;

        for (unsigned x = 0; x < width; ++x) {
            const Color& c = srcRow[x];
            dstRow[x * 3 + 0] = static_cast<uint8_t>(c.B * 255.0f);
            dstRow[x * 3 + 1] = static_cast<uint8_t>(c.G * 255.0f);
            dstRow[x * 3 + 2] = static_cast<uint8_t>(c.R * 255.0f);
        }
    }

    std::ofstream outFile("output.bmp", std::ios::binary | std::ios::out);
    if (!outFile) return -1;

    outFile.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    outFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());

    return 0;
}