#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"	
#include "touch.h"		
#include "usart3.h"
#include "common.h" 
#include "timer1.h"

/************************************************
 ALIENTEK STM32F103开发板 扩展实验5
 ATK-RM04 WIFI模块测试实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

u8 digital=0;

int main()
{
	u8 key;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	usart3_init(115200);
	usmart_dev.init(72);		//初始化USMART
	KEY_Init();
	atk_8266_test();
	while(1)
 {
	key=KEY_Scan(0);
	if(USART3_RX_STA&0x8000)
	{
		printf("USART3_RX_BUF=%s\r\n",USART3_RX_BUF);
		digital=USART3_RX_BUF[USART3_MAX_RECV_LEN-1];
		TIM3_Int_Init(9999,7199);
		USART3_RX_STA=0;
	}
		if(key==KEY1_PRES)
	{
		 TIM_Cmd(TIM3,ENABLE);
	}
 }
}

void TIM3_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		digital=digital-1;
		printf("\r\n当前数值为%d,正在倒计时\r\n\r\n",digital);
		delay_ms(200);
		if(digital==0)
		{
			printf("\r\n当前数值为0,计数完毕\r\n\r\n");
			TIM_Cmd(TIM3,DISABLE);
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIM7更新中断标志    
	}	    
}

// int main(void)
// {	 
//	u8 key,fontok=0; 	    
//	delay_init();	    	 //延时函数初始化	  
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//	uart_init(115200);	 	//串口初始化为115200
// 	usmart_dev.init(72);		//初始化USMART		
// 	LED_Init();		  			//初始化与LED连接的硬件接口
//	KEY_Init();					//初始化按键
//	LCD_Init();			   		//初始化LCD   
//	W25QXX_Init();				//初始化W25Q128
//	tp_dev.init();				//初始化触摸屏
//	usart3_init(115200);		//初始化串口3 
// 	my_mem_init(SRAMIN);		//初始化内部内存池
//	exfuns_init();				//为fatfs相关变量申请内存  
// 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
// 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
//	key=KEY_Scan(0);  
//	if(key==KEY0_PRES&&((tp_dev.touchtype&0X80)==0))//强制校准
//	{
//		LCD_Clear(WHITE);		//清屏0
//		TP_Adjust();  			//屏幕校准 
//		TP_Save_Adjdata();	  
//		LCD_Clear(WHITE);		//清屏
//	}
//	fontok=font_init();			//检查字库是否OK
//	if(fontok||key==KEY1_PRES)	//需要更新字库				 
//	{
//		LCD_Clear(WHITE);		//清屏
// 		POINT_COLOR=RED;		//设置字体为红色	   	   	  
//		LCD_ShowString(60,50,200,16,16,"ALIENTEK STM32");
//		while(SD_Init())		//检测SD卡
//		{
//			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
//			delay_ms(200);
//			LCD_Fill(60,70,200+60,70+16,WHITE);
//			delay_ms(200);		    
//		}								 						    
//		LCD_ShowString(60,70,200,16,16,"SD Card OK");
//		LCD_ShowString(60,90,200,16,16,"Font Updating...");
//		key=update_font(20,110,16,"0:");//从SD卡更新
//		while(key)//更新失败		
//		{			 		  
//			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
//			delay_ms(200);
//			LCD_Fill(20,110,200+20,110+16,WHITE);
//			delay_ms(200);		       
//		} 		  
//		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
//		delay_ms(1500);	
//		LCD_Clear(WHITE);//清屏	       
//	}  
//	atk_8266_test();		//进入ATK_ESP8266测试
//}










