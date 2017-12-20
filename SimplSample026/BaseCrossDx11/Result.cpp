#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	void ClearResult::OnCreate() {
		//���b�Z�[�W�X�v���C�g
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"CLEAR_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
	}
	void ClearResult::OnUpdateStage() {
		//�X�v���C�g�̍X�V
		m_MessageSprite->OnUpdate();
		//�������g�̍X�V
		this->OnUpdate();
	}
	void ClearResult::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//B�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
			}
		}
	}

	void ClearResult::OnDrawStage() {
		//�`��f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//�f�t�H���g�`��̊J�n
		Dev->StartDefaultDraw();
		//�X�v���C�g�`��
		m_MessageSprite->OnDraw();
		//�������g�̕`��
		this->OnDraw();
		//�f�t�H���g�`��̏I��
		Dev->EndDefaultDraw();
	}


	void ClearResult::OnDraw() {
		//�������Ȃ�
	}

	//--------------------------------------------------------------------------------------
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	void Gameover::OnCreate() {
		//BGM�̍Đ�
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"GAMEOVER_BGM");
		m_AudioObjectPtr->Start(L"GAMEOVER_BGM", 0, 1.0f);
		//���b�Z�[�W�X�v���C�g
		m_BG = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"GAMEOVER_BG_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);

		m_Text = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"GAMEOVER_TEXT_TX",
			Vec2(1403/1.25f, 196/1.25f),
			0.0f,
			Vec2(0, 250),
			1, 1);

	}
	void Gameover::OnUpdateStage() {
		//�X�v���C�g�̍X�V
		m_BG->OnUpdate();
		m_Text->OnUpdate();
		//�������g�̍X�V
		this->OnUpdate();
	}
	void Gameover::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//B�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_AudioObjectPtr->Stop(L"GAMEOVER_BGM");
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
			}
		}
	}

	void Gameover::OnDrawStage() {
		//�`��f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//�f�t�H���g�`��̊J�n
		Dev->StartDefaultDraw();
		//�X�v���C�g�`��
		m_BG->OnDraw();
		m_Text->OnDraw();
		//�������g�̕`��
		this->OnDraw();
		//�f�t�H���g�`��̏I��
		Dev->EndDefaultDraw();
	}


	void Gameover::OnDraw() {
		//�������Ȃ�
	}

}