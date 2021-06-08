#include <DxLib.h>	// 自分で作ったもの→"" ;  
#include <array>    // std::の配列
#include <cassert>
#include "_Debug.h"
#include "Singleton.h"

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
    ChangeWindowMode(TRUE);// Windowモードで起動
    SetMainWindowText(TEXT("1916213_佐藤弘哲"));//ウィンドウタイトルを変更
    SetGraphMode(640, 480, 16);// 画面解像度と色数の設定

    if (DxLib_Init() == -1) {
        // エラー発生時の処理
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    int image_[6] = {};
    Rect rcA = {100,100,50,50};
    KeyBoardData keystate;
    for (int i = 0; i < 6; i++) {
        wchar_t path[80];
        wsprintf(path,L"Asset/Adventurer-1.5/Individual Sprites/adventurer-run-%02d.png", i);
        image_[i] = LoadGraph(path);
        assert(image_[i] != -1);
    }

    unsigned int frameNo = 0;
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClsDrawScreen();

        GetHitKeyStateAll(keystate.data());
        
        MoveByInput(rcA.center,keystate);

        DrawBox(rcA.Left(),rcA.Top(),rcA.Right(),rcA.Bottom(),0xffffff,true);
       

        DrawRotaGraph(rcA.center.x,rcA.center.y,3.0f,0.0f,image_[frameNo/10],true);
        //Debug::OutLine(16);
        //Debug::OutLine(static_cast<float>(16.555));
        //Debug::OutLine("Debug Out");
        //Debug::OutLine(L"Debug WOut");
        Singleton& single = Singleton::GetInstance();
        single.OutputLife();


        ScreenFlip();
        frameNo = (frameNo + 1) % 60;
    }

    DxLib_End();// ＤＸライブラリ終了
    return 1;
}