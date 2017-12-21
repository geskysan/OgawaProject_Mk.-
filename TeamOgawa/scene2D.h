//2D�I�u�W�F�N�g�̏���	[scene2D.h]
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------

//���_�t�H�[�}�b�g(���_���W[2D] / ���_�J���[ /  �e�N�X�`�����W)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_TEXTURE_MAX	(3)

//------------------------------------------------
//�\���̒�`
//------------------------------------------------
//��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float		rhw;	//���W�ϐ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`�����W
}VERTEX_2D;

//------------------------------------------------
//2D�I�u�W�F�N�g�N���X
//------------------------------------------------
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 6, CScene::OBJTYPE objType = CScene::OBJTYPE_2D);
	~CScene2D();

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot , D3DXVECTOR2 polygonSize);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 polygonSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	void SetVertexPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3);
	void SetVertexCol(D3DXCOLOR col);
	void SetVertexTex(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3);
	void LoadTexture(const char *pTextureName);
	void SetLengthPos(float fLength);
	float GetLength(void) { return m_fLength; }
	bool GetbEnable(void) { return m_bEnable; }
	void SetbEnable(bool bEnable) { m_bEnable = bEnable; }
protected:
	void SetVertexPos(void);
	void SetVertexTex(void);
	D3DXVECTOR2 m_posTex;
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;						// �ʒu�W
	D3DXVECTOR3 m_rot;						// ����
	float m_fLength;						// �Ίp���̒���
	float m_fAngle;							// �Ίp���̌X��

	bool m_bEnable;

};
#endif // !_SCENE2D_H_