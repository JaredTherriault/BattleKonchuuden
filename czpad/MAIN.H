#ifndef _MAIN_H_
#define _MAIN_H_

#include	"yuma.h"			//
#include	"mathf.h"
#include	<libcd.h>
#include	<libpad.h>

//	ステータスの定義
enum {
	STATUS_LOGO,			//0　ロゴ
	STATUS_TITLE,			//1　タイトル
	STATUS_GAME,			//2　ゲーム
	STATUS_PROLOGUE,		//3　プロローグ１
	STATUS_GAME_OVER,		//4　ゲームオーバー
	STATUS_CONTINUE,		//5  コンテニュー
	STATUS_YOKOKU,			//6  体験版予告
	STATUS_MULTI,			//7  マルチチャンネル
	STATUS_ZAULS,			//8  もばいるくん
	STATUS_DONYU2,			//9  マルチチャンネル用導入
	STATUS_RENDA_CHECK,		//10 連打チェック
	STATUS_HANA_SYSTEM,		//11 花育てシーン
	STATUS_NEWITEM,			//12 秘密のセクション
	STATUS_SKATBOAD,		//13 スケートボード
	STATUS_DONYU,			//14 導入
	STATUS_BOSS00,			// 15 boss sekizou stage 
	STATUS_BOSS01,			// 16 boss kaizoku sencyou stage  
	STATUS_BOSS02,			// 17 boss akirame no kesin stage 
	STATUS_MINI2,			//18  ミニゲーム２（オーリーを捕まえろ）
	STATUS_MINI3,			//19  ミニゲーム３（がけを飛び越えろ）
	STATUS_MINI4,			//20  ミニゲーム４（オーリーを救え、おどれアポダンス)� 
	STATUS_ENDING0,		//21  エンディング（部屋の中)
	STATUS_MINI6,			//22  ミニゲーム６（木の葉の兵隊から逃げろ）
	STATUS_BOSS03,			// 23 boss mizu genjin stage 
	STATUS_IDO,				//24 シーン間移動
	STATUS_ENDING,			//25 エンディング
	STATUS_BOSS04,			// 26 boss sand worm 
	STATUS_BOSS05,			// 27 boss giant scorpion 
};
extern	Sint16	test_rgb[];
extern	Sint8	test_work8;
extern	Sint16	test_work16;
extern	Sint32	test_work32;

//	
extern	Uint8	main_status;
extern	Uint8	main_status_sub;
extern	Uint8	main_status_old;
extern	Uint8	local_status;
extern	Uint8	local_status2;
extern	Uint8	local_status3;
extern	Uint8	local_status4;
extern	Uint32	main_timer;
extern	Sint32	local_timer;
extern	Uint8	debug_status;
extern	void	pause_select(void);
extern	void	pause_on(void);
extern	void	pause_off(void);

enum {
	DEBUG_OFF,
	DEBUG_YOSHIDA,
	DEBUG_GUN,
	DEBUG_CBYASU,
	DEBUG_GO,
	DEBUG_WAKI,
	DEBUG_AI,
};



extern	Uint8 	activeBuff;
//extern	Uint16	sprite_pointer;
//extern	GsSPRITE	sprite[];

#define OT_LENGTH  12			// OT resolution (size)  OT解像度（大きさ）
extern	GsOT 	 WorldOT[2];			// OT info (double buffer)
extern	GsOT_TAG OTTags[2][1<<OT_LENGTH];	// OT's tag area (double buffer)
extern	RECT	rectbuf;
extern	u_long *TmdBase;

//最大オブジェクト数
#define	OBJECTMAX	100
//extern	GsDOBJ2	object[OBJECTMAX]; 

extern	Uint32   Objnum;		//
extern	Uint32   preset_p[0x10000];
extern	Uint8	sync;
extern	Uint16	light_mode;			//ライトモード
extern	ANGLE	pers;		//画角
extern	Uint16	hs;			//投影面までの距離
extern	Sint8	area;
extern	Sint8	stage;
extern	Sint8	area_sub;
extern	Sint8	stage_sub;

extern	char	task_file_name[16];

extern	ANGLE	keisya[];



//	関数プロトタイプ宣言
extern	void db_swap(void);

extern	void	initSystem(void);

extern	void	initgraph(void);
extern	void	option_init(void);

extern	void	pause_check(void);
extern	void	task_load(void);
extern	void jt_init4(void);			/* Gs SortObject4J Fook Func */

extern	void	draw_grid(RECT *rect, unsigned char r, unsigned char g, unsigned char b);
extern	void	debug_task_hyoji(void);
extern	void	pause_hyoji(void);
extern	void	pause_mask(void);
extern	void	item_work_get(void);
extern	void	game_data_init(void);


