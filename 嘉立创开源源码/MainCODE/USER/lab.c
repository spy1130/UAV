typedef struct
{
  uint16_t CAN_FilterIdHigh;      
  uint16_t CAN_FilterIdLow;          
  uint16_t CAN_FilterMaskIdHigh;    
  uint16_t CAN_FilterMaskIdLow;     
  uint16_t CAN_FilterFIFOAssignment; 
  uint8_t CAN_FilterNumber;       
  uint8_t CAN_FilterMode;       
  uint8_t CAN_FilterScale;           
  FunctionalState CAN_FilterActivation; 
} CAN_FilterInitTypeDef;


CAN_FilterInitTypeDef CAN_FilterInitStruct

CAN_FilterInitStruct.CAN_FilterActivation = 1
CAN_FilterInitStruct.CAN_FilterFIFOAssignment =  0x00
CAN_FilterInitStruct.CAN_FilterNumber = 6;
CAN_FilterInitStruct.CAN_FilterScale = 0x01;
CAN_FilterInitStruct.CAN_FilterMode  = 0x00;
CAN_FilterInitStruct.CAN_FilterIdHigh = 0x00;
CAN_FilterInitStruct.CAN_FilterIdLow  = 0x91A4;//37284  1001 0001 1010 0100
CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0xFFFF;
CAN_FilterInitStruct.CAN_FilterMaskIdLow  = 0xFFFF;	
CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;

CAN_FilterInit(&CAN_FilterInitStruct);


0x4000 6400 - 0x4000 67FF

typedef struct
{
  __IO uint32_t MCR;                            //0x4000 6400
  __IO uint32_t MSR;  							//0x4000 6404
  __IO uint32_t TSR;							//0x4000 6408
  __IO uint32_t RF0R;							//0x4000 640C
  __IO uint32_t RF1R;							//0x4000 6410
  __IO uint32_t IER;							//0x4000 6414
  __IO uint32_t ESR;							//0x4000 6418
  __IO uint32_t BTR;							//0x4000 641C
  uint32_t  RESERVED0[88];	

typedef struct
{
  __IO uint32_t TIR;
  __IO uint32_t TDTR;
  __IO uint32_t TDLR;
  __IO uint32_t TDHR;
} CAN_TxMailBox_TypeDef;	
  CAN_TxMailBox_TypeDef sTxMailBox[3];			//4000 657C+4=4000 6580
	

typedef struct
{
  __IO uint32_t RIR;
  __IO uint32_t RDTR;
  __IO uint32_t RDLR;
  __IO uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];      //4000 65B0


  uint32_t  RESERVED1[12];						
  __IO uint32_t FMR;			               //4000 6600				
  __IO uint32_t FM1R;						   //4000 6604		
  uint32_t  RESERVED2;
  __IO uint32_t FS1R;
  uint32_t  RESERVED3;
  __IO uint32_t FFA1R;
  uint32_t  RESERVED4;
  __IO uint32_t FA1R;
  uint32_t  RESERVED5[8];

typedef struct
{
  __IO uint32_t FR1;
  __IO uint32_t FR2;
} CAN_FilterRegister_TypeDef;
  CAN_FilterRegister_TypeDef sFilterRegister[14]; 

} CAN_TypeDef;

#define CAN1    ((CAN_TypeDef *) CAN1_BASE)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x6400)
#define APB1PERIPH_BASE       PERIPH_BASE
#define PERIPH_BASE           ((uint32_t)0x40000000)

#define CAN1 ((CAN_TypeDef *)  0x40000000+0x6400 = 0x4000 6400



0x000091A4
CAN_FilterInitStruct.CAN_FilterIdHigh = ((0x1234<<3 |CAN_Id_Extended |CAN_RTR_Data)&0xFFFF0000)>>16;
CAN_FilterInitStruct.CAN_FilterIdLow  = ((0x1234<<3 |CAN_Id_Extended |CAN_RTR_Data)&0xFFFF);
CAN_Id_Extended = 0x00000004
CAN_RTR_Data = 0x00000000

