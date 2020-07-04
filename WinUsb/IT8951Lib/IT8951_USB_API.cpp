//
//
//// **************************************************************************
//// IT8951_USB_API.cpp
////  USB API for CDB access to IT8951
////
////
//// Copyright (c) 2008-2016 ITE Tech. Inc. All Rights Reserved.
////
//// Author: Eric Su
//// **************************************************************************
//#include "pch.h"
//#include "winbase.h"
//#include "Ntddscsi.h"
//#include "winioctl.h"
//#include "it8951UsbCmd.h"
//#include "IT8951_USB_API.h"
//#define BIGENDIAN (htons(1) == 1)
//
//
////#include "mydefine.h"
////UINT8 SWAP_8(UINT8 x)
////{
////	x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
////	x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
////	return((x >> 4) | (x << 4));
////}
////DWORD SWAP_32(DWORD v)
////{
////	UINT32 temp = v;
////	BYTE arr[4];
////	memcpy(arr,&temp,4);//目前在Window x64cpu发现是小头
////	BYTE swap[4];
////	swap[3] = SWAP_8(*(arr));
////	swap[2] = SWAP_8(*(arr + 1));
////	swap[1] = SWAP_8(*(arr + 2));
////	swap[0] = SWAP_8(*(arr + 3));
////	INT32 swapValue;
////	memcpy(&swapValue, swap, 4);//目前在Window x64cpu发现是小头
////	DWORD retValue = swapValue;
////	return retValue;
////}
//DWORD SWAP_32(DWORD v)
//{
//	DWORD retValue = ((0xFF000000 & v) >> 24) | ((0x00FF0000 & v) >> 8) | ((0x0000FF00 & v) << 8) | ((0x000000FF & v) << 24);
//	return retValue;
//}
//
////HANDLE hDev = NULL;
////BYTE gSPTDataBuf[SPT_BUF_SIZE+1024];
////
////DWORD gulPanelW = 1600;
////DWORD gulPanelH = 1200;
//
//BYTE gucEnHSDConvert = 0;
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//HANDLE IT8951OpenDeviceAPI(const char* pString)
//{
//	//Create File(IT8951 USB Device)
//	hDev = CreateFile(
//		                (LPCSTR)pString,                        // file name
//			            ( GENERIC_READ | GENERIC_WRITE),        // access mode
//                	    ( FILE_SHARE_READ | FILE_SHARE_WRITE ), // share mode
//                	    NULL,                                   // SD
//                	    OPEN_EXISTING,                          // how to create
//			            0,						                // file attributes
//			            NULL                        			// handle to template file
//			        );
//	return hDev;
//}
//
//BYTE gucCounter = 0;
//
//
//static volatile DWORD IT8951GetDriveNo(BYTE* pDriveNo)
//{
//	INT32 i;
//	BYTE  bFlag;
//
//	std::string cstrDriveName = "Generic Storage RamDisc 1.00";
//
//
//	char* path = (char*)malloc(7);
//	memcpy(path, "\\\\.\\A:", 6);
//	path[6] = 0;
//	for(i=0;i<16;i++)
//	{
//		//Assign Physical Drive Name
//		//! try A~P
//        //盘符
//		path[4] = 0x41 + i;
//
//		//printf("Scanning Drive %d\r\n",i);
//		//Sleep(100);
//		//Open
//		hDev = CreateFile(
//			            (LPCSTR)path,      // file name
//			            ( GENERIC_READ | GENERIC_WRITE),        // access mode
//                	    ( FILE_SHARE_READ | FILE_SHARE_WRITE ), // share mode
//                	    NULL,                                   // SD
//                	    OPEN_EXISTING,                          // how to create
//			            0,						                // file attributes
//			            NULL                        			// handle to template file
//			        );
//
//		if(hDev != INVALID_HANDLE_VALUE)
//		{
//			//Create File successful => Inguiry
//			IT8951InquiryAPI(&bFlag);
//
//			gucCounter++;
//
//			if(bFlag)
//			{
//				gSPTDataBuf[36] = '\0';
//				if( strcmp((char*)&gSPTDataBuf[8], cstrDriveName.c_str()) == 0)
//				{
//					//Set Drive No.
//					*pDriveNo = (BYTE)i;
//
//					//Close Handle
//					CloseHandle(hDev);
//
//					return bFlag;
//				}
//			}
//
//		}
//
//		//Close Handle
//		CloseHandle(hDev);
//
//	}
//
//	return 0;
//}
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951GetSystemInfoAPI(_TRSP_SYSTEM_INFO_DATA* pstSystemInfo)
//{
//	DWORD dwReturnBytes = 0;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	BYTE bSuccess;
//	UINT32  i;
//	UINT32* pi = (UINT32*)gSPTDataBuf;
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_IN;
//	pstSPTDBuf->DataTransferLength = 0x70;//112 bytes
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = gSPTDataBuf;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	
//	//Copy Scsi Buffer to SPT Buf
//	pstSPTDBuf->Cdb[0] = 0xFE;
//	pstSPTDBuf->Cdb[1] = 0x00;
//	pstSPTDBuf->Cdb[2] = 0x38;//Signature 8951
//	pstSPTDBuf->Cdb[3] = 0x39;
//	pstSPTDBuf->Cdb[4] = 0x35;
//	pstSPTDBuf->Cdb[5] = 0x31;
//	pstSPTDBuf->Cdb[6] = 0x80;//Command:Get System Information
//	pstSPTDBuf->Cdb[7] = 0x00;
//	pstSPTDBuf->Cdb[8] = 0x01;//Version[8-11]:0x00010002
//	pstSPTDBuf->Cdb[9] = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x02;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(gSPTDataBuf), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//							sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof(gSPTDataBuf), //sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//    //! memcpy(*destination, *source, size)
//	memcpy(pstSystemInfo, gSPTDataBuf, sizeof(_TRSP_SYSTEM_INFO_DATA));
//
//	//Endian Convert (Big => Little)
//	pi = (UINT32*)pstSystemInfo;
//	for(i=0;i<sizeof(_TRSP_SYSTEM_INFO_DATA)/sizeof(UINT32);i++)
//	{
//	   pi[i] = SWAP_32(pi[i]);
//	}
//
//    if(gucEnHSDConvert == 1)
//	{
//	    //For HSD only
//	    pstSystemInfo->uiWidth  = pstSystemInfo->uiWidth*2;
//	    pstSystemInfo->uiHeight = pstSystemInfo->uiHeight/2;
//	}
//
//	//Update Panel width and Height
//	PANEL_W = pstSystemInfo->uiWidth;
//	PANEL_H = pstSystemInfo->uiHeight;
//
//
//	return bSuccess;
//
//}
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951InquiryAPI(BYTE* bFlag)
//{
//	DWORD dwReturnBytes = 0;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	BYTE bSuccess;
//
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = 1;
//	pstSPTDBuf->DataTransferLength = 0x28;//112
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Set CDB
//	pstSPTDBuf->Cdb[0] = 0x12;//Inquiry
//	pstSPTDBuf->Cdb[1] = 0x00;
//	pstSPTDBuf->Cdb[2] = 0x00;
//	pstSPTDBuf->Cdb[3] = 0x00;
//	pstSPTDBuf->Cdb[4] = 0x00;
//	pstSPTDBuf->Cdb[5] = 0x00;
//	pstSPTDBuf->Cdb[6] = 0x81;  //! read memory?
//	pstSPTDBuf->Cdb[7] = 0x00;
//	pstSPTDBuf->Cdb[8] = 0x00;
//	pstSPTDBuf->Cdb[9] = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	*bFlag = bSuccess;
//
//	return bSuccess;
//
//
//}
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951ReadRegAPI(DWORD ulRegAddr, DWORD* pulRegVal)
//{
//	DWORD dwReturnBytes = 0;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	BYTE bSuccess;
//
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn			   = 1; //! SCSI_IOCTL_DATA_IN 1
//	pstSPTDBuf->DataTransferLength = 4;
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//CDB - SCSI Request Sense Command
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = (BYTE)((ulRegAddr >> 24) & 0xFF); //Byte 2~5 Register Address BigEndian for IT8951
//	pstSPTDBuf->Cdb[3]  = (BYTE)((ulRegAddr >> 16) & 0xFF);
//	pstSPTDBuf->Cdb[4]  = (BYTE)((ulRegAddr >> 8) & 0xFF);
//	pstSPTDBuf->Cdb[5]  = (BYTE)((ulRegAddr) & 0xFF);
//	pstSPTDBuf->Cdb[6]  = 0x83;//IT8951 USB ReadReg
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x04;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(gSPTDataBuf), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(gSPTDataBuf), //sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//	if(bSuccess != 0)
//	{
//		//Read Successful => Set 4 bytes Read Value in Big Endian format
//	    *pulRegVal = (gSPTDataBuf[0] << 24) | (gSPTDataBuf[1] << 16) |(gSPTDataBuf[2] << 8) | (gSPTDataBuf[3]);
//	}
//
//	return bSuccess;
//
//}
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951WriteRegAPI(DWORD ulRegAddr, DWORD ulRegVal)
//{
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//
//	pstSPTDBuf->Length    = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = 0; //! SCSI_IOCTL_DATA_OUT 0
//	pstSPTDBuf->DataTransferLength = 4;//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = (BYTE)((ulRegAddr >> 24) & 0xFF); //Byte 2~5 Register Address BigEndian for IT8951
//	pstSPTDBuf->Cdb[3]  = (BYTE)((ulRegAddr >> 16) & 0xFF);
//	pstSPTDBuf->Cdb[4]  = (BYTE)((ulRegAddr >> 8) & 0xFF);
//	pstSPTDBuf->Cdb[5]  = (BYTE)((ulRegAddr) & 0xFF);
//	pstSPTDBuf->Cdb[6]  = 0x84;
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x04;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Fill Write Register Value (Note: need to convert to Big Endian)
//	gSPTDataBuf[0] = (BYTE)((ulRegVal >> 24) & 0xFF);
//	gSPTDataBuf[1] = (BYTE)((ulRegVal >> 16) & 0xFF);
//	gSPTDataBuf[2] = (BYTE)((ulRegVal >> 8) & 0xFF);
//	gSPTDataBuf[3] = (BYTE)((ulRegVal >> 0) & 0xFF);
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(gSPTDataBuf),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(gSPTDataBuf),
//                            &dwReturnBytes,
//			                NULL );
//
//	return bSuccess;
//
//
//}
//
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//
//DWORD IT8951ReadMemAPI(DWORD ulMemAddr, WORD usLength, BYTE* RecvBuf)
//{
//	BYTE  bSuccess;
//	DWORD dwReturnBytes = 0;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = 1;//Read - 1
//	pstSPTDBuf->DataTransferLength = usLength;
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)RecvBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//CDB - SCSI Request Sense Command
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = (BYTE)((ulMemAddr >> 24) & 0xFF); //Byte 2~5 Register Address BigEndian for IT8951
//	pstSPTDBuf->Cdb[3]  = (BYTE)((ulMemAddr >> 16) & 0xFF);
//	pstSPTDBuf->Cdb[4]  = (BYTE)((ulMemAddr >> 8) & 0xFF);
//	pstSPTDBuf->Cdb[5]  = (BYTE)((ulMemAddr) & 0xFF);
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_READ_MEM;//0x81
//	pstSPTDBuf->Cdb[7]  = (BYTE)((usLength >> 8) & 0xFF);
//	pstSPTDBuf->Cdb[8]  = (BYTE)((usLength) & 0xFF);
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	//Return 4 bytes Read Value in Big Endian format
//	return 1;
//}
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951WriteMemAPI(DWORD ulMemAddr, WORD usLength, BYTE* pSrcBuf)
//{
//	DWORD ulRetCode;
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//
//
//	pstSPTDBuf->Length    = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_OUT;//Out
//	pstSPTDBuf->DataTransferLength = usLength;//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)pSrcBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = (BYTE)((ulMemAddr >> 24) & 0xFF); //Byte 2~5 Register Address BigEndian for IT8951
//	pstSPTDBuf->Cdb[3]  = (BYTE)((ulMemAddr >> 16) & 0xFF);
//	pstSPTDBuf->Cdb[4]  = (BYTE)((ulMemAddr >> 8) & 0xFF);
//	pstSPTDBuf->Cdb[5]  = (BYTE)((ulMemAddr) & 0xFF);
//#ifdef EN_FAST_WRITE_MEM//{IT8951_USB_OP_FAST_WRITE_MEM
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_FAST_WRITE_MEM;//0xA5 for Fast Write Memory(Need FW support);//IT8951_USB_OP_WRITE_MEM;//0x82
//#else
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_WRITE_MEM;//0x82
//#endif//}IT8951_USB_OP_FAST_WRITE_MEM
//	pstSPTDBuf->Cdb[7]  = (BYTE)((usLength >> 8) & 0xFF);
//	pstSPTDBuf->Cdb[8]  = (BYTE)((usLength) & 0xFF);
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	return bSuccess;
//
//
//}
//
//DWORD IT8951LoadImage(BYTE* pSrcImgBuf, DWORD ulITEImageBufAddr, DWORD ulX, DWORD ulY, DWORD ulW, DWORD ulH)
//{
//	UINT32 j;
//	BYTE* pCurStartBuf;
//	DWORD ulCurDevImgStartBuf;
//	DWORD ulSendLineCnt = 0;
//	DWORD retVal = 0;
//
//	//if(ulW != gulPanelW)//v.1.9.5
//	if(ulW <= 2048 && ulW != gulPanelW)//v.1.9.4
//	{
//        if(gucEnHSDConvert == 1)
//		{
//			//Load Partial Image => Send 1 Line for each transfer
//			for(j=0;j<ulH;j++)
//			{
//				//Set Line Start Address
//				ulCurDevImgStartBuf = ulITEImageBufAddr + ((ulY+j)*gulPanelW) + ulX;
//				pCurStartBuf        = pSrcImgBuf + (j*ulW);
//
//				//We Send 1 Line for each Bulk Transfer
//				retVal = IT8951WriteMemAPI(ulCurDevImgStartBuf, (WORD)ulW, pCurStartBuf);
//				if (retVal == 0)
//				{
//					break;
//				}
//			}
//		}
//		else //__EN_HSD_CONVERT__
//		{
//			//Using IT8951 New USB Command for Loading Image - it Needs IT8951 F/W support
//			LOAD_IMG_AREA stLdImgInfo;
//
//			ulSendLineCnt = SPT_BUF_SIZE/ulW;
//
//			for(j=0;j<ulH;j=j+ulSendLineCnt)
//			{
//				if( ulSendLineCnt > (ulH-j))
//				{
//					ulSendLineCnt = ulH-j;
//				}
//
//				stLdImgInfo.iX = ulX;
//				stLdImgInfo.iY = ulY + j;
//				stLdImgInfo.iW = ulW;
//				stLdImgInfo.iH = ulSendLineCnt;
//
//				//Set Image Buffer Start Address
//				stLdImgInfo.iAddress = ulITEImageBufAddr;
//				pCurStartBuf         = pSrcImgBuf + (j*ulW);
//
//				//We Send Multi Line for each Bulk Transfer
//				retVal = IT8951LdImgAreaAPI(&stLdImgInfo, pCurStartBuf);
//				if (retVal == 0)
//				{
//					break;
//				}
//
//			}
//		}
//
//	}
//	else
//	{
//		//Full Image - Fast Method => Send Multi Lines for each transfer
//		ulSendLineCnt = SPT_BUF_SIZE/ulW;
//
//		for(j=0;j<ulH;j=j+ulSendLineCnt)
//		{
//			//Set Line Start Address
//			ulCurDevImgStartBuf = ulITEImageBufAddr + ((ulY+j)*gulPanelW) + ulX;
//			pCurStartBuf        = pSrcImgBuf + (j*ulW);
//
//			if( ulSendLineCnt > (ulH-j))
//			{
//				ulSendLineCnt = ulH-j;
//			}
//			//We Send Multi Lines for each Bulk Transfer
//			retVal = IT8951WriteMemAPI(ulCurDevImgStartBuf, (WORD)(ulW*ulSendLineCnt), pCurStartBuf);
//			if (retVal == 0)
//			{
//				break;
//			}
//		}
//	}
//
//	return retVal;
//}
//
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951DisplayAreaAPI(DWORD ulX, DWORD ulY, DWORD ulW, DWORD ulH, DWORD ulMode, DWORD ulMemAddr, DWORD ulEnWaitReady)
//{
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	TDRAW_UPD_ARG_DATA stDrawUPDArgData;
//
//	//Set Display Area 0x94 Arguments
//	stDrawUPDArgData.iPosX          = SWAP_32(ulX); //Conver Little to Big for IT8951/61
//    stDrawUPDArgData.iPosY          = SWAP_32(ulY);
//    stDrawUPDArgData.iWidth         = SWAP_32(ulW);
//    stDrawUPDArgData.iHeight        = SWAP_32(ulH);
//    stDrawUPDArgData.iEngineIndex   = SWAP_32(ulEnWaitReady);
//    stDrawUPDArgData.iMemAddr       = SWAP_32(ulMemAddr);
//    stDrawUPDArgData.iWavMode       = SWAP_32(ulMode);
//
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = 0;
//	pstSPTDBuf->DataTransferLength = sizeof(TDRAW_UPD_ARG_DATA);//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)&stDrawUPDArgData;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_DPY_AREA;   // 0x94
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x00;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(TDRAW_UPD_ARG_DATA), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(TDRAW_UPD_ARG_DATA), //sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	return bSuccess;
//
//
//}
//
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951LdImgAreaAPI(LOAD_IMG_AREA* pstLdImgArea, BYTE* pSrcBuf)
//{
//	DWORD ulRetCode;
//
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	WORD usLength;
//	INT32 i;
//
//	//Set Image Length for this transfer
//	usLength = (WORD)(pstLdImgArea->iW*pstLdImgArea->iH);
//
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_OUT;//Out
//	pstSPTDBuf->DataTransferLength = sizeof(LOAD_IMG_AREA) + usLength;//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Little Endian to Big for IT8951/61
//	for(i=0;i<sizeof(LOAD_IMG_AREA)/sizeof(int);i++)
//	{
//		((int*)pstLdImgArea)[i] = SWAP_32(((int*)pstLdImgArea)[i]);
//	}
//	//Fill SPTD Buffer
//	//    => Byte[0~19]: Load Image Arguments
//	//    => Byte[20~x]: Image Pixel Data
//	memcpy(gSPTDataBuf, pstLdImgArea, sizeof(LOAD_IMG_AREA));
//	memcpy(&gSPTDataBuf[sizeof(LOAD_IMG_AREA)], pSrcBuf, usLength);
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_LD_IMG_AREA;//0xA2
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x00;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	return bSuccess;
//
//
//}
//
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//
//DWORD IT8951PMICCtrlAPI(T_PMIC_CTRL* pstPMICCtrl)
//{
//	DWORD ulRetCode;
//
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	WORD usLength;
//	INT32 i;
//
//	//Set Image Length for this transfer
//
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_IN;//Out
//	pstSPTDBuf->DataTransferLength = sizeof(T_PMIC_CTRL);//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_PMIC_CTRL;//0xA3
//	pstSPTDBuf->Cdb[7]  = (BYTE)(pstPMICCtrl->usSetVComVal >> 8);
//	pstSPTDBuf->Cdb[8]  = (BYTE)(pstPMICCtrl->usSetVComVal);
//	pstSPTDBuf->Cdb[9]  = (BYTE)(pstPMICCtrl->ucDoSetVCom);
//	pstSPTDBuf->Cdb[10] = (BYTE)(pstPMICCtrl->ucDoPowerSeqSW);
//	pstSPTDBuf->Cdb[11] = (BYTE)(pstPMICCtrl->ucPowerOnOff);
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	else
//	{
//		//Successful -> Get Return Value(Vcom)
//		pstPMICCtrl->usSetVComVal = (gSPTDataBuf[0] << 8) | gSPTDataBuf[1]; //Big to Little Endian
//
//	}
//	return bSuccess;
//
//
//}
//
////------------------------------------------------------------------------
////      BYTE ucSetVCom :  0 - Get Current VCom Value only
////                        1 - Set VCom Value by *pusVComVal (Unit mv) e.g. -1.59V => Set 159 = 0x9F)
////
////      WORD* pusVComVal: pointer to VComValue
////                        this pointer will be updated to the latest VCom Value(Current)
////
////------------------------------------------------------------------------
//DWORD IT8951SetVComAPI(BYTE ucSetVCom, WORD* pusVComVal)
//{
//	T_PMIC_CTRL stPMICCtrl;
//	BYTE  bSuccess;
//
//	stPMICCtrl.ucDoSetVCom    = ucSetVCom;
//	stPMICCtrl.usSetVComVal   = *pusVComVal;
//
//	//ucDoPowerSeqSW=0表示不配置power,如果要配置power，不管是on还是off,ucDoPowerSeqSW都必须设置为1
//	stPMICCtrl.ucDoPowerSeqSW = 0;
//	stPMICCtrl.ucPowerOnOff   = 0;
//
//	bSuccess = IT8951PMICCtrlAPI(&stPMICCtrl);
//
//	if(!bSuccess)
//	{
//		return GetLastError();
//	}
//
//	//Set Read Value
//	*pusVComVal = stPMICCtrl.usSetVComVal;
//
//	return bSuccess;
//}
////------------------------------------------------------------------------
////   ucSWPowerOn : 0 - Power off Seq, 1 - Power on Seq
////   usWithSetVComVal: 0xFFFF - No Setting, others - VCom Value
////                     (e.g. -1.59 => usWithSetVComVal = 159 = 0x9F)
////------------------------------------------------------------------------
//DWORD IT8951SWPowerSeqAPI(BYTE ucSWPowerOn, WORD usWithSetVComVal)
//{
//	T_PMIC_CTRL stPMICCtrl;
//	BYTE  bSuccess;
//
//	stPMICCtrl.ucDoSetVCom    = (usWithSetVComVal == 0xFFFF)? 0 : 1;
//	stPMICCtrl.usSetVComVal   = usWithSetVComVal;
//	stPMICCtrl.ucDoPowerSeqSW = 1;
//	stPMICCtrl.ucPowerOnOff   = ucSWPowerOn;  //0 - Power off, 1 - Power on
//
//	bSuccess = (BYTE)IT8951PMICCtrlAPI(&stPMICCtrl);
//
//	if(!bSuccess)
//	{
//		return GetLastError();
//	}
//
//	//Set Read Value
//	//*pusVComVal = stPMICCtrl.usSetVComVal;
//
//	return bSuccess;
//
//}
//
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951ImgCopyAPI(TDMA_IMG_COPY* pstDMAImgCpy)
//{
//	DWORD ulRetCode;
//
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	INT32 i;
//
//	//Set Image Length for this transfer
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_OUT;//Out
//	pstSPTDBuf->DataTransferLength = sizeof(TDMA_IMG_COPY);//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Little Endian to Big for IT8951/61
//	for(i=0;i<sizeof(TDMA_IMG_COPY)/sizeof(int);i++)
//	{
//		((int*)pstDMAImgCpy)[i] = SWAP_32(((int*)pstDMAImgCpy)[i]);
//	}
//	//Fill SPTD Buffer
//	//    => Byte[0~23]: Image Copy Arguments
//	memcpy(gSPTDataBuf, pstDMAImgCpy, sizeof(TDMA_IMG_COPY));
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_IMG_CPY;//0xA4
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x00;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	return bSuccess;
//
//
//}
//
////USB SPI functions for Erase, Read and Write
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//DWORD IT8951SFIBlockEraseAPI(TSPICmdArgEraseData* pstArgErase)
//{
//#if 0
//
//
//#else
//	DWORD ulRetCode;
//
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	INT32 i;
//	TSPICmdArgEraseData stArgErase;
//
//	//Set Image Length for this transfer
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_OUT;//Out
//	pstSPTDBuf->DataTransferLength = sizeof(TSPICmdArgEraseData);//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Little Endian to Big for IT8951/61
//	stArgErase.iSPIAddress = SWAP_32(pstArgErase->iSPIAddress);
//	stArgErase.iLength     = SWAP_32(pstArgErase->iLength);
//	//Fill SPTD Buffer
//	//    => Byte[0~23]: SPI Erase Arguments
//	memcpy(gSPTDataBuf, &stArgErase, sizeof(TSPICmdArgEraseData));
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_USB_SPI_ERASE;//0x96
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x00;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	return bSuccess;
//
//#endif
//
//
//}
//
//DWORD IT8951SFIEraseAPI(DWORD ulSFIAddr, DWORD ulSize)
//{
//	INT32 ulBlkSize = 128*1024; //64 or 128
//	INT32 ulRemainSize = ulSize;
//	INT32 i;
//	INT32 EraseBlkCnt;
//	TSPICmdArgEraseData stArgErase;
//
//	//Set Erase Size
//	stArgErase.iLength     = ulBlkSize;
//
//	EraseBlkCnt = ulSize/ulBlkSize + ((ulSize % ulBlkSize)? 1 : 0);
//
//	for(i=0;i<EraseBlkCnt;i++)
//	{
//		stArgErase.iSPIAddress = ulSFIAddr + i*ulBlkSize;
//
//		IT8951SFIBlockEraseAPI(&stArgErase);
//
//	}
//
//	return EraseBlkCnt;
//
//
//}
//
//
//DWORD IT8951SFIPageWriteAPI(TSPICmdArgData* pstSPIArg, BYTE* pWBuf)
//{
//
//	DWORD ulRetCode;
//
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	INT32 i;
//	TSPICmdArgData stSPICmd;
//
//
//	//Set Image Length for this transfer
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_OUT;//Out
//	pstSPTDBuf->DataTransferLength = sizeof(TSPICmdArgData);//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	memcpy((void*)&stSPICmd, (void*)pstSPIArg, sizeof(TSPICmdArgData));
//
//	//Little Endian to Big for IT8951/61
//	stSPICmd.iDRAMAddress = SWAP_32(pstSPIArg->iDRAMAddress);
//	stSPICmd.iLength      = SWAP_32(pstSPIArg->iLength);
//	stSPICmd.iSPIAddress  = SWAP_32(pstSPIArg->iSPIAddress);
//
//	//Fill SPTD Buffer
//	//    => Byte[0~23]: SPI Erase Arguments
//	memcpy(gSPTDataBuf, &stSPICmd, sizeof(TSPICmdArgData));
//	//memcpy(&gSPTDataBuf[sizeof(TSPICmdArgData)], (void*)pWBuf, pstSPIArg->iLength);
//
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_USB_SPI_WRITE;//0x98
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x00;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	return bSuccess;
//
//}
//
//DWORD IT8951SFIPageReadAPI(TSPICmdArgData* pstSPIArg, BYTE* pRBuf)
//{
//
//	DWORD ulRetCode;
//
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	INT32 i;
//	TSPICmdArgData stSPICmd;
//
//
//	//Set Image Length for this transfer
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_OUT;//Out
//	pstSPTDBuf->DataTransferLength = sizeof(TSPICmdArgData);//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	memcpy((void*)&stSPICmd, (void*)pstSPIArg, sizeof(TSPICmdArgData));
//
//	//Little Endian to Big for IT8951/61
//	stSPICmd.iDRAMAddress = SWAP_32(pstSPIArg->iDRAMAddress);
//	stSPICmd.iLength      = SWAP_32(pstSPIArg->iLength);
//	stSPICmd.iSPIAddress  = SWAP_32(pstSPIArg->iSPIAddress);
//
//	//Fill SPTD Buffer
//	//    => Byte[0~23]: SPI Erase Arguments
//	memcpy(gSPTDataBuf, &stSPICmd, sizeof(TSPICmdArgData));
//
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_USB_SPI_READ;//0x97
//	pstSPTDBuf->Cdb[7]  = 0x00;
//	pstSPTDBuf->Cdb[8]  = 0x00;
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	return bSuccess;
//
//}
//
//
////------------------------------------------------------------------------
////
////------------------------------------------------------------------------
//
//DWORD IT8951FSetTempCtrlAPI(T_F_SET_TEMP* pstFTempCtrl)
//{
//	DWORD ulRetCode;
//
//	DWORD dwReturnBytes = 0;
//	BYTE  bSuccess;
//	SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//	SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//	WORD usLength;
//	INT32 i;
//
//	//Set Image Length for this transfer
//
//	pstSPTDBuf->Length             = sizeof(SCSI_PASS_THROUGH_DIRECT);
//	pstSPTDBuf->ScsiStatus         = 0;
//	pstSPTDBuf->PathId             = 0;
//	pstSPTDBuf->TargetId           = 0;
//	pstSPTDBuf->Lun                = 0;
//	pstSPTDBuf->CdbLength          = 16;
//	pstSPTDBuf->SenseInfoLength    = 0;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//	pstSPTDBuf->DataIn             = SCSI_IOCTL_DATA_IN;//In
//	pstSPTDBuf->DataTransferLength = sizeof(pstFTempCtrl);//DWORD R/W Access
//	pstSPTDBuf->TimeOutValue       = 5;
//	pstSPTDBuf->DataBuffer         = (void*)gSPTDataBuf;
//	pstSPTDBuf->SenseInfoOffset    = 0;
//
//	//Copy Scsi Buffer to SPTD Buf
//	pstSPTDBuf->Cdb[0]  = 0xFE;
//	pstSPTDBuf->Cdb[1]  = 0x00;
//	pstSPTDBuf->Cdb[2]  = 0x00;
//	pstSPTDBuf->Cdb[3]  = 0x00;
//	pstSPTDBuf->Cdb[4]  = 0x00;
//	pstSPTDBuf->Cdb[5]  = 0x00;
//	pstSPTDBuf->Cdb[6]  = IT8951_USB_OP_FSET_TEMP;//0xA5
//	pstSPTDBuf->Cdb[7]  = (BYTE)(pstFTempCtrl->ucSetTemp);
//	pstSPTDBuf->Cdb[8]  = (BYTE)(pstFTempCtrl->ucTempVal);
//	pstSPTDBuf->Cdb[9]  = 0x00;
//	pstSPTDBuf->Cdb[10] = 0x00;
//	pstSPTDBuf->Cdb[11] = 0x00;
//	pstSPTDBuf->Cdb[12] = 0x00;
//	pstSPTDBuf->Cdb[13] = 0x00;
//	pstSPTDBuf->Cdb[14] = 0x00;
//	pstSPTDBuf->Cdb[15] = 0x00;
//
//	//Send SCSI Command
//	bSuccess = DeviceIoControl(hDev,
//		                    IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//			                &stSPTDBuf,
//			                sizeof(SCSI_PASS_THROUGH_DIRECT), //sizeof( TSPTWBData),
//			                &stSPTDBuf,
//                            sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof( TSPTWBData),
//                            &dwReturnBytes,
//			                NULL );
//
//	if(!bSuccess)
//	{
//		ulRetCode = GetLastError();
//	}
//	else
//	{
//		//Successful -> Get Return Value(Vcom)
//		pstFTempCtrl->ucTempVal = gSPTDataBuf[0]; //Big to Little Endian
//
//	}
//	return bSuccess;
//
//
//}
//
//DWORD IT8951GetSetTempAPI(BYTE ucSet, BYTE ucSetValue)
//{
//	T_F_SET_TEMP stFSetTemp;
//	DWORD ulRetCode;
//
//	stFSetTemp.ucSetTemp = ucSet;
//	stFSetTemp.ucTempVal = ucSetValue;
//
//	ulRetCode = IT8951FSetTempCtrlAPI(&stFSetTemp);
//	if(ulRetCode == 1)
//	{
//		return (DWORD)stFSetTemp.ucTempVal;
//	}
//	else
//	{
//		return ulRetCode;
//	}
//
//
//
//}
//
//void IT8951WaitDpyReady()
//{
//	TDWord ulStatus = 0;
//	//DWORD ulStatus = 0;
//
//	do
//	{
//		//Wait unitil All status are zero(No zero => means TCon Engine is Busy)
//	    IT8951ReadRegAPI(0x18001224, &ulStatus );
//
//	}while(ulStatus & 0xFFFF);
//}
//
//DWORD IT8951DisplayArea1bppAPI(DWORD ulX, DWORD ulY, DWORD ulW, DWORD ulH, DWORD ulMode, DWORD ulMemAddr, DWORD ulEnWaitReady, DWORD ulImgPitch)
//{
//	TDWord ulOriRegVal;
//	//DWORD ulOriRegVal;
//
//	//Enable Bitmap mode
//	IT8951ReadRegAPI(0x18001138, &ulOriRegVal);
//	//Set Image bitch
//	if(ulImgPitch != NULL)
//	{
//		//Set Image pitch width
//		IT8951WriteRegAPI(0x1800124C, ulImgPitch/4);//DWORD unit (e.g.-Image width 1600 => ulImagePitch = 1600/8(Set By Caller),
//		                                            //Set value ulImagePitch/4 = 50)
//
//		ulOriRegVal |= (1<<17); //Enable Set Image pitch
//	}
//	else
//	{
//		ulOriRegVal &= ~(1<<17); //Disable image pitch
//	}
//
//	IT8951WriteRegAPI(0x18001138, ulOriRegVal | (1<<18));//Set Bit[18] = 1 to Enable Bitmap mode
//
//	//Set Bitmap mode color definition
//	IT8951WriteRegAPI(0x18001250, 0xF0 | (0x00 << 8)); //0 - Set Black(0x00), 1 - Set White(0xF0)
//
//	//Display
//	IT8951DisplayAreaAPI(ulX, ulY, ulW, ulH, ulMode, ulMemAddr, ulEnWaitReady);
//
//	//Restore to normal mode here?(or put it in caller function)
//	IT8951WriteRegAPI(0x18001138, ulOriRegVal & ~(1<<18));//Set Bit[18] = 0 to Disable Bitmap mode
//
//	return 0;
//
//}
//
//
//DWORD IT8951SoftwareResetAPI(void)
//{
//     DWORD dwReturnBytes = 0;
//     SCSI_PASS_THROUGH_DIRECT stSPTDBuf;
//     SCSI_PASS_THROUGH_DIRECT* pstSPTDBuf = &stSPTDBuf;
//     BYTE bSuccess;
//
//     pstSPTDBuf->Length              = sizeof(SCSI_PASS_THROUGH_DIRECT);
//     pstSPTDBuf->ScsiStatus          = 0;
//     pstSPTDBuf->PathId              = 0;
//     pstSPTDBuf->TargetId            = 0;
//     pstSPTDBuf->Lun                      = 0;
//     pstSPTDBuf->CdbLength           = 16;
//     pstSPTDBuf->SenseInfoLength     = 0;
//     pstSPTDBuf->SenseInfoOffset     = 0;
//     pstSPTDBuf->DataIn              = SCSI_IOCTL_DATA_OUT;
//     pstSPTDBuf->DataTransferLength  = 0;
//     pstSPTDBuf->TimeOutValue        = 5;
//     pstSPTDBuf->DataBuffer          = (void*)gSPTDataBuf;
//     pstSPTDBuf->SenseInfoLength     = 0;
//
//     //Copy Scsi Buffer to SPT Buf
//     pstSPTDBuf->Cdb[0] = 0xFE;
//     pstSPTDBuf->Cdb[1] = 0x00;
//     pstSPTDBuf->Cdb[2] = 0x00;
//     pstSPTDBuf->Cdb[3] = 0x00;
//     pstSPTDBuf->Cdb[4] = 0x00;
//     pstSPTDBuf->Cdb[5] = 0x00;
//     pstSPTDBuf->Cdb[6] = 0xA7;
//     pstSPTDBuf->Cdb[7] = 0x00;
//     pstSPTDBuf->Cdb[8] = 0x00;
//     pstSPTDBuf->Cdb[9] = 0x00;
//     pstSPTDBuf->Cdb[10] = 0x00;
//     pstSPTDBuf->Cdb[11] = 0x00;
//     pstSPTDBuf->Cdb[12] = 0x00;
//     pstSPTDBuf->Cdb[13] = 0x00;
//     pstSPTDBuf->Cdb[14] = 0x00;
//     pstSPTDBuf->Cdb[15] = 0x00;
//
//     bSuccess = DeviceIoControl(hDev,
//         IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH_DIRECT,//IOCTL_SCSI_PASS_THROUGH,
//         &stSPTDBuf,
//         sizeof(SCSI_PASS_THROUGH_DIRECT),//+sizeof(gSPTDataBuf), //sizeof( TSPTWBData),
//         &stSPTDBuf,
//         sizeof(SCSI_PASS_THROUGH_DIRECT),//sizeof(gSPTDataBuf), //sizeof( TSPTWBData),
//         &dwReturnBytes,
//         NULL);
//     return bSuccess;
//
//}