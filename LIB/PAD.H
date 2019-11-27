#ifndef _PAD1_H_
#define _PAD1_H_

extern	void setPad(int port, Uint8 *rxbuf);
extern	void	pad_work_clear(Uint16 num);
extern	void	sindo_set(Uint16 num,Sint16 time);
extern	void	sindo_set2(Uint16 num, Sint16 level, Sint16 time);
extern	void	set_control_mode(Uint8 port, Uint8 mode);
extern	void	checkPad(int port, Uint8 *rxbuf);


//	����ǁ[�ɑΉ����邽�߂̍\����
typedef struct {
	unsigned char Lock;	// �R���g���[���̐؂�ւ��X�C�b�`���b�N���
	unsigned char Motor0;
	unsigned char Motor1;	//	�A�N�`���G�[�^(�U���q)�ɃZ�b�g����l
	unsigned char Send;	//�A�N�`���G�[�^(�U���q)����f�[�^���M�ʒu�ݒ�֐��R�[���ς݃t���O
	Sint16	act_timer0;		//���[�^�[�O�̐U���p
	Sint16	act_flag0;		//���[�^�[�O�̐U���p
	Sint16	act_timer1;		//���[�^�[�P�̐U���p
	Sint16	act_flag1;		//���[�^�[�P�̐U���p
} PAD_BUF;



void	sindo_set(Uint16 num,Sint16 time);
void	sindo_set2(Uint16 num, Sint16 level, Sint16 time);

extern	PAD_BUF	padbuf[2];
extern	Uint8 padbuff[2][34];


#endif
