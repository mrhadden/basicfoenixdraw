
#ifndef __BASIC_STD
#define __BASIC_STD 

#include <stdlib.h>
#include <string.h>




#ifdef USING_816
	
	#ifdef USING_DEBUG	

	#else

	#endif
	
//* Addresses are the byte AFTER the block. Use this to confirm block locations and check for overlaps
	#define BANK0_BEGIN       ((volatile unsigned char *)0x000000) //Start of bank 0 and Direct page
	#define unused_0000       ((volatile unsigned char *)0x000000) //12 Bytes unused
	#define SCREENBEGIN       ((volatile unsigned char *)0x00000C) //3 Bytes Start of screen in video RAM. This is the upper-left corrner of the current video page being written to. This may not be what's being displayed by VICKY. Update this if you change VICKY's display page.
	#define COLS_VISIBLE      ((volatile unsigned char *)0x00000F) //2 Bytes Columns visible per screen line. A virtual line can be longer than displayed, up to COLS_PER_LINE long. Default  80
	#define COLS_PER_LINE     ((volatile unsigned char *)0x000011) //2 Bytes Columns in memory per screen line. A virtual line can be this long. Default128
	#define LINES_VISIBLE     ((volatile unsigned char *)0x000013) //2 Bytes The number of rows visible on the screen. Default25
	#define LINES_MAX         ((volatile unsigned char *)0x000015) //2 Bytes The number of rows in memory for the screen. Default64
	#define CURSORPOS         ((volatile unsigned char *)0x000017) //3 Bytes The next character written to the screen will be written in this location.
	#define CURSORX           ((volatile unsigned char *)0x00001A) //2 Bytes This is where the blinking cursor sits. Do not edit this direectly. Call LOCATE to update the location and handle moving the cursor correctly.
	#define CURSORY           ((volatile unsigned char *)0x00001C) //2 Bytes This is where the blinking cursor sits. Do not edit this direectly. Call LOCATE to update the location and handle moving the cursor correctly.
	#define CURCOLOR_L        ((volatile unsigned char *)0x00001E) //2 Bytes Color of next character to be printed to the screen.
	#define CURCOLOR_H        ((volatile unsigned char *)0x00001F) //2 Bytes Color of next character to be printed to the screen.
	#define CURATTR           ((volatile unsigned char *)0x000020) //2 Bytes Attribute of next character to be printed to the screen.
	#define STACKBOT          ((volatile unsigned char *)0x000022) //2 Bytes Lowest location the stack should be allowed to write to. If SP falls below this value, the runtime should generate STACK OVERFLOW error and abort.
	#define STACKTOP          ((volatile unsigned char *)0x000024) //2 Bytes Highest location the stack can occupy. If SP goes above this value, the runtime should generate STACK OVERFLOW error and abort.
	
	
	
	//CONTROL BITS FIELDS)
	#define MSTR_CTRL_TEXT_MODE_EN    (0x01)
	#define MSTR_CTRL_TEXT_OVERLAY    (0x02)//        ENABLE THE OVERLAY OF THE TEXT MODE ON TOP OF GRAPHIC MODE (THE BACKGROUND COLOR IS IGNORED))
	#define MSTR_CTRL_GRAPH_MODE_EN   (0x04)
	#define MSTR_CTRL_BITMAP_EN       (0x08)
	#define MSTR_CTRL_TILEMAP_EN      (0x10)
	#define MSTR_CTRL_SPRITE_EN       (0x20)
	#define MSTR_CTRL_GAMMA_EN        (0x40)
	#define MSTR_CTRL_DISABLE_VID     (0x80)
	#define MASTER_CTRL_REG_L	   ((volatile unsigned char *)0xAF0000)
	#define MASTER_CTRL_REG_H	   ((volatile unsigned char *)0xAF0001)
	
	#define VKY_RESERVED_00           ((volatile unsigned char *)0xAF0002)
	#define VKY_RESERVED_01           ((volatile unsigned char *)0xAF0003)
	#define BORDER_CTRL_REG           ((volatile unsigned char *)0xAF0004)
	#define BORDER_CTRL_ENABLE        0x01
	#define BORDER_COLOR_B            ((volatile unsigned char *)0xAF0005)
	#define BORDER_COLOR_G            ((volatile unsigned char *)0xAF0006)
	#define BORDER_COLOR_R            ((volatile unsigned char *)0xAF0007)

	#define VKY_TXT_CURSOR_CTRL_REG   ((volatile unsigned char *)0xAF0010)//   [0]  ENABLE TEXT MODE)
	#define VKY_CURSOR_ENABLE         ((volatile unsigned char *)0x01)
	#define VKY_CURSOR_FLASH_RATE0    ((volatile unsigned char *)0x02)
	#define VKY_CURSOR_FLASH_RATE1    ((volatile unsigned char *)0x04)
	#define VKY_CURSOR_FONT_PAGE0     ((volatile unsigned char *)0x08)//        PICK FONT PAGE 0 OR FONT PAGE 1)
	#define VKY_CURSOR_FONT_PAGE1     ((volatile unsigned char *)0x10)//       PICK FONT PAGE 0 OR FONT PAGE 1)
	#define VKY_TXT_RESERVED          ((volatile unsigned char *)0xAF0011)//   NOT IN USE)
	#define VKY_TXT_CURSOR_CHAR_REG   ((volatile unsigned char *)0xAF0012)

	#define VKY_TXT_CURSOR_COLR_REG   ((volatile unsigned char *)0xAF0013)
	#define VKY_TXT_CURSOR_X_REG_L    ((volatile unsigned char *)0xAF0014)
	#define VKY_TXT_CURSOR_X_REG_H    ((volatile unsigned char *)0xAF0015)
	#define VKY_TXT_CURSOR_Y_REG_L    ((volatile unsigned char *)0xAF0016)
	#define VKY_TXT_CURSOR_Y_REG_H    ((volatile unsigned char *)0xAF0017)

	#define VKY_INFO_CHIP_NUM_L       ((volatile unsigned char *)0xAF001C)
	#define VKY_INFO_CHIP_NUM_H       ((volatile unsigned char *)0xAF001D)
	#define VKY_INFO_CHIP_VER_L       ((volatile unsigned char *)0xAF001E)
	#define VKY_INFO_CHIP_VER_H       ((volatile unsigned char *)0xAF001F)

	//)
	// BIT FIELD DEFINITION FOR THE CONTROL REGISTER)
	#define TILE_ENABLE               ((volatile unsigned char *)0x01)
	#define TILE_LUT0                 ((volatile unsigned char *)0x02)
	#define TILE_LUT1                 ((volatile unsigned char *)0x04)
	#define TILE_LUT2                 ((volatile unsigned char *)0x08)
	#define TILESHEET_256X256_EN      ((volatile unsigned char *)0x80)//    0 -> SEQUENTIAL, 1-> 256X256 TILE SHEET STRIDING)
	//)
	//TILE MAP LAYER 0 REGISTERS)
	#define TL0_CONTROL_REG           ((volatile unsigned char *)0xAF0100)//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL0_START_ADDY_L          ((volatile unsigned char *)0xAF0101)//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL0_START_ADDY_M          ((volatile unsigned char *)0xAF0102)
	#define TL0_START_ADDY_H          ((volatile unsigned char *)0xAF0103)
	#define TL0_MAP_X_STRIDE_L        ((volatile unsigned char *)0xAF0104)//        THE STRIDE OF THE MAP)
	#define TL0_MAP_X_STRIDE_H        ((volatile unsigned char *)0xAF0105)
	#define TL0_MAP_Y_STRIDE_L        ((volatile unsigned char *)0xAF0106)//        THE STRIDE OF THE MAP)
	#define TL0_MAP_Y_STRIDE_H        ((volatile unsigned char *)0xAF0107)
	//TL0_RESERVED_0            ((volatile unsigned char *)0xAF0108)
	//TL0_RESERVED_1            ((volatile unsigned char *)0xAF0109)
	//TL0_RESERVED_2            ((volatile unsigned char *)0xAF010A)
	//TL0_RESERVED_3            ((volatile unsigned char *)0xAF010B)
	//TL0_RESERVED_4            ((volatile unsigned char *)0xAF010C)
	//TL0_RESERVED_5            ((volatile unsigned char *)0xAF010D)
	//TL0_RESERVED_6            ((volatile unsigned char *)0xAF010E)
	//TL0_RESERVED_7            ((volatile unsigned char *)0xAF010F)
	//TILE MAP LAYER 1 REGISTERS)
	#define TL1_CONTROL_REG           ((volatile unsigned char *)0xAF0108)//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL1_START_ADDY_L          ((volatile unsigned char *)0xAF0109)//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL1_START_ADDY_M          ((volatile unsigned char *)0xAF010A)
	#define TL1_START_ADDY_H          ((volatile unsigned char *)0xAF010B)
	#define TL1_MAP_X_STRIDE_L        ((volatile unsigned char *)0xAF010C)//        THE STRIDE OF THE MAP)
	#define TL1_MAP_X_STRIDE_H        ((volatile unsigned char *)0xAF010D)
	#define TL1_MAP_Y_STRIDE_L        ((volatile unsigned char *)0xAF010E)//        THE STRIDE OF THE MAP)
	#define TL1_MAP_Y_STRIDE_H        ((volatile unsigned char *)0xAF010F)
	//TL1_RESERVED_0            ((volatile unsigned char *)0xAF0118)
	//TL1_RESERVED_1            ((volatile unsigned char *)0xAF0119)
	//TL1_RESERVED_2            ((volatile unsigned char *)0xAF011A)
	//TL1_RESERVED_3            ((volatile unsigned char *)0xAF011B)
	//TL1_RESERVED_4            ((volatile unsigned char *)0xAF011C)
	//TL1_RESERVED_5            ((volatile unsigned char *)0xAF011D)
	//TL1_RESERVED_6            ((volatile unsigned char *)0xAF011E)
	//TL1_RESERVED_7            ((volatile unsigned char *)0xAF011F)
	//TILE MAP LAYER 2 REGISTERS)
	#define TL2_CONTROL_REG           ((volatile unsigned char *)0xAF0110)//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL2_START_ADDY_L          ((volatile unsigned char *)0xAF0111)//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL2_START_ADDY_M          ((volatile unsigned char *)0xAF0112)
	#define TL2_START_ADDY_H          ((volatile unsigned char *)0xAF0113)
	#define TL2_MAP_X_STRIDE_L        ((volatile unsigned char *)0xAF0114)//        THE STRIDE OF THE MAP)
	#define TL2_MAP_X_STRIDE_H        ((volatile unsigned char *)0xAF0115)
	#define TL2_MAP_Y_STRIDE_L        ((volatile unsigned char *)0xAF0116)//        THE STRIDE OF THE MAP)
	#define TL2_MAP_Y_STRIDE_H        ((volatile unsigned char *)0xAF0117)
	//TL2_RESERVED_0            ((volatile unsigned char *)0xAF0128)
	//TL2_RESERVED_1            ((volatile unsigned char *)0xAF0129)
	//TL2_RESERVED_2            ((volatile unsigned char *)0xAF012A)
	//TL2_RESERVED_3            ((volatile unsigned char *)0xAF012B)
	//TL2_RESERVED_4            ((volatile unsigned char *)0xAF012C)
	//TL2_RESERVED_5            ((volatile unsigned char *)0xAF012D)
	//TL2_RESERVED_6            ((volatile unsigned char *)0xAF012E)
	//TL2_RESERVED_7            ((volatile unsigned char *)0xAF012F)
	//TILE MAP LAYER 3 REGISTERS)
	#define TL3_CONTROL_REG           ((volatile unsigned char *)0xAF0118)//        BIT[0] - ENABLE, BIT[3:1] - LUT SELECT,)
	#define TL3_START_ADDY_L          ((volatile unsigned char *)0xAF0119)//        NOT USED RIGHT NOW - STARTING ADDRESS TO WHERE IS THE MAP)
	#define TL3_START_ADDY_M          ((volatile unsigned char *)0xAF011A)
	#define TL3_START_ADDY_H          ((volatile unsigned char *)0xAF011B)
	#define TL3_MAP_X_STRIDE_L        ((volatile unsigned char *)0xAF011C)//        THE STRIDE OF THE MAP)
	#define TL3_MAP_X_STRIDE_H        ((volatile unsigned char *)0xAF011D)
	#define TL3_MAP_Y_STRIDE_L        ((volatile unsigned char *)0xAF011E)//        THE STRIDE OF THE MAP)
	#define TL3_MAP_Y_STRIDE_H        ((volatile unsigned char *)0xAF011F)
	//TL3_RESERVED_0            ((volatile unsigned char *)0xAF0138)
	//TL3_RESERVED_1            ((volatile unsigned char *)0xAF0139)
	//TL3_RESERVED_2            ((volatile unsigned char *)0xAF013A)
	//TL3_RESERVED_3            ((volatile unsigned char *)0xAF013B)
	//TL3_RESERVED_4            ((volatile unsigned char *)0xAF013C)
	//TL3_RESERVED_5            ((volatile unsigned char *)0xAF013D)
	//TL3_RESERVED_6            ((volatile unsigned char *)0xAF013E)
	//TL3_RESERVED_7            ((volatile unsigned char *)0xAF013F)
	//BITMAP REGISTERS)
	#define BM_CONTROL_REG            ((volatile unsigned char *)0xAF0140)
	#define BM_START_ADDY_L           ((volatile unsigned char *)0xAF0141)
	#define BM_START_ADDY_M           ((volatile unsigned char *)0xAF0142)
	#define BM_START_ADDY_H           ((volatile unsigned char *)0xAF0143)
	#define BM_X_SIZE_L               ((volatile unsigned char *)0xAF0144)
	#define BM_X_SIZE_H               ((volatile unsigned char *)0xAF0145)
	#define BM_Y_SIZE_L               ((volatile unsigned char *)0xAF0146)
	#define BM_Y_SIZE_H               ((volatile unsigned char *)0xAF0147)

	#define ASM_BM_CONTROL_REG           $AF0140
	#define ASM_BM_START_ADDY_L          $AF0141
	#define ASM_BM_START_ADDY_M          $AF0142
	#define ASM_BM_START_ADDY_H          $AF0143
	#define ASM_BM_X_SIZE_L              $AF0144
	#define ASM_BM_X_SIZE_H              $AF0145
	#define ASM_BM_Y_SIZE_L              $AF0146
	#define ASM_BM_Y_SIZE_H              $AF0147


	#define BM_RESERVED_0             ((volatile unsigned char *)0xAF0148)
	#define BM_RESERVED_1             ((volatile unsigned char *)0xAF0149)
	#define BM_RESERVED_2             ((volatile unsigned char *)0xAF014A)
	#define BM_RESERVED_3             ((volatile unsigned char *)0xAF014B)
	#define BM_RESERVED_4             ((volatile unsigned char *)0xAF014C)
	#define BM_RESERVED_5             ((volatile unsigned char *)0xAF014D)
	#define BM_RESERVED_6             ((volatile unsigned char *)0xAF014E)
	#define BM_RESERVED_7             ((volatile unsigned char *)0xAF014F)
	//SPRITE REGISTERS)
	// BIT FIELD DEFINITION FOR THE CONTROL REGISTER)
	#define SPRITE_ENABLE               ((volatile unsigned char *)0x01)
	#define SPRITE_LUT0                 ((volatile unsigned char *)0x02)
	#define SPRITE_LUT1                 ((volatile unsigned char *)0x04)
	#define SPRITE_LUT2                 ((volatile unsigned char *)0x08)
	#define SPRITE_DEPTH0               ((volatile unsigned char *)0x10)
	#define SPRITE_DEPTH1               ((volatile unsigned char *)0x20)
	#define SPRITE_DEPTH2               ((volatile unsigned char *)0x40)

	// SPRITE 0 (HIGHEST PRIORITY))
	#define SP00_CONTROL_REG          ((volatile unsigned char *)0xAF0200)
	#define SP00_ADDY_PTR_L           ((volatile unsigned char *)0xAF0201)
	#define SP00_ADDY_PTR_M           ((volatile unsigned char *)0xAF0202)
	#define SP00_ADDY_PTR_H           ((volatile unsigned char *)0xAF0203)
	#define SP00_X_POS_L              ((volatile unsigned char *)0xAF0204)
	#define SP00_X_POS_H              ((volatile unsigned char *)0xAF0205)
	#define SP00_Y_POS_L              ((volatile unsigned char *)0xAF0206)
	#define SP00_Y_POS_H              ((volatile unsigned char *)0xAF0207)
	// SPRITE 1)
	#define SP01_CONTROL_REG          ((volatile unsigned char *)0xAF0208)
	#define SP01_ADDY_PTR_L           ((volatile unsigned char *)0xAF0209)
	#define SP01_ADDY_PTR_M           ((volatile unsigned char *)0xAF020A)
	#define SP01_ADDY_PTR_H           ((volatile unsigned char *)0xAF020B)
	#define SP01_X_POS_L              ((volatile unsigned char *)0xAF020C)
	#define SP01_X_POS_H              ((volatile unsigned char *)0xAF020D)
	#define SP01_Y_POS_L              ((volatile unsigned char *)0xAF020E)
	#define SP01_Y_POS_H              ((volatile unsigned char *)0xAF020F)
	// SPRITE 2)
	#define SP02_CONTROL_REG          ((volatile unsigned char *)0xAF0210)
	#define SP02_ADDY_PTR_L           ((volatile unsigned char *)0xAF0211)
	#define SP02_ADDY_PTR_M           ((volatile unsigned char *)0xAF0212)
	#define SP02_ADDY_PTR_H           ((volatile unsigned char *)0xAF0213)
	#define SP02_X_POS_L              ((volatile unsigned char *)0xAF0214)
	#define SP02_X_POS_H              ((volatile unsigned char *)0xAF0215)
	#define SP02_Y_POS_L              ((volatile unsigned char *)0xAF0216)
	#define SP02_Y_POS_H              ((volatile unsigned char *)0xAF0217)
	// SPRITE 3)
	#define SP03_CONTROL_REG          ((volatile unsigned char *)0xAF0218)
	#define SP03_ADDY_PTR_L           ((volatile unsigned char *)0xAF0219)
	#define SP03_ADDY_PTR_M           ((volatile unsigned char *)0xAF021A)
	#define SP03_ADDY_PTR_H           ((volatile unsigned char *)0xAF021B)
	#define SP03_X_POS_L              ((volatile unsigned char *)0xAF021C)
	#define SP03_X_POS_H              ((volatile unsigned char *)0xAF021D)
	#define SP03_Y_POS_L              ((volatile unsigned char *)0xAF021E)
	#define SP03_Y_POS_H              ((volatile unsigned char *)0xAF021F)
	// SPRITE 4)
	#define SP04_CONTROL_REG          ((volatile unsigned char *)0xAF0220)
	#define SP04_ADDY_PTR_L           ((volatile unsigned char *)0xAF0221)
	#define SP04_ADDY_PTR_M           ((volatile unsigned char *)0xAF0222)
	#define SP04_ADDY_PTR_H           ((volatile unsigned char *)0xAF0223)
	#define SP04_X_POS_L              ((volatile unsigned char *)0xAF0224)
	#define SP04_X_POS_H              ((volatile unsigned char *)0xAF0225)
	#define SP04_Y_POS_L              ((volatile unsigned char *)0xAF0226)
	#define SP04_Y_POS_H              ((volatile unsigned char *)0xAF0227)
	// SPRITE 5)
	#define SP05_CONTROL_REG          ((volatile unsigned char *)0xAF0228)
	#define SP05_ADDY_PTR_L           ((volatile unsigned char *)0xAF0229)
	#define SP05_ADDY_PTR_M           ((volatile unsigned char *)0xAF022A)
	#define SP05_ADDY_PTR_H           ((volatile unsigned char *)0xAF022B)
	#define SP05_X_POS_L              ((volatile unsigned char *)0xAF022C)
	#define SP05_X_POS_H              ((volatile unsigned char *)0xAF022D)
	#define SP05_Y_POS_L              ((volatile unsigned char *)0xAF022E)
	#define SP05_Y_POS_H              ((volatile unsigned char *)0xAF022F)
	// SPRITE 6)
	#define SP06_CONTROL_REG          ((volatile unsigned char *)0xAF0230)
	#define SP06_ADDY_PTR_L           ((volatile unsigned char *)0xAF0231)
	#define SP06_ADDY_PTR_M           ((volatile unsigned char *)0xAF0232)
	#define SP06_ADDY_PTR_H           ((volatile unsigned char *)0xAF0233)
	#define SP06_X_POS_L              ((volatile unsigned char *)0xAF0234)
	#define SP06_X_POS_H              ((volatile unsigned char *)0xAF0235)
	#define SP06_Y_POS_L              ((volatile unsigned char *)0xAF0236)
	#define SP06_Y_POS_H              ((volatile unsigned char *)0xAF0237)
	// SPRITE 7)
	#define SP07_CONTROL_REG          ((volatile unsigned char *)0xAF0238)
	#define SP07_ADDY_PTR_L           ((volatile unsigned char *)0xAF0239)
	#define SP07_ADDY_PTR_M           ((volatile unsigned char *)0xAF023A)
	#define SP07_ADDY_PTR_H           ((volatile unsigned char *)0xAF023B)
	#define SP07_X_POS_L              ((volatile unsigned char *)0xAF023C)
	#define SP07_X_POS_H              ((volatile unsigned char *)0xAF023D)
	#define SP07_Y_POS_L              ((volatile unsigned char *)0xAF023E)
	#define SP07_Y_POS_H              ((volatile unsigned char *)0xAF023F)
	// SPRITE 8)
	#define SP08_CONTROL_REG          ((volatile unsigned char *)0xAF0240)
	#define SP08_ADDY_PTR_L           ((volatile unsigned char *)0xAF0241)
	#define SP08_ADDY_PTR_M           ((volatile unsigned char *)0xAF0242)
	#define SP08_ADDY_PTR_H           ((volatile unsigned char *)0xAF0243)
	#define SP08_X_POS_L              ((volatile unsigned char *)0xAF0244)
	#define SP08_X_POS_H              ((volatile unsigned char *)0xAF0245)
	#define SP08_Y_POS_L              ((volatile unsigned char *)0xAF0246)
	#define SP08_Y_POS_H              ((volatile unsigned char *)0xAF0247)
	// SPRITE 9)
	#define SP09_CONTROL_REG          ((volatile unsigned char *)0xAF0248)
	#define SP09_ADDY_PTR_L           ((volatile unsigned char *)0xAF0249)
	#define SP09_ADDY_PTR_M           ((volatile unsigned char *)0xAF024A)
	#define SP09_ADDY_PTR_H           ((volatile unsigned char *)0xAF024B)
	#define SP09_X_POS_L              ((volatile unsigned char *)0xAF024C)
	#define SP09_X_POS_H              ((volatile unsigned char *)0xAF024D)
	#define SP09_Y_POS_L              ((volatile unsigned char *)0xAF024E)
	#define SP09_Y_POS_H              ((volatile unsigned char *)0xAF024F)
	// SPRITE 10)
	#define SP10_CONTROL_REG          ((volatile unsigned char *)0xAF0250)
	#define SP10_ADDY_PTR_L           ((volatile unsigned char *)0xAF0251)
	#define SP10_ADDY_PTR_M           ((volatile unsigned char *)0xAF0252)
	#define SP10_ADDY_PTR_H           ((volatile unsigned char *)0xAF0253)
	#define SP10_X_POS_L              ((volatile unsigned char *)0xAF0254)
	#define SP10_X_POS_H              ((volatile unsigned char *)0xAF0255)
	#define SP10_Y_POS_L              ((volatile unsigned char *)0xAF0256)
	#define SP10_Y_POS_H              ((volatile unsigned char *)0xAF0257)
	// SPRITE 11)
	#define SP11_CONTROL_REG          ((volatile unsigned char *)0xAF0258)
	#define SP11_ADDY_PTR_L           ((volatile unsigned char *)0xAF0259)
	#define SP11_ADDY_PTR_M           ((volatile unsigned char *)0xAF025A)
	#define SP11_ADDY_PTR_H           ((volatile unsigned char *)0xAF025B)
	#define SP11_X_POS_L              ((volatile unsigned char *)0xAF025C)
	#define SP11_X_POS_H              ((volatile unsigned char *)0xAF025D)
	#define SP11_Y_POS_L              ((volatile unsigned char *)0xAF025E)
	#define SP11_Y_POS_H              ((volatile unsigned char *)0xAF025F)
	// SPRITE 12)
	#define SP12_CONTROL_REG          ((volatile unsigned char *)0xAF0260)
	#define SP12_ADDY_PTR_L           ((volatile unsigned char *)0xAF0261)
	#define SP12_ADDY_PTR_M           ((volatile unsigned char *)0xAF0262)
	#define SP12_ADDY_PTR_H           ((volatile unsigned char *)0xAF0263)
	#define SP12_X_POS_L              ((volatile unsigned char *)0xAF0264)
	#define SP12_X_POS_H              ((volatile unsigned char *)0xAF0265)
	#define SP12_Y_POS_L              ((volatile unsigned char *)0xAF0266)
	#define SP12_Y_POS_H              ((volatile unsigned char *)0xAF0267)
	// SPRITE 13)
	#define SP13_CONTROL_REG          ((volatile unsigned char *)0xAF0268)
	#define SP13_ADDY_PTR_L           ((volatile unsigned char *)0xAF0269)
	#define SP13_ADDY_PTR_M           ((volatile unsigned char *)0xAF026A)
	#define SP13_ADDY_PTR_H           ((volatile unsigned char *)0xAF026B)
	#define SP13_X_POS_L              ((volatile unsigned char *)0xAF026C)
	#define SP13_X_POS_H              ((volatile unsigned char *)0xAF026D)
	#define SP13_Y_POS_L              ((volatile unsigned char *)0xAF026E)
	#define SP13_Y_POS_H              ((volatile unsigned char *)0xAF026F)
	// SPRITE 14)
	#define SP14_CONTROL_REG          ((volatile unsigned char *)0xAF0270)
	#define SP14_ADDY_PTR_L           ((volatile unsigned char *)0xAF0271)
	#define SP14_ADDY_PTR_M           ((volatile unsigned char *)0xAF0272)
	#define SP14_ADDY_PTR_H           ((volatile unsigned char *)0xAF0273)
	#define SP14_X_POS_L              ((volatile unsigned char *)0xAF0274)
	#define SP14_X_POS_H              ((volatile unsigned char *)0xAF0275)
	#define SP14_Y_POS_L              ((volatile unsigned char *)0xAF0276)
	#define SP14_Y_POS_H              ((volatile unsigned char *)0xAF0277)
	// SPRITE 15)
	#define SP15_CONTROL_REG          ((volatile unsigned char *)0xAF0278)
	#define SP15_ADDY_PTR_L           ((volatile unsigned char *)0xAF0279)
	#define SP15_ADDY_PTR_M           ((volatile unsigned char *)0xAF027A)
	#define SP15_ADDY_PTR_H           ((volatile unsigned char *)0xAF027B)
	#define SP15_X_POS_L              ((volatile unsigned char *)0xAF027C)
	#define SP15_X_POS_H              ((volatile unsigned char *)0xAF027D)
	#define SP15_Y_POS_L              ((volatile unsigned char *)0xAF027E)
	#define SP15_Y_POS_H              ((volatile unsigned char *)0xAF027F)
	// SPRITE 16)
	#define SP16_CONTROL_REG          ((volatile unsigned char *)0xAF0280)
	#define SP16_ADDY_PTR_L           ((volatile unsigned char *)0xAF0281)
	#define SP16_ADDY_PTR_M           ((volatile unsigned char *)0xAF0282)
	#define SP16_ADDY_PTR_H           ((volatile unsigned char *)0xAF0283)
	#define SP16_X_POS_L              ((volatile unsigned char *)0xAF0284)
	#define SP16_X_POS_H              ((volatile unsigned char *)0xAF0285)
	#define SP16_Y_POS_L              ((volatile unsigned char *)0xAF0286)
	#define SP16_Y_POS_H              ((volatile unsigned char *)0xAF0287)
	// SPRITE 17)
	#define SP17_CONTROL_REG          ((volatile unsigned char *)0xAF0288)
	#define SP17_ADDY_PTR_L           ((volatile unsigned char *)0xAF0289)
	#define SP17_ADDY_PTR_M           ((volatile unsigned char *)0xAF028A)
	#define SP17_ADDY_PTR_H           ((volatile unsigned char *)0xAF028B)
	#define SP17_X_POS_L              ((volatile unsigned char *)0xAF028C)
	#define SP17_X_POS_H              ((volatile unsigned char *)0xAF028D)
	#define SP17_Y_POS_L              ((volatile unsigned char *)0xAF028E)
	#define SP17_Y_POS_H              ((volatile unsigned char *)0xAF028F)
	// DMA CONTROLLER 0xAF0400 - 0xAF04FF)
	#define VDMA_CONTROL_REG          ((volatile unsigned char *)0xAF0400)
	#define VDMA_COUNT_REG_L          ((volatile unsigned char *)0xAF0401)
	#define VDMA_COUNT_REG_M          ((volatile unsigned char *)0xAF0402)
	#define VDMA_COUNT_REG_H          ((volatile unsigned char *)0xAF0403)
	#define VDMA_DATA_2_WRITE_L       ((volatile unsigned char *)0xAF0404)
	#define VDMA_DATA_2_WRITE_H       ((volatile unsigned char *)0xAF0405)
	#define VDMA_STRIDE_L             ((volatile unsigned char *)0xAF0406)
	#define VDMA_STRIDE_H             ((volatile unsigned char *)0xAF0407)
	#define VDMA_SRC_ADDY_L           ((volatile unsigned char *)0xAF0408)
	#define VDMA_SRC_ADDY_M           ((volatile unsigned char *)0xAF0409)
	#define VDMA_SRC_ADDY_H           ((volatile unsigned char *)0xAF040A)
	#define VDMA_RESERVED_0           ((volatile unsigned char *)0xAF040B)
	#define VDMA_DST_ADDY_L           ((volatile unsigned char *)0xAF040C)
	#define VDMA_DST_ADDY_M           ((volatile unsigned char *)0xAF040D)
	#define VDMA_DST_ADDY_H           ((volatile unsigned char *)0xAF040E)
	#define VDMA_RESERVED_1           ((volatile unsigned char *)0xAF040F)
	#define FG_CHAR_LUT_PTR           ((volatile unsigned char *)0xAF1F40)
	#define BG_CHAR_LUT_PTR		    ((volatile unsigned char *)0xAF1F80)

	#define GRPH_LUT0_PTR		 ((volatile unsigned char *)0xAF2000)
	#define GRPH_LUT1_PTR		 ((volatile unsigned char *)0xAF2400)
	#define GRPH_LUT2_PTR		 ((volatile unsigned char *)0xAF2800)
	#define GRPH_LUT3_PTR		 ((volatile unsigned char *)0xAF2C00)
	#define GRPH_LUT4_PTR		 ((volatile unsigned char *)0xAF3000)
	#define GRPH_LUT5_PTR		 ((volatile unsigned char *)0xAF3400)
	#define GRPH_LUT6_PTR		 ((volatile unsigned char *)0xAF3800)
	#define GRPH_LUT7_PTR		 ((volatile unsigned char *)0xAF3C00)

	#define GAMMA_B_LUT_PTR		 ((volatile unsigned char *)0xAF4000)
	#define GAMMA_G_LUT_PTR		 ((volatile unsigned char *)0xAF4100)
	#define GAMMA_R_LUT_PTR		 ((volatile unsigned char *)0xAF4200)

	#define TILE_MAP0       		 ((volatile unsigned char *)0xAF5000)//0xAF5000 - 0xAF57FF)
	#define TILE_MAP1                 ((volatile unsigned char *)0xAF5800) //    0xAF5800 - 0xAF5FFF)
	#define TILE_MAP2                 ((volatile unsigned char *)0xAF6000) //    0xAF6000 - 0xAF67FF)
	#define TILE_MAP3                 ((volatile unsigned char *)0xAF6800)  //   0xAF6800 - 0xAF6FFF)

	#define FONT_MEMORY_BANK          ((volatile unsigned char *)0xAF8000)   //  0xAF8000 - 0xAFBFFF)
	#define CS_TEXT_MEM_PTR           ((volatile unsigned char *)0xAFA000)
	#define CS_COLOR_MEM_PTR          ((volatile unsigned char *)0xAFC000)

	#define BMP_X_SIZE        ((volatile unsigned char *)0x000040) //2 BYTES)
	#define BM_CLEAR_SCRN_X   ((volatile unsigned char *)0x000040)
	#define BMP_Y_SIZE        ((volatile unsigned char *)0x000042) //2 BYTES)
	#define BM_CLEAR_SCRN_Y   ((volatile unsigned char *)0x000042)
	#define BMP_PRSE_SRC_PTR  ((volatile unsigned char *)0x000044) //3 BYTES)
	#define BMP_PRSE_DST_PTR  ((volatile unsigned char *)0x000048) //3 BYTES)
	#define BMP_COLOR_PALET   ((volatile unsigned char *)0x00004C) //2 BYTES)
	#define SCRN_X_STRIDE     ((volatile unsigned char *)0x00004E) //2 BYTES, BASICALLY HOW MANY PIXEL ACCROSS IN BITMAP MODE)
	#define BMP_FILE_SIZE     ((volatile unsigned char *)0x000050) //4 BYTES)
	#define BMP_POSITION_X    ((volatile unsigned char *)0x000054) //2 BYTES WHERE, THE BMP WILL BE POSITION ON THE X AXIS)
	#define BMP_POSITION_Y    ((volatile unsigned char *)0x000056) //2 BYTES WHERE, THE BMP WILL BE POSITION ON THE Y AXIS)
	#define BMP_PALET_CHOICE  ((volatile unsigned char *)0x000058)


	#define BTX_START                 ((volatile unsigned char *)0xAFE000) //BEATRIX REGISTERS)
	#define BTX_END                   ((volatile unsigned char *)0xAFFFFF)	
	
	#define MOUSE_PTR_GRAP0_START     ((volatile unsigned char *)0xAF0500) //  16 x 16  256 Pixels (Grey Scale) 0  Transparent, 1  Black , 255  White
	#define MOUSE_PTR_GRAP0_END       ((volatile unsigned char *)0xAF05FF) //  Pointer 0
	#define MOUSE_PTR_GRAP1_START     ((volatile unsigned char *)0xAF0600) // 
	#define FPGA_YOR                 ((volatile unsigned char *)0xAF070F) // 
	#define MOUSE_PTR_GRAP1_END       ((volatile unsigned char *)0xAF06FF) //  Pointer 1

	#define MOUSE_PTR_CTRL_REG_L     ((volatile unsigned char *)0xAF0700) //  Bit[0] Enable, Bit[1]  0  ( 0  Pointer0, 1  Pointer1)
	#define MOUSE_PTR_CTRL_REG_H     ((volatile unsigned char *)0xAF0701) // 
	#define MOUSE_PTR_X_POS_L        ((volatile unsigned char *)0xAF0702) //  X Position (0 - 639) (Can only read now) Writing will have no effect
	#define MOUSE_PTR_X_POS_H        ((volatile unsigned char *)0xAF0703) // 
	#define MOUSE_PTR_Y_POS_L        ((volatile unsigned char *)0xAF0704) //  Y Position (0 - 479) (Can only read now) Writing will have no effect
	#define MOUSE_PTR_Y_POS_H        ((volatile unsigned char *)0xAF0705) // 
	#define MOUSE_PTR_BYTE0          ((volatile unsigned char *)0xAF0706) //  Byte 0 of Mouse Packet (you must write 3 Bytes)
	#define MOUSE_PTR_BYTE1          ((volatile unsigned char *)0xAF0707) //  Byte 1 of Mouse Packet (if you don't, then )
	#define MOUSE_PTR_BYTE2          ((volatile unsigned char *)0xAF0708) //  Byte 2 of Mouse Packet (state Machine will be jammed in 1 state)
                                  // (And the mouse won't work)
								  
	#define MOUSE_POS_X_LO  ((volatile unsigned char *)0x0000E1)
	#define MOUSE_POS_X_HI  ((volatile unsigned char *)0x0000E2)
	#define MOUSE_POS_Y_LO  ((volatile unsigned char *)0x0000E3)
	#define MOUSE_POS_Y_HI  ((volatile unsigned char *)0x0000E4)
							  
	#define C256F_MODEL_MAJOR        ((volatile unsigned char *)0xAF070B) // 
	#define C256F_MODEL_MINOR        ((volatile unsigned char *)0xAF070C) // 
	#define FPGA_DOR                 ((volatile unsigned char *)0xAF070D) // 
	#define FPGA_MOR                 ((volatile unsigned char *)0xAF070E) // 
	
	#define	KEYBOARD_SCAN_CODE		 ((volatile unsigned char *)0xAF115F) //
	#define	KEY_BUFFER_RPOS  		 ((volatile unsigned char *)0x000F40) //
	#define	KEY_BUFFER       		 ((volatile unsigned char *)0x000F00) //
	
	// clock
	#define	RTC_SEC       ((volatile unsigned char *)0xAF0800 )//Seconds Register
	#define	RTC_SEC_ALARM ((volatile unsigned char *)0xAF0801 )//Seconds Alarm Register
	#define	RTC_MIN       ((volatile unsigned char *)0xAF0802 )//Minutes Register
	#define	RTC_MIN_ALARM ((volatile unsigned char *)0xAF0803 )//Minutes Alarm Register
	#define	RTC_HRS       ((volatile unsigned char *)0xAF0804 )//Hours Register
	#define	RTC_HRS_ALARM ((volatile unsigned char *)0xAF0805 )//Hours Alarm Register
	#define	RTC_DAY       ((volatile unsigned char *)0xAF0806 )//Day Register
	#define	RTC_DAY_ALARM ((volatile unsigned char *)0xAF0807 )//Day Alarm Register
	#define	RTC_DOW       ((volatile unsigned char *)0xAF0808 )//Day of Week Register
	#define	RTC_MONTH     ((volatile unsigned char *)0xAF0809 )//Month Register
	#define	RTC_YEAR      ((volatile unsigned char *)0xAF080A )//Year Register
	#define	RTC_RATES     ((volatile unsigned char *)0xAF080B )//Rates Register
	#define	RTC_ENABLE    ((volatile unsigned char *)0xAF080C )//Enables Register
	#define	RTC_FLAGS     ((volatile unsigned char *)0xAF080D )//Flags Register
	#define	RTC_CTRL      ((volatile unsigned char *)0xAF080E )//Control Register
	#define	RTC_CENTURY   ((volatile unsigned char *)0xAF080F )//Century Register

	
	
	#define	BITMAP_BANK_0       		 ((volatile unsigned char *)0xB00000) //
	#define	BITMAP_BANK_1       		 ((volatile unsigned char *)0xB10000) //
	#define	BITMAP_BANK_2       		 ((volatile unsigned char *)0xB20000) //
	#define	BITMAP_BANK_3       		 ((volatile unsigned char *)0xB30000) //
	#define	BITMAP_BANK_4       		 ((volatile unsigned char *)0xB40000) //



	#define WIN_BORDER_CHAR_TOP 		   	(0xC4)	
	#define WIN_BORDER_CHAR_BOTTOM 		   	(0xC4)	
	#define WIN_BORDER_CHAR_EDGE 		   	(0xBA)
	#define WIN_BORDER_CHAR_CORNER_TLEFT	(0xD6)
	#define WIN_BORDER_CHAR_CORNER_BLEFT	(0xD3)	
	#define WIN_BORDER_CHAR_CORNER_TRIGHT  	(0xB7)
	#define WIN_BORDER_CHAR_CORNER_BRIGHT  	(0xD3)



#endif


#endif