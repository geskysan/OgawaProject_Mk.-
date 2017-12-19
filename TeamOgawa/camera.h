// カメラの処理	[camera.h]
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"

class CPlayer;

//------------------------------------------------
//カメラのクラス
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
	D3DXMATRIX m_mtxView;			// ビューマトリックス
	D3DXMATRIX m_mtxProjection;		// プロジェクションマトリックス

	D3DXVECTOR3 m_posP;				// 視点
	D3DXVECTOR3 m_posPDest;			// 視点の慣性
	D3DXVECTOR3 m_posR;				// 注視点
	D3DXVECTOR3 m_posRDest;			// 注視点の慣性
	
	D3DXVECTOR3 m_vecU;				// 上方向ベクトル
	D3DXVECTOR3 m_rot;				// 向き
	float m_fLengthInterval;		// 視点から注視点までの距離
	float m_fLengthIntervalXZ;		// 視点から注視点までの距離(XZ平面)

	D3DXQUATERNION m_quatRot;
	D3DXMATRIX m_mtxRot;

#ifdef _DEBUG
	bool m_bCameraDebug;			// デバッグ用	キー操作でカメラ移動
#endif // _DEBUG
};

#endif
