#include "Camera.h"

RECT RectDraw;
float DrawWidth = 1;
float DrawHeight = 1;
float ViewX = 0;
float ViewY = 0;

Camera::Camera(int width, int height, DirectX::XMFLOAT3 scaleFactors, int w, int h)
{
	this->width = width;
	this->height = height;
	this->scaleFactors = scaleFactors;

	//Kích thước camera
	roomDimension.x = width;  //Kích thước background
	roomDimension.y = height;  //kích thước background

	ViewX = 0;
	ViewY = 0;
	cameraPosX = 0;
	cameraPosY = 0;
	cameraDimension.x = min(w, width);  //Kích thước camera
	cameraDimension.y = min(h, height); //Kích thước camera

	cameraBorder.top = 0;
	cameraBorder.left = 0;
	cameraBorder.right = width; //4771
	cameraBorder.bottom = height;  //668

	D3DXMatrixOrthoLH(&orthographicMatrix, (float)cameraDimension.x, -(float)cameraDimension.y, 0.0f, 1.0f);
	//D3DXMatrixOrthoLH(&orthographicMatrix, 800, -600, 0.0f, 1.0f);

	D3DXMatrixIdentity(&identityMatrix);

	DrawWidth = (float)BUFFER_WIDTH / cameraDimension.x;
	DrawHeight = (float)BUFFER_HEIGHT / cameraDimension.y;
}

Camera::~Camera()
{
}
void Camera::Update()
{
	int cameraX = this->width / 2, cameraY = this->height / 2;
	if (this->following)
	{
		cameraX = this->following->getPositionX();
		cameraY = -this->following->getPositionY()/10;
	}

	//Tịnh tiến hoặc phóng to thu nhỏ camera bằng ma trận
	/* Đọc begin programing directx - Chương 5*/
	this->viewMatrix = D3DXMATRIX(
				1,	 0,	 0,					0,
				0,	 1,	 0,					0,
				0,   0,	 1,					0,
				-cameraX ,- cameraY ,  0,	 1
	);


}

void Camera::Follow(BaseObject* following)
{
	this->following = following;
}

void Camera::Unfollow()
{
	this->following = nullptr;
}

bool Camera::IsFollowing() const
{
	return this->following != nullptr;
}

void Camera::SetTransform() const
{
	auto gDevice = DeviceManager::getInstance()->getDevice();
	gDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	gDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	gDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

}

RECT Camera::cameraRect()
{
	POINT center;
	center.x = (int)cameraPosX;
	center.y = (int)cameraPosY;

	int half_cam_width = cameraDimension.x / 2;
	int half_cam_height = cameraDimension.y / 2;

	RECT rect;
	rect.top = center.y - half_cam_height;
	rect.left = center.x - half_cam_width;
	rect.right = center.x + half_cam_width;
	rect.bottom = center.y + half_cam_height;

	return rect;
}

