/****************************************************************************************
*						�ԑ�T�E���h�c�[��												*
*														1998/7/6 written by red			*
*														�Ƃ肠�����w�`���(;_;)		*
*														SOUND_CLOSE()�����			*
****************************************************************************************/
#include <sys/types.h>
#include <libetc.h>
//#include <libgte.h>/*graphic system?*/
//#include <libgpu.h>
#include <libcd.h>	/*use cd-rom */
#include <libds.h>	/*cd-xa vol*/
#include <libsnd.h>/*sound system*/
#include <libsn.h> 
#include <stdio.h>/*for printf???*/

#include "ak_sound.h"/*�ԑ�w�b�_�t�@�C��*/
#include "../lib/libfio.h"/*�R������X�[�p�[���C�u����*/
#include "../lib/libdbg.h"/*�������f�o�b�O�p(���g�p�����H)*/
#include "../lib/libsxa.h"// �X�[�`�[XA

#define TEST 0			/*0:�����[�X�o�[�W���� 1:�f�o�b�O�o�[�W����*/

#define SPEED 0			/*0:normal speed 1:double speed */

/****************************************************************************************
*						�֐��v���g�^�C�v�錾											*
*																						*
****************************************************************************************/
void 	cbsync( u_char , u_char* );
int 	AK_READ(void);			/*�^�C�g���R�[���f�[�^���[�h�֐�*/
int 	SE_LOAD(short);			/*SE �f�[�^���[�h�֐�*/
void DATA_CLOSE(short);
void BGM_VOL_0(void);

void red_xa_ready_callback( u_char intr, u_char *result );
int XA_CNT(void);

/****************************************************************************************
*						�ϐ���`														*
*																						*
****************************************************************************************/
/*ak_sound.h�ɂ�extern*/

/*psx libds*/
// DslATV	CD_VOL;		/*�I�[�f�B�I�A�b�e�l�[�^*/
/*	�T�E���h�c�[���p */
// short vab[4];			/* vab data id */
// short seq[4];			/* seq data id */

static char seq_table [SS_SEQ_TABSIZ * SEQ_NO * SEP_NO];  /* seq table size */

int CurPos = 0;
int EndPos = 0;
int StartPos = 0;
static int Loop_F = 1;
static int XA_END = 0;
static int AK_Chan = 0;
static int VOLFLAG = 0;
static int	var_err = 0;
/* XA */
static int Flame_cnt = 0;

static char *redsecter_buffer =  ( char * )( 0x801fff00 - 2336 );// �Z�N�^���o�b�t�@
static int  red_xa_error;// XA error �J�E���g�p



//static int RepTime;					// XA���s�[�g�񐔃J�E���g
// char	VAB_STATUS[4];			// ���������Ǘ����[�N 
// char	SEQ_STATUS[4];
//int	 	SN_ENT_W[4][2];




/****************************************************************************************
*					�\���̂ƃe�[�u������												*
*																						*
****************************************************************************************/
SND_DATA snd_data = { 0, 127, 127, 0 };/*���ۂɎg���\���̂̎���*/
unsigned char param[4] = {0,0,0,0};

CATSND BGM_TBL_ALL[]={/*�������S�Čł߂��f�[�^�̃e�[�u��*/
#include "BGM.REP"
};


/****************************************************************************************
*					�֐��X�^�[�g														*
*																						*
****************************************************************************************/

