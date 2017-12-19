//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************
// サウンドクラス
//*********************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_NONE = 0,			// タイトル
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	void SetVolume(SOUND_LABEL label, float fValue);

private:
	// パラメータ構造体
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウンタ
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];					// パラメータ
};

#endif
