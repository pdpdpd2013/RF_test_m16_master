unsigned char ur_data=0;	//存储串口接收到的数据
//串口初始化
void Usart_Init(unsigned int baud)
{
	DDRD|=0X02;								//TXD设置输出，增强抗干扰能力。
	DDRD&=~(1<<0);
	PORTD|=0X03;							//RXD内部上拉有效
	UBRRH=(unsigned char)(baud>>8);			//设置波特率:fosc/(16*(UBRR+1))
	UBRRL=(unsigned char)baud;
	UCSRB|=(1<<RXEN)|(1<<TXEN);				//使能接收、发送
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);//Z1Z0:00-11,5-8位数据
	//设置帧格式：8位数据，1位停止位（USBS=1时2位），无校验位
	UCSRB|=(0<<TXCIE)|(1<<RXCIE)|(0<<UDRIE);//中断允许
} 
//发送数据
void Usart_Transmit(unsigned char data)
{
	while(!(UCSRA&(1<<UDRE)));				//等待发送寄存器空
	UDR=data;								//将数据放入缓冲器，发送
}
//接收中断
SIGNAL(SIG_UART_RECV)
{
	unsigned char data=0;
	data=UDR;
	Usart_Transmit(data);
	ur_data=data;
}
