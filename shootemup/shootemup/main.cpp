#include<DxLib.h>
#include<cmath>
#include <memory>
//#include"Geometry.h"
#include "HomingShot.h"
///�����蔻��֐�
///@param posA A�̍��W
///@param radiusA A�̔��a
///@param posB B�̍��W
///@param radiusB B�̔��a
bool IsHit(const Position2& posA, float radiusA, const Position2& posB,  float radiusB) {
	//�����蔻����������Ă�������
	return false;
}
using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("�e������`");
	
	//SetUseASyncLoadFlag(true);
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	double nextdeltatime = GetNowCount();
	//�w�i�p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);



	//�e�̔��a
	float bulletRadius = 5.0f;

	//���@�̔��a
	float playerRadius = 10.0f;

	//�K����256���炢����Ƃ�
	Bullet bullets[256];

	HomingShot homingShots[32] = {};
	Position2 enemypos(320,25);//�G���W
	Position2 playerpos(320, 400);//���@���W

	unsigned int frame = 0;//�t���[���Ǘ��p

	char keystate[256] = {};
	char lastKeyState[256] = {};
	bool isRightHomig = false;
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;
	constexpr float homing_shot_speed = 3.0f;
	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		//�w�i
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//�v���C���[
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640,playerpos.x+4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0,playerpos.x-4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0,playerpos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480,playerpos.y+4);
		}
		if (keystate[KEY_INPUT_Z] && !lastKeyState[KEY_INPUT_Z]) {
			DrawString(100, 100, "����", 0x0);
			int count = 0;
			for (auto& h : homingShots) {
				if (!h.isActive) {
					h.isActive = true;
					h.pos = playerpos;
					h.vel = {count%2==0 ?homing_shot_speed*2:-homing_shot_speed*2,2.0f*count };
					h.vel.Normalize();
					h.vel *= homing_shot_speed;
					isRightHomig = !isRightHomig;
					h.trail.Clear();
					if (++count > 5) {
						break;
					}
				}
			}

		}

		for (auto& hshot : homingShots) {
			if (!hshot.isActive) {
				continue;
			}
			if (frame % 2 == 0) {
				hshot.trail.Update();
			}
			hshot.pos += hshot.vel;

			hshot.trail.Draw();
			//for (int i = 1; i < 5; ++i) {

			//	auto tailPos = hshot.pos - hshot.vel*2 * static_cast<float>(i);	
			//	auto thickness = static_cast<float>(6-i);
			//	DrawLineAA(hshot.pos.x, hshot.pos.y, tailPos.x, tailPos.y, 0xff0000,thickness * 4.0f);
			//}
			//hshot.vel = (hshot.vel + (enemypos - hshot.pos).Normalized()).Normalized() * homing_shot_speed;
			auto nVelocity = hshot.vel.Normalized();
			auto nToEnemy = (enemypos - hshot.pos).Normalized();
			auto dot = Dot(nVelocity,nToEnemy);
			auto angle = acos(dot);
			angle = std::fminf(angle,DX_PI_F / 48.0f);
			float sign = Cross(nVelocity,nToEnemy) > 0.0f ?1.0f : -1.0f;
			angle = atan2(hshot.vel.y, hshot.vel.x) + sign * angle;
			hshot.vel = hshot.vel.Normalized() + Vector2(cos(angle),sin(angle))*homing_shot_speed;

			DrawCircleAA(hshot.pos.x,hshot.pos.y,5,16,0xff4444,true);

			//�e���E��
			// �G�ɓ�������
			if ((enemypos - hshot.pos).SQMagnitude() < 900.0f) {
				hshot.isActive = false;
			}
			// �͈͊O�ɏo��
			if (hshot.pos.x + 16 < 0 || hshot.pos.x - 16 > 640 ||
				hshot.pos.y + 24 < 0 || hshot.pos.y - 24 > 480) {
				hshot.isActive = false;
			}
		}

		DrawCircleAA(enemypos.x,enemypos.y, 50.0f, 16, 0x00ff00, false, 3.0f);

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//���@�̖{��(�����蔻��)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		//�e����
		if (frame % 12 == 0) {
			for (auto& b : bullets) {
				if (!b.isActive) {
					//b.pos = enemypos;
					//b.vel = Vector2(0, 5);
					//b.isActive = true;
					break;
				}
			}
		}

		//�e�̍X�V����ѕ\��
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//�e�̌��ݍ��W�ɒe�̌��ݑ��x�����Z���Ă�������
			
			float angle = 0.0f;
			//�e�̊p�x��atan2�Ōv�Z���Ă��������Bangle�ɒl������񂾂�I�D
			
			DrawRotaGraph(b.pos.x, b.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//�e�̖{��(�����蔻��)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//�e���E��
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//������I
			//����IsHit�͎����������Ă܂���B�����ŏ����Ă��������B
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//�������������������Ă��������B
			}
		}

		//�G�̕\��
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//�G�̖{��(�����蔻��)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		auto dcall = GetDrawCallCount();
		int fps = GetFPS();

		DrawFormatString(10,70,0x0,"DrawCall = %d",dcall);
		DrawFormatString(10, 90, 0x0, "fps = %d",fps);

		++frame;
		ScreenFlip();
		copy(begin(keystate),end(keystate),begin(lastKeyState));
		nextdeltatime += 16.66;
		// 1�t���[���̌��E�l 16.66ms (1�b�Ԃ�60�t���[���̏ꍇ) �������������ɓ��B���Ă����炻�̕��҂�
		if (nextdeltatime > GetNowCount()) {
			WaitTimer(static_cast<int>(nextdeltatime) - GetNowCount());
		}
	}

	DxLib_End();

	return 0;
}