#include "../../include/libnge2.h"
#include <time.h> 

//真假定义
bool _GameOver;
bool Cget;
bool Tmp;
bool Fin;
bool Over;
bool Sc;

bool Menu;
bool Game;

//声音定义
//music_ops _Bmg;
music_ops _MP3;
music_ops _Wav;

//图像定义
image_p _Logo;
image_p _Menu;
image_p _Help;
image_p _BG;
image_p _Mouse;
image_p _CardA;
image_p _CardB;
image_p _CardBox;
image_p _Start;
image_p _Finish;

//鼠标坐标
float _mouseX = 19;
float _mouseY = 28;
int _mouseN = 8;
float _addY = 0;

//变量定义
int rs = 0;
int Gn = 0;
int My = 0;
int Myn = 0;
int T_y = -1;
int F_y = -1;
int F_n = -1;

//数组定义
int **Crr = new int*[8];
int *Trr = new int[4];
int **Frr = new int*[4];
int *Mrr = new int[5];

/*void play_Bmg(char *str){
	_Bmg.load(str);
	_Bmg.playstop();
}*/

void play_MP3(char *str){
	_MP3.load(str);
	_MP3.playstop();
}

void play_Wav(char *str){
	_Wav.load(str);
	_Wav.playstop();
}

//函数定义
void get_mouseY(){//取得鼠标图标的Y坐标
	_mouseY = 75;
	for(int i=19; i>=0; i--){
		if(Crr[_mouseN][i]>0 && Crr[_mouseN][i]<53){
			_mouseY += i*15;
			break;
		}
	}
	_mouseY += 27;
	_addY = _mouseY-240;
	if(_addY>0){
		_addY = -_addY;
	}else{
		_addY = 0;
	}
}

void set_mouseX(){//取得鼠标图标的X,Y坐标
	if(_mouseN<8){	get_mouseY();	}else{	_mouseY=28;	}//Y
	switch(_mouseN){//X
	case 0:		_mouseX=22;		break;
	case 1:		_mouseX=82;		break;
	case 2:		_mouseX=142;	break;
	case 3:		_mouseX=202;	break;
	case 4:		_mouseX=262;	break;
	case 5:		_mouseX=322;	break;
	case 6:		_mouseX=382;	break;
	case 7:		_mouseX=442;	break;
	case 8:		_mouseX=19;		break;
	case 9:		_mouseX=72;		break;
	case 10:	_mouseX=125;	break;
	case 11:	_mouseX=178;	break;
	case 12:	_mouseX=285;	break;
	case 13:	_mouseX=338;	break;
	case 14:	_mouseX=391;	break;
	case 15:	_mouseX=444;	break;
	}
}

int get_numberC(int num){//取得卡的点数
	int No = num%13;
	if(No==0){	No=13;	}
	return No;
}

int get_colorC(int num){//取得卡的颜色
	return (num-1)/13;
}

void get_finishC(){
	int ff = false;
	while(!ff){
		ff = true;
		for(int fi=0; fi<4; fi++){
			int fn = -1;
			int fa = 0;
			int fj = 0;
			if(Frr[fi][0]!=0){
				for(fj=12; fj>=0; fj--){
					if(Frr[fi][fj]>0 && Frr[fi][fj]<53){
						fn = fj;
						break;
					}
				}
				fa = int(get_numberC(Frr[fi][fn]));
			}			
			for(fj=0; fj<4; fj++){//检查临时存放数组
				if(Trr[fj]!=0){
					int fb = int(get_numberC(Trr[fj]));
					int fc = int(get_colorC(Trr[fj]));
					if(fc==fi && fa==fb-1){
						Frr[fi][fn+1] = Trr[fj];
						Trr[fj] = 0;
						ff = false;
						break;
					}
				}
			}
			for(fj=0; fj<8; fj++){
				if(Crr[fj][0]!=0){
					int fy = 19;
					for(int fk=fy; fk>=0; fk--){//取最后一张卡
						if(Crr[fj][fk]>0 && Crr[fj][fk]<53){
							fy = fk;
							break;
						}
					}
					int fd = int(get_numberC(Crr[fj][fy]));
					int fe = int(get_colorC(Crr[fj][fy]));
					if(fa==fd-1 && fe==fi){
						Frr[fi][fn+1] = Crr[fj][fy];
						Crr[fj][fy] = 0;
						ff = false;
						break;
					}
				}
			}
		}
	}
	if(Frr[0][12]>0&&Frr[1][12]>0&&Frr[2][12]>0&&Frr[3][12]>0){
		play_MP3("res/music/win.mp3");
		Sc = false;
		Over = true;
	}
}

