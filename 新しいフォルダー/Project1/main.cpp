#include <DxLib.h>	// �����ō�������́�"" ;  
#include <array>    // std::�̔z��
#include <cassert>
#include "_Debug.h"

struct Vector2 {
    float x, y;
};

using Position2 = Vector2;
using KeyBoardData = std::array<char, 256>;
struct Rect{
    Position2 center;
    float w;    // weight /2
    float h;    // height / w

    float Left()const {
        return center.x - w;
    }
    float Top()const {
        return center.y - h;
    }
    float Right()const {
        return center.x + w;
    }
    float Bottom()const{
        return center.y + h;
    }
    float Width()const {
        return w * 2;
    }
    float Height()const{
        return h * 2;
    }
};

void MoveByInput(Position2 & pos ,const KeyBoardData& keystate)
{
    constexpr float speed = 4.0f;
    if (keystate[KEY_INPUT_LEFT])
    {
        pos.x -= speed;
    }
    if (keystate[KEY_INPUT_RIGHT])
    {
        pos.x += speed;
    }
    if (keystate[KEY_INPUT_UP])
    {
        pos.y -= speed;
    }
    if (keystate[KEY_INPUT_DOWN])
    {
        pos.y += speed;
    }
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){
    ChangeWindowMode(TRUE);// Window���[�h�ŋN��
    SetMainWindowText(TEXT("MyGame"));//�E�B���h�E�^�C�g����ύX
    SetGraphMode(640, 480, 16);// ��ʉ𑜓x�ƐF���̐ݒ�

    if (DxLib_Init() == -1) {
        // �G���[�������̏���
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    Rect rcA = {100,100,50,50};
    KeyBoardData keystate;

    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClsDrawScreen();

        GetHitKeyStateAll(keystate.data());
        
        MoveByInput(rcA.center,keystate);

        DrawBox(rcA.Left(),rcA.Top(),rcA.Right(),rcA.Bottom(),0xffffff,true);
       
        Debug::OutLine(16);
        Debug::OutLine(static_cast<float>(16.555));
        Debug::OutLine("Debug Out");
        Debug::OutLine(L"Debug WOut");
        
        ScreenFlip();
    }

    DxLib_End();// �c�w���C�u�����I��
    return 1;
}