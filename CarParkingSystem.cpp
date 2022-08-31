
# define F_CPU 8000000UL
#include <avr/io.h>
# include <util/delay.h>
void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num);
void disp_string(  char *str);

int main(void)
{
	
	DDRB = 0XFF;
	DDRC = 0X00;
	lcd_init();
	disp_cmd(0X80);
	disp_string("WELCOME");
	_delay_ms(1000);
	disp_cmd(0X01);
	_delay_ms(2);
	disp_cmd(0X80);
	disp_string("CAR PARKING ");
	disp_cmd(0XC0);
	disp_string("    SYSTEM");
	

	
	int x=0;
	while (1)
	{
		
		
		_delay_ms(1000);
		disp_cmd(0X01);
		_delay_ms(2);
		disp_cmd(0X80);
		disp_string("NUMBER OF CARS");
		
		
		if(PINC==0X01)
		{
			x++;
			
		}
		disp_cmd(0XC4);
		disp_num(x);
		
		_delay_ms(1000);
	}
	return 0;
}


void disp_cmd(unsigned int cmd)
{
	PORTB=((cmd & 0XF0)+0X04);
	_delay_ms(1);
	PORTB=PORTB - 0X04;
	PORTB=(((cmd<<4)& 0XF0)+0X04);
	_delay_ms(1);
	PORTB=PORTB-0X04;
	
}
void disp_data( int cmd)
{
	PORTB=((cmd  & 0XF0)+0X05);
	_delay_ms(1);
	PORTB=PORTB - 0X04;
	PORTB=(((cmd <<4)& 0XF0)+0X05);
	_delay_ms(1);
	PORTB=PORTB-0X04;
	
}

void disp_string( char *str)
{
	int i=0;
	while (str[i]!='\0')
	{
		disp_data (str[i]);
		i++;
		
	}
}

void disp_num(unsigned int num)
{
	int a=0;
	if (num==0)
	{
		disp_data(48);
	}
	disp_cmd (0X04);
	while (num!=0)
	{
		a=num % 10;
		disp_data(a+48);
		num=num/10;
	}
	disp_cmd (0X06);
}
void lcd_init()
{
	disp_cmd(0X02);
	disp_cmd(0X28);
	disp_cmd(0X0C);
	disp_cmd(0X06);
}