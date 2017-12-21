//ライトの処理	[light.h]
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define NUM_LIGHT	(4)	//ライトの数

//------------------------------------------------
//ライトのクラス
//------------------------------------------------
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetLight(void);

private:
	D3DLIGHT9 m_aLight[NUM_LIGHT];	//ライト情報
};
#endif // !_LIGHT_H_