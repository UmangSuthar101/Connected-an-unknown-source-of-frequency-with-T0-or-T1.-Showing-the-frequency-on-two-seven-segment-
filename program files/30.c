#include<reg51.h>
#define lcd P1
sbit rs=P3^0;
sbit e=P3^1;

unsigned long z=0;
void delay (int);
void display (unsigned char);
void cmd (unsigned char);
void init (void);
void string (char *);
void intro (void);
char i=0;

	
void delay (int i)
{
	int j=0;
	for(j=0;j<i;j++)
	{
		TMOD=0x51;
		TH0=0xFC;
		TL0=0x66;
		TR0=1;
		while(TF0==0);
		TR0=0;
		TF0=0;
	}
}

void cmd (unsigned char c)
{
	lcd=c;
	rs=0;
	e=1;
	delay(10);
	e=0;
}
void display (unsigned char c)
{
	lcd=c;
	rs=1;
	e=1;
	delay(10);
	e=0;
}
void string (char *c)
{
	while(*c)
	{
		display(*c++);
	}
}
void init (void)
{
	cmd(0x38);
	cmd(0x01);
  cmd(0x0c);
	cmd(0x80);
}
void intro (void)
{
	cmd(0x80);
	string("    LYMBEDGE  ");
	cmd(0xc0);
	string("    ROBOTICS     ");
	delay(2000);
	cmd(0x01);
	cmd(0x80);
	string("   FREQUENCY   ");
	cmd(0xc0);
	string("    COUNTER    ");
	delay(2000);
	cmd(0x01);
	cmd(0x80);
}

void main()
{
	unsigned int temp=0;
	unsigned int temp1=0;
	unsigned int frequency;
	init();
	intro();
	delay(100);
	while(1)
	{
				
	  TMOD=0x51;
		TH1=0;
		TL1=0;
		TR1=1;
		delay(100);
		TR1=0;
		frequency=(TH1*256)+TL1;
		frequency=frequency*10;
  	
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(i==0)
		{
			string("FREQUENCY In Hz");
			i++;
		}
		
		
   	cmd(0xc5);
		if((frequency>=1) && (frequency<10))
		{
			string("    ");
	  	temp=frequency*10000;
  		temp1=((temp/10000)+48);
  		display(temp1);
			
	  }
	  else if((frequency>=10) && (frequency<100))
		{
			string("   ");
	 		temp=frequency*1000;
  		temp1=((temp/10000)+48);
  		display(temp1);
		
			temp1=(((temp/1000)%10)+48);
	  	display(temp1);
					
		}
		//////////////////////////////////////////////////////////////////////
		else if((frequency>=100) && (frequency<1000))//1234
		{
			string("  ");
	 		temp=frequency*100;
  		temp1=((temp/10000)+48);
  		display(temp1);
		
			temp1=(((temp/1000)%10)+48);
	  	display(temp1);
			
			temp1=(((temp/100)%10)+48);
			display(temp1);
				
		}
		
		else if((frequency>=1000) && (frequency<10000))//1234
		{
			string(" ");
	 		temp=frequency*10;
  		temp1=((temp/10000)+48);
  		display(temp1);
		
			temp1=(((temp/1000)%10)+48);
	  	display(temp1);
			
			temp1=(((temp/100)%10)+48);
			display(temp1);
			
			temp1=(((temp/10)%10)+48);
			display(temp1);
				
		}
		else if((frequency>=10000) && (frequency<100000))//12345
		{
	 		temp=frequency*1;
  		temp1=((temp/10000)+48);
  		display(temp1);
		
			temp1=(((temp/1000)%10)+48);
	  	display(temp1);
			
			temp1=(((temp/100)%10)+48);
			display(temp1);
			
			temp1=(((temp/10)%10)+48);
			display(temp1);
			
			temp1=((temp%10)+48);
			display(temp1);
			
				
		}
		else
		{
			string("    0");
		}	
		delay(500);
 }
while(1);	
}
