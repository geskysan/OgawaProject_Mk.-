#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"

class CResult : public CScene
{
public:
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};
#endif // !_RESULT_H_