void get_moveN(){//取得可移动卡数
	Gn = 5;
	if(Trr[0]>0 && Trr[0]<53){	Gn--;	}
	if(Trr[1]>0 && Trr[1]<53){	Gn--;	}
	if(Trr[2]>0 && Trr[2]<53){	Gn--;	}
	if(Trr[3]>0 && Trr[3]<53){	Gn--;	}
}

void get_moveC(){
	Tmp = false;
	Fin = false;
	Cget = false;	
	if(Crr[_mouseN][0]==0){
		play_Wav("res/music/wrong.mp3");
		//Printf("Get Number Error!")
	}else{
		play_Wav("res/music/select.mp3");
		Cget = true;//已选择卡
		My =_mouseN;//选择列
		get_moveN();//取得最大可移动卡数
		int gy = 19;
		int gi;
		for(gi=gy; gi>=0; gi--){
			if(Crr[_mouseN][gi]>0 && Crr[_mouseN][gi]<53){
				gy = gi;			
				break;
			}
		}//取得选择列最后一个卡位置
		Myn = gy;
		for(gi=0; gi<5; gi++){
			Mrr[gi] = 0;//清空移动数组
		}
		Mrr[0] = Crr[_mouseN][gy];//加入最后一张移动卡 此处为反向获取卡点
		if(Gn>1){//可取移动数量大于1时
			int gx = gy-Gn;//取卡位置上限
			if(gx<0){	gx=0;	}
			int mry = 1;//移动数组新元素位置
			int ga = 0;
			int gb = 0;
			int gc = 0;
			int gd = 0;
			for(gi=gy-1; gi>=gx; gi--){
				ga = int(get_numberC(Crr[_mouseN][gi+1]));
				gb = int(get_numberC(Crr[_mouseN][gi]));
				if(gb == ga+1){//判断点数
					gc = int(get_colorC(Crr[_mouseN][gi+1]))%2;
					gd = int(get_colorC(Crr[_mouseN][gi]))%2;
					if(gc != gd){//判断颜色
						Mrr[mry] = Crr[_mouseN][gi];
						mry++;
					}else{
						//printf("Get Color Same!\n");
						break;
					}
				}else{
					//printf("Get Number Over!\n");
					break;
				}
			}
		}
	}
}
//197
void put_moveC(){
	int Tyn = Myn;
	int pi;
	if(Tmp){
		if(_mouseN%8 == T_y && _mouseN>7){
			//printf("Put Temp No Move Over!");
		}else{
			if(_mouseN<8){
				if(Crr[_mouseN][0] == 0){
					Crr[_mouseN][0] = Trr[T_y];
					Trr[T_y] = 0;
				}else{
					int pn = 0;
					for(pi=19; pi>=0; pi--){
						if(Crr[_mouseN][pi]>0 && Crr[_mouseN][pi]<53){
							pn = pi;
							break;
						}
					}
					int Ta = int(get_numberC(Crr[_mouseN][pn]));
					int Tb = int(get_numberC(Trr[T_y]));
					if(Ta==Tb+1){
						int Tc = int(get_colorC(Crr[_mouseN][pn]))%2;
						int Td = int(get_colorC(Trr[T_y]))%2;
						if(Tc!=Td){
							Crr[_mouseN][pn+1] = Trr[T_y];
							Trr[T_y] = 0;
						}else{
							play_Wav("res/music/wrong.mp3");
							//printf("Put Temp Color Wrong!");
						}
					}else{
						play_Wav("res/music/wrong.mp3");
						//printf("Put Temp Number Wrong!");
					}
				}
				
			}else if(_mouseN<12){
				int pn = _mouseN%8;
				if(Trr[pn]==0){
					Trr[pn] = Trr[T_y];
					Trr[T_y] = 0;
				}else{
					play_Wav("res/music/wrong.mp3");
					//printf("Put Temps No Move Over!");
				}
			}else{
				play_Wav("res/music/wrong.mp3");
				//printf("Put Temps No Move Here!");
			}			
		}
	}else if(Fin){
		if(_mouseN%12 == F_y && _mouseN>11){
			//printf("Put Finish No Move Over!");
		}else{
			if(_mouseN<8){
				if(Crr[_mouseN][0] == 0){
					Crr[_mouseN][0] = Frr[F_y][F_n];
					Frr[F_y][F_n] = 0;
				}else{
					int pn = 0;
					for(pi=19; pi>=0; pi--){
						if(Crr[_mouseN][pi]>0 && Crr[_mouseN][pi]<53){
							pn = pi;
							break;
						}
					}
					int Ma = int(get_numberC(Crr[_mouseN][pn]));
					int Mb = int(get_numberC(Frr[F_y][F_n]));
					if(Ma==Mb+1){
						int Mc = int(get_colorC(Crr[_mouseN][pn]))%2;
						int Md = int(get_colorC(Frr[F_y][F_n]))%2;
						if(Mc!=Md){
							Crr[_mouseN][pn+1] = Frr[F_y][F_n];
							Frr[F_y][F_n] = 0;
						}else{
							play_Wav("res/music/wrong.mp3");
							//printf("Put Finishs Color Wrong!\n");
						}
					}else{
						play_Wav("res/music/wrong.mp3");
						//printf("Put Finishs Number Over!\n");
					}
				}				
			}else{
				play_Wav("res/music/wrong.mp3");
				//printf("Put Finishs No Move Over!");
			}			
		}
	}else if(Cget){
		if(_mouseN == My){//如果还处于当前选择列 则不作任何动作返回选择状态
			//printf("Put No Move Over!");
		}else if(_mouseN>11){
			play_Wav("res/music/wrong.mp3");
			//printf("Put No Move Here!");
		}else if(_mouseN>7){
			int pz = _mouseN-8;
			if(Trr[pz]==0){
				Trr[pz] = Mrr[0];
				Crr[My][Myn] = 0;
			}else{
				play_Wav("res/music/wrong.mp3");
				//printf("Put No Move Here!");
			}
		}else if(Crr[_mouseN][0] == 0){	//当前列为空时	
			int pn = 0;
			for(pi=4; pi>=0; pi--){
				if(Mrr[pi]>0 && Mrr[pi]<53){
					pn = pi;
					break;
				}
			}//用pn记录下移动卡片最大位置
			int py = 0;//当前位置
			for(pi=pn; pi>=0; pi--){
				Crr[_mouseN][py] = Mrr[pi];
				py++;
				Crr[My][Myn] = 0;
				Myn--;
			}
		}else{
			int pn = 19;
			for(pi=pn; pi>=0; pi--){
				if(Crr[_mouseN][pi]>0 && Crr[_mouseN][pi]<53){
					pn = pi;
					break;
				}
			}//取得当前列的最后一个卡片位置		
			int pa = int(get_numberC(Mrr[0]));
			int pb = int(get_numberC(Crr[_mouseN][pn]));
			if(pa<pb){//判断两卡点数大小
				int py = 0;
				int pc = 0;
				bool pp = false;//是否存在对应点卡
				for(pi=0; pi<5; pi++){
					pc = int(get_numberC(Mrr[pi]));
					if(pc==pb-1){
						py = pi;
						pp = true;
						break;
					}
				}
				if(pp){//存在移动
					int pd = int(get_colorC(Crr[_mouseN][pn]))%2;
					int pe = int(get_colorC(Mrr[py]))%2;
					int pf = pn+1;
					if(pd != pe){
						for(pi=py; pi>=0; pi--){
							Crr[_mouseN][pf] = Mrr[pi];
							pf++;
							Crr[My][Myn] = 0;
							Myn--;
						}
					}else{
						play_Wav("res/music/wrong.mp3");
						//printf("Put Color Same!");
					}
				}else{
					play_Wav("res/music/wrong.mp3");
					//printf("Put Number Error!");
				}
			}else{
				play_Wav("res/music/wrong.mp3");
				//printf("Put Number Over!");
			}
		}
	}
	if(!Fin){
		get_finishC();//整理卡片
		if(!Tmp && !Fin && _mouseN == My){
			if(Crr[My][Tyn]>0 && Crr[My][Tyn]<53){
				for(pi=0; pi<4; pi++){
					if(Trr[pi]==0){//当前卡片存放至临时数组
						Trr[pi] = Crr[My][Tyn];
						Crr[My][Tyn] = 0;
						break;
					}
				}
			}
		}
		get_finishC();
	}
	Tmp = false;
	Fin = false;
	Cget = false;
	My = 16;
	Myn = 19;
	T_y = -1;
	F_y = -1;
	F_n = -1;
}

