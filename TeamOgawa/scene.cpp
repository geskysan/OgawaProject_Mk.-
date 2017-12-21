//=============================================================================
//
// 描画対象オブジェクトの処理 [scene.cpp]
// Author : 
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "sceneBillboard.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ENABLE_DELETE_FLAG		// 死亡フラグ
//#undef	ENABLE_DELETE_FLAG

//*****************************************************************************
// 静的変数
//*****************************************************************************
// リスト用
CScene *CScene::m_apTop[NUM_PRIORITY] = {};
CScene *CScene::m_apCur[NUM_PRIORITY] = {};


//=============================================================================
// リスト初期化
//=============================================================================
void CScene::InitList(void)
{
}

//=============================================================================
// リスト開放
//=============================================================================
void CScene::UninitList(void)
{
}

//=============================================================================
// リスト先頭取得
//=============================================================================
CScene *CScene::GetListTop(int nPriority)
{
	return m_apTop[nPriority];
}

//=============================================================================
// リスト内オブジェ更新
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			// オブジェクトの更新処理
			pScene->Update();

			pScene = pSceneNext;
		}
	}

#ifdef ENABLE_DELETE_FLAG
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDelete == true)
			{
				pScene->UnlinkList();

				delete pScene;
			}

			pScene = pSceneNext;
		}
	}
#endif
}

//=============================================================================
// リスト内オブジェ描画
//=============================================================================
void CScene::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();

	// カメラの設定
	pCamera->SetCamera();

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			// オブジェクトの描画処理
			pScene->Draw();

			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// オブジェクトを破棄
//=============================================================================
void CScene::Release(void)
{
#ifdef ENABLE_DELETE_FLAG
	m_bDelete = true;
#else
	// リストから削除
	UnlinkList();

	delete this;
#endif
}

//=============================================================================
// オブジェクト全体を破棄
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			// オブジェクトの終了処理
			pScene->Uninit();

			//			delete pScene;

			pScene = pSceneNext;
		}
	}

#ifdef ENABLE_DELETE_FLAG
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDelete == true)
			{
				pScene->UnlinkList();

				delete pScene;
			}

			pScene = pSceneNext;
		}
	}
#endif
}

//=============================================================================
// CSceneコンストラクタ
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objType)
{
	// リストに登録
	LinkList(nPriority);

	m_objType = objType;
	m_bDelete = false;
}

//=============================================================================
// CSceneデストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// リストに登録
//=============================================================================
void CScene::LinkList(int nPriority)
{
	// プライオリティを設定
	m_nPriority = nPriority;

	if (!m_apTop[nPriority])
	{// リストの先頭(pTop)が存在しない場合
		m_apTop[nPriority] = this;
	}
	if (!m_apCur[nPriority])
	{// 現在のオブジェクト(pCur)が存在しない場合
		m_apCur[nPriority] = this;
	}

	m_apCur[nPriority]->m_pNext = this;		// 現在のオブジェクト(pCur)の次のオブジェクトを自分(this)にする
	if (m_apCur[nPriority] == this)
	{// 現在のオブジェクト(pCur)が自分(this)の場合
		m_pPrev = NULL;						// 自分(this)の前のオブジェをNULLする
	}
	else
	{
		m_pPrev = m_apCur[nPriority];		// 自分(this)の前のオブジェクトを現在のオブジェクト(pCur)にする
	}
	m_apCur[nPriority] = this;				// 現在のオブジェクト(pCur)を自分(this)にする
	m_pNext = NULL;							// 自分(this)の次のオブジェをNULLにする
}

//=============================================================================
// リストから削除
//=============================================================================
void CScene::UnlinkList(void)
{
	CScene *pScene, *pSceneNext, *pScenePrev;

	// リストの先頭(pTop)から現在位置(pCur)に向かって辿っていく
	pScene = m_apTop[m_nPriority];
	while (pScene)
	{
		pSceneNext = pScene->m_pNext;

		if (pScene == this)
		{// 対象のオブジェクトが自分(this)の場合
			if (pScene->m_pPrev)
			{// 対象のオブジェクトの前にオブジェクトが存在する場合
			 // 自分(this)の前のオブジェクトの次のオブジェクトを自分(this)の次のオブジェクトにする
				pScene->m_pPrev->m_pNext = pScene->m_pNext;
			}
			if (pScene->m_pNext)
			{// 対象のオブジェクトの次にオブジェクトが存在する場合
			 // 自分(this)の次のオブジェクトの前のオブジェクトを自分(this)の前のオブジェクトにする
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;
			}

			if (pScene == m_apTop[m_nPriority])
			{// 対象のオブジェクトがリストの先頭の場合
				m_apTop[m_nPriority] = pSceneNext;
			}
		}

		pScene = pSceneNext;
	}

	// リストの現在位置(pCur)から先頭(pTop)に向かって辿っていく
	pScene = m_apCur[m_nPriority];
	while (pScene)
	{
		pScenePrev = pScene->m_pPrev;

		if (pScene == this)
		{// 対象のオブジェクトが自分(this)の場合
			if (pScene->m_pPrev)
			{// 対象のオブジェクトの前にオブジェクトが存在する場合
			 // 自分(this)の前のオブジェクトの次のオブジェクトを自分(this)の次のオブジェクトにする
				pScene->m_pPrev->m_pNext = pScene->m_pNext;
			}
			if (pScene->m_pNext)
			{// 対象のオブジェクトの次にオブジェクトが存在する場合
			 // 自分(this)の次のオブジェクトの前のオブジェクトを自分(this)の前のオブジェクトのする
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;
			}

			if (pScene == m_apCur[m_nPriority])
			{// 対象のオブジェクトが現在のオブジェクト(pCur)の場合
				m_apCur[m_nPriority] = pScenePrev;
			}
		}

		pScene = pScenePrev;
	}
}