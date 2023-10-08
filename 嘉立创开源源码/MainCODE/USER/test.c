void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));  
   
  SCB->VTOR = 0x08000000 | (0x00010000 & (uint32_t)0x1FFFFF80);
}



//0x1FFFFF80
//0x00010000