//extern	DRAWENV		draw[2];	/* drawing environment: 描画環境 */
//extern	DISPENV		disp[2];	/* display environment: 表示環境 */
// Background color バックグラウンド色 
extern	int back_r;
extern	int back_g;
extern	int back_b;
//extern	GsCOORDINATE2   viewcoordnate;
extern	int cube_def_pos[];
extern	short rotx[];
extern	short roty[];
extern	short rotz[];
extern	Uint8 frame;

extern	Uint16	object_pointer;
extern	Uint16	kaisou_pointer;


//	モデル表示用
typedef struct {
	Uint16	exist;
	GsDOBJ2	*obj;
	GsCOORDINATE2   coordnate;
	ANGLE	ang[XYZ];
	Sint32	scl[XYZ];
	Sint16	hit_check_no;		//ヒットチェック用
	Sint16	myobj;				//オブジェナンバー
} MODEL_DATA;

//extern	MODEL_DATA	model_data[OBJECTMAX];

//	キー設定用
typedef struct {
	Uint16	key_jump;		//ジャンプボタン
	Uint16	key_dush;		//ダッシュ・調べる
	Uint16	key_action;		//攻撃、決定ボタン
	Uint16	key_menu;		//メニューボタン
	Uint16	key_event;		//回復アイテム使用ボタン
	Uint16	key_item;		//アイテム選択.
	Uint16	sound_mode;		//ステレオ、モノ
	Sint8	disp_mode;		//ディスプレーの表示
	Sint32	rader_offset[XY];	//レーダーのオフセット
	CdlATV	vol;			//ＣＤ及びＸＡのボリュームセット
	Uint8	main_vol;		//メインボリューム
	Uint8	se_vol;			//効果音のボリューム
	Uint8	bgm_vol;		//ＢＧＭのボリューム
	Uint8	actuator;		//アクチュエータ(振動子）のオン1、オフ0
} OPTION;


#define	OPTION_RADER_ON		0<<0
#define	OPTION_RADER_OFF	1<<0

extern	OPTION	option;

extern	Uint8	pause_flag;			//ポーズボタン
extern	Uint8	frame_flag;			//こま送りフラグ

extern	Sint8	next_event_flag; 	//	次にイベントがおきるかどうか
extern	Uint16	next_event_no; 		//	次に起こるイベント番号
extern	CdlLOC	loc[];
extern	Uint16	maho_no;
extern	Sint16	item_num;
extern	Uint8	minigame_no;			//ミニゲームの番号（面によって違う）
extern	Sint16	combo_no;
extern	Uint8	dead_mode;


//	地面との当たりに使うための構造体
typedef struct {
	SVECTOR	a;
	SVECTOR	b;
	SVECTOR	c;
	VECTOR	aans;
	VECTOR	bans;
	VECTOR	cans;
	VECTOR	ans;
} VECT_S;

//	サブタスクファイルロード
typedef struct {
	Uint16	num;
	char	filename;
//	char	*filename;
//	void	*add;
} TASK_LOAD;


typedef struct {
	long	*work;				//使用ワーク先頭番地
	Sint32	pos[XYZ];
	ANGLE	ang[XYZ];
	Uint8	syurui;
	Uint8	main_status;
	Uint8	sub_status;
	Uint8	loop;				//
	Sint8	shadow;				//影
	Sint8	motion_buf;			//モーション番号
} INITAL_POS;

typedef struct {
	Uint8	area;
	Uint8	stage;
} AREA_STAGE;

typedef struct {
	Uint32	*add;		//ファイル先頭アドレス
	Sint16	tex_no;		//テクスチャー番号
	Sint16	list_no;	//リストナンバー
	Sint16	offset;		//テクスチャーオフセット
	Uint16	dx;			//フレームバッファ内のオフセットX
	Uint16	dy;			//フレームバッファ内のオフセットY
	Uint16	clutx;		//CLUT X
	Uint16	cluty;		//CLUT X
} TIM_TABLE;


typedef struct {
	Sint16	a2[XY];		//始点
	Sint16	b2[XY];		//終点
	Uint8	r,g,b;		//カラー
} LINE_STRUCT;

typedef struct {
	Uint16	year;
	Uint8	month;
	Uint8	day;
	Uint8	hour;
	Uint8	min;
} TIME;


//.ここから花／アイテム／ＣＤの定義

#define	HANA_MAX	3
#define	ITEM_MAX	128

