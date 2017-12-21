#include "result.h"
#include "debugproc.h"

CResult::CResult()
{

}

CResult::~CResult()
{

}

HRESULT CResult::Init(void)
{
	return S_OK;
}

void CResult::Uninit(void)
{

}

void CResult::Update(void)
{
	CDebugProc::Print("シーン : リザルト\n");
}

void CResult::Draw(void)
{

}

