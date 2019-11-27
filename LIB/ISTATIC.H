#if !defined(__ISTATIC_H__)
#define	__ISTATIC_H__

/* ---- �������m�ۂ̐� ---- */
/* ---- �o�g�� <=> �r�k�f�̂݃��[�N ---- */
//#define ISTATIC2_ADDR     (0x801e5200) /* �i�Q�o�������[�N�j 32 *  64 = 0x600 Byte(s) */
#define ISTATIC2_ADDR     (0x801e4a00) /* �i�Q�o�������[�N�j 32 *  64 = 0x600 Byte(s) */
#define IUNITFT_DATA_ADDR (0x801e5800) /* ��    �e���v���[�g 34 *  64 = 0x800 Byte(s) */
#define ILEVEL_DATA_ADDR  (0x801e6000) /* LEVEL �e���v���[�g  2 * 100 = 0x100 Byte(s) */
#define IUNITT_DATA_ADDR  (0x801e6100) /* ��    �e���v���[�g 34 *  64 = 0x800 Byte(s) */
#define IPUB_DATA_ADDR    (0x801e6900) /* IPUB  ���[�N                  0x100 Bype(s) */
#define IMAP_ADDR         (0x801e6a00) /* IMAP �}�b�v�f�[�^�擪        0x1500 Byte(s) */
//#define                 (0x801e7f00) /* �c�� 256                      0x100 Byte(s) */

/* ---- �Q�[�����풓�f�[�^ ---- */
#define IRESULT_ADDR (0x801e8000)     /* ���Z�f�[�^��n���[�N (2+1+1)*8 = 32 Byte */
#define ISTATIC_ADDR (0x801efa00)     /* �Q�b�g�������̃f�[�^ */

/* ---- ���Y��ʂւ̎�n���[�N ---- */
typedef struct __tagIRESULT{
	long nSum;                    /* 4: ���v           */
	char nID;                     /* 1: �L�����i���o�[ */
	char nTime;                   /* 1: ��           */
	char pad[2];                  /* 2: ��           */
} IRESULT, *LPIRESULT;

/* ---- �Q�b�g���������[�N ---- */
typedef struct __tagISTATIC{
	long hp;                      /* 4: �q�b�g�|�C���g            */
	long dp;                      /* 4: �f�B�t�F���X�|�C���g      */
	long hpmax;                   /* 4: �q�b�g�|�C���g            */
	long dpmax;                   /* 4: �f�B�t�F���X�|�C���g      */
	short exp;                    /* 2: �l���o���l                */
	short at;                     /* 2: �U����                    */
	char lv;                      /* 1: ���x���i�����ĂȂ����͂O�j*/
	char crank;                   /* 1: �R�}���h�����N            */
	char arank;                   /* 1: �I�[�������N              */
	char pad;                     /* 1:                           */
} ISTATIC, *LPISTATIC;

#endif