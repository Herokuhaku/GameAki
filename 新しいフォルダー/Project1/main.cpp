#include <DxLib.h>	// �����ō�������́�"" ;  

struct Vector2 {
    float x, y;
};

using Position2 = Vector2;

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

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){
    ChangeWindowMode(TRUE);// Window���[�h�ŋN��
    SetMainWindowText("MyGame");//�E�B���h�E�^�C�g����ύX
    SetGraphMode(640, 480, 16);// ��ʉ𑜓x�ƐF���̐ݒ�

    if (DxLib_Init() == -1) {
        // �G���[�������̏���
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    Rect rcA = {100,100,50,50};
    char keystate[256];

    constexpr float speed = 4.0f;
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClsDrawScreen();
        GetHitKeyStateAll(keystate);

        if (keystate[KEY_INPUT_LEFT])
        {
            rcA.center.x -= speed;
        }
        if (keystate[KEY_INPUT_RIGHT])
        {
            rcA.center.x += speed;
        }
        if (keystate[KEY_INPUT_UP])
        {
            rcA.center.y -= speed;
        }
        if (keystate[KEY_INPUT_DOWN])
        {
            rcA.center.y += speed;
        }
        DrawBox(rcA.Left(),rcA.Top(),rcA.Right(),rcA.Bottom(),0xffffff,true);
        ScreenFlip();
    }

    DxLib_End();// �c�w���C�u�����I��
    return 1;
}