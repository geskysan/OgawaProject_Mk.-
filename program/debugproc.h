//	�f�o�b�O����	[debugproc.h]
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------
#define	LENGTH_STRING_BUFF		(1024)		// �f�o�b�O�\���̃o�b�t�@

//------------------------------------------------
//�f�o�b�O�����N���X
//------------------------------------------------
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void Init(void);
	void Uninit(void);

	static void Print(char *fmt, ...);
	static void Draw(void);

	static bool IsEnableDisp(void) { return m_bDisp; }
	static void EnableDisp(bool bDisp) { m_bDisp = bDisp; }

private:
	static LPD3DXFONT m_pFont;				// �t�H���g�ւ̃|�C���^
	static char m_aStr[LENGTH_STRING_BUFF];	// �f�o�b�O�\���̃o�b�t�@

	static bool m_bDisp;					// �f�o�b�O�\��ON/OFF
};

#endif