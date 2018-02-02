#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	void Title::OnCreate() {
		//BGM�̍Đ�
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"TITLE_BGM");
		m_AudioObjectPtr->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 1.5f);
		//���b�Z�[�W�X�v���C�g
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"TITLE_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
		m_PushSprite = ObjectFactory::Create<MessageSprite>(
			GetThis<Stage>(),
			L"PUSH_A_TX",
			Vec2(600, 100),
			0.0f,
			Vec2(0, -260),
			1, 1);
		m_FadeSprite = ObjectFactory::Create<Fade>(
			GetThis<Stage>(),
			L"FADE_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
	}
	void Title::OnUpdateStage() {
		//�X�v���C�g�̍X�V
		m_MessageSprite->OnUpdate();
		m_PushSprite->OnUpdate();
		m_FadeSprite->OnUpdate();
		//�������g�̍X�V
		this->OnUpdate();
	}
	void Title::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (!FadeFlag) {
				//B�{�^��
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					m_AudioObjectPtr->AddAudioResource(L"PRESS_SE");
					m_AudioObjectPtr->Start(L"PRESS_SE", 0, 0.5f);
					m_AudioObjectPtr->Stop(L"TITLE_BGM");
					FadeFlag = true;
					//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
				}
			}
		}
		if (FadeFlag)
		{
			m_FadeSprite->SetFadeFlag(true);
		}
		if (m_FadeSprite->GetChangeFlag())
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
		}
	}

	void Title::OnDrawStage() {
		//�`��f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//�f�t�H���g�`��̊J�n
		Dev->StartDefaultDraw();
		//�X�v���C�g�`��
		m_MessageSprite->OnDraw();
		m_PushSprite->OnDraw();
		m_FadeSprite->OnDraw();
		//�������g�̕`��
		this->OnDraw();
		//�f�t�H���g�`��̏I��
		Dev->EndDefaultDraw();
	}


	void Title::OnDraw() {
		//�������Ȃ�
	}

}