#include "Camera.h"

Camera::Camera()
{
	camera_Position = D3DXVECTOR2(0, 240);

	camera_width = 320;
	camera_height = 240;

	//right and bottom should be setCameraXXX(map - camera_width)
	bound_left = bound_top = bound_right = bound_bottom = 0;

	scroll_x = false;
	scroll_y = false;

	following = true;
}

Camera::~Camera()
{
}

void Camera::setCameraPosition(D3DXVECTOR2 position)
{
	this->camera_Position = position;
}

void Camera::setCameraPosition(float x, float y)
{
	this->camera_Position.x = x;
	this->camera_Position.y = y;
}

void Camera::setCameraPositionX(float x)
{
	this->camera_Position.x = x;
}

void Camera::setCameraPositionY(float y)
{
	this->camera_Position.y = y;
}

float Camera::getCameraWidth()
{
	return this->camera_width;
}

float Camera::getCameraHeight()
{
	return this->camera_height;
}

D3DXVECTOR2 Camera::toCameraPosistion(float WorldPositionX, float WorldPositionY)
{
	return D3DXVECTOR2(WorldPositionX - this->camera_Position.x, WorldPositionY - this->camera_Position.y);
}

float Camera::getCameraPositionX()
{
	return this->camera_Position.x;
}

float Camera::getCameraPositionY()
{
	return this->camera_Position.y;
}

D3DXVECTOR2 Camera::getCameraPosition()
{
	return this->camera_Position;
}

void Camera::setBound(float left, float top, float right, float bottom)
{
	this->bound_left = left;
	this->bound_top = top;
	this->bound_right = right;
	this->bound_bottom = bottom;
}

float Camera::getBoundleft()
{
	return this->bound_left;
}

float Camera::getBoundTop()
{
	return this->bound_top;
}

float Camera::getBoundRight()
{
	return this->bound_right;
}

float Camera::getBoundBottom()
{
	return this->bound_bottom;
}

void Camera::setScrollX(bool isscrollX)
{
	this->scroll_x = isscrollX;
}

void Camera::setScrollY(bool isscrollY)
{
	this->scroll_y = isscrollY;
}

bool Camera::isFollowing()
{
	return this->following;
}

void Camera::Update(DWORD dt)
{

	if (scroll_x)
	{
		camera_Position.x += CAMERA_DEFAULT_SCROLLING_SPEED_VX * &dt;
	}

	if (scroll_y)
	{
		camera_Position.y += CAMERA_DEFAULT_SCROLLING_SPEED_VY * &dt;
	}

	//DebugOut(L"[INFO] cam posx: %f \n", camera_Position.x);

	if (this->camera_Position.x < this->bound_left)
		this->camera_Position.x = this->bound_left;

	if (this->camera_Position.x + this->camera_width > this->bound_right)
		this->camera_Position.x = this->bound_right - this->camera_width;

	if (this->camera_Position.y < this->bound_top)
		this->camera_Position.y = this->bound_top;

	if (this->camera_Position.y + this->camera_height > this->bound_bottom)
		this->camera_Position.y = this->bound_bottom - this->camera_height;
}