void get_tempC(){//取临时数组
	T_y = int(_mouseN%8);
	if(Trr[T_y]==0){
		play_Wav("res/music/wrong.mp3");
		//Printf("Get Number Error!")
	}else{
		My = 16;
		Myn = 19;
		Tmp = false;
		Fin = false;
		Cget = false;
		play_Wav("res/music/select.mp3");
		if(Trr[T_y]==0){
			//printf("Get Temp Number Error!\n");
		}else{
			Tmp = true;
			for(int ti=0; ti<5; ti++){
				Mrr[ti] = 0;
			}
			Mrr[0] = Trr[T_y];
		}
	}
}

void get_finishedC(){//取完成数组	
	F_y = int(_mouseN%12);
	if(Frr[F_y][0]==0){
		play_Wav("res/music/wrong.mp3");
		//Printf("Get Number Error!")
	}else{
		My = 16;
		Myn = 19;
		Tmp = false;
		Fin = false;
		Cget = false;
		play_Wav("res/music/select.mp3");
		if(Frr[F_y][0]==0){	
			//printf("Get Finish Number Error!\n");
		}else{
			Fin = true;
			int Fy = 12;
			int Fi;
			for(Fi=0; Fi<5; Fi++){
				Mrr[Fi] = 0;
			}
			for(Fi=Fy; Fi>=0; Fi--){
				if(Frr[F_y][Fi]>0 && Frr[F_y][Fi]<53){
					Fy = Fi;
					break;
				}
			}
			Mrr[0] = Frr[F_y][Fy];
			F_n = Fy;
		}
	}
}

