//=============================================
// ランキング処理
//=============================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene2D.h"
#include "stdio.h"
#include "stdarg.h"


class CRanking : public CScene2D
{
public:
	CRanking();
	~CRanking();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ランキングの値をゲットする関数
	int GetRanking(void) { return m_Ranking; }

private:
	int m_Ranking;	// ランキングの値
};
#endif 

