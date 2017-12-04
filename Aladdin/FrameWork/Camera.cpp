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
	if (!this->following)
		return;
	float x = this->following->getPositionX();
	float y = this->following->getPositionY();
	if (this->following)
	{
		cameraX = this->following->getPositionX();
		cameraY = -this->following->getPositionY()/10;
	}

	//Tịnh tiến hoặc phóng to thu nhỏ camera bằng ma trận
	/* Đọc begin programing directx - Chương 5*/
	this->viewMatrix = D3DXMATRIX(
				scaleFactors.x * cos(angle),	 scaleFactors.x * sin(angle),						 0,		0,
				-scaleFactors.y * sin(angle),	 scaleFactors.y * cos(angle),						 0,		0,
				0,														   0,				scaleFactors.z,	0,
				-cameraX * scaleFactors.x * cos(angle) 
				+ cameraY * scaleFactors.y * sin(angle), -cameraX * scaleFactors.y * sin(angle)
														 - cameraY * scaleFactors.y * cos(angle),
																									  0,	 1
	);



	//float temp;
	//temp = x - cameraPosX;
	//if (abs(temp) < 2)
	//	cameraPosX = x;
	//else
	//	cameraPosX += temp*0.25f;
	//temp = y - cameraPosY;
	//if (abs(temp) < 2)
	//	cameraPosY = -y;
	//else
	//	cameraPosY += temp*0.5f;


	//float half_cam_width = (float)cameraDimension.x / 2;
	//float half_cam_height = (float)cameraDimension.y / 2;

	////Ràng buộc camera không vượt 1/2
	//cameraPosX = Clamp<float>(cameraPosX, (float)cameraBorder.left + half_cam_width, (float)cameraBorder.right - half_cam_width);
	//cameraPosY = Clamp<float>(cameraPosY, (float)cameraBorder.top + half_cam_height, (float)cameraBorder.bottom - half_cam_height);

	//viewMatrix = D3DXMATRIX(
	//	1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	-cameraPosX, -cameraPosY, 0, 1);

	//DrawRect.top = (int)(cameraPosY - half_cam_height);
	//DrawRect.left = (int)(cameraPosX - half_cam_width);
	//DrawRect.right = (int)(cameraPosX + half_cam_width);
	//DrawRect.bottom = (int)(cameraPosY + half_cam_height);
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

