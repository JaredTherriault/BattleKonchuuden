/****************************************************************************************
*						�ԑ�T�E���h�c�[��												*
*														1998/7/21 written by red		*
****************************************************************************************/
#include <sys/types.h>
#include <libetc.h>
//#include <libgte.h>/*graphic system?*/
//#include <libgpu.h>
#include <libcd.h>
#include <libds.h>	/*cd-xa vol*/
#include <libsnd.h>/*sound system*/
#include <libsn.h> 
#include <stdio.h>/*for printf???*/

#include "ak_sound.h"/*�ԑ�w�b�_�t�@�C��*/
//#include "c:/psenv/psx/include/lz.h"/*lzdec*/
//#include "c:/psenv/psx/include/pk_sub.h"/*read_data*/
/****************************************************************************************
*						�g�p�n���h���錾												*
*																						*
****************************************************************************************/

//DslATV CD_VOL;/*xa �̃{�����[���w��*/
CdlATV CD_VOL;// xa �{�����[���w��
//KON SE_TBL[];/*�T�E���h�e�[�u��*/
//CdlFILE	FP;		/*iso9660�t�@�C���f�B�X�N���v�^*/
