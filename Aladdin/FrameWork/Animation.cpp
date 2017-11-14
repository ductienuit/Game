﻿#include "Animation.h"
#include"debug.h"


Animation::Animation(Sprite * spriteSheet, float timeAnimate, bool loop)
{
	_spriteSheet = spriteSheet;
	_timeAnimate = timeAnimate;

	_canAnimate = true;
	_totalFrames = 0;
	_index = 0;
	_timer = 0;
	_valueFlashes = 0.5f;

	_startFrame = 0;
	_endFrame = _totalFrames - 1;

	this->setLoop(loop);
	_canFlashes = false;
	_flashColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

Animation::Animation(Sprite * spriteSheet, int totalFrames, int cols, float timeAnimate)
{
	_spriteSheet = spriteSheet;
	_timeAnimate = timeAnimate;
	_canAnimate = true;
	_totalFrames = totalFrames;
	_index = 0;
	_timer = 0;
	_valueFlashes = 0.5f;

	_startFrame = 0;
	_endFrame = _totalFrames - 1;

	int frameW = spriteSheet->getTextureWidth() / cols;
	int frameH = spriteSheet->getTextureHeight() * cols / totalFrames;

	for (int i = 0; i < totalFrames; i++)
	{
		int x = i % cols;
		int y = i / cols;

		this->addFrameRect(x * frameW, y * frameH, frameW, frameH);
	}

	_currentRect = _frameRectList[_index];

	_flashColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

Animation::~Animation()
{
	// dont release sprite
}

void Animation::NextFrame()
{
	this->setIndex(_index + 1);
}

void Animation::PrevFrame()
{
	this->setIndex(_index - 1);
}

int  Animation::getIndex()
{
	// use in Explostion::update
	return _index;
}

void Animation::setIndex(int index)
{
	if (index == _index || _totalFrames == 0)
		return;
	_index = index;

	if (_index >= _totalFrames)
		_index = _startFrame;
	_currentRect = _frameRectList[_index];

	if (!_isLoop && _index == _endFrame)
	{
		this->Stop();
	}
}

void Animation::Update(float dt)
{
	if (!_canFlashes && !_canAnimate)
		return;

	_timer += dt / 1000;
	if (_timer >= _timeAnimate)
	{
		if (_canAnimate)
			this->NextFrame();

		_timer -= _timeAnimate;				// không thể gán bằng 0. vì như vậy là làm tròn. sẽ có sai số

		if (_canFlashes)
		{
			if (_spriteSheet->getOpacity() != _valueFlashes)
			{
				_spriteSheet->setOpacity(_valueFlashes);
				_spriteSheet->setColor(D3DXCOLOR(_flashColor.r, _flashColor.g, _flashColor.b, _valueFlashes));
			}
			else
			{
				_spriteSheet->setOpacity(1.0f);
				_spriteSheet->setColor(D3DXCOLOR(_flashColor.r, _flashColor.g, _flashColor.b, 1.0f));
			}
		}
	}
}

void Animation::setTimeAnimate(float time)
{
	_timeAnimate = time;
}

float Animation::getTimeAnimate()
{
	return _timeAnimate;
}

void Animation::Start()
{
	if (_canAnimate == false)
		_canAnimate = true;
}

void Animation::Stop()
{
	if (_canAnimate == true)
		_canAnimate = false;
}

void Animation::setcanAnimate(bool can)
{
	if (_canAnimate != can)
		_canAnimate = can;
}

bool Animation::isAnimate()
{
	// 7ung => use in AirCraft::draw
	return _canAnimate;
}

bool Animation::isLastAnimation()
{
	//chưa dùng tới
	return false;
}

void Animation::addFrameRect(RECT rect)
{
	//nếu là rect đầu tiên thì set current luôn
	if (_frameRectList.empty())
	{
		_currentRect = rect;

		// trường hợp kiểm tra _bounding trước khi vẽ lần đầu tiên, nếu ko có setFrameRect thì nó sẽ lấy nguyên spriteSheet
		// sẽ làm sai kích thước của frame hiện tại
		// vậy lần đầu gán cho frame đầu. 
		// cách khác là setframeRect ở object cho sprite.

		// _spriteSheet->setFrameRect(_currentRect);
	}
	_frameRectList.push_back(rect);
	_totalFrames = _frameRectList.size();

	_endFrame = _totalFrames - 1;
}

void Animation::addFrameRect(float left, float top, int width, int height)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = left + width;
	rect.bottom = top + height;

	this->addFrameRect(rect);
}

void Animation::addFrameRect(float left, float top, float right, float bottom)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;

	this->addFrameRect(rect);
}

void Animation::addFrameRect(eID id, char * firstRectName, int numb)
{
	string name;
	name = firstRectName;
	for(int i=0;i<numb;i++)
	{
		name = firstRectName + std::to_string(i);
		this->addFrameRect(SpriteManager::getInstance()->getSourceRect(id, name));
	}
}

void Animation::addFrameRect(eID id, char* firstRectName, ...)
{
	va_list vl;
	char* name;

	va_start(vl, firstRectName);            //Lấy toàn bộ các đối số nhập vào list vl

	name = firstRectName;

	while (name != NULL)
	{
		this->addFrameRect(SpriteManager::getInstance()->getSourceRect(id, name));
		name = va_arg(vl, char*);
	}

	va_end(vl);
}

void Animation::setLoop(bool isLoop)
{
	if (isLoop != _isLoop)
		_isLoop = isLoop;
}

bool Animation::isLoop()
{
	return _isLoop;
}

void Animation::Restart(int from)
{
	setIndex(from);

	if (_canAnimate == false)
		_canAnimate = true;
}

void Animation::EnableFlashes(bool enable)
{
	if (_canFlashes == enable)
		return;

	_canFlashes = enable;
	_spriteSheet->setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void Animation::setValueFlashes(float value)
{
	if (_valueFlashes != value)
		_valueFlashes = value;
}

void Animation::AnimateFromTo(int from, int to, bool loop)
{
	if (from <= to)
	{
		_startFrame = from;
		_endFrame = to;
	}
	else
	{
		_startFrame = to;
		_endFrame = from;
	}

	this->setIndex(from);
	_isLoop = loop;
	_timer = 0.0f;

	if (_canAnimate == false)
		_canAnimate = true;
}

void Animation::setColorFlash(D3DXCOLOR color)
{
	_flashColor = color;
}

D3DXCOLOR Animation::getColorFlash()
{
	return _flashColor;
}

void Animation::Draw(LPD3DXSPRITE spriteHandle, Viewport * viewport)
{
	_spriteSheet->setFrameRect(_currentRect);
	_spriteSheet->Render(spriteHandle, viewport);
}