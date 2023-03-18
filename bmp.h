#include "main.h"
#include "string.h"
#include <iostream>

using std::cout;
using std::endl;

struct HEADERIMAGEINFO
{
    int32_t strSize;
    int32_t width;
    int32_t height;
};

class bmpImage
{
private:
    pixelBuf Bufer;

    int32_t fSize;
    int32_t bitPos;
    int32_t strSize;
    int32_t width;
    int32_t height;

public:
    bmpImage(const char *filename)
    {
        FILE *img = fopen(filename, "rb");
        unsigned char *imgHeader = new unsigned char[54];
        fread(imgHeader, sizeof(unsigned char), 54, img);
        fSize = *reinterpret_cast<int32_t *>(&imgHeader[2]);
        bitPos = *reinterpret_cast<int32_t *>(&imgHeader[10]);
        strSize = *reinterpret_cast<int32_t *>(&imgHeader[14]);
        width = *reinterpret_cast<int32_t *>(&imgHeader[18]);
        height = *reinterpret_cast<int32_t *>(&imgHeader[22]);

        unsigned char *imgBuf = new unsigned char[fSize];
        fread(imgBuf, sizeof(unsigned char), fSize, img);
        int j = 0;
        for (int i = fSize; i > bitPos; i -= 3)
        {
            cout << ((static_cast<int>(imgBuf[i]) > 127)?1:0) << " ";
            if (i % (3 * width) == bitPos){
                j++;
                cout<<"\n";
            }
        }
        cout << "size = " << fSize << "pos = " << bitPos << " strsize = " << strSize << " w = " << width << " h = " << height <<" j = "<<j<< endl;
    }
};
