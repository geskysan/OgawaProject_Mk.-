#include "objectmanager.h"
#include "objectblock.h"
#include "player.h"
#include "debugproc.h"
CObjectManager::CObjectManager()
{

	for (int iCntNumY = 0; iCntNumY < NUM_OBJECT_Y; iCntNumY++)
	{
		for (int iCntNumX = 0; iCntNumX < NUM_OBJECT_X; iCntNumX++)
		{
			m_apObject[iCntNumX][iCntNumY] = NULL;
		}
	}
}

CObjectManager::~CObjectManager()
{
	
}

HRESULT CObjectManager::Init(const char *FileName)
{
	FILE *fp;
	fopen_s(&fp, FileName, "r");

	if (!fp)
	{
		MessageBox(NULL, "マップデータが読み込めませんでした。", NULL, MB_OK);
		return S_FALSE;
	}

	for (int iCntNumY = 0; iCntNumY < NUM_OBJECT_Y; iCntNumY++)
	{
		for (int iCntNumX = 0; iCntNumX < NUM_OBJECT_X; iCntNumX++)
		{
			OBJECT_TYPE Objtype;
			fscanf(fp, "%d, ", &Objtype);

			if (Objtype == OBJECT_BLOCK)
			{
				m_apObject[iCntNumX][iCntNumY] = new CObjectBlock;
				m_apObject[iCntNumX][iCntNumY]->Init(D3DXVECTOR3(iCntNumX * 50, iCntNumY*-50, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50, 50, 50);
			}
		}
	}
	fclose(fp);
	return S_OK;
}

void CObjectManager::Uninit()
{
	for (int iCntNumY = 0; iCntNumY < NUM_OBJECT_Y; iCntNumY++)
	{
		for (int iCntNumX = 0; iCntNumX < NUM_OBJECT_X; iCntNumX++)
		{
			SAFE_UNINIT(m_apObject[iCntNumX][iCntNumY]);
		}
	}
	Release();
}

void CObjectManager::Update()
{

}

void CObjectManager::Draw()
{

}

void CObjectManager::Collision(CPlayer *pPlayer)
{
	int iColCount = 0;
	for (int iCntNumY = 0; iCntNumY < NUM_OBJECT_Y; iCntNumY++)
	{
		for (int iCntNumX = 0; iCntNumX < NUM_OBJECT_X; iCntNumX++)
		{
			if (m_apObject[iCntNumX][iCntNumY])
			{
				if (pPlayer->CollisionBlock(m_apObject[iCntNumX][iCntNumY]))
					iColCount++;
			}
		}
	}

	CDebugProc::Print("当たり判定をした回数は%dです。\n", iColCount);
}