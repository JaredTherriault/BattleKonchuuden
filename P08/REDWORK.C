/****************************************************************************************
*						赤沢メモリーカードツール												*
*														1998/11/07 written by red		*
****************************************************************************************/
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>/*graphic system?*/
#include <libgpu.h>
//#include <libds.h>	/*cd-xa vol*/
//#include <libsnd.h>/*sound system*/
#include <libgs.h>
#include <libsn.h> 
#include <stdio.h>/*for printf???*/

#include "ak_mem.h"/*赤沢ヘッダファイル*/
/****************************************************************************************
*						使用ハンドラ宣言												*
*																						*
****************************************************************************************/

GsSPRITE AK_Font[16];			// 文字表示用

