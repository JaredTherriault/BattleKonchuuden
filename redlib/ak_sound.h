/*�ԑ�w�b�_�t�@�C��*/
#ifndef __AKAZAWA_H__
#define __AKAZAWA_H__
// define

#define SEQ_NO	1	/*�����I�[�v���r�d�p�t�@�C��(�ő�R�Q)*/
#define NO_SEP	1	/*�r�d�o���g�p��*/
#define SEP_NO	16	/*�r�d�o���̂r�d�p�ő吔  max=16*/

#define BGM_UP  		0			/* main volume */
#define BGM_DOWN		1			/* main volume */

#define MVOL			127			/* main volume */
#define SVOL			95			/* seq data volume ����100*/ 
#define VOL				127			/* vab data volume */

#define	XA_VOL_D		90			/*default volume (xa)*/
#define	BGM_VOL_D		95			/*default volume (seq)*/
#define	SE_VOL_D		36			/*default volume (se)*/

#define SP_MARGIN	( 4 * 75 )	/* 4sec �A���_�[�t���[�������̕ی�*/
//#define SP_MARGIN	( 16 * 75 )	/* 1sec �A���_�[�t���[�������̕ی�*/
#define	XA_FREQ		32

#define XA_ERR_MAX	0x100		/*���g���C��256��*/

#define		LZDATA_ADDR0		0x80160000		/* ���k�f�[�^�̐擪�Ԓn */
#define		LZDATA_ADDR1		0x80120000		/* ���k�f�[�^�̉𓀐擪�Ԓn */
#define		LOAD_ADDR0  		0x80120000		/* �Ƃ肠�����]���p�擪�Ԓn */
//#define		secter_buffer		0x80120000		/* �Z�N�^���o�b�t�@�擪�Ԓn */
//�T�E���h�c�[���p

/*  VB �̓T�E���h�o�b�t�@�ɓ]�������*/
//�i�풓�j
#define VAB_HADDR0      0x801f0000L             /* �풓SE (0xc20�j   Header Address */
#define VAB_BADDR0      0x80120000L             /* �풓SE            Data   Address */
#define SEQ_ADDR0       0x801fC000L      		/* �풓BGM�i���g�p�j Data   Address */
//�i�r�d�j
#define VAB_HADDR1      0x801f2000L             /*     SE            Header Address */
#define VAB_BADDR1      0x80120000L             /*     SE            Data   Address */
#define SEQ_ADDR1       0x801fC000L      		/*     BGM�i���g�p�j Data   Address */
//�i�r�d�j
#define VAB_HADDR2      0x801f4000L             /*     SE            Header Address */
#define VAB_BADDR2      0x80120000L             /*     SE            Data   Address */
#define SEQ_ADDR2       0x801fC000L      		/*     BGM�i���g�p�j Data   Address */
//�i�a�f�l�j
//#define VAB_HADDR3      0x801f8000L             /*     SE            Header Address */
#define VAB_HADDR3      0x801f2000L             /*     SE            Header Address */
#define VAB_BADDR3      0x80180000L             /*     SE            Data   Address */
//#define SEQ_ADDR3       0x801fB000L      		/*     BGM           Data   Address */
#define SEQ_ADDR3       0x801f5000L      		/*     BGM           Data   Address */

// �T�E���h�i���o�|       0x80114000L			/*     BGM           Data   Address */
#define OPENVABID0      0x00000000				/* VAB OPEN ID */
#define OPENVABID1      0x00000001				/* VAB OPEN ID */
#define OPENVABID2      0x00000002				/* VAB OPEN ID */
#define OPENVABID3      0x00000003				/* VAB OPEN ID */
#define OPENVABID4      0x00000004				/* VAB OPEN ID */
#define OPENVABID5      0x00000005				/* VAB OPEN ID */
#define OPENVABID6      0x00000006				/* VAB OPEN ID */
#define OPENVABID7      0x00000007				/* VAB OPEN ID */
#define OPENVABID8      0x00000008				/* VAB OPEN ID */
#define OPENVABID9      0x00000009				/* VAB OPEN ID */
#define OPENVABIDa      0x0000000a				/* VAB OPEN ID */
#define OPENVABIDb      0x0000000b				/* VAB OPEN ID */
#define OPENVABIDc      0x0000000c				/* VAB OPEN ID */
#define OPENVABIDd      0x0000000d				/* VAB OPEN ID */
#define OPENVABIDe      0x0000000e				/* VAB OPEN ID */
#define OPENVABIDf      0x0000000f				/* VAB OPEN ID */


