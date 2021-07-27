#include "Trail.h"
#include "HomingShot.h"
#include <DxLib.h>

constexpr size_t history_limit = 32.0f;

Trail::Trail(HomingShot& owner):owner_(owner)
{
}

void Trail::Update(void)
{
	history_.push_front(owner_.pos);
	if (history_.size() > history_limit) {
		history_.pop_back();
	}
}

void Trail::Draw(void)
{
	auto lastpos = owner_.pos;
	float thickness = 20.0f;
	for (const auto& pos : history_) {
		DrawLineAA(lastpos.x, lastpos.y, pos.x, pos.y, 0xffffff, thickness);
		thickness *= 0.9;
		lastpos = pos;
	}
}
