#include <DxLib.h>	// 自分で作ったもの→"" ;  

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){
    ChangeWindowMode(TRUE);// Windowモードで起動
    SetMainWindowText("MyGame");//ウィンドウタイトルを変更
    SetGraphMode(640, 480, 16);// 画面解像度と色数の設定

    if (DxLib_Init() == -1) {
        // エラー発生時の処理
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClsDrawScreen();
        
        ScreenFlip();
    }

    DxLib_End();// ＤＸライブラリ終了
    return 1;
}