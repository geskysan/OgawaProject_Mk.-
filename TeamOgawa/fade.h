#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "scene2D.h"

//*********************************************************
// フェードクラス
//*********************************************************
class CFade : public CScene2D
{
public:
	CFade(int nPri = 7);
	~CFade();

	// フェードの状態
	typedef enum
	{
		STATUS_NONE = 0,
		STATUS_FADEOUT,		// フェードアウト中
		STATUS_FADEOUT_END,	// フェードアウト終了
		STATUS_FADEIN,		// フェードイン中
		STATUS_FADEIN_END,	// フェードイン終了
		STATUS_MAX,
	} STATUS;

	static CFade *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Start(STATUS status, int nTimer, CManager::MODE modeNext = CManager::MODE_NONE);
	STATUS GetStatus(void) { return m_status; }

private:
	D3DXCOLOR m_color;			// 色
	bool m_bFade;				// フェードしているかどうか
	int m_nTimer;				// タイマー
	float m_fValueAlpha;		// アルファ値
	STATUS m_status;			// 状態
	CManager::MODE m_modeNext;	// 次のモード
};
#endif // !_FADE_H_