//3D�I�u�W�F�N�g�̏���	[scene3D.h]
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------
//���_�t�H�[�}�b�g(���_���W / �@�� / ���_�J���[ / �e�N�X�`�����W)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//------------------------------------------------
//�\���̒�`
//------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

//------------------------------------------------
//3D�I�u�W�F�N�g�N���X
//------------------------------------------------
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 3, CScene::OBJTYPE objtype = CScene::OBJTYPE_3D);
	~CScene3D();

	static CScene3D *Create(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidht, int iHeight);
	
	HRESULT Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidth, int Height);
	HRESULT Init(void) { return S_OK; }
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void LoadTexture(const char *TextureName);
	void SetType(int nType) { m_nType = nType; }

	void SetVertexPos(D3DXVECTOR3 RightUp, D3DXVECTOR3 RightDown, D3DXVECTOR3 LeftUp, D3DXVECTOR3 LeftDown);
	void SetEnable(bool bUse) { m_bEnable = bUse; }
	bool GetEnable(void) { return m_bEnable; }
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_scale;					// �傫
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �Ίp���̊p�x

	int m_nType;							// ���

	bool m_bEnable;							//�`��̐؂�ւ�
	static const char *m_apTextureName[];

};
#endif // !_SCENE3D_H_