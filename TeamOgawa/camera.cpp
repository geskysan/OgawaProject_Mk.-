//�J�����̏���	[camera.cpp]

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------
#define	VIEW_ANGLE				(D3DXToRadian(50.f))	// ����p
#define	VIEW_NEAR_Z				(10.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z				(100000.0f)				// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE				(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE			(D3DX_PI * 0.01f)		// �J�����̉�]��
#define	VALUE_MOVE_DRAG			(0.30f)					// �h���b�O���̈ړ���
#define	VALUE_ROTATE_MOUSE		(0.003f)				// �}�E�X�ł̉�]��

#define	CAM_LENGTH_RATE			(5.0f)					// �z�C�[�����͌W��
#define	CAM_LENGTH_LIMIT_MIN	(100.0f)				// ���_�ƒ����_�̋����ŏ��l
#define	CAM_LENGTH_LIMIT_MAX	(1000.0f)				// ���_�ƒ����_�̋����ő�l

#define PLAYER_LENGTH_POS_R		(40)						//�v���C���[�ƒ����_�̋���
#define PLAYER_LENGTH_POS_P		(100)					//�v���C���[�Ǝ��_�̋���

//------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------
CCamera::CCamera()
{
	float fLengthXZ;

	m_posP = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fLengthInterval = sqrtf((m_posP.x - m_posR.x) * (m_posP.x - m_posR.x)
		+ (m_posP.y - m_posR.y) * (m_posP.y - m_posR.y)
		+ (m_posP.z - m_posR.z) * (m_posP.z - m_posR.z));
	fLengthXZ = sqrtf((m_posP.x - m_posR.x) * (m_posP.x - m_posR.x)
		+ (m_posP.z - m_posR.z) * (m_posP.z - m_posR.z));
	m_rot.y = atan2f((m_posR.x - m_posP.x), (m_posR.z - m_posP.z));
	m_rot.x = atan2f((m_posR.y - m_posP.y), fLengthXZ);

	m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;

	D3DXMatrixIdentity(&m_mtxRot);
	D3DXQuaternionIdentity(&m_quatRot);
}

//------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------
CCamera::~CCamera()
{

}

//------------------------------------------------
//CCamera�̏�����
//------------------------------------------------
HRESULT CCamera::Init(void)
{
	SetPosition(m_posP, m_posR);
	SetCamera();

#ifdef _DEBUG
	m_bCameraDebug = false;
#endif // _DEBUG

	return S_OK;
}

//------------------------------------------------
//CCamera�̏I������
//------------------------------------------------
void CCamera::Uninit(void)
{
}

