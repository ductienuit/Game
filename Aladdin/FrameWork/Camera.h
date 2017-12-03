#ifndef CAMERA_H
#define CAMERA_H

#include <DirectXMath.h>
#include "../Objects/BaseObject.h"

class Camera
{
public:
	//Constructors and Destructor
	Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	//Game Functions
	void Update();
	void Follow(BaseObject *following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform() const;

private:
	float angle;
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	BaseObject *following;

	int width;
	int height;
};

#endif /* CAMERA_H */