//.	ワフモクのステータス(構造体)
typedef struct {
	short	swStatusWaf;		//.	ワフモクのご機嫌 
	short	swStatusHana;		//.	花の育っている段階 
	char	chrKindHana;		//.	何が実るか 
	char	chrShapeHana;		//.	花の見かけの種類 
	char	chrSerialHana;		//.	この花をうんだＣＤ 
} WAFMOKU, *LPWAFMOKU;

//.	メインのワークにいなければならない
extern	WAFMOKU		g_wafmokuData[HANA_MAX];

//.モバイルくんのワーク.
extern char g_zlsSignal;
extern char g_zlsStartUp;

extern	VECT_S	vect;				//	床のほうせんを求めるためのべくとる値

//	定義
#define SCR_Z		1024	// projection: 投影面までの距離
#define OTSIZE		4096	/* depth of OT: ＯＴの段数（２のべき乗） */

extern	PACKET *err_mes();

extern	Uint8	game_system_status;
extern	TIME	time;
extern	Uint8	pause_status;
extern	Uint8	loading_flag;		//ロード中
extern	Uint8	stage_job_no;		//各ステージ中のジョブタスク
extern	Uint8	stage_local_status;	//各ステージ中のローカル


//	あとでとるワーク
extern	Sint32	test32[10];
extern	Sint16	test16[10];
extern	Sint8	test8[10];
extern	Sint8	mini_game_p;
extern	Uint8	mini_game_status;
extern	Uint8	ido_no;
extern	void	multi_chanel_task_bar(void);
extern	void	multi_channel_play(void);


//#define	DEBUG_
//#define	DATE_

extern	void	date_hyoji(void);
extern	Uint8	game44_status;
extern	Uint8	game55_status;

typedef struct {
	Sint16	syurui;
	Sint16	event_no;
	SVECTOR	pos;
} ITEM_HAICHI;


extern	Uint8	monita_kai;
extern	Sint8	debug_mode_flag;
extern	Sint16	guide_pointer;			//ガイド表示用
extern	Uint8	skatboad_flag;			//スケボー乗れる
extern	Uint8	camera_flag;			//視点変更できる
extern	Sint16	item_count;
extern	Sint16	item_count_buf[];		//とったアイテムの種類を記録
extern	Uint8	multi_ret_flag;

//	マルチチャンネル管理用ワーク
#define	MULTI_PLAY_MAX	160

typedef struct {
	Sint8	panel_no;
	Sint8	sub_panel_no;
	Uint8	area;
	Uint8	stage;
	Sint16	event_no;		//再生するイベント番号
} MULTI_CHANNEL_PLAY_WORK;
	

typedef struct {
	Uint8	flag;				//マルチチャンネル管理中フラグ
	Uint8	pointer;			//ポインター
	Uint8	num;				//プレイ数(1-38)
	Uint8	index;				//インデックス
	Sint16	cursorx;			//カーソルの値
	Sint16	cursory;			//カーソルの値
	Uint8	play[4];			//再生中のときの操作ボタン管理
	MULTI_CHANNEL_PLAY_WORK	multi_p[MULTI_PLAY_MAX];	//再生時に必要なワーク
} MULTI_CHANNEL_KANRI;
extern	Uint8	multi_check6111;
extern	Uint8	multi_check5820;

extern	MULTI_CHANNEL_KANRI	multi_channel_work;
extern	void	set_now_loading_font(void);
extern	Sint8	seqplay_flag;
extern	Sint8	seqpause_flag;
extern	Sint8	movie_play;
extern	void	multi_chan_flag_restre(void);

extern	Uint8	pause_moji;

typedef struct {
	Uint8	flag;
	Uint8	abr;
	Uint32	rgb;
	Uint16	depth;
} MOBLUR_DATA;

extern	MOBLUR_DATA moblur_data;
extern	Uint8	mobile_set_p;


typedef struct {
	Sint16	timer;			//時間秒
	Sint16	ten;			//１/１０秒
} SKATEBOAD_PARK;

typedef struct {
	Uint8	hour;
	Uint8	min;
	Uint8	sec;
	Uint8	frame;
} CLEAR_TIME;

extern	CLEAR_TIME	clear_time;


extern	SKATEBOAD_PARK	skatb_high_score[];
extern	Sint8	skatb_ticket;
extern	Uint8	item_get_pat;
extern	Uint8	donyu_multi_status;
extern	Uint8	hiru_yoru_bgm_sel;		//昼とよるのＢＧＭのチェック用（0:昼,1:夜）


//#define	TEST_DEBUG
//#define	FNT_DEBUG

//#define	TAIKEN_BAN

//	マスターの時定義する
#define	MASTER

#endif


