//マネージャーの処理	[manager.h]
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "library.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define GRAVITY	(0.398f)			//重力

//------------------------------------------------
//プロトタイプ宣言
//------------------------------------------------
class CRenderer;
class CDebugProc;
class CSound;
class CFade;
class CTest;
class CInputKeyboard;
class CLight;
class CCamera;
class CInputJoypad;
class CGamemain;
class CTitle;
class CInputCheck;
//------------------------------------------------
//マネージャークラス
//------------------------------------------------
class CManager
{
public:
	CManager();
	~CManager();

	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_GAMEMAIN,
		MODE_RESULT,
		MODE_INPUTCHECK,
		MODE_MAX,
	}MODE;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CRenderer *GetRenderer(void){ return m_pRenderer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CInputCheck *GetInputCheck(void) { return m_pInputCheck; }
	static CInputJoypad *GetInputJoypad(void) { return m_pInputJoypad; }
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CGamemain *GetGameMain(void) { return m_pGameMain; }
	static CSound *GetSound(void) { return m_pSound; }
private:
	static MODE m_mode;
	static CRenderer *m_pRenderer;
	static CCamera *m_pCamera;
	static CInputCheck *m_pInputCheck;
	static CInputJoypad *m_pInputJoypad;
	static CInputKeyboard *m_pInputKeyboard;
	static CLight *m_pLight;
	static CSound *m_pSound;
	//モード
	static CTitle *m_pTitle;
	static CGamemain *m_pGameMain;
#ifdef _DEBUG
	static CDebugProc *m_pDebugProc;
#endif 
};
#endif // !_MANAGER_H_