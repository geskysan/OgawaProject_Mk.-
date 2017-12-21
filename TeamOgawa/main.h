// ���C������ [main.h]
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma warning(disable:4996)
#pragma warning(disable:4005)

//------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------
#include <Windows.h>
#include <list>
#include "d3dx9.h"
#include "stdio.h"
#include "XAudio2.h"
#include "dinput.h"
#define DIRECTINPUT_VERSION (0x0800)
//�������[���[�N�Ή����u
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
// ���C�u�����t�@�C��
//------------------------------------------------
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dinput8.lib")

//------------------------------------------------
// �}�N����`
//------------------------------------------------
#define SCREEN_WIDTH	(960)	//�E�B���h�E�̉���
#define SCREEN_HEIGHT	(540)	//�E�B���h�E�̏c��
#define CENTER_WIDTH	(SCREEN_WIDTH / 2) //�E�B���h�E�̉����̒��S
#define CENTER_HEIGHT	(SCREEN_HEIGHT / 2)  //�E�B���h�E�̏c���̒��S

#endif // !_MAIN_h_