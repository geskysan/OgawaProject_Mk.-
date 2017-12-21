#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "scene2D.h"

//*********************************************************
// �t�F�[�h�N���X
//*********************************************************
class CFade : public CScene2D
{
public:
	CFade(int nPri = 7);
	~CFade();

	// �t�F�[�h�̏��
	typedef enum
	{
		STATUS_NONE = 0,
		STATUS_FADEOUT,		// �t�F�[�h�A�E�g��
		STATUS_FADEOUT_END,	// �t�F�[�h�A�E�g�I��
		STATUS_FADEIN,		// �t�F�[�h�C����
		STATUS_FADEIN_END,	// �t�F�[�h�C���I��
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
	D3DXCOLOR m_color;			// �F
	bool m_bFade;				// �t�F�[�h���Ă��邩�ǂ���
	int m_nTimer;				// �^�C�}�[
	float m_fValueAlpha;		// �A���t�@�l
	STATUS m_status;			// ���
	CManager::MODE m_modeNext;	// ���̃��[�h
};
#endif // !_FADE_H_