//���͂̏���
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//------------------------------------------------
//���̓N���X
//------------------------------------------------
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInst, HWND hWnd);
	virtual void Uninit(void);
	virtual HRESULT Update(void) = 0;		// ---> �������z�֐���

protected:
	LPDIRECTINPUTDEVICE8		m_pDIDevice;		// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^
	static LPDIRECTINPUT8		m_pDInput;			// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
};

//------------------------------------------------
// �L�[�{�[�h���̓N���X
//------------------------------------------------
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	BOOL GetKeyPress(int nKey);
	BOOL GetKeyTrigger(int nKey);
	BOOL GetKeyRelease(int nKey);
	BOOL GetKeyRepeat(int nKey);
	void FlushKeyTrigger(int nKey);

private:
	BYTE			m_aKeyState[256];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE			m_aKeyStateTrigger[256];	// �g���K�[���[�N
	BYTE			m_aKeyStateRelease[256];	// �����[�X���[�N
	BYTE			m_aKeyStateRepeat[256];		// ���s�[�g���[�N
	int				m_aKeyStateRepeatCnt[256];	// ���s�[�g�J�E���^
};

//------------------------------------------------
// �}�E�X���̓N���X
//------------------------------------------------
class CInputMouse : public CInput
{
public:
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	BOOL GetLeftPress(void);
	BOOL GetLeftTrigger(void);
	BOOL GetRightPress(void);
	BOOL GetRightTrigger(void);
	BOOL GetCenterPress(void);
	BOOL GetCenterTrigger(void);
	LONG GetAxisX(void);
	LONG GetAxisY(void);
	LONG GetAxisZ(void);
	POINT *GetPosWorld(void) { return &m_posMouseWorld; }

private:
	DIMOUSESTATE2	m_mouseState;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	DIMOUSESTATE2	m_mouseStateTrigger;		// �g���K�[���[�N
	POINT			m_posMouseWorld;			// �}�E�X�̃X�N���[�����W
};

//------------------------------------------------
// �W���C�p�b�h���̓N���X
//------------------------------------------------
class CInputJoypad : public CInput
{
public:
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	// �L�[�̎��
	typedef enum
	{
		KEY_LEFT = 0,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,

		KEY_SQUARE,
		KEY_CROSS,
		KEY_TRIANGLE,
		KEY_CIRCLE,

		KEY_L1,
		KEY_R1,
		KEY_R2,
		KEY_L2,
		KEY_R3,
		KEY_L3,

		KEY_SHARE,
		KEY_OPTIONS,
		KEY_PS,
		KEY_TOUCHPAD,
		KEY_MAX
	} KEY;

	bool GetKeyPress(KEY key);
	bool GetKeyTrigger(KEY key);
	bool GetKeyRelease(KEY key);
	bool GetKeyRepeat(KEY key);
	
	D3DXVECTOR2 GetJoyStickR() { return m_JoyStickR; }
	D3DXVECTOR2 GetJoyStickL() { return m_JoyStickL; }

private:
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
	static BOOL CALLBACK EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
	void SetKeyState(void);

	D3DXVECTOR2     m_JoyStickR;
	D3DXVECTOR2     m_JoyStickL;

	DIJOYSTATE2		m_joypadState;					// �W���C�p�b�h��Ԃ��󂯎�郏�[�N
	bool			m_aKeyState[KEY_MAX];			// �v���X���[�N
	bool			m_aKeyStateTrigger[KEY_MAX];	// �g���K�[���[�N
	bool			m_aKeyStateRelease[KEY_MAX];	// �����[�X���[�N
	bool			m_aKeyStateRepeat[KEY_MAX];		// ���s�[�g���[�N
	int				m_aKeyStateRepeatCnt[KEY_MAX];	// ���s�[�g�J�E���^
};

#endif