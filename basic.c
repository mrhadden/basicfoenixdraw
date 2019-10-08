#include "basic.h"

#define BITMAP_SEG0   ((char far*)0xB00000)
#define BITMAP_SEG1   ((char far*)0xB10000)
#define BITMAP_SEG2   ((char far*)0xB20000)
#define BITMAP_SEG3   ((char far*)0xB30000)
#define BITMAP_SEG4   ((char far*)0xB40000)
		
void k_clear_screen(int bcolor);

void k_enable_border(void);
void k_disable_border(void);
void k_set_border_color(char r,char g,char b);

void k_set_text_gamma(char c);
void k_set_text_color(char c);

void setFColors(void);
void setBColors(void);
void  k_test_graphics(void);

void far setColors(void);

#define GRP_LUT_BASE_ADDR GRPH_LUT0_PTR

void main(void)
{
	k_test_graphics();
}


char * k_pad_string(char * dest,char * src,char filler,int width)
{
	int len = 0;

	memset(dest,0,width + 1);
	memset(dest,filler,width);

	len = strlen(src);

	if(len > width)
		len = width;
	
	memcpy(&dest[width - len],src,len);

	return dest;
}

void k_test_graphics(void)
{
	char bg[12] = {0x30,0x40,0x50,0x60,0x70,0x80,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0};
	
	char fcolor = 0x01;
	int i = 0;
	int offset = 0;
	char c = 0;
	char color = 0;

	*BM_START_ADDY_L = 0x00;
	*BM_START_ADDY_M = 0x00;
	*BM_START_ADDY_H = 0x00;
	*((char far*)0xAF1F80) = 0x02;
	
	*BM_X_SIZE_L = 0x80;
	*BM_X_SIZE_H = 0x02;	
	*BM_Y_SIZE_L = 0xE0;
	*BM_Y_SIZE_H = 0x01;	
	
	*FG_CHAR_LUT_PTR    = 0x00;
	*BG_CHAR_LUT_PTR    = 0x00;
	*BM_CONTROL_REG 	= 0x08;
	*MASTER_CTRL_REG_L 	= 0x0C;

	k_set_border_color(0xAA,0xAA,0xAA);
	
	while(1)
	{
		offset = 0;

		//for(fcolor=0x10;fcolor<0xF0;fcolor+=0x10)		
		for(fcolor=0;fcolor<10;fcolor++)		
		{
			
			
			memset((unsigned char far *)BITMAP_BANK_0,fcolor + 0,0xffff);
			memset((unsigned char far *)BITMAP_BANK_1,fcolor + 1,0xffff);
			memset((unsigned char far *)BITMAP_BANK_2,fcolor + 2,0xffff);
			memset((unsigned char far *)BITMAP_BANK_3,fcolor + 3,0xffff);
			memset((unsigned char far *)BITMAP_BANK_4,fcolor + 4,0xffff);
			
			for(i=0x0000;i<0xFFFF;i++)
			{		
				((unsigned char far *)BITMAP_BANK_0)[i] = (char)fcolor + 0;
				
				((unsigned char far *)BITMAP_BANK_1)[i] = (char)fcolor + 1;

				((unsigned char far *)BITMAP_BANK_2)[i] = (char)fcolor + 2;
				
				((unsigned char far *)BITMAP_BANK_3)[i] = (char)fcolor + 3;
				
				((unsigned char far *)BITMAP_BANK_4)[i] = (char)fcolor + 4;
			}	

			k_set_border_color(bg[offset],bg[offset],bg[offset]);
			
			offset++;
			if(offset > 11)
				offset = 0;
			
		}
	
	}
	
	return;
}

void k_disable_border(void)
{
	BORDER_CTRL_REG[0] = 0x00 ;
}

void k_set_border_color(char r,char g,char b)
{
	BORDER_COLOR_B[0] = b;
	BORDER_COLOR_G[0] = g;
	BORDER_COLOR_R[0] = r;
}

void k_clear_screen(int bcolor)
{
	memset((unsigned char far *)0xAFA000,0,0xAFA000 + 0xC000);
	memset((unsigned char far *)0xAFC000,bcolor,0xAFA000 + 0xC000);
}


void k_set_background(int col,int row,int bcolor)
{
	((volatile unsigned char far *)(0xAFC000 + (128 * row) + col))[0] =  bcolor;
}



void far setColors(void)
{
	unsigned long colorIndex = 0;
	
	//colorIndex = 0;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;
	
	//colorIndex = 1 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;
	
	//colorIndex = 2 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;


	//colorIndex = 3 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 4 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 5 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 6 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x80;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 7 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x45;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 8 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x13;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x45;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x8B;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 9 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x20;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 10 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x20;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 11 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x20;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 12 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x00;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 13 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x20;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x20;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x20;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 14 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x40;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x40;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0x40;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;

	//colorIndex = 15 * 4;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;
	GRP_LUT_BASE_ADDR[colorIndex++] = 0xFF;
	
}