float _float(int num){//整形转浮点
	float tnum = 1;
	return (float)num*tnum;
}

int _int(float num){//浮点转整形
	int tnum = 1;
	return (int)num*tnum;
}

int rand_int(int min, int max){//生成一个(min,max)的整数
	static int g_seed ;
	static int inited = 0;
	if(inited == 0){
		g_seed = time(NULL);
		inited = 1;
	}
	g_seed = 214013*g_seed+2531011;
	return min+(g_seed ^ g_seed>>15)%(max-min+1);
}

void _Aformat(){//初始化三个数组
	int ai,aj;
	for(ai = 0 ; ai < 4 ; ai++){//临时存放区数组 和 已完成区数组
		Trr[ai] = 0;
		Frr[ai] = new int[13];
		for(aj = 0 ; aj < 13 ; aj++){
			Frr[ai][aj] = 0;
		}
	}

	for(ai = 0 ; ai < 8 ; ai++){//游戏区数组
		Crr[ai] = new int[20];
		for(aj = 0 ; aj < 20 ; aj++){
			Crr[ai][aj] = 0;
		}
	}
	int *Nrr = new int[52];//乱序引用数组
	for(ai = 0 ; ai < 52 ; ai++){
		Nrr[ai] = int(ai)+1;
	}
	int al = 51;
	int ak = int(rand_int(0,al));
	int am = 0;
	int an = 0;
	while(al>0){//乱序附值
		Crr[am][an] = Nrr[ak];
		for(ai = ak ; ai <= al; ai++){
			Nrr[ai] = Nrr[ai+1];
		}
		am++;		
		if(am%9==8){
			am = 0;
			an++;
		}
		al--;
		ak = int(rand_int(0,al));
	}
	Crr[am][an] = Nrr[0];
	delete []Nrr;
	Nrr = NULL;
}

