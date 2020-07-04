//#ifndef __IT8951_USB_API___
//#define __IT8951_USB_API___
//
//#include "pch.h"
//#include "Ntddscsi.h"
//#include "winioctl.h"
//#include "IT8951UsbCmd.h"
////*********************************************************
////  typedef 
////*********************************************************
////#define SPT_BUF_SIZE  (60*1024)//(2048)
//
//#ifndef  TDWord
//#define TDWord DWORD
//#endif // ! TDWord
//
//typedef struct
//{
//	SCSI_PASS_THROUGH stSPTD;
//	BYTE DataBuffer[SPT_BUF_SIZE];
//
//}SCSI_PASS_THROUGH_WITH_BUFFER;
//
//
//
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
//DWORD IT8951DisplayAreaAPI(DWORD ulX, DWORD ulY, DWORD ulW, DWORD ulH, DWORD ulMode, DWORD ulMemAddr, DWORD ulEnWaitReady );
//static volatile DWORD IT8951GetDriveNo(BYTE* pDriveNo);
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
//
//void IT8951WaitDpyReady();
//
//
////extern HANDLE hDev;
////
////extern BYTE gSPTDataBuf[SPT_BUF_SIZE+1024];
////
////extern DWORD gulPanelW;
////extern DWORD gulPanelH;
//
//#endif //}__IT8951_USB_API___
//
