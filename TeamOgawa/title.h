#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

};
#endif // !_TITLE_H_