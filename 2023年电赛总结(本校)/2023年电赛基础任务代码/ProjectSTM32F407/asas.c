				case state_num:
				{
					//在杆子附近起飞，可能先开始啥都找不到，硬着头皮x周直飞。如果找到杆子，接着直飞，如果找到黑线，就巡线
					
					//利用id05，在在串口5中获得高度，在这里计算z轴速度，利用实时控制帧控制飞机上升还是下降
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
//						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
//						//这里会把实时XYZ-YAW期望速度置零		
//						rt_tar.st_data.yaw_dps =0;// yaw_16;
//						rt_tar.st_data.vel_x =0;//speed_x_axis_16;
//						rt_tar.st_data.vel_y =0;//;
//						rt_tar.st_data.vel_z = speed_z_axis_16;

//						dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。
						
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
							rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
							//这里会把实时XYZ-YAW期望速度置零		
							rt_tar.st_data.yaw_dps = yaw_16;
							rt_tar.st_data.vel_x =speed_x_axis_16;
							rt_tar.st_data.vel_y =speed_y_axis_16;
							rt_tar.st_data.vel_z = speed_z_axis_16;

							dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。
							
							
							sprintf(buf1,"[s9]巡线");//\[b1] 欢迎光临，请进
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
//						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
//						//这里会把实时XYZ-YAW期望速度置零		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =0;
//						rt_tar.st_data.vel_y =0;
//						rt_tar.st_data.vel_z = speed_z_axis_16;

//						dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。
//						
//						
//						sprintf(buf1,"[s9]调节高度");//\[b1] 欢迎光临，请进
//					  speak_len1=strlen(buf1);
//						speak_context((u8*)buf1,speak_len1);

//						
//					}
//					else
//					{
//						time_dly_cnt_ms = 0;
//						mission_step += 1;
//					}

//            mission_step += Lifting_Height(50,10);//上升高度
//            time_dly_cnt_ms = 0;

//            
//            rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
//						//这里会把实时XYZ-YAW期望速度置零		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =0;
//						rt_tar.st_data.vel_y =0;
//						rt_tar.st_data.vel_z =0;
//					
//					  dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。

//					   OneKey_Land();
					
//             mission_step += 1;
//					   time_dly_cnt_ms = 0;
//						 
//						 sprintf(buf1,"[s9]降落");//\[b1] 欢迎光临，请进
//					   speak_len1=strlen(buf1);
//						 speak_context((u8*)buf1,speak_len1);

				}
				break;
				
				
				
				case state_num+1:
				{
					//等5秒
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
//					//前进1米
//					//mission_step += Horizontal_Move(100,150,0);
//          //time_dly_cnt_ms = 0;
//					
//					//左转90度
//          //mission_step += Rotate(0x08,36,30);
//				  //time_dly_cnt_ms = 0;
//					
//					//左转90度
//					OneKey_Land();
//					
//					time_dly_cnt_ms = 0;
//					mission_step += 1;
////						rt_tar.st_data.rol = 0;
////						rt_tar.st_data.pit = 0;
////						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
////						//这里会把实时XYZ-YAW期望速度置零		
////						rt_tar.st_data.yaw_dps = 30;
////						rt_tar.st_data.vel_x =25;
////						rt_tar.st_data.vel_y =0;
////						rt_tar.st_data.vel_z =0;
////					
////					  dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。
////					
////					  mission_step +=1;//下降高度
////					  time_dly_cnt_ms = 0;

////              mission_step +=target_location(100,100);
////              time_dly_cnt_ms = 0;							
//					
//					  sprintf(buf1,"[s9]旋转360");//\[b1] 欢迎光临，请进
//					  speak_len1=strlen(buf1);
//						speak_context((u8*)buf1,speak_len1);
//					
//				}
//				break;	
				case state_num+2:
				{
					//等5秒
					if(time_dly_cnt_ms<10000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}
					
//					mission_step += Horizontal_Move(50,20,0);//前进一米
//				  time_dly_cnt_ms = 0;				

				}
				break;
        case state_num+3:
				{
					//前进1米
					//mission_step +=Falling_Head1(50,10);//下降高度
					//mission_step +=Lifting_Height1(50，10);//上升高度
					  rt_tar.st_data.rol = 0;
						rt_tar.st_data.pit = 0;
						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
						//这里会把实时XYZ-YAW期望速度置零		
						rt_tar.st_data.yaw_dps = -30;
						rt_tar.st_data.vel_x =25;
						rt_tar.st_data.vel_y =0;
						rt_tar.st_data.vel_z =0;
					
					  dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。
					
					  mission_step += 1;
					  time_dly_cnt_ms = 0;
						
					  sprintf(buf1,"[s9]旋转180度");//\[b1] 欢迎光临，请进
					  speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						  
				}
				break;
				case state_num+4:
				{
					//等5秒
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
					//左转90度
					  rt_tar.st_data.rol = 0;
						rt_tar.st_data.pit = 0;
						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
						//这里会把实时XYZ-YAW期望速度置零		
						rt_tar.st_data.yaw_dps = 30;
						rt_tar.st_data.vel_x =0;
						rt_tar.st_data.vel_y =0;
						rt_tar.st_data.vel_z =0;
					
					  dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。	
					
					  time_dly_cnt_ms = 0;
						mission_step += 1;
					
						sprintf(buf1,"[s9]左转九十度");//\[b1] 欢迎光临，请进
					  speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);					
						
				}
				break;
				
				case state_num+6:
				{
					//执行一键降落
					OneKey_Land();
					
					time_dly_cnt_ms = 0;
					mission_step += 1;
					
					sprintf(buf1,"[s9]降落");//\[b1] 欢迎光临，请进
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
			