//------------------------------------------------
//CCamera�̍X�V����
//------------------------------------------------
void CCamera::Update(void)
{
//	CInputKeyboard *pInputKeyboard;
//	// �L�[�{�[�h�擾
//	pInputKeyboard = CManager::GetInputKeyboard();
//
//#ifdef _DEBUG
//
//	CDebugProc::Print("F1�ŃJ�����̃L�[����\n");
//	
//	if (pInputKeyboard->GetKeyTrigger(DIK_F1))
//	{
//		if (m_bCameraDebug)
//			m_bCameraDebug = false;
//		else
//			m_bCameraDebug = true;
//	}
//
//	if (!m_bCameraDebug)
//	{
//		CDebugProc::Print("�f�o�b�O�J�������[�h : ON\n");
//		return;
//	}
//	else
//		CDebugProc::Print("�f�o�b�O�J�������[�h : OFF\n");
//
//#endif // !_DEBUG
//
//	if (pInputKeyboard->GetKeyPress(DIK_A))
//	{
//		if (pInputKeyboard->GetKeyPress(DIK_W))
//		{// ���O�ړ�
//			m_posP.x -= cosf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z += sinf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else if (pInputKeyboard->GetKeyPress(DIK_S))
//		{// ����ړ�
//			m_posP.x -= cosf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z += sinf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else
//		{// ���ړ�
//			m_posP.x -= cosf(m_rot.y) * VALUE_MOVE;
//			m_posP.z += sinf(m_rot.y) * VALUE_MOVE;
//		}
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	else if (pInputKeyboard->GetKeyPress(DIK_D))
//	{// �E�ړ�
//		if (pInputKeyboard->GetKeyPress(DIK_W))
//		{// �E�O�ړ�
//			m_posP.x += cosf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z -= sinf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else if (pInputKeyboard->GetKeyPress(DIK_S))
//		{// �E��ړ�
//			m_posP.x += cosf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z -= sinf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else
//		{// �E�ړ�
//			m_posP.x += cosf(m_rot.y) * VALUE_MOVE;
//			m_posP.z -= sinf(m_rot.y) * VALUE_MOVE;
//		}
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	else if (pInputKeyboard->GetKeyPress(DIK_W))
//	{// �O�ړ�
//		m_posP.x += sinf(m_rot.y) * VALUE_MOVE;
//		m_posP.z += cosf(m_rot.y) * VALUE_MOVE;
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	else if (pInputKeyboard->GetKeyPress(DIK_S))
//	{// ��ړ�
//		m_posP.x -= sinf(m_rot.y) * VALUE_MOVE;
//		m_posP.z -= cosf(m_rot.y) * VALUE_MOVE;
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//
//	if (pInputKeyboard->GetKeyPress(DIK_T))
//	{// �����_�ړ��u��v
//		m_rot.x += VALUE_ROTATE;
//		if (m_rot.x > (D3DX_PI / 2.0f - D3DX_PI*0.1f))
//		{
//			m_rot.x = (D3DX_PI / 2.0f - D3DX_PI*0.1f);
//		}
//
//		m_posR.y = m_posP.y + sinf(m_rot.x) * m_fLengthInterval;
//
//		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	if (pInputKeyboard->GetKeyPress(DIK_B))
//	{// �����_�ړ��u���v
//		m_rot.x -= VALUE_ROTATE;
//		if (m_rot.x < (-D3DX_PI / 2.0f + D3DX_PI*0.1f))
//		{
//			m_rot.x = (-D3DX_PI / 2.0f + D3DX_PI*0.1f);
//		}
//
//		m_posR.y = m_posP.y + sinf(m_rot.x) * m_fLengthInterval;
//
//		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	if (pInputKeyboard->GetKeyPress(DIK_Q))
//	{// �����_�ړ��u���v
//		m_rot.y -= VALUE_ROTATE;
//		if (m_rot.y < -D3DX_PI)
//		{
//			m_rot.y += D3DX_PI*2.0f;
//		}
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	if (pInputKeyboard->GetKeyPress(DIK_E))
//	{// �����_�ړ��u�E�v
//		m_rot.y += VALUE_ROTATE;
//		if (m_rot.y > D3DX_PI)
//		{
//			m_rot.y -= D3DX_PI*2.0f;
//		}
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//
//	if (pInputKeyboard->GetKeyPress(DIK_Y))
//	{// ���_�ړ��u��v
//		m_rot.x -= VALUE_ROTATE;
//		if (m_rot.x < (-D3DX_PI / 2.0f + D3DX_PI*0.02f))
//		{
//			m_rot.x = (-D3DX_PI / 2.0f + D3DX_PI*0.02f);
//		}
//
//		m_posP.y = m_posR.y - sinf(m_rot.x) * m_fLengthInterval;
//
//		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
//		m_posP.x = m_posR.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posP.z = m_posR.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	if (pInputKeyboard->GetKeyPress(DIK_N))
//	{// ���_�ړ��u���v
//		m_rot.x += VALUE_ROTATE;
//		if (m_rot.x > (D3DX_PI / 2.0f - D3DX_PI*0.02f))
//		{
//			m_rot.x = (D3DX_PI / 2.0f - D3DX_PI*0.02f);
//		}
//
//		m_posP.y = m_posR.y - sinf(m_rot.x) * m_fLengthInterval;
//
//		m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;
//		m_posP.x = m_posR.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posP.z = m_posR.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	if (pInputKeyboard->GetKeyPress(DIK_Z))
//	{// ���_�ړ��u���v
//		m_rot.y += VALUE_ROTATE;
//		if (m_rot.y > D3DX_PI)
//		{
//			m_rot.y -= D3DX_PI*2.0f;
//		}
//
//		m_posP.x = m_posR.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posP.z = m_posR.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	if (pInputKeyboard->GetKeyPress(DIK_X))
//	{// ���_�ړ��u�E�v
//		m_rot.y -= VALUE_ROTATE;
//		if (m_rot.y < -D3DX_PI)
//		{
//			m_rot.y += D3DX_PI*2.0f;
//		}
//
//		m_posP.x = m_posR.x - sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posP.z = m_posR.z - cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//
	SetCamera();
}

