//2D�`��ɂ��A�j���[�V����	[2Danim.h]
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
	int m_iAnimPattern;		 //�A�j���[�V�����̃p�^�[��
	int m_iAnimCurrentTimer; //���݂̎���
	int m_iAnimTime;		 //�؂�ւ�鎞��
	bool m_bAnimLoop;		 //�A�j���[�V�����̃��[�v	true�con / false�coff
	bool m_bAnimate;		 //�A�j���[�V���������邩�ǂ���
	D3DXVECTOR2 m_vTextureSize;	//�|���S���̑傫��
	int m_iTextureDivisionSide; //���̕����� 
	int m_iTextureDivisionVer;  //�c�̕�����
	
	void AnimationLoad();

};
#endif // !_2DANIM_H_