#include "title.h"
#include "debugproc.h"

CTitle::CTitle()
{

}

CTitle::~CTitle()
{

}

HRESULT CTitle::Init(void)
{
	return S_OK;
}

void CTitle::Uninit(void)
{
	Release();
}

void CTitle::Update(void)
{
	CDebugProc::Print("シーン : タイトル\n");
}

void CTitle::Draw(void)
{

}