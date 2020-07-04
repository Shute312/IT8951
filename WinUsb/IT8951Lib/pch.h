// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

#define BIGENDIAN (htons(1) == 1)

// 添加要在此处预编译的标头
#include "framework.h"
//
//
//#include "Ntddscsi.h"
//#include "winioctl.h"
//#include "IT8951UsbCmd.h"
//#include "winbase.h"
//#include "Ntddscsi.h"
//#include "winioctl.h"
//
//
//#define SPT_BUF_SIZE  (60*1024)//(2048)
//
//	static HANDLE hDev = NULL;
//
//	static BYTE gSPTDataBuf[SPT_BUF_SIZE + 1024];
//
//	static DWORD gulPanelW = 1600;
//	static DWORD gulPanelH = 1200;
//
//
//
//
//    //IT8951 USB Op Code - Fill this code to CDB[6]
//#define IT8951_USB_OP_GET_SYS      0x80
//#define IT8951_USB_OP_READ_MEM     0x81
//#define IT8951_USB_OP_WRITE_MEM    0x82
//#define IT8951_USB_OP_READ_REG     0x83
//#define IT8951_USB_OP_WRITE_REG    0x84
//
//#define IT8951_USB_OP_DPY_AREA     0x94
//
//#define IT8951_USB_OP_USB_SPI_ERASE 0x96 //Eric Added
//#define IT8951_USB_OP_USB_SPI_READ  0x97
//#define IT8951_USB_OP_USB_SPI_WRITE 0x98
//
//#define IT8951_USB_OP_LD_IMG_AREA  0xA2
//#define IT8951_USB_OP_PMIC_CTRL    0xA3
//#define IT8951_USB_OP_IMG_CPY      0xA4 //Not used in Current Version(IT8961 Samp only)
//#define IT8951_USB_OP_FSET_TEMP    0xA4
//
////#define IT8951_USB_OP_FAST_WRITE_MEM 0xA5
////	#define EN_FAST_WRITE_MEM
//
//
//#define PANEL_W  gulPanelW//1024//1600
//#define PANEL_H  gulPanelH//758//1200
//
////*****************************************************
////  Structure of Get Device Information（112bytes）
////*****************************************************
//    typedef struct _TRSP_SYSTEM_INFO_DATA
//    {
//        UINT32 uiStandardCmdNo; // Standard command number2T-con Communication Protocol
//        UINT32 uiExtendCmdNo; // Extend command number
//        UINT32 uiSignature; // 31 35 39 38h (8951)
//        UINT32 uiVersion; // command table version
//        UINT32 uiWidth; // Panel Width
//        UINT32 uiHeight; // Panel Height
//        UINT32 uiUpdateBufBase; // Update Buffer Address
//        UINT32 uiImageBufBase; // Image Buffer Address(default image buffer)
//        UINT32 uiTemperatureNo; // Temperature segment number
//        UINT32 uiModeNo; // Display mode number
//        UINT32 uiFrameCount[8]; // Frame count for each mode(8).
//        UINT32 uiNumImgBuf;//Numbers of Image buffer
//        UINT32 uiWbfSFIAddr;//这里跟文档有些变化源文档是保留9个字节，这里是1+8
//        UINT32 uiReserved[8];
//
//        void* lpCmdInfoDatas[1]; // Command table pointer
//    } TRSP_SYSTEM_INFO_DATA;
//
//    //--------------------------------------------------------
//    //    Display Area
//    //--------------------------------------------------------
//
//    typedef struct  _TDRAW_UPD_ARG_DATA
//    {
//        INT32     iMemAddr;
//        INT32     iWavMode;
//        //INT32     iAlpha;
//        INT32     iPosX;
//        INT32     iPosY;
//        INT32     iWidth;
//        INT32     iHeight;
//        INT32     iEngineIndex;
//    } TDRAW_UPD_ARG_DATA;
//    typedef TDRAW_UPD_ARG_DATA  TDrawUPDArgData;
//    typedef TDrawUPDArgData* LPDrawUPDArgData;
//
//    //--------------------------------------------------------
//    //    Load Image Area
//    //--------------------------------------------------------
//    typedef struct _LOAD_IMG_AREA_
//    {
//        INT32     iAddress;
//        INT32     iX;
//        INT32     iY;
//        INT32     iW;
//        INT32     iH;
//    } LOAD_IMG_AREA;
//    //--------------------------------------------------------
//    //    PMIC Control
//    //--------------------------------------------------------
//    typedef struct _PMIC_CTRL_
//    {
//        unsigned short usSetVComVal;
//        unsigned char  ucDoSetVCom;
//        unsigned char  ucDoPowerSeqSW;
//        unsigned char  ucPowerOnOff;
//        unsigned char  ucReserved[3];
//
//
//    }T_PMIC_CTRL;
//    //--------------------------------------------------------
//    //    Forece Set/Get Temperature Control
//    //--------------------------------------------------------
//    typedef struct
//    {
//        unsigned char ucSetTemp;
//        unsigned char ucTempVal;
//
//    }T_F_SET_TEMP;
//    //--------------------------------------------------------
//    //    Image DMA Copy 
//    //--------------------------------------------------------
//    typedef struct _DMA_IMG_COPY_
//    {
//        INT32     iSrcAddr;
//        INT32     iDestAddr;
//        INT32     iX;    //Src X
//        INT32     iY;    //Src Y
//        INT32     iW;
//        INT32     iH;
//        INT32     iX2;   //Target X For different (x,y)
//        INT32     iY2;   //Target Y
//    } TDMA_IMG_COPY;
//
//    //---------------------------------------------------------------------------
//    // SPI Struct
//    //---------------------------------------------------------------------------
//    typedef struct  _TSPI_CMD_ARG_DATA
//    {
//        INT32     iSPIAddress;
//        INT32     iDRAMAddress;
//        INT32     iLength;            /*Byte count*/
//    } TSPI_CMD_ARG_DATA;
//    typedef TSPI_CMD_ARG_DATA  TSPICmdArgData;
//    typedef TSPICmdArgData* LPSPICmdArgData;
//    //---------------------------------------------------------------------------
//    typedef struct  _TSPI_CMD_ARG_ERASE_DATA
//    {
//        INT32     iSPIAddress;
//        INT32     iLength;            /*Byte count*/
//    } TSPI_CMD_ARG_ERASE_DATA;
//    typedef TSPI_CMD_ARG_ERASE_DATA  TSPICmdArgEraseData;
//    typedef TSPICmdArgEraseData* LPSPICmdArgEraseData;
//
//    //----------------------------------------------------
//    //   For USB Command 0xA5
//    //----------------------------------------------------
//#define TABLE_TYPE_LUT                      0  //See Tableinfo.h
//#define TABLE_TYPE_VCOM                     1
//#define TABLE_TYPE_TCON                     2
//
//    typedef struct
//    {
//        BYTE ucType;        //Table type
//        BYTE ucMode;        //Display Mode
//        BYTE ucTempSeg;     //Temperature segments
//        BYTE ucSizeL;       //Table Size L
//        BYTE ucSizeH;       //Table Size H
//        BYTE ucFrameCntL;   //Frame counts L
//        BYTE ucFrameCntH;   //Frame Counts H
//        BYTE ucReserved;    //Reserved for padding to 8-bytes
//
//    }TSetLUTInfo;
//
//    //*********************************************************
//    //  typedef 
//    //*********************************************************
//    //#define SPT_BUF_SIZE  (60*1024)//(2048)
//
//#ifndef  TDWord
//#define TDWord DWORD
//#endif // ! TDWord
//
//    typedef struct
//    {
//        SCSI_PASS_THROUGH stSPTD;
//        BYTE DataBuffer[SPT_BUF_SIZE];
//
//    }SCSI_PASS_THROUGH_WITH_BUFFER;



    ////*********************************************************
    ////  Function API
    ////*********************************************************
    //DWORD IT8951ReadRegAPI(DWORD ulRegAddr, DWORD* pulRegVal);
    //DWORD IT8951WriteRegAPI(DWORD ulRegAddr, DWORD ulRegVal);
    //DWORD IT8951InquiryAPI(BYTE* bFlag);
    //DWORD IT8951GetSystemInfoAPI(_TRSP_SYSTEM_INFO_DATA* pstSystemInfo);
    //HANDLE IT8951OpenDeviceAPI(const char* pString);
    //DWORD IT8951ReadMemAPI(DWORD ulMemAddr, WORD usLength, BYTE* RecvBuf);
    //DWORD IT8951WriteMemAPI(DWORD ulMemAddr, WORD usLength, BYTE* pSrcBuf);
    //DWORD IT8951LoadImage(BYTE* pSrcImgBuf, DWORD ulITEImageBufAddr, DWORD ulX, DWORD ulY, DWORD ulW, DWORD ulH);
    //DWORD IT8951DisplayAreaAPI(DWORD ulX, DWORD ulY, DWORD ulW, DWORD ulH, DWORD ulMode, DWORD ulMemAddr, DWORD ulEnWaitReady);
    //volatile DWORD IT8951GetDriveNo(BYTE* pDriveNo);
    //DWORD IT8951LdImgAreaAPI(LOAD_IMG_AREA* pstLdImgArea, BYTE* pSrcBuf);
    //DWORD IT8951PMICCtrlAPI(T_PMIC_CTRL* pstPMICCtrl);
    //DWORD IT8951SetVComAPI(BYTE ucSetVCom, WORD* pusVComVal);
    //DWORD IT8951SWPowerSeqAPI(BYTE ucSWPowerOn, WORD usWithSetVComVal);
    //DWORD IT8951ImgCopyAPI(TDMA_IMG_COPY* pstDMAImgCpy);
    //DWORD IT8951SFIBlockEraseAPI(TSPICmdArgEraseData* pstArgErase);
    //DWORD IT8951SFIPageWriteAPI(TSPICmdArgData* pstSPIArg, BYTE* pWBuf);
    //DWORD IT8951SFIPageReadAPI(TSPICmdArgData* pstSPIArg, BYTE* pRBuf);
    //DWORD IT8951FSetTempCtrlAPI(T_F_SET_TEMP* pstFTempCtrl);
    //DWORD IT8951GetSetTempAPI(BYTE ucSet, BYTE ucSetValue);
    //DWORD IT8951SoftwareResetAPI();
    //DWORD SWAP_32(DWORD v);

    //void IT8951WaitDpyReady();

#endif //PCH_H