// enum

// �ϐ�
/*	�T�E���h�c�[���p */
extern short vab[4];			/* vab data id */
extern short seq[4];			/* seq data id */

/*ak_sound.c �݂̂ł����g�p���Ȃ��̂ł����ł͎~�߂Ă���*/
//extern char seq_table [SS_SEQ_TABSIZ * SEQ_NO * SEP_NO];  /* seq table size */
//extern int	var_err;


/* XA */
/*from psx libds*/
//extern DslATV	CD_VOL;		/*�I�[�f�B�I�A�b�e�l�[�^(cd-cd,xa�̃{�����[���w��Ɏg�p)*/
/*CD_VOL ��work.c�ɂĒ�`���ׂ��H*/
// libcd �֕ύX
extern CdlATV CD_VOL;// �I�[�f�B�I�A�b�e�l�[�^


extern int CurPos,EndPos,StartPos,Loop_F,XA_END,Chan;



extern unsigned char		param[4];
extern unsigned char		result[8];



//extern int 		CurPos,EndPos,StartPos,Loop_F,XA_END,Chan;
extern char		VAB_STATUS[4];			// ���������Ǘ����[�N 
extern char		SEQ_STATUS[4];
extern int	 	SN_ENT_W[4][2];


// �\����
typedef struct {/*�T�E���h�֌W�\����*/
	u_char  FLAG;			/* �T�C�Y�I�ɂ��܂����̂ŕt���Ă݂����� */
	u_char	BGM_VOL;		/* �a�f�l�i�w�`���݁j �{�����[���l�i�O�`�P�Q�V�j*/
	u_char	SE_VOL;			/* �r�d  			  �{�����[��  �i�O�`�P�Q�V�j*/
	u_char  MODE;			/* �O�F�X�e���I�^�P�F���m���� */
} SND_DATA;

extern SND_DATA snd_data;


/*program no & pitch*/
typedef struct {/*�r�d�i���o�[�\����*/
	long prog;	/* program no */
	long pitch;	/* pitch */
} KON;

/*�T�E���h�ł߂��z�ǂݍ��ݗp*/
typedef struct {
	int ST;// start point
	int SI;// size
} CATSND;




extern KON SE_TBL[];/*ak_sntbl.c�ɂăe�[�u���w�肵�܂�*/
//extern SE_TBL[];/*���̂͊֐��̊O���ɋL�q*/


// table
// extern short test_sound_table[];// exsample
/*KON �͍\���́A���̐錾�͍\���̂̌�̕����ǂ��H�H*/
//extern SE_TBL[];//�ǂ����\���̂̐錾�����Ńe�[�u���̂ق��͗v��Ȃ��炵��

extern int	VAB_HADDR[];
extern int	VAB_BADDR[];
extern int	OPENVABID[];

// �ȉ��̃e�[�u����XA�ȊO�͖��g�p���(�f�[�^�ł߂����������)
extern char *BGM_LTBL[][3];/*������z��ւ̎Q��(���{�P�Q�R�o)*/
extern char *SE_LTBL[][2];
extern char *XA_LTBL[];/*XA�̏ꏊ*/
extern int XA_LONG[][8];/*������͕ύX�̉\������*/
// ������m�����g�p
extern char *REP_TBL[];/*REP������e�[�u��*/

// ���܂Ɏg���ėp�e�X�g�ϐ�
extern int bgm;		/*BGM ���[�v�e�X�g�p*/


#endif