/*�������֐��͂���ő��v�Ȃ͂����I�I�I*/
/*�f�[�^���[�h�O�ɏ��������Ă݂�Ƃ肠����*/
void 	SOUND_I(void){/*�T�E���h�֌W������*/
int	i;/*roop counter*/

	SsInit();/*libsnd*/

//CdSetDebug(2);


	SsSetTableSize (seq_table, SEQ_NO, NO_SEP);/*�Ƃ肠����SEP���g�p*/
//	SsSetTickMode(30|SS_NOTICK);	/* set tick mode = NOTICK */
	SsSetTickMode(SS_TICK60);		/*����\1/60 callback�����ďo��*/
//	SsSetTickMode(SS_NOTICK);		/* set tick mode = NOTICK */


	SsStart2();						/* start sound */
	/*SS_TICK60�Ȃ̂�SsStart()�ł͂Ȃ��A��������Ă�*/


	SsSetMVol(127,127);				/*���C���{�����[��(�f�[�^���[�h��̂ق����ǂ��H)*/

	snd_data.FLAG	= 0;			/*�����\��*/
	snd_data.BGM_VOL= 127;			/*�{�����[�������l(�ő�ɐݒ�)*/
	snd_data.SE_VOL	= 127;			/*����*/
	snd_data.MODE	= 0;			/*0:stereo 1:monoral*/



	// �T�E���h�Ǘ����[�N������ 
	for(i=0;i<4;i++)
		VAB_STATUS[i] = 0;
	for(i=0;i<4;i++)
		SEQ_STATUS[i] = 0;
	for(i=0;i<4;i++){
		SN_ENT_W[i][0]	= -1;
		SN_ENT_W[i][1]	= -1;
	}

/*���o�[�u�^�C�v�ݒ�*/
	SsUtSetReverbType(SS_REV_TYPE_HALL);		// �T�E���h���o�[�u�^�C�v�ݒ� 
	SsSetRVol(127,127);
	SsUtReverbOn();								// ���o�[�u���n�m 
	SsUtSetReverbDepth(127*0.3,127*0.3);


	SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);	// SsInit()(SndInit()�̓����ŌĂ΂��)�łb�c�̑���������������Ă��܂��̂ōĐݒ� 
	SsSetSerialVol(SS_SERIAL_A, 127, 127);


//	AK_READ();
// �^�C�g���R�[����SE���ǉ����ꂽ�ׁASE_LOAD�֐���ʂɗp�ӂ��܂���
}
/****************************************************************************************************
	SE(VAB)�̃G���g���ł��B
	�T�E���h�̃f�[�^�e�[�u���iSE_TBL�j�̉��Ԗڂ�炷����o�^����
	���j�T���v�����Q�Ƃ������ʁB���������Ă���炷�炵���E�E�E
	1998/10/27�ǉ�����
	������G���g�������Ƃ��ɘA�����Ė�悤�ɂ���ׁAKeyOff�̓R�����g
****************************************************************************************************/
void 	SE_ENT(int snd_no){
u_short	SE_Vol;
	SE_Vol = (u_short)(snd_data.SE_VOL*SE_VOL_D/127);
//	SsVoKeyOff(SE_TBL[snd_no].prog,SE_TBL[snd_no].pitch);
	SsVoKeyOn( SE_TBL[snd_no].prog,SE_TBL[snd_no].pitch,SE_Vol,SE_Vol);
}
/****************************************************************************************************
	SE(VAB)�̃N���A�ł��B
	�T�E���h�̃f�[�^�e�[�u���iSE_TBL�j�̉��Ԗڂ���������o�^����
****************************************************************************************************/
void 	SE_CLR(int snd_no){
	SsVoKeyOff(SE_TBL[snd_no].prog,SE_TBL[snd_no].pitch);
}
/****************************************************************************************************
	SE(VAB)�̃I�[���N���A�ł��B
	���jSsUtAllKeyOff ���� SEQ����u�����Ă��܂��̂������C�ɂȂ�B
****************************************************************************************************/
void 	SE_ALLCLR(void){
	SsUtAllKeyOff(0);
}
/****************************************************************************************************
	BGM�iSEQ�j�̃G���g���ł��B
****************************************************************************************************/
int 	BGM_ENT(short bgm_no){
	SsSeqPlay(bgm_no,SSPLAY_PLAY,SSPLAY_INFINITY);
	return ( SN_ENT_W[3][1] );
}
/****************************************************************************************************
	BGM�iSEQ�j�̃N���A�ł��B
****************************************************************************************************/
void 	BGM_CLR(short bgm_no){
	SsSeqPause(seq[3]);
}
/****************************************************************************************************
	BGM�iSEQ)�ꎞ��~ �ԑ�e�X�g
****************************************************************************************************/
void BGM_PAUSE(void){
	SsSeqPause(seq[3]);
}
/****************************************************************************************************
	BGM�iSEQ�j���v���C�B
****************************************************************************************************/
void 	BGM_RENT(short bgm_no){
u_short	BG_Vol;
	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);
	SsSeqReplay(bgm_no);
}

