#include "ranking.h"
#include "debugproc.h"

CRanking::CRanking()
{

}

CRanking::~CRanking()
{

}

HRESULT CRanking::Init(void)
{
	FILE *fp;
	fp = fopen("data/Ranking.txt", "r+");
	if (fp == NULL) {
		CDebugProc::Print("�e�L�X�g�˂����R�m�����[�I�I");
	}

	return S_OK;
}

void CRanking::Uninit(void)
{

}

void CRanking::Update(void)
{

}

void CRanking::Draw(void)
{

}

int CRanking::GetRanking(void) 
{

}
