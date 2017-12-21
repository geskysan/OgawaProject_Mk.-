// メイン処理 [main.h]
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma warning(disable:4996)
#pragma warning(disable:4005)

//------------------------------------------------
// インクルードファイル
//------------------------------------------------
#include <Windows.h>
#include <list>
#include "d3dx9.h"
#include "stdio.h"
#include "XAudio2.h"
#include "dinput.h"
#define DIRECTINPUT_VERSION (0x0800)
//メモリーリーク対応処置
#ifndef MEMORY_LEAK_H
#define MEMORY_LEAK_H
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif // _DEBUG
#endif // !MEMORY_LEAK_H

#ifndef SAFE_UNINIT
#define SAFE_UNINIT(p) {if(p){(p)->Uninit();(p)=NULL;}}
#endif //!SAFE_UNINIT

#ifndef SEFE_UNINIT_DELETE
#define SAFE_UNINIT_DELETE(p) {if(p){(p)->Uninit();delete (p);(p)=NULL;}}
#endif // !SEFE_UNINIT_DELETE

#ifndef SAFE_RELESE
#define SAFE_RELESE(p) {if(p){(p)->Release();(p) = NULL;}}
#endif // !SAFE_RELESE

//------------------------------------------------
// ライブラリファイル
//------------------------------------------------
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dinput8.lib")

//------------------------------------------------
// マクロ定義
//------------------------------------------------
#define SCREEN_WIDTH	(960)	//ウィンドウの横幅
#define SCREEN_HEIGHT	(540)	//ウィンドウの縦幅
#define CENTER_WIDTH	(SCREEN_WIDTH / 2) //ウィンドウの横幅の中心
#define CENTER_HEIGHT	(SCREEN_HEIGHT / 2)  //ウィンドウの縦幅の中心

#endif // !_MAIN_h_