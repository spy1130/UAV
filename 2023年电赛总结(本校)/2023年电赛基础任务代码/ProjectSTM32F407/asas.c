				case state_num:
				{
					//�ڸ��Ӹ�����ɣ������ȿ�ʼɶ���Ҳ�����Ӳ��ͷƤx��ֱ�ɡ�����ҵ����ӣ�����ֱ�ɣ�����ҵ����ߣ���Ѳ��
					
					//����id05�����ڴ���5�л�ø߶ȣ����������z���ٶȣ�����ʵʱ����֡���Ʒɻ����������½�
					//mission_step +=target_altituded(150);
					
					if (0)
					{
//						speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//int16_t
//					
//						speed_z_axis_16=(int16_t) speed_z_axis;
//						
//						
//						rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
//						//������ʵʱXYZ-YAW�����ٶ�����		
//						rt_tar.st_data.yaw_dps =0;// yaw_16;
//						rt_tar.st_data.vel_x =0;//speed_x_axis_16;
//						rt_tar.st_data.vel_y =0;//;
//						rt_tar.st_data.vel_z = speed_z_axis_16;

//						dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�
						
						if( rx_end_flag==0x01)
						{
							first_frame_end=0;
							second_frame_end=0;
							rx_end_flag=0;
						}
						
						
						
						
						
						
						
						
						
					}
					else
					{
						
							if (rx_end_flag==0)
							{
								
								if (near_alarm_flag==1||far_alarm_flag==1)
								{
									time_dly_cnt_ms=time_dly_cnt_ms+20;//ms
									if (time_dly_cnt_ms<=3000)
									{
										if(near_alarm_flag==1)
										{
											speed_x_axis_16=10;
											speed_y_axis_16=-10;
											yaw_16=0;
										}
										else
										{
											speed_x_axis_16=10;
											speed_y_axis_16=10;
											yaw_16=0;
										}
									}
									else
									{
										speed_x_axis_16=10;
										speed_y_axis_16=0;
										yaw_16=0;
										time_dly_cnt_ms=3100;
									}
									
									
									
									
								}
								else
								{
									speed_x_axis_16=10;
									speed_y_axis_16=0;
									yaw_16=0;
								}
							}
							else
							{
		//						rx_end_flag=0;
								
								time_dly_cnt_ms=0;//ms
								
								if(second_frame_end==1)
								{
									//two frame information
									
									if(rx_buff[1]==0xf1)
									{	
										follow_line();
									}
									
									
									if(rx_buff[21]==0xf1)
									{	
										follow_line_20();
									}
									
									if(rx_buff[1]!=0xf1&&rx_buff[21]!=0xf1)
									{
										speed_x_axis_16=10;
										speed_y_axis_16=0;
										yaw_16=0;
									}
										
									
									
								}
								else
								{
									//one frame information
									if(rx_buff[1]==0xf1)
									{	
										follow_line();
									}
									else
									{
										speed_x_axis_16=10;
										speed_y_axis_16=0;
										yaw_16=0;
									}
									
									
								}

							speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//int16_t
							
							speed_z_axis_16=(int16_t) speed_z_axis;
							
							
							rt_tar.st_data.rol = 0;
							rt_tar.st_data.pit = 0;
							rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
							//������ʵʱXYZ-YAW�����ٶ�����		
							rt_tar.st_data.yaw_dps = yaw_16;
							rt_tar.st_data.vel_x =speed_x_axis_16;
							rt_tar.st_data.vel_y =speed_y_axis_16;
							rt_tar.st_data.vel_z = speed_z_axis_16;

							dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�
							
							
							sprintf(buf1,"[s9]Ѳ��");//\[b1] ��ӭ���٣����
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
					
					
						}
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
//					
//					  if(time_dly_cnt_ms<5000)
//					  {
//						time_dly_cnt_ms+=20;//ms
//						
//						
//						speed_z_axis=p_altitude*(altitude_set-alt_fu_xm);//int16_t
//						
//						speed_z_axis_16=(int16_t) speed_z_axis;
//						
//						
//						rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
//						//������ʵʱXYZ-YAW�����ٶ�����		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =0;
//						rt_tar.st_data.vel_y =0;
//						rt_tar.st_data.vel_z = speed_z_axis_16;

//						dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�
//						
//						
//						sprintf(buf1,"[s9]���ڸ߶�");//\[b1] ��ӭ���٣����
//					  speak_len1=strlen(buf1);
//						speak_context((u8*)buf1,speak_len1);

//						
//					}
//					else
//					{
//						time_dly_cnt_ms = 0;
//						mission_step += 1;
//					}

//            mission_step += Lifting_Height(50,10);//�����߶�
//            time_dly_cnt_ms = 0;

//            
//            rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
//						//������ʵʱXYZ-YAW�����ٶ�����		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =0;
//						rt_tar.st_data.vel_y =0;
//						rt_tar.st_data.vel_z =0;
//					
//					  dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�

//					   OneKey_Land();
					
//             mission_step += 1;
//					   time_dly_cnt_ms = 0;
//						 
//						 sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
//					   speak_len1=strlen(buf1);
//						 speak_context((u8*)buf1,speak_len1);

				}
				break;
				
				
				
				case state_num+1:
				{
					//��5��
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}
				}
				break;
