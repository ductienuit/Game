#ifndef CAMERA_H
#define CAMERA_H

#include <DirectXMath.h>
#include "../Objects/BaseObject.h"

class Camera
{
public:
	//Constructors and Destructor
	Camera(int width, int height, DirectX::XMFLOAT3 scaleFactors, int w = 320, int h = 236);
	~Camera();

	//Game Functions
	void Update();
	void Follow(BaseObject *following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform() const;
	RECT cameraRect();
private:
	float angle;
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	BaseObject *following;

	POINT roomDimension;
	POINT cameraDimension;
	RECT cameraBorder;
	float cameraPosX, cameraPosY, cameraTagetX, cameraTargetY;

	int width;
	int height;
};

#endif /* CAMERA_H */
extern RECT RectDraw;
extern float DrawWidth;
extern float DrawHeight;
extern float ViewX;
extern float ViewY;