/****************************************************************************************************
	BGM�iSEQ�j�̃T�E���h�t�F�[�h
	���j���݂̃{�����[���l����̕ω�
		���Ԃ��{�����[���̔{�����x�X�g
		SsUtAoutVol�ł��H
****************************************************************************************************/
//void 	BGM_FADE(int fade_flag,short seq_no,short seq_vol,long seq_time){
void 	BGM_FADE(int fade_flag,short seq_vol,long seq_time){
u_short	BG_Vol;
	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
	if(fade_flag == BGM_DOWN   )
//		SsSeqSetDecrescendo(seq_no,BG_Vol,seq_time);
		SsSeqSetDecrescendo(0,BG_Vol,seq_time);
	if(fade_flag == BGM_UP   )
//		SsSeqSetCrescendo(seq_no,BG_Vol,seq_time);
		SsSeqSetCrescendo(0,BG_Vol,seq_time);
}
/****************************************************************************************************/
/****************************************************************************************************/
void	BGM_VOL_SET(void){
u_short	BG_Vol;

	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);

	/* �w�`�{�����[���ݒ� */
	CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
	CD_VOL.val1 = 0;
	CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
	CD_VOL.val3 = 0;
//	DsMix(&CD_VOL);
CdMix(&CD_VOL);

}

void	BGM_VOL_0(void){
u_short	BG_Vol;

	BG_Vol = 0;
	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);

	/* �w�`�{�����[���ݒ� */
	CD_VOL.val0 = 0;
	CD_VOL.val1 = 0;
	CD_VOL.val2 = 0;
	CD_VOL.val3 = 0;
//	DsMix(&CD_VOL);
CdMix(&CD_VOL);

	SsSetRVol(0,0);
	SsUtReverbOff();								// ���o�[�u��OFF 
	SsUtSetReverbDepth(0,0);

}



void	SND_MODE_SET(void){/*�\���̒��Œ�`���ꂽ���[�h���Z�b�g����*/
	if(snd_data.MODE == 0){
	/* �X�e���I�Z�b�g */
		SsSetStereo();
	}
	else{
	/* ���m�����Z�b�g */
		SsSetMono();
	}
}
/****************************************************************************************************/
/****************************************************************************************************/
void 	SOUND_E(){

	BGM_VOL_0();
	SsSeqStop(seq[3]);	/* stop seq data */
	SsSeqClose(seq[3]);	/* close seq data */
	SsVabClose(vab[3]);	/* close vab data */
	SsEnd();		/* sound system end */
	SsQuit();
}
/****************************************************************************************************
	�f�[�^���[�h(test)
****************************************************************************************************/
int AK_READ(void){/*�Ƃ肠�����̃f�[�^���[�h�p�֐�*/

u_short	BG_Vol;

//	printf("MCCHK : %d\n", FioGetMachine() );
#if (TEST)
	fio.dbg_flg = FIO_MC_DEV;
#endif

#if 0
		FioReadFile(SE_LTBL[1][0], (void *)VAB_HADDR0);
		FioReadFile(SE_LTBL[1][1], (void *)VAB_BADDR0);
#endif

//		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[0].ST,BGM_TBL_ALL[0].SI);
//		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[1].ST,BGM_TBL_ALL[1].SI);

		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[65].ST,BGM_TBL_ALL[65].SI);
		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[66].ST,BGM_TBL_ALL[66].SI);


	vab[2] = SsVabOpenHead ((void *)VAB_HADDR0, OPENVABID0);
	if (vab[2] < 0) {
		var_err = 1;
		printf("BGM ERROR 0\n");
		return(0);
	}

	if (SsVabTransBody ((void *)VAB_BADDR0, vab[2]) != vab[2]) {
		var_err = 2;
		printf("BGM ERROR 1\n");
		return(0);
	}
	SsVabTransCompleted (SS_WAIT_COMPLETED);