typedef struct
{
  uint32_t StdId;  
  uint32_t ExtId;  
  uint8_t IDE;    
  uint8_t RTR;   
  uint8_t DLC;    
  uint8_t Data[8]; 
} CanTxMsg;

can_transmit_data.StdId = 0;          //0x123
can_transmit_data.ExtId = 0x1234;
can_transmit_data.RTR = CAN_RTR_DATA;
can_transmit_data.IDE = CAN_Id_Extended;0x00000004


    CAN1->sFilterRegister[0].FR1 = 
    ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh) << 16) |
        (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);
    /* 32-bit mask or Second 32-bit identifier */
    CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 = 
    ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
        (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdLow);

uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{
  uint8_t transmit_mailbox = 0;


  /* Select one empty transmit mailbox */
  if ((CANx->TSR&0x04000000) == 0x04000000)//bit26 = 1硬件设置
  {
    transmit_mailbox = 0;
  }
 
  
    if (TxMessage->IDE == CAN_Id_Standard)
    {
      assert_param(IS_CAN_STDID(TxMessage->StdId));  
      CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->StdId << 21) | \
                                                  TxMessage->RTR);
    }
  
  
if (transmit_mailbox != CAN_TxStatus_NoMailBox)
  {
    /* Set up the Id */
    CANx->sTxMailBox[transmit_mailbox].TIR &= 0x00000001;
    if (TxMessage->IDE == 0x00000000)
    {
       
      CANx->sTxMailBox[0].TIR |= ((TxMessage->StdId << 21) | \
                                                  TxMessage->RTR);
		Bits 31:21 STID[10:0]/EXID[28:18]  EXID[17:0]  IDE  RTR  TXRQ	
		CANx->sTxMailBox[0].TIR |= 0x123 << 21 | 0x00000000
		
    }
	
	
	
    else
    {
      assert_param(IS_CAN_EXTID(TxMessage->ExtId));
      CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->ExtId << 3) | \
                                                  TxMessage->IDE | \
                                                  TxMessage->RTR);
    }
}
	
	
	
	
	
	
	
	

标识符：0x000091A0  
  
STID[10:0]/EXID[28:18]  EXID[17:0]  IDE  RTR  TXRQ	
    else
    {
     
		CANx->sTxMailBox[0].TIR |= 0x1234 << 3 | 0x00000004 | 0x00000000 = 0x000091A4
		
		
      CANx->sTxMailBox[0].TIR |= ((TxMessage->ExtId << 3) | \
                                                  TxMessage->IDE | \
                                                  TxMessage->RTR);
    }
    
    /* Set up the DLC */
    TxMessage->DLC &= (uint8_t)0x0000000F;
	
    CANx->sTxMailBox[0].TDTR &= (uint32_t)0xFFFFFFF0;
    CANx->sTxMailBox[0].TDTR |= TxMessage->DLC;

	
    /* Set up the data field */
    CANx->sTxMailBox[0].TDLR = (((uint32_t)TxMessage->Data[3] << 24) | 
                                             ((uint32_t)TxMessage->Data[2] << 16) |
                                             ((uint32_t)TxMessage->Data[1] << 8) | 
                                             ((uint32_t)TxMessage->Data[0]));
	
	
	
	
    CANx->sTxMailBox[transmit_mailbox].TDHR = (((uint32_t)TxMessage->Data[7] << 24) | 
                                             ((uint32_t)TxMessage->Data[6] << 16) |
                                             ((uint32_t)TxMessage->Data[5] << 8) |
                                             ((uint32_t)TxMessage->Data[4]));
											 
    /* Request transmission */
    CANx->sTxMailBox[0].TIR |= 0x00000001;
  }
  return transmit_mailbox;
}


