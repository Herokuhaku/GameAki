#include <DxLib.h>	// �����ō�������́�"" ;  

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){
    ChangeWindowMode(TRUE);// Window���[�h�ŋN��
    SetMainWindowText("MyGame");//�E�B���h�E�^�C�g����ύX
    SetGraphMode(640, 480, 16);// ��ʉ𑜓x�ƐF���̐ݒ�

    if (DxLib_Init() == -1) {
        // �G���[�������̏���
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClsDrawScreen();
        
        ScreenFlip();
    }

    DxLib_End();// �c�w���C�u�����I��
    return 1;
}