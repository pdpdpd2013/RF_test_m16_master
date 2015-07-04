//设一个变量：记录KEY()的返回值
#define		KEY_DDR		DDRC
#define		KEY_PORT   PORTC
#define 	KEY_PIN		PINC

//说明：采用线反转法4*4键盘   采用PA口
//键值：  第一列A3 第二列A2 第三列A1 第四列A0
//A7第一行：0x77   0x7b    0x7d    0x7e
//A6第二行：0xb7   0xbb    0xbd    0xbe
//A5第三行：0xd7   0xdb    0xdd    0xde
//A4第四行：0xe7   0xeb    0xed    0xee
//快速读状态，不延时
unsigned char KEY(void)
{
	KEY_PORT=0X0F;
	KEY_DDR=0XF0;				//高4位出低，低4位拉高
	unsigned char key_data=0;	//保存按键状态的变量	
	if(KEY_PIN!=0x0F)			//若有按键按下
	{
		_delay_ms(10);			//防抖动
		key_data=KEY_PIN;		//保存此时低四位的状态

		KEY_PORT=0XF0;
		KEY_DDR=0X0F;			//高4位拉高，低4位出低
		key_data|=KEY_PIN;		//保存此时高四位的状态，并与低四位合并

		while(KEY_PIN!=0xF0);	//等待按键释放
		_delay_ms(10);			//延时消抖
		while(KEY_PIN!=0xF0);	//等待按键释放
		switch(key_data)		//对按键的值编码
		{
			case 0x77:key_data=1; break;	//第一行
			case 0x7b:key_data=2; break;
			case 0x7d:key_data=3; break;
			case 0x7e:key_data=4; break;
			case 0xb7:key_data=5; break;	//第二行
			case 0xbb:key_data=6; break;
			case 0xbd:key_data=7; break;
			case 0xbe:key_data=8; break;
			case 0xd7:key_data=9; break;	//第三行
			case 0xdb:key_data=10;break;
			case 0xdd:key_data=11;break;
			case 0xde:key_data=12;break;
			case 0xe7:key_data=13;break;	//第四行
			case 0xeb:key_data=14;break;
			case 0xed:key_data=15;break;
			case 0xee:key_data=16;break;
			default:key_data=0;break;		//无有效按键
		}
	}
	return (key_data);						//返回键值
}
