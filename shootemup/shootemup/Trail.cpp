#include "Trail.h"
#include "HomingShot.h"
#include <DxLib.h>

constexpr size_t history_limit = 48.0f;

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
	float div = 1.0f/static_cast<float>(history_.size());
	float u = 0.0f;
	for (const auto& pos : history_) {
		//DrawLineAA(lastpos.x, lastpos.y, pos.x, pos.y, 0xffffff, thickness);
		auto v = pos - lastpos;
		v.Normalize();
		v = Vector2(-v.y, v.x);
		// v*16 
		auto p1 = lastpos + (v * 16);
		auto p2 = pos + (v * 16);
		auto p3 = pos - (v * 16);
		auto p4 = lastpos - (v * 16);

		DrawRectModiGraph(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y,u*256.0,div,div*256,64,handle_,true);
		thickness *= 0.95;
		lastpos = pos;
	}
}

void Trail::Clear(void)
{
	history_.clear();
}

void Trail::SetHandle(int handle)
{
	handle_ = handle;
}