//	seq[3] = SsSeqOpen((void *)SEQ_ADDR0, vab[3]);	/* open seq data */

	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
//	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);	/* set seq data volume (0-127)*/

	printf("se_set\n");
	return(1);
}


int SE_LOAD(short dtno){/*SE�f�[�^���[�h�p�֐�*/

u_short	BG_Vol;

//DATA_CLOSE(2);// �^�C�g���R�[��SE�͕��Ă����K�v����

//	printf("MCCHK : %d\n", FioGetMachine() );
#if (TEST)
	fio.dbg_flg = FIO_MC_DEV;
#endif

	switch(dtno){
		case 0:// �{�җp

			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[0].ST,BGM_TBL_ALL[0].SI);
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[1].ST,BGM_TBL_ALL[1].SI);
		break;
		case 1:// �^�C�g���p
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[65].ST,BGM_TBL_ALL[65].SI);
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[66].ST,BGM_TBL_ALL[66].SI);
		break;
		case 2:// PDA�p�ǉ�
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[70].ST,BGM_TBL_ALL[70].SI);
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[71].ST,BGM_TBL_ALL[71].SI);
		break;
	}// switch last
	
	vab[2] = SsVabOpenHead ((void *)VAB_HADDR0, OPENVABID0);
	if (vab[2] < 0) {
		var_err = 1;
		printf("BGM ERROR 0\n");
		return(0);
	}

	if (SsVabTransBody ((void *)VAB_BADDR0, vab[2]) != vab[2]) {
		var_err = 2;
		printf("BGM ERROR 1\n");
		return(0);
	}
	SsVabTransCompleted (SS_WAIT_COMPLETED);

	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);

	printf("se_set\n");
	return(1);
}


/****************************************************************************************************
	�a�f�l���[�h
****************************************************************************************************/
void 	BGM_LOAD(int no){
//int		i,j;
//char	*BGM_DATA;/*�ł߂���g��Ȃ��Ȃ���*/
int		BGM_no;
u_short	BG_Vol;
//u_long	*addr1;

		BGM_no = no;
//			/* �a�f�l�o�^ */

#if (TEST)
	fio.dbg_flg = FIO_MC_DEV;
#endif

			BGM_no = no;
VSync(0);
	FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR3,BGM_TBL_ALL[BGM_no].ST,BGM_TBL_ALL[BGM_no].SI);
	FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR3,BGM_TBL_ALL[BGM_no + 1].ST,BGM_TBL_ALL[BGM_no + 1].SI);
	FioDivReadFile("DT\\BGM.DAT",(unsigned char *)SEQ_ADDR3,BGM_TBL_ALL[BGM_no + 2].ST,BGM_TBL_ALL[BGM_no + 2].SI);

#if 0
			BGM_DATA  =  BGM_LTBL[BGM_no][0]; /*�S���ł߂���g���Ȃ��Ȃ���*/

			BGM_DATA  =  BGM_LTBL[BGM_no][0];
			FioReadFile(BGM_DATA,(void *)VAB_HADDR3);
			
			BGM_DATA  =  BGM_LTBL[BGM_no][1];
			FioReadFile(BGM_DATA,(void *)VAB_BADDR3);
			
			BGM_DATA  =  BGM_LTBL[BGM_no][2];
			FioReadFile(BGM_DATA,(void *)SEQ_ADDR3);
#endif
VSync(0);
			vab[3] = SsVabOpenHead ((u_char *)VAB_HADDR3, OPENVABID3);
			if (vab[3] < 0) {
				var_err = 1;
				printf("BGM ERROR 2\n");
				return;
			}
