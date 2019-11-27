/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : TITLE MAP [ DEV CODE: 97026 ]                            */
/*  File Attribute: HEADER                                                   */
/*  File Name     : TITLE.H                                                  */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _TITLE_H_
#define _TITLE_H_

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

//�ȉ��Ɏ������̂� TITLE.C �̊O������Q�Ƃ������̂ł���
extern int  Title();
extern int  Lx68060Sprt(int,int,int,int,int,int,int,int,int,int,
                        int,int,int);
extern int  Lx68060PGT4(int,int,int,int,int,int,int,int,
                        int,int,int,int,int,int,int,int,
                        int,int,int,int,
                        int,int,int,
                        int,int,int,
                        int,int,int,
                        int,int,int);
extern int  p05_sys_flag;



#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif



#endif  /* _TITLE_H_ */