//------------------------------------------------
//�J�����̈ʒu�ݒ�
//------------------------------------------------
void CCamera::SetPosition(D3DXVECTOR3 posP, D3DXVECTOR3 posR)
{
	float fLengthXZ;

	m_fLengthInterval = sqrtf((posR.x - posP.x) * (posR.x - posP.x)
		+ (posR.y - posP.y) * (posR.y - posP.y)
		+ (posR.z - posP.z) * (posR.z - posP.z));
	fLengthXZ = sqrtf((posR.x - posP.x) * (posR.x - posP.x)
		+ (posR.z - posP.z) * (posR.z - posP.z));

	m_posP = posP;
	m_posR = posR;
	m_rot.y = atan2f((posR.x - posP.x), (posR.z - posP.z));
	m_rot.x = atan2f((posR.y - posP.y), fLengthXZ);

	m_fLengthIntervalXZ = cosf(m_rot.x) * m_fLengthInterval;

	if (fLengthXZ == 0.0f)
	{
		m_vecU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}

	D3DXQuaternionRotationYawPitchRoll(&m_quatRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixRotationQuaternion(&m_mtxRot, &m_quatRot);
}

//------------------------------------------------
//CCamera�̐ݒ�
//------------------------------------------------
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �r���[�s��̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �J�����̈ʒu�ƕ�����ݒ�
#if 1
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posP,			// �J�����̎��_
		&m_posR,			// �J�����̒����_
		&m_vecU);			// �J�����̏�̕���
#else
	m_mtxView = pCamera->GetMtxRotation();
#endif

	// �r���[�s��̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �r���[�|�[�g�̎擾
	D3DVIEWPORT9 vp;
	if (FAILED(pDevice->GetViewport(&vp)))
	{
		return;
	}

	// �ˉe�s��̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// ��p�ƕ`��͈͂�ݒ�
	float fAspect = (float)vp.Width / (float)vp.Height;
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, VIEW_ANGLE, fAspect, VIEW_NEAR_Z, VIEW_FAR_Z);

	// �ˉe�s��̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//------------------------------------------------
//�J�����̃v���C���[�ǔ�
//------------------------------------------------
void CCamera::PlayerCamera(CPlayer *pPlayer)
{
#ifdef _DEBUG
	if (m_bCameraDebug)
		return;
#endif

	
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	CDebugProc::Print("�����_�̍��� :%f,%f,%f\n", m_posRDest.x, m_posRDest.y, m_posRDest.z);
	//�����_
	float PlayerLength = PLAYER_LENGTH_POS_R;
	if (!pPlayer->GetDirection())
		PlayerLength *= -1.0f;

	m_posRDest.x = PlayerPos.x + PlayerLength;
	m_posRDest.y = PlayerPos.y;

	D3DXVECTOR3 fDiff = m_posRDest - m_posR;
	m_posR += fDiff * 0.1f;

	//Diff = m_posRDest - m_posR;
	//m_posR += Diff * 0.25f;
	//m_posRDest += (-m_posRDest)*0.15f;
	//m_posPDest.x += PlayerPos.x;
	//m_posPDest.y = PlayerPos.y - 150.f;
	//m_posPDest.z += PlayerPos.z;

	//���_
	m_posP.x = m_posR.x;
	m_posP.y = m_posR.y;
	m_posP.z = m_posR.z - PLAYER_LENGTH_POS_P*4;

//	m_posP.x += (0.0f - m_posR.x)*0.35f;
//	m_posP.z += (0.0f - m_posR.z)*0.35f;

	SetCamera();
}