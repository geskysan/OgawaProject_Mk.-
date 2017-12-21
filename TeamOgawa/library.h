#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "main.h"

float SetAngle(float x, float y);	//‘ÎŠpü‚ÌŒX‚«
float SetLength(float x, float y);//‘ÎŠpü‚Ì’·‚³
bool  CollisionAABB(D3DXVECTOR3 BBMin0, D3DXVECTOR3 BBMax0, D3DXVECTOR3 BBMin1, D3DXVECTOR3 BBMax1);
bool  CollisionAABB2D(D3DXVECTOR3 BBMin0, D3DXVECTOR3 BBMax0, D3DXVECTOR3 BBMin1, D3DXVECTOR3 BBMax1);

#endif // !_LIBRARY_H_