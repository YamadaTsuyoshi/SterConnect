#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	void StageSelect::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"STAGESELECT_BGM");
		m_AudioObjectPtr->Start(L"STAGESELECT_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
		//���b�Z�[�W�X�v���C�g
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"STAGESELECT_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
		m_FadeSprite = ObjectFactory::Create<Fade>(
			GetThis<Stage>(),
			L"FADE_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
	}
	void StageSelect::OnUpdateStage() {
		//�X�v���C�g�̍X�V
		m_MessageSprite->OnUpdate();
		m_FadeSprite->OnUpdate();
		//�������g�̍X�V
		this->OnUpdate();
	}
	void StageSelect::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//B�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_AudioObjectPtr->AddAudioResource(L"PRESS_SE");
				m_AudioObjectPtr->Start(L"PRESS_SE", 0, 0.5f);
				m_AudioObjectPtr->Stop(L"STAGESELECT_BGM");
				FadeFlag = true;
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
		if (FadeFlag)
		{
			m_FadeSprite->SetFadeFlag(true);
		}
		if (m_FadeSprite->GetChangeFlag())
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}

	void StageSelect::OnDrawStage() {
		//�`��f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//�f�t�H���g�`��̊J�n
		Dev->StartDefaultDraw();
		//�X�v���C�g�`��
		m_MessageSprite->OnDraw();
		m_FadeSprite->OnDraw();
		//�������g�̕`��
		this->OnDraw();
		//�f�t�H���g�`��̏I��
		Dev->EndDefaultDraw();
	}


	void StageSelect::OnDraw() {
		//�������Ȃ�
	}

}