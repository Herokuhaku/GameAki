#include <DxLib.h>	// �����ō�������́�"" ;  
#include <array>    // std::�̔z��
#include <cassert>
#include "_Debug.h"
#include "Singleton.h"
#include "Geometry.h"

using KeyBoardData = std::array<char, 256>;

//struct Rect{
//    Position2 center;
//    float w;    // weight /2
//    float h;    // height / w
//
//    float Left()const {
//        return center.x - w;
//    }
//    float Top()const {
//        return center.y - h;
//    }
//    float Right()const {
//        return center.x + w;
//    }
//    float Bottom()const{
//        return center.y + h;
//    }
//    float Width()const {
//        return w * 2;
//    }
//    float Height()const{
//        return h * 2;
//    }
//};

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

Position2 GetMousePosition2() {
    int mx, my;
    GetMousePoint(&mx,&my);
    return { static_cast<float>(mx),static_cast<float>(my) };
}

// �x���@�����W�A���ɕϊ�
float DegreeToRadian(float deg) {
    return deg * DX_PI / 180.0f;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){
    ChangeWindowMode(TRUE);// Window���[�h�ŋN��
    SetMainWindowText(TEXT("1916213_�����O�N"));//�E�B���h�E�^�C�g����ύX
    SetGraphMode(640, 480, 16);// ��ʉ𑜓x�ƐF���̐ݒ�

    if (DxLib_Init() == -1) {
        // �G���[�������̏���
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    int image_[6] = {};
    Rect rcA = {100,100,50,50};
    KeyBoardData keystate;
    constexpr size_t picture_num = 5;
    for (int i = 0; i < picture_num; i++) {
        wchar_t path[80];
        //wsprintf(path,L"Asset/Adventurer-1.5/Individual Sprites/adventurer-run-%02d.png", i);
        wsprintf(path, L"Asset/Adventurer-1.5/Individual Sprites/adventurer-attack1-%02d.png", i);
        image_[i] = LoadGraph(path);
        assert(image_[i] != -1);
    }
    int groundH = LoadGraph(L"Asset/ground.png");
    int bgAssetH = LoadGraph(L"Asset/Assets.png");
    int arrowH = LoadGraph(L"Asset/arrow.png");
    unsigned int frameNo = 0;
    constexpr size_t frames_per_pict = 5;
    int lastMouseInput = 0;
    bool isReverse = false; 
    int frame_for_angle = 0;
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        ClsDrawScreen();

        GetHitKeyStateAll(keystate.data());
        
        auto currentMouseInput = GetMouseInput();
        if ((currentMouseInput & MOUSE_INPUT_LEFT) &&
            !(lastMouseInput & MOUSE_INPUT_LEFT)) {
            isReverse = !isReverse;
        }
        lastMouseInput = currentMouseInput;

        MoveByInput(rcA.center,keystate);

        DrawBox(rcA.Left(),rcA.Top(),rcA.Right(),rcA.Bottom(),0xffffff,true);
       
        // ���݂̃}�E�X���W���擾
        auto mpos = GetMousePosition2();
        Vector2 dir = mpos - rcA.center;
        // �(0��)���E�x�N�g���ŁA�}�E�X�̌������p�x�ŕԂ�
        float angle = atan2(dir.y, dir.x);

        auto imgIdx = frameNo / frames_per_pict;
        int centerx = 16;
        if (isReverse) {
            int w, h;
            GetGraphSize(image_[imgIdx],&w,&h);
            centerx = w - centerx;
        }

        
        // �n�ʂ̕`��
        float sin_amp = 50.0f;
        constexpr int block_size = 32;
        float base_y = 240;
        auto count = 720 / block_size;
        float x = 10;
        float y = sin_amp * sin(DegreeToRadian(frame_for_angle)) + base_y;
        Position2 currentpos(x,y);
        Vector2 lastdelta90vec = Vector2{0.0f,0.0f};
        Position2 lastDeltaVector2[2] = { {0.0f,0.0f},{0.0f,0.0f} };
        Position2 lastpos = Vector2::ZERO;
        for (int i = 1; i <= count; ++i) {
            // ����x����L�΂���̍��Wx
            float nextx = i * block_size;
            // ��]��
            float ang = DegreeToRadian(nextx * 0.5 + frame_for_angle);
            // ����y����L�΂���̍��Wy
            float nexty = sin(ang) * sin_amp;
            // x�̃u���b�N�T�C�Y�ɑ΂��āAy�̃x�N�g���̑傫��(���K��)
            auto deltavec = Vector2(block_size,nexty).Normalized() * block_size;
            // �n�ʂ̍�������x�N�g�����𑫂�
            auto nextpos = currentpos + deltavec;



            auto middlevecR = deltavec.Rotated90();
         if (!(lastDeltaVector2[0] == Vector2::ZERO)) {
                middlevecR = (middlevecR + lastDeltaVector2[0]).Normalized() * block_size;
            }

         auto middlevecL = lastDeltaVector2[0];
         if (!(lastDeltaVector2[1] == Vector2::ZERO)) {
             middlevecL = (middlevecL + lastDeltaVector2[1]).Normalized() * block_size;
         }

            lastDeltaVector2[1] = lastDeltaVector2[0];
            lastDeltaVector2[0] = deltavec.Rotated90();

        auto middleposL = currentpos + middlevecL*2;
        auto middleposR = nextpos + middlevecR*2;

        
        if (lastpos != Vector2::ZERO) {
            //auto rightpos = nextpos + middlevecR;
            //auto leftpos = lastpos + middlevecL;
            //DrawRectModiGraph(lastpos.x, lastpos.y,
            //    currentpos.x, currentpos.y,
            //    rightpos.x, rightpos.y,
            //    leftpos.x, leftpos.y,
            //    i*block_size, 0,block_size,64, arrowH, true);
            auto rightpos = nextpos + middlevecR;
            auto leftpos = lastpos + middlevecL;
            DrawRectModiGraph(lastpos.x, lastpos.y,
                currentpos.x, currentpos.y,
                rightpos.x, rightpos.y,
                leftpos.x, leftpos.y,
                48, 0, 16, 16, bgAssetH, true);
        }
        //DrawLineAA(lastpos.x, lastpos.y,
        //    currentpos.x, currentpos.y, 0xffffff, 3.0f);

        //DrawLineAA(//�E��
        //    currentpos.x, currentpos.y, //�n�_
        //    rightpos.x, rightpos.y, //�I�_
        //    0xffffff, 2.0f);
        //DrawLineAA(//����
        //    currentpos.x, currentpos.y, //�n�_
        //    leftpos.x, leftpos.y, //�I�_
        //    0x8888ff, 2.0f);
        
        //x = nextx;
            //y = nexty;
        lastpos = currentpos;
        currentpos = nextpos;
        }


        DrawRotaGraph2(rcA.center.x, rcA.center.y,centerx,35, 4.0f,0.0f, image_[frameNo / frames_per_pict], true,isReverse);

        //DrawRotaGraph(rcA.center.x,rcA.center.y,3.0f,angle,image_[frameNo/frames_per_pict],true);
        DrawCircleAA(rcA.center.x, rcA.center.y, 5.0f, 16, 0x00ff00);
        //Debug::OutLine(16);
        //Debug::OutLine(static_cast<float>(16.555));
        //Debug::OutLine("Debug Out");
        //Debug::OutLine(L"Debug WOut");
        Singleton& single = Singleton::GetInstance();
        single.OutputLife();

        ScreenFlip();
        frameNo = (frameNo + 1) % (frames_per_pict*picture_num);
        frame_for_angle = (frame_for_angle + 1) % 720;
    }

    DxLib::DxLib_End();// �c�w���C�u�����I��
    return 1;
}