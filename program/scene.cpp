//=============================================================================
//
// �`��ΏۃI�u�W�F�N�g�̏��� [scene.cpp]
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
// �}�N����`
//*****************************************************************************
#define	ENABLE_DELETE_FLAG		// ���S�t���O
//#undef	ENABLE_DELETE_FLAG

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
// ���X�g�p
CScene *CScene::m_apTop[NUM_PRIORITY] = {};
CScene *CScene::m_apCur[NUM_PRIORITY] = {};


//=============================================================================
// ���X�g������
//=============================================================================
void CScene::InitList(void)
{
}

//=============================================================================
// ���X�g�J��
//=============================================================================
void CScene::UninitList(void)
{
}

//=============================================================================
// ���X�g�擪�擾
//=============================================================================
CScene *CScene::GetListTop(int nPriority)
{
	return m_apTop[nPriority];
}

//=============================================================================
// ���X�g���I�u�W�F�X�V
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			// �I�u�W�F�N�g�̍X�V����
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
// ���X�g���I�u�W�F�`��
//=============================================================================
void CScene::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̐ݒ�
	pCamera->SetCamera();

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			// �I�u�W�F�N�g�̕`�揈��
			pScene->Draw();

			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g��j��
//=============================================================================
void CScene::Release(void)
{
#ifdef ENABLE_DELETE_FLAG
	m_bDelete = true;
#else
	// ���X�g����폜
	UnlinkList();

	delete this;
#endif
}

//=============================================================================
// �I�u�W�F�N�g�S�̂�j��
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_apTop[nCntPri];

		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;

			// �I�u�W�F�N�g�̏I������
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
// CScene�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objType)
{
	// ���X�g�ɓo�^
	LinkList(nPriority);

	m_objType = objType;
	m_bDelete = false;
}

//=============================================================================
// CScene�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// ���X�g�ɓo�^
//=============================================================================
void CScene::LinkList(int nPriority)
{
	// �v���C�I���e�B��ݒ�
	m_nPriority = nPriority;

	if (!m_apTop[nPriority])
	{// ���X�g�̐擪(pTop)�����݂��Ȃ��ꍇ
		m_apTop[nPriority] = this;
	}
	if (!m_apCur[nPriority])
	{// ���݂̃I�u�W�F�N�g(pCur)�����݂��Ȃ��ꍇ
		m_apCur[nPriority] = this;
	}

	m_apCur[nPriority]->m_pNext = this;		// ���݂̃I�u�W�F�N�g(pCur)�̎��̃I�u�W�F�N�g������(this)�ɂ���
	if (m_apCur[nPriority] == this)
	{// ���݂̃I�u�W�F�N�g(pCur)������(this)�̏ꍇ
		m_pPrev = NULL;						// ����(this)�̑O�̃I�u�W�F��NULL����
	}
	else
	{
		m_pPrev = m_apCur[nPriority];		// ����(this)�̑O�̃I�u�W�F�N�g�����݂̃I�u�W�F�N�g(pCur)�ɂ���
	}
	m_apCur[nPriority] = this;				// ���݂̃I�u�W�F�N�g(pCur)������(this)�ɂ���
	m_pNext = NULL;							// ����(this)�̎��̃I�u�W�F��NULL�ɂ���
}

//=============================================================================
// ���X�g����폜
//=============================================================================
void CScene::UnlinkList(void)
{
	CScene *pScene, *pSceneNext, *pScenePrev;

	// ���X�g�̐擪(pTop)���猻�݈ʒu(pCur)�Ɍ������ĒH���Ă���
	pScene = m_apTop[m_nPriority];
	while (pScene)
	{
		pSceneNext = pScene->m_pNext;

		if (pScene == this)
		{// �Ώۂ̃I�u�W�F�N�g������(this)�̏ꍇ
			if (pScene->m_pPrev)
			{// �Ώۂ̃I�u�W�F�N�g�̑O�ɃI�u�W�F�N�g�����݂���ꍇ
			 // ����(this)�̑O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g������(this)�̎��̃I�u�W�F�N�g�ɂ���
				pScene->m_pPrev->m_pNext = pScene->m_pNext;
			}
			if (pScene->m_pNext)
			{// �Ώۂ̃I�u�W�F�N�g�̎��ɃI�u�W�F�N�g�����݂���ꍇ
			 // ����(this)�̎��̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g������(this)�̑O�̃I�u�W�F�N�g�ɂ���
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;
			}

			if (pScene == m_apTop[m_nPriority])
			{// �Ώۂ̃I�u�W�F�N�g�����X�g�̐擪�̏ꍇ
				m_apTop[m_nPriority] = pSceneNext;
			}
		}

		pScene = pSceneNext;
	}

	// ���X�g�̌��݈ʒu(pCur)����擪(pTop)�Ɍ������ĒH���Ă���
	pScene = m_apCur[m_nPriority];
	while (pScene)
	{
		pScenePrev = pScene->m_pPrev;

		if (pScene == this)
		{// �Ώۂ̃I�u�W�F�N�g������(this)�̏ꍇ
			if (pScene->m_pPrev)
			{// �Ώۂ̃I�u�W�F�N�g�̑O�ɃI�u�W�F�N�g�����݂���ꍇ
			 // ����(this)�̑O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g������(this)�̎��̃I�u�W�F�N�g�ɂ���
				pScene->m_pPrev->m_pNext = pScene->m_pNext;
			}
			if (pScene->m_pNext)
			{// �Ώۂ̃I�u�W�F�N�g�̎��ɃI�u�W�F�N�g�����݂���ꍇ
			 // ����(this)�̎��̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g������(this)�̑O�̃I�u�W�F�N�g�̂���
				pScene->m_pNext->m_pPrev = pScene->m_pPrev;
			}

			if (pScene == m_apCur[m_nPriority])
			{// �Ώۂ̃I�u�W�F�N�g�����݂̃I�u�W�F�N�g(pCur)�̏ꍇ
				m_apCur[m_nPriority] = pScenePrev;
			}
		}

		pScene = pScenePrev;
	}
}