void _Bdown(int Kcode){//按下事件
  switch(Kcode){
	case PSP_BUTTON_LEFT_TRIGGER:
	case PSP_BUTTON_RIGHT_TRIGGER:
	case PSP_BUTTON_HOLD:
	case PSP_BUTTON_SELECT:		break;
	case PSP_BUTTON_UP:
		if(!Over){
			if(_mouseN<8){
				_mouseN += 8;
			}
		}
		break;
	case PSP_BUTTON_DOWN:
		if(!Over){
			if(_mouseN>7){
				_mouseN -= 8;
			}
		}
		break;
	case PSP_BUTTON_LEFT:
		if(!Over){
			if(_mouseY==28){
				if(_mouseN==8){
					_mouseN = 15;
				}else{
					_mouseN--;
			}
			}else{
				if(_mouseN==0){
					_mouseN = 7;
				}else{
					_mouseN--;
				}
			}
		}
		break;
	case PSP_BUTTON_RIGHT:
		if(!Over){
			if(_mouseY==28){
				if(_mouseN==15){
					_mouseN = 8;
				}else{
					_mouseN++;
				}
			}else{
				if(_mouseN==7){
					_mouseN = 0;
				}else{
					_mouseN++;
				}
			}
		}
		break;
	case PSP_BUTTON_CIRCLE:
	case PSP_BUTTON_SQUARE:
		if(!Over){
			if (Cget || Tmp || Fin){
				put_moveC();
			}else{			
				if(_mouseN<8){
					get_moveC();
				}else if(_mouseN>7 && _mouseN<12){
					get_tempC();
				}else {
					get_finishedC();
				}
			}
		}
		break;
	case PSP_BUTTON_CROSS:
		if(!Over){
			Tmp = false;
			Fin = false;
			Cget = false;
			My = 16;
			Myn = 19;
			T_y = -1;
			F_y = -1;
			F_n = -1;
		}
		break;
	case PSP_BUTTON_START:
		Tmp = false;
		Fin = false;
		Cget = false;
		Over = false;
		Sc = false;
		rs = int(rand_int(0,88));
		if(rs%2==0){
			play_MP3("res/music/start0.mp3");
		}else{
			play_MP3("res/music/start1.mp3");
		}	
		My = 16;
		Myn = 19;
		T_y = -1;
		F_y = -1;
		F_n = -1;
		_Aformat();	
		break;
	case PSP_BUTTON_HOME:
		_GameOver = true;
		break;
  }
}

void _MbtnDown(int Kcode){
	switch(Kcode){
	case PSP_BUTTON_UP:
	case PSP_BUTTON_DOWN: 
	case PSP_BUTTON_LEFT:
	case PSP_BUTTON_RIGHT:
	case PSP_BUTTON_SQUARE:
	case PSP_BUTTON_LEFT_TRIGGER:
	case PSP_BUTTON_RIGHT_TRIGGER:
	case PSP_BUTTON_HOME:
	case PSP_BUTTON_HOLD:
	case PSP_BUTTON_SELECT:		break;
	case PSP_BUTTON_TRIANGLE:
		Menu = true;
		break;
	case PSP_BUTTON_CIRCLE:
	case PSP_BUTTON_START:	
		if(!Menu){
			Game = true;
		}
		break;
	case PSP_BUTTON_CROSS:
		Menu = false;
		break;
	}
}

