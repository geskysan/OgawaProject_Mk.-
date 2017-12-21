//プレイヤーの処理	[player.cpp]

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "3Danim.h"
#include "camera.h"
#include "scene2D.h"
#include "objectblock.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define PLAYER_SPEED (0.5f)		//プレイヤーの移動速度
#define INERTIA_MOVE (0.15f)	//プレイヤーの慣性
#define JUMP_POWER (1.39f)		//プレイヤーのジャンプ力
#define MAX_JUMP_TIMER	8		
#define PLAYER_SIZE_X	20
#define PLAYER_SIZE_Y	35

//------------------------------------------------
//コンストラクタ
//------------------------------------------------
CPlayer::CPlayer()
{
	m_AddMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//------------------------------------------------
//デストラクタ
//------------------------------------------------
CPlayer::~CPlayer()
{

}

//------------------------------------------------
//初期化処理
//------------------------------------------------
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CScene3D::Init(0, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), PLAYER_SIZE_X, PLAYER_SIZE_Y);
	CScene3D::LoadTexture("data/TEXTURE/megaman.png");
	CScene3D::SetVertexPos(D3DXVECTOR3(PLAYER_SIZE_X/2, PLAYER_SIZE_Y, 0),
		D3DXVECTOR3(PLAYER_SIZE_X/2, 0, 0),
		D3DXVECTOR3(-PLAYER_SIZE_X/2, PLAYER_SIZE_Y, 0),
		D3DXVECTOR3(-PLAYER_SIZE_X/2, 0, 0));
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump = false;
	m_bJumpKey = false;
	JumpPawer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fJumpPower = 0.0f;
	m_iJumpTimer = 0;
	CollisionTop = false;
	CollisionRight = false;
	CollisionLeft = false;
	m_bDirection = false;

	return S_OK;
}

//------------------------------------------------
//終了処理
//------------------------------------------------
void CPlayer::Uninit(void)
{
	CScene3D::Uninit();
}

//------------------------------------------------
//更新処理
//------------------------------------------------
void CPlayer::Update()
{
	m_AddMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetCollisionTop(false);
	SetCollisionLeft(false);
	SetCollisionRight(false);
	CCamera *pCamera = CManager::GetCamera();
	pCamera->PlayerCamera(this);
	
	UpdateBB();

	CDebugProc::Print("PlayerBBMin %f,%f,%f\n",m_BBMin.x,m_BBMin.y,m_BBMin.z);
	CDebugProc::Print("PlayerBBMax %f,%f,%f\n", m_BBMax.x, m_BBMax.y, m_BBMax.z);
	CDebugProc::Print("プレイヤー座標 : X : %f Y : %f Z : %f\n", m_pos.x, m_pos.y, m_pos.z);
}

//------------------------------------------------
//描画処理
//------------------------------------------------
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::Draw();
}

//------------------------------------------------
//キー操作処理
//------------------------------------------------
void CPlayer::KeyControl()
{

	CInputKeyboard *pKeyboard;
	pKeyboard = CManager::GetInputKeyboard();

	CInputJoypad *pJoypad;
	pJoypad = CManager::GetInputJoypad();

	CDebugProc::Print("重力ON\n");	
	m_Move.y -= GRAVITY;

	//移動
	if (pKeyboard->GetKeyPress(DIK_LEFT) && !CollisionRight)
	{//左に移動
		m_bDirection = false;
		m_Move.x += -PLAYER_SPEED;

	}
    if (pKeyboard->GetKeyPress(DIK_RIGHT)&& !CollisionLeft)
	{//右に移動
		m_bDirection=true;
		m_Move.x += PLAYER_SPEED;

	}

	if (pKeyboard->GetKeyTrigger(DIK_R))
	{
		C3DAnim *m_ap3DAnim = new C3DAnim;
		m_ap3DAnim->Init(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(60, 60), false, 3, 20, 1);
	}
	JumpControl();

	if (m_pos.y < -2300)
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_pos += m_Move + m_AddMove;
	m_Move.x += (-m_Move.x)*INERTIA_MOVE;

	CollisionLeft = false;
	CollisionRight = false;

	CDebugProc::Print("移動速度 : %f,%f,%f\n", m_Move.x, m_Move.y, m_Move.z);
}

void CPlayer::JumpControl(void)
{
	CInputKeyboard *pKeyboard;
	pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard->GetKeyPress(DIK_SPACE) && m_iJumpTimer < MAX_JUMP_TIMER && m_bJump)
	{
		m_bJumpKey = true;
		m_iJumpTimer++;
		m_Move.y += JUMP_POWER;
	}
	
	if (pKeyboard->GetKeyRelease(DIK_SPACE))
	{
		m_bJumpKey = false;
		m_bJump = false;
		m_iJumpTimer = 0;
	}
}

void CPlayer::AddPostion(D3DXVECTOR3 pos)
{
	m_pos += pos;

}

void CPlayer::UpdateBB()
{
	m_BBMin = m_pos + D3DXVECTOR3(-PLAYER_SIZE_X / 2, 0.0f, 0.0f);
	m_BBMax = m_pos + D3DXVECTOR3(PLAYER_SIZE_X / 2, PLAYER_SIZE_Y , 0.0f);

}

bool CPlayer::CollisionBlock(CObjectBlock *pObject)
{
	D3DXVECTOR3 BlockBBMin = pObject->GetBBMin();
	D3DXVECTOR3 BlockBBMax = pObject->GetBBMax();

	if (m_BBMin.x < BlockBBMax.x && BlockBBMin.x < m_BBMax.x &&
		m_BBMin.y < BlockBBMax.y && BlockBBMin.y < m_BBMax.y &&
		m_BBMin.z < BlockBBMax.z && BlockBBMin.z < m_BBMax.z)
	{
		float fTop, fBottom, fRight, fLeft;
		fTop = abs(m_BBMin.y - BlockBBMax.y);
		fBottom = abs(BlockBBMin.y - m_BBMax.y);
		fRight = abs(BlockBBMax.x - m_BBMin.x);
		fLeft = abs(m_BBMax.x - BlockBBMin.x);
		
		if (fTop < fBottom && fTop < fLeft && fTop < fRight)
		{
			CDebugProc::Print("上\n");
			SetCollisionTop(true);
			AddPostion(D3DXVECTOR3(0.0f, fTop, 0.0f));
		}
		else if (fBottom < fLeft&& fBottom < fRight)
		{
			SetCollisionBottom();
			AddPostion(D3DXVECTOR3(0.0f, -fBottom, 0.0f));
		}
		else if (fLeft < fRight)
		{
			SetCollisionLeft(true);
			AddPostion(D3DXVECTOR3(-fLeft, 0.0f, 0.0f));
		}
		else
		{
			SetCollisionRight(true);
			AddPostion(D3DXVECTOR3(fRight, 0.0f, 0.0f));
		}

		UpdateBB();
		return true;

	}
	return false;
}

void CPlayer::SetCollisionTop(bool btop)
{
//	CollisionTop = btop;
	if (btop)
	{
		m_Move.y = 0.0f;
		m_bJump = true;

	}
}

void CPlayer::SetCollisionRight(bool bRight) 
{
	CollisionRight = bRight; 
	if(bRight)
		m_Move.x = 0.0f;

}

void CPlayer::SetCollisionLeft(bool bLeft) 
{ 
	CollisionLeft = bLeft;

	if(bLeft)
		m_Move.x = 0.0f;

}

void CPlayer::SetCollisionBottom() 
{ 
	m_Move.y = 0.0f;
}