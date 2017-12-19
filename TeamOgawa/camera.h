// �J�����̏���	[camera.h]
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"

class CPlayer;

//------------------------------------------------
//�J�����̃N���X
//------------------------------------------------
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetPosition(D3DXVECTOR3 posP, D3DXVECTOR3 posR);

	D3DXVECTOR3 GetPosP(void) { return m_posP; }
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetVecU(void) { return m_vecU; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetCamera(void);
	void PlayerCamera(CPlayer *pPlayer);
	D3DXMATRIX GetViewMatrix(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMatrix(void) { return m_mtxProjection; }

private:
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X

	D3DXVECTOR3 m_posP;				// ���_
	D3DXVECTOR3 m_posPDest;			// ���_�̊���
	D3DXVECTOR3 m_posR;				// �����_
	D3DXVECTOR3 m_posRDest;			// �����_�̊���
	
	D3DXVECTOR3 m_vecU;				// ������x�N�g��
	D3DXVECTOR3 m_rot;				// ����
	float m_fLengthInterval;		// ���_���璍���_�܂ł̋���
	float m_fLengthIntervalXZ;		// ���_���璍���_�܂ł̋���(XZ����)

	D3DXQUATERNION m_quatRot;
	D3DXMATRIX m_mtxRot;

#ifdef _DEBUG
	bool m_bCameraDebug;			// �f�o�b�O�p	�L�[����ŃJ�����ړ�
#endif // _DEBUG
};

#endif