VSync(0);
			if (SsVabTransBody ((u_char*)VAB_BADDR3, vab[3]) != vab[3]) {
				var_err = 2;
				printf("BGM ERROR 3\n");
				return;
			}
			SsVabTransCompleted (SS_WAIT_COMPLETED);
			seq[3] = SsSeqOpen((u_long *)SEQ_ADDR3, vab[3]);	/* open seq data */

			BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
			SsSeqSetVol(seq[3], BG_Vol,BG_Vol);	/* set seq data volume (0-127)*/

			VAB_STATUS[3] = 1;		// �o�^�� 
			SEQ_STATUS[3] = 1;		// �o�^�� 


			SN_ENT_W[3][0]	= 1;	/* BGM */
			SN_ENT_W[3][1]	= no;	/* BGM NO */

			printf("DATA SET\n");
//		}// else last
}
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/

/*test*/
void DATA_CLOSE(short no){
	switch (no){
		case 1:// ���ׂăN���[�Y
			SsSeqStop(seq[3]);/*�s�K�v�H�H�H*/
			SsSeqClose(seq[3]);
			SsVabClose(vab[3]);
			SsVabClose(vab[2]);/*�풓�r�d*/
			printf("DATA CLOSE ALL\n");
		break;
		case 2:// �r�d�N���[�Y
			SsVabClose(vab[2]);/*�풓�r�d*/
			printf("DATA CLOSE SE\n");
		break;
		case 3:// �a�f�l�N���[�Y
			SsSeqStop(seq[3]);/*�s�K�v�H�H�H*/
			SsSeqClose(seq[3]);
			SsVabClose(vab[3]);
			printf("DATA CLOSE BGM\n");
		break;
		default:
			printf("error!!\n");
		break;
	}
}
/****************************************************************************************************/
/****************************************************************************************************/
/*�ȉ��w�`*/

/*���ۂɂ݂�ȂɌĂ�ł��炤�֐��͂�������E�E�E
--------------------------------------------------------------------------------*/


void 	XA_CLR(void){



		CdSyncCallback(NULL);
		CdReadyCallback(NULL);
		red_xa_error = 0;





		// XA
		/* �{�����[���ݒ� */
		CD_VOL.val0 = 0;
		CD_VOL.val1 = 0;
		CD_VOL.val2 = 0;
		CD_VOL.val3 = 0;
//		DsMix(&CD_VOL);
CdMix(&CD_VOL);
#if (SPEED)
//		param[0] = DslModeSpeed | DslModeRT | DslModeSF;
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
//		param[0] = DslModeRT | DslModeSF;
param[0] = CdlModeRT | CdlModeSF;
#endif
CdControl( CdlPause , param , NULL );
CdFlush();
}

int 	XA_FADE(void){

// 0 :up 1:down

// XA VOL DOWN
		/* �{�����[���ݒ� */
			if(CD_VOL.val0 > 0)CD_VOL.val0 -=3;
				CD_VOL.val1 = 0;
			if(CD_VOL.val2 > 0)CD_VOL.val2 -=3;
				CD_VOL.val3 = 0;

//			DsMix(&CD_VOL);
CdMix(&CD_VOL);
#if (SPEED)
//			param[0] = DslModeSpeed | DslModeRT | DslModeSF;
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
//			param[0] = DslModeRT | DslModeSF;
param[0] = CdlModeRT | CdlModeSF;
#endif
			if((CD_VOL.val0 <= 0)&&(CD_VOL.val2 <= 0)){

				CD_VOL.val0 = CD_VOL.val2 = 0;/*�Ƃ肠�����O�N���A���Ă���*/

//				DsCommand( DslPause, param, 0 ,-1);
CdControl( CdlPause , param , 0 );
//				DsFlush();		/* �o�^�����̉��� */
CdFlush();
				VOLFLAG = 1;
			}
			return(VOLFLAG);
}// function last




/*from oh_tools.c*/
/*----------------------------------------------------------------------------
*
-----------------------------------------------------------------------------*/

