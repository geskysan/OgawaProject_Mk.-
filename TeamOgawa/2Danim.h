//2D描画によるアニメーション	[2Danim.h]
#ifndef _2DANIM_H_
#define _2DANIM_H_

#include "scene2D.h"

class C2DAnim : public CScene2D
{
public:
	C2DAnim();
	~C2DAnim();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 vSize, bool bLoop, int AnimTime, int iDivisionSide, int iDivisionVer, bool bAnimate = true);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	int GetAnimPattern(void) { return m_iAnimPattern; }
	void SetAnimPattern(int iNumPattern);
private:
	int m_iAnimPattern;		 //アニメーションのパターン
	int m_iAnimCurrentTimer; //現在の時間
	int m_iAnimTime;		 //切り替わる時間
	bool m_bAnimLoop;		 //アニメーションのループ	true…on / false…off
	bool m_bAnimate;		 //アニメーションをするかどうか
	D3DXVECTOR2 m_vTextureSize;	//ポリゴンの大きさ
	int m_iTextureDivisionSide; //横の分割数 
	int m_iTextureDivisionVer;  //縦の分割数
	
	void AnimationLoad();

};
#endif // !_2DANIM_H_