extern "C"

int main(int argc, char* argv[]){

	//初始化程序结构
	NGE_Init(INIT_ALL);

	//按扭事件定义
	InitInput(_MbtnDown,NULL,1);
	
	_Logo = image_load("res/image/logo.png",DISPLAY_PIXEL_FORMAT_8888,1);
	while(!Game){
		InputProc();
		BeginScene(1);
		DrawImage(_Logo,0,0,480,272,0,0,480,272);	
		EndScene();
		// 限制帧数 
		LimitFps(30);
	}
	image_free(_Logo);

	Game = false;
	Menu = false;

	//初始化声音
	CoolAudioDefaultInit();	
	MP3PlayInit(&_MP3);
	MP3PlayInit(&_Wav);

	_Menu = image_load("res/image/menu.png",DISPLAY_PIXEL_FORMAT_8888,1);
	_Help = image_load("res/image/help.png",DISPLAY_PIXEL_FORMAT_4444,1);
	_BG = image_load("res/image/bg.png",DISPLAY_PIXEL_FORMAT_4444,1);

	while(!Game){
		InputProc();
		BeginScene(1);
		if(!Menu){
			DrawImage(_Menu,0,0,480,272,0,0,480,272);
		}else{
			DrawImage(_BG,0,0,480,272,0,0,480,272);
			DrawImage(_Help,0,0,480,272,0,0,480,272);
		}
		EndScene();
		// 限制帧数 
		LimitFps(30);
	}
	
	image_free(_Menu);
	image_free(_Help);			
	
	//按扭事件定义
	InitInput(_Bdown,NULL,1);

	//加载鼠标图标
	_Mouse = image_load("res/image/mouse.png",DISPLAY_PIXEL_FORMAT_8888,1);	
	_CardBox = image_load("res/image/box.png",DISPLAY_PIXEL_FORMAT_4444,1);	
	_CardA = image_load("res/image/cardA.png",DISPLAY_PIXEL_FORMAT_4444,1);
	_CardB = image_load("res/image/cardB.png",DISPLAY_PIXEL_FORMAT_4444,1);
	_Start = image_load("res/image/start.png",DISPLAY_PIXEL_FORMAT_4444,1);
	_Finish = image_load("res/image/finish.png",DISPLAY_PIXEL_FORMAT_4444,1);
	
	//初始化数组
	_Aformat();

	rs = int(rand_int(0,8));
	if(rs%2==0){
		play_MP3("res/music/start0.mp3");
	}else{
		play_MP3("res/music/start1.mp3");
	}

	int i = 0;
	int j = 0;
	int ci,cj;

	//循环执行程序
	while(!_GameOver){
		//循环判断输入情况
		if(Sc){
			InputProc();
		}		
		
		//刷新鼠标位置
		set_mouseX();

		//刷新显示对象
		BeginScene(1);		
		DrawImage(_BG,0,0,480,272,0,0,480,272);
		DrawImage(_CardBox,0,0,480,72,0,_addY,480,72);
		for(j=0; j<20; j++){
			for(i = 0; i < 8; i++){
				if(Crr[i][j]!=0){
					ci = int(get_colorC(Crr[i][j]));
					cj = int(get_numberC(Crr[i][j]));
					if(Cget && i==My && j==Myn){
						if(cj<8){
							RenderQuad(_CardA,150-float(_float(ci))*50,(float(_float(cj))-1)*70,50,70,5+float(_float(i))*60,75+float(_float(j))*15+_addY,1,1,0,MAKE_RGBA_4444(188,188,188,255));
						}else{
							RenderQuad(_CardB,150-float(_float(ci))*50,(float(_float(cj))-8)*70,50,70,5+float(_float(i))*60,75+float(_float(j))*15+_addY,1,1,0,MAKE_RGBA_4444(188,188,188,255));
						}
					}else{
						if(cj<8){
							RenderQuad(_CardA,150-float(_float(ci))*50,(float(_float(cj))-1)*70,50,70,5+float(_float(i))*60,75+float(_float(j))*15+_addY,1,1,0,MAKE_RGBA_4444(255,255,255,255));
						}else{
							RenderQuad(_CardB,150-float(_float(ci))*50,(float(_float(cj))-8)*70,50,70,5+float(_float(i))*60,75+float(_float(j))*15+_addY,1,1,0,MAKE_RGBA_4444(255,255,255,255));
						}
					}
				}
			}
		}
		for(j=0; j<4; j++){
			if(Trr[j]>0 && Trr[j]<53){
				ci = int(get_colorC(Trr[j]));
				cj = int(get_numberC(Trr[j]));
				if(Tmp && j==T_y){
					if(cj<8){
						RenderQuad(_CardA,150-float(_float(ci))*50,(float(_float(cj))-1)*70,50,70,2+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(188,188,188,255));
					}else{
						RenderQuad(_CardB,150-float(_float(ci))*50,(float(_float(cj))-8)*70,50,70,2+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(188,188,188,255));
					}
				}else{
					if(cj<8){
						RenderQuad(_CardA,150-float(_float(ci))*50,(float(_float(cj))-1)*70,50,70,2+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(255,255,255,255));
					}else{
						RenderQuad(_CardB,150-float(_float(ci))*50,(float(_float(cj))-8)*70,50,70,2+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(255,255,255,255));
					}
				}
			}
			if(Frr[j][0]>0 && Frr[j][0]<53){				
				int Fry = 12;
				for(i=Fry; i>=0; i--){
					if(Frr[j][i]>0 && Frr[j][i]<53){
						Fry = i;
						break;
					}
				}
				ci = int(get_colorC(Frr[j][Fry]));
				cj = int(get_numberC(Frr[j][Fry]));
				if(Fin && j==F_y){
					if(cj<8){
						RenderQuad(_CardA,150-float(_float(ci))*50,(float(_float(cj))-1)*70,50,70,269+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(188,188,188,255));
					}else{
						RenderQuad(_CardB,150-float(_float(ci))*50,(float(_float(cj))-8)*70,50,70,269+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(188,188,188,255));
					}
				}else{
					if(cj<8){
						RenderQuad(_CardA,150-float(_float(ci))*50,(float(_float(cj))-1)*70,50,70,269+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(255,255,255,255));
					}else{
						RenderQuad(_CardB,150-float(_float(ci))*50,(float(_float(cj))-8)*70,50,70,269+float(_float(j))*53,1+_addY,1,1,0,MAKE_RGBA_4444(255,255,255,255));
					}
				}
			}
		}		
		DrawImage(_Mouse,0,0,17,18,_mouseX,_mouseY+_addY,17,18);
		if(_MP3.eos()==1){
			Sc = true;
		}else if(!Sc){
			if(Over){
				DrawImage(_Finish,0,0,253,35,113,118,253,35);
			}else{
				DrawImage(_Start,0,0,480,34,0,114,480,34);
			}
		}
		EndScene();
		
		// 限制帧数 
		LimitFps(30);
	}

	//释放数组占用的内存
	delete(Trr);
	Trr = NULL;
	for(i = 0 ; i < 4; i++){
		delete(Frr[i]);
	}
	delete(Frr);
	Frr = NULL;
	for(i = 0 ; i < 8; i++){
		delete(Crr[i]);
	}
	delete(Crr);
	Crr = NULL;
	delete(Mrr);
	Mrr = NULL;

	//释放图像占用的内存
	image_free(_Mouse);
	image_free(_BG);
	image_free(_CardBox);
	image_free(_CardA);
	image_free(_CardB);
	image_free(_Start);
	image_free(_Finish);

	//释放声音占用的内存
	CoolAudioDefaultFini();
	MP3PlayFini();

	//关闭程序
	NGE_Quit();
	return 0;
}
