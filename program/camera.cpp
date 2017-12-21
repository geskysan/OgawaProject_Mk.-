//カメラの処理	[camera.cpp]

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define	VIEW_ANGLE				(D3DXToRadian(50.f))	// 視野角
#define	VIEW_NEAR_Z				(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z				(100000.0f)				// ビュー平面のFarZ値

#define	VALUE_MOVE				(2.0f)					// カメラの移動量
#define	VALUE_ROTATE			(D3DX_PI * 0.01f)		// カメラの回転量
#define	VALUE_MOVE_DRAG			(0.30f)					// ドラッグ時の移動量
#define	VALUE_ROTATE_MOUSE		(0.003f)				// マウスでの回転量

#define	CAM_LENGTH_RATE			(5.0f)					// ホイール入力係数
#define	CAM_LENGTH_LIMIT_MIN	(100.0f)				// 視点と注視点の距離最小値
#define	CAM_LENGTH_LIMIT_MAX	(1000.0f)				// 視点と注視点の距離最大値

#define PLAYER_LENGTH_POS_R		(40)						//プレイヤーと注視点の距離
#define PLAYER_LENGTH_POS_P		(100)					//プレイヤーと視点の距離

//------------------------------------------------
//コンストラクタ
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
//デストラクタ
//------------------------------------------------
CCamera::~CCamera()
{

}

//------------------------------------------------
//CCameraの初期化
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
//CCameraの終了処理
//------------------------------------------------
void CCamera::Uninit(void)
{
}

//------------------------------------------------
//CCameraの更新処理
//------------------------------------------------
void CCamera::Update(void)
{
//	CInputKeyboard *pInputKeyboard;
//	// キーボード取得
//	pInputKeyboard = CManager::GetInputKeyboard();
//
//#ifdef _DEBUG
//
//	CDebugProc::Print("F1でカメラのキー操作\n");
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
//		CDebugProc::Print("デバッグカメラモード : ON\n");
//		return;
//	}
//	else
//		CDebugProc::Print("デバッグカメラモード : OFF\n");
//
//#endif // !_DEBUG
//
//	if (pInputKeyboard->GetKeyPress(DIK_A))
//	{
//		if (pInputKeyboard->GetKeyPress(DIK_W))
//		{// 左前移動
//			m_posP.x -= cosf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z += sinf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else if (pInputKeyboard->GetKeyPress(DIK_S))
//		{// 左後移動
//			m_posP.x -= cosf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z += sinf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else
//		{// 左移動
//			m_posP.x -= cosf(m_rot.y) * VALUE_MOVE;
//			m_posP.z += sinf(m_rot.y) * VALUE_MOVE;
//		}
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	else if (pInputKeyboard->GetKeyPress(DIK_D))
//	{// 右移動
//		if (pInputKeyboard->GetKeyPress(DIK_W))
//		{// 右前移動
//			m_posP.x += cosf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z -= sinf(m_rot.y - D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else if (pInputKeyboard->GetKeyPress(DIK_S))
//		{// 右後移動
//			m_posP.x += cosf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//			m_posP.z -= sinf(m_rot.y + D3DX_PI * 0.25f) * VALUE_MOVE;
//		}
//		else
//		{// 右移動
//			m_posP.x += cosf(m_rot.y) * VALUE_MOVE;
//			m_posP.z -= sinf(m_rot.y) * VALUE_MOVE;
//		}
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	else if (pInputKeyboard->GetKeyPress(DIK_W))
//	{// 前移動
//		m_posP.x += sinf(m_rot.y) * VALUE_MOVE;
//		m_posP.z += cosf(m_rot.y) * VALUE_MOVE;
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//	else if (pInputKeyboard->GetKeyPress(DIK_S))
//	{// 後移動
//		m_posP.x -= sinf(m_rot.y) * VALUE_MOVE;
//		m_posP.z -= cosf(m_rot.y) * VALUE_MOVE;
//
//		m_posR.x = m_posP.x + sinf(m_rot.y) * m_fLengthIntervalXZ;
//		m_posR.z = m_posP.z + cosf(m_rot.y) * m_fLengthIntervalXZ;
//	}
//
//	if (pInputKeyboard->GetKeyPress(DIK_T))
//	{// 注視点移動「上」
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
//	{// 注視点移動「下」
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
//	{// 注視点移動「左」
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
//	{// 注視点移動「右」
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
//	{// 視点移動「上」
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
//	{// 視点移動「下」
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
//	{// 視点移動「左」
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
//	{// 視点移動「右」
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
//カメラの位置設定
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
//CCameraの設定
//------------------------------------------------
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ビュー行列の初期化
	D3DXMatrixIdentity(&m_mtxView);

	// カメラの位置と方向を設定
#if 1
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posP,			// カメラの視点
		&m_posR,			// カメラの注視点
		&m_vecU);			// カメラの上の方向
#else
	m_mtxView = pCamera->GetMtxRotation();
#endif

	// ビュー行列の設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// ビューポートの取得
	D3DVIEWPORT9 vp;
	if (FAILED(pDevice->GetViewport(&vp)))
	{
		return;
	}

	// 射影行列の初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// 画角と描画範囲を設定
	float fAspect = (float)vp.Width / (float)vp.Height;
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, VIEW_ANGLE, fAspect, VIEW_NEAR_Z, VIEW_FAR_Z);

	// 射影行列の設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//------------------------------------------------
//カメラのプレイヤー追尾
//------------------------------------------------
void CCamera::PlayerCamera(CPlayer *pPlayer)
{
#ifdef _DEBUG
	if (m_bCameraDebug)
		return;
#endif

	
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();
	CDebugProc::Print("注視点の差分 :%f,%f,%f\n", m_posRDest.x, m_posRDest.y, m_posRDest.z);
	//注視点
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

	//視点
	m_posP.x = m_posR.x;
	m_posP.y = m_posR.y;
	m_posP.z = m_posR.z - PLAYER_LENGTH_POS_P*4;

//	m_posP.x += (0.0f - m_posR.x)*0.35f;
//	m_posP.z += (0.0f - m_posR.z)*0.35f;

	SetCamera();
}