CdlLOC		r_pos;// �O�ɏo���Ă݂�





int 	XA_LOAD(int no){
CdlFILE			file;
CdlFILTER filter;



int			ans;
int		NO;
char	*XA_DATA;

unsigned short err_flag = 0;

Flame_cnt = 0;// �J�E���^�N���A

		ans		= 0;
		NO		= no & 0x0000ffff;			/* �t�@�C���ԍ��Q�b�g */
		AK_Chan	= (no >> 16) & 0xf;			/* �`�����l���Q�b�g   */
		Loop_F	= (no >> 20) & 1;			/* ���[�v�t���O�Q�b�g */
		XA_END  = 0;						/* �G���h�t���O�N���A */

#if(SPEED)
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
param[0] = CdlModeRT | CdlModeSF | CdlModeSize1;
#endif

CdSyncCallback(NULL);
printf("CDCD\n");
CdControlB( CdlSetmode , param , 0 );
CdSync(0,NULL);
//VSync(0);
//VSync(0);
//VSync(0);

		/* �t�@�C���ʒu�̊l�� */
		XA_DATA  =  XA_LTBL[NO];

		do{
//			if( DsSearchFile( &file, XA_DATA ) == 0 ) {
//			if( PkSearchFile( &file, XA_DATA ) == 0 ) {
//			if( CdSearchFile( &file, XA_DATA ) == 0 ) {
if (FioCdSearchFile( &file, XA_DATA ) == 0 ) {
				err_flag ++;/*���g���C�t���O�C���N�������g*/
				ans  = 1;		// �����G���[ 
//				goto abort;
printf("LOAD ERR!\n");
			}// if last
			else{
				err_flag = XA_ERR_MAX;/*���g���C�����𔲂���*/
				ans = 0;		// �G���[�t���O�N���A

//CdControl( CdlSeekL, (u_char * )&filter, 0 );

printf("LOAD OK!!\n");
			}// else last
		}// do last
		while( (err_flag < XA_ERR_MAX) );


		/* ADPCM �Đ��`���l���ݒ� */
		filter.file = 1;
		filter.chan = (u_char)AK_Chan;
		
		CdControlB( CdlSetfilter, (u_char * )&filter, 0 );

		/* ���[�v�p�Z�N�^�ԍ� */
		StartPos = CdPosToInt( &file.pos );
//		EndPos   = StartPos + file.size / 2048;
		EndPos   = StartPos+XA_LONG[NO][AK_Chan];	// �e�[�u���g�p
		CurPos   = StartPos;
		
		CdIntToPos(StartPos,&r_pos);
		
		/* �{�����[���ݒ� */
		CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val1 = 0;
		CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val3 = 0;

//CdSync(0,NULL);
CdControlB( CdlSeekL, (u_char *)&( r_pos ), NULL);
//CdSync(0,NULL);

		CdMix(&CD_VOL);

		/* �Đ� */
#if(SPEED)
//		DsPacket( DslModeSpeed | DslModeRT | DslModeSF, &file.pos, DslReadS, 0, -1 );
#else
//		DsPacket( DslModeRT | DslModeSF, &file.pos, DslReadN, 0, -1 );
CdControl(CdlReadN,(u_char *)&r_pos,0);// �t������
return ( 1 );
#endif

//abort:
if(ans == 1){
	printf("XAMISS\n");
}

	return(ans);

}