//				case 10:
//				{
//					//ǰ��1��
//					//mission_step += Horizontal_Move(100,150,0);
//          //time_dly_cnt_ms = 0;
//					
//					//��ת90��
//          //mission_step += Rotate(0x08,36,30);
//				  //time_dly_cnt_ms = 0;
//					
//					//��ת90��
//					OneKey_Land();
//					
//					time_dly_cnt_ms = 0;
//					mission_step += 1;
////						rt_tar.st_data.rol = 0;
////						rt_tar.st_data.pit = 0;
////						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
////						//������ʵʱXYZ-YAW�����ٶ�����		
////						rt_tar.st_data.yaw_dps = 30;
////						rt_tar.st_data.vel_x =25;
////						rt_tar.st_data.vel_y =0;
////						rt_tar.st_data.vel_z =0;
////					
////					  dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�
////					
////					  mission_step +=1;//�½��߶�
////					  time_dly_cnt_ms = 0;

////              mission_step +=target_location(100,100);
////              time_dly_cnt_ms = 0;							
//					
//					  sprintf(buf1,"[s9]��ת360");//\[b1] ��ӭ���٣����
//					  speak_len1=strlen(buf1);
//						speak_context((u8*)buf1,speak_len1);
//					
//				}
//				break;	
				case state_num+2:
				{
					//��5��
					if(time_dly_cnt_ms<10000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}
					
//					mission_step += Horizontal_Move(50,20,0);//ǰ��һ��
//				  time_dly_cnt_ms = 0;				

				}
				break;
        case state_num+3:
				{
					//ǰ��1��
					//mission_step +=Falling_Head1(50,10);//�½��߶�
					//mission_step +=Lifting_Height1(50��10);//�����߶�
					  rt_tar.st_data.rol = 0;
						rt_tar.st_data.pit = 0;
						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
						//������ʵʱXYZ-YAW�����ٶ�����		
						rt_tar.st_data.yaw_dps = -30;
						rt_tar.st_data.vel_x =25;
						rt_tar.st_data.vel_y =0;
						rt_tar.st_data.vel_z =0;
					
					  dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�
					
					  mission_step += 1;
					  time_dly_cnt_ms = 0;
						
					  sprintf(buf1,"[s9]��ת180��");//\[b1] ��ӭ���٣����
					  speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						  
				}
				break;
				case state_num+4:
				{
					//��5��
					if(time_dly_cnt_ms<6000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}	
					
//					 mission_step += Rotate(0x08,36,30);
//						time_dly_cnt_ms = 0;
				}
				break;
				case state_num+5:
				{
					//��ת90��
					  rt_tar.st_data.rol = 0;
						rt_tar.st_data.pit = 0;
						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
						//������ʵʱXYZ-YAW�����ٶ�����		
						rt_tar.st_data.yaw_dps = 30;
						rt_tar.st_data.vel_x =0;
						rt_tar.st_data.vel_y =0;
						rt_tar.st_data.vel_z =0;
					
					  dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�	
					
					  time_dly_cnt_ms = 0;
						mission_step += 1;
					
						sprintf(buf1,"[s9]��ת��ʮ��");//\[b1] ��ӭ���٣����
					  speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);					
						
				}
				break;
				
				case state_num+6:
				{
					//ִ��һ������
					OneKey_Land();
					
					time_dly_cnt_ms = 0;
					mission_step += 1;
					
					sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					
				}
				break;
				case state_num+7:
				{
					
				}
				break;				
				default:break;
			}
			