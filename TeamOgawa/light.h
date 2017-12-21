//���C�g�̏���	[light.h]
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------
#define NUM_LIGHT	(4)	//���C�g�̐�

//------------------------------------------------
//���C�g�̃N���X
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
	D3DLIGHT9 m_aLight[NUM_LIGHT];	//���C�g���
};
#endif // !_LIGHT_H_