/****************************************************************************************************/
/****************************************************************************************************/
int 	XA_SYNC(void){

int		ANS;
//unsigned char result[8];


	if(XA_END == 0){
	if( Flame_cnt % XA_FREQ == 0){
		if( (CurPos > EndPos) || (CurPos < (StartPos - SP_MARGIN)) ){
			//if(Loop_F){/*���[�v���Ƀ~�X�鎞������̂Ń��[�v�͈�؂Ȃ��ɕύX12/4*/
				CD_VOL.val0 = 0;
				CD_VOL.val1 = 0;
				CD_VOL.val2 = 0;
				CD_VOL.val3 = 0;
				CdMix(&CD_VOL);
				/* �Đ� �i���s�[�g�j*/
				CurPos   = StartPos;
				//�Z�N�^�ԍ�����|�W�V�����Q�b�g 
				//CdIntToPos( StartPos, &r_pos );
				/* �{�����[���ݒ� */
				CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
				CD_VOL.val1 = 0;
				CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
				CD_VOL.val3 = 0;
				CdMix(&CD_VOL);
#if(SPEED)
#else
param[0] = CdlModeRT | CdlModeSF | CdlModeSize1;// ���S�ȕt������
CdControlB(CdlSetmode , param, 0 );// 11/17�t������

CdControl(CdlReadN,(u_char *)&r_pos,0);// ������t������

CdReadyCallback( red_xa_ready_callback );

CdSyncCallback(NULL);// 11/18
CdReadyCallback(NULL);
#endif
			//}// Loop_F last
			//else{/*���������[�v���̕����Ȃ̂ŃR�����g*/
				/* ��~ */
				XA_CLR();
				XA_END = 1;
				printf("STOP\n");
			//}// else last
		}// Cur_Pos last
		else{
// ���݃Z�N�^�ԍ��Q�b�g 

				ANS = CdControl(CdlGetlocP , 0 , 0 );
				CdSyncCallback(NULL);
				CdSyncCallback(cbsync);

//printf("ANS:%d\n",ANS);
//			if(ANS == 0){
			if ( CdSync(0,(void *)NULL) == CdlDiskError ){// 11/19�T���v���̂܂܂��ƃ��[�N��ׂ��Ă��܂��Ă����B
				/* �G���[�ɂ���~ */
				XA_CLR();
				XA_END = 1;/*���̃\�[�X�ł͂P*/
				printf("ERROR\n");
			}// ANS == 0 last
		}// else last
	}// Flame_cnt last
	}// XA_END last
#if (TEST)
FntPrint("\nS:%d\n",StartPos);
FntPrint("C:%d\n",CurPos);
FntPrint("E:%d\n",EndPos);
FntPrint("F:%d\n",XA_END);
#endif
	return(XA_END);
}

void cbsync( u_char intr, u_char* result ){
int cnt;
	if( intr == CdlComplete ) {
		CdSyncCallback(NULL);// ��삳��̒ǉ�
		
		CdReadyCallback( red_xa_ready_callback );
		CdReadyCallback(NULL);
		
		cnt = CdPosToInt( (CdlLOC* )&result[5] );
		if( cnt > 0 ){
			CurPos = cnt;
		}
			CdControlB(CdlGetlocP, 0, 0 );// 11/17�ǉ�
	}
	else{
		CdSyncCallback(NULL);
		CdReadyCallback(NULL);
		CdControl(CdlPause, 0, 0 );// 11/17�ǉ�
	}
}


void red_xa_ready_callback( u_char intr, u_char *result ){
   if ( intr == CdlDataReady ){
       CdGetSector( redsecter_buffer, 2336 / sizeof( long ) );
   }
   else{
        red_xa_error++;
        if( red_xa_error > XA_ERR_MAX ){
          XA_CLR();
          XA_END = 1;// �ǉ����Ă݂�11/22
          printf("XA ERROR MAX!!\n");
        }
   }
	
}


int XA_CNT(void){
	Flame_cnt++;
	if(Flame_cnt >  (127922-126194) ){
		XA_CLR();
		return ( 1 );
	}
	return ( 0 );
}


void 	XA_START(void){

		/* �{�����[���ݒ� */
		CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val1 = 0;
		CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val3 = 0;
//		DsMix(&CD_VOL);
CdMix(&CD_VOL);
#if (SPEED)
//		param[0] = DslModeSpeed | DslModeRT | DslModeSF;
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
//		param[0] = DslModeRT | DslModeSF;
param[0] = CdlModeRT | CdlModeSF;
#endif
//		DsCommand( DslReadS, param, 0 ,-1);
CdControl( CdlReadS, param, 0 );
}

