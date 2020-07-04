// IT8951Demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../IT8951Lib/pch.h"
#include "../IT8951Lib/dllmain.cpp"

int main()
{
    BYTE retCode = 1;
    BYTE status = 1;
    status = Open();

    if (status != 0)
    {
        UINT32 info[28];
        BYTE infoSize = GetDeviceInfo(info);
        if (infoSize > 7)
        {
            
            LOAD_IMG_AREA area;

            //x,y,w,h最好按4字节对齐(32bits)

            area.iX = 0;
            area.iY = 0;
            area.iW = info[4];
            area.iH = info[5];
            //ASSERT(area.iX % 4 == 0);//4字节对齐
            //ASSERT(area.iY % 4 == 0);//4字节对齐
            //ASSERT(area.iW % 4 == 0);//4字节对齐
            //ASSERT(area.iH % 4 == 0);//4字节对齐
            area.iAddress = info[7];
            INT32 buffLength = area.iW * area.iH;
            BYTE* img = (BYTE*)malloc(buffLength);
            memset(img, 255, buffLength);//全部设置为白色
            for (INT32 y = 300; y < area.iH; y++)
            {
                for (INT32 x = 300; x < area.iW; x++)
                {
                    img[y * area.iW + x] = 0x00;
                }
            }
            status = SendImage(img, area.iAddress, area.iX, area.iY, area.iW, area.iH);
            if (status!=0)
            {
                status = RenderImage(area.iAddress, area.iX, area.iY, area.iW, area.iH);
                //status = RenderImage(area.iAddress, 600, 600, area.iW - 600, area.iH-600);
                if (status != 0)
                {
                    retCode = 0;
                }
            }
            else
            {
                Erase(area.iAddress, area.iW * area.iH);
            }
        }
        Close();
    }


    std::cout << "Hello World!\n";

    return retCode;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
