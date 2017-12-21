#include "library.h"

float SetAngle(float x, float y)		//‘ÎŠpü‚ÌŒX‚«
{
	return atan2f(x / 2, y / 2);
}

float SetLength(float x, float y)		//‘ÎŠpü‚Ì’·‚³
{
	return sqrtf((x / 2) * (x / 2) + (y / 2)*(y / 2));
}

bool  CollisionAABB(D3DXVECTOR3 BBMin0, D3DXVECTOR3 BBMax0, D3DXVECTOR3 BBMin1, D3DXVECTOR3 BBMax1)
{
	if (BBMin0.x < BBMax1.x && BBMax0.x > BBMin1.x &&
		BBMin0.y < BBMax1.y && BBMax0.y > BBMin1.y &&
		BBMin0.z < BBMax1.z && BBMax0.z > BBMin1.z)
		{
			return true;
		}
	return false;
}

bool  CollisionAABB2D(D3DXVECTOR3 BBMin0, D3DXVECTOR3 BBMax0, D3DXVECTOR3 BBMin1, D3DXVECTOR3 BBMax1)
{
	if (BBMin0.x < BBMax1.x && BBMax0.x > BBMin1.x &&
		BBMin0.y < BBMax1.y && BBMax0.y > BBMin1.y )
	{
		return true;
	}
	return false;

}