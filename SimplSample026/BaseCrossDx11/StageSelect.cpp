#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	void StageSelect::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"STAGESELECT_BGM");
		m_AudioObjectPtr->Start(L"STAGESELECT_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
		//�`��I�u�W�F�N�g�̒ǉ�
		CreateDrawObjects();
		//���b�Z�[�W�X�v���C�g
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"STAGESELECT_TX",
			Vec2(1280, 800),
			0.0f,
			Vec2(0, 0),
			1, 1);
		m_kaguya = AddGameObject<DefSp>(
			L"KAGUYA_TX",
			Vec2(100.0f, 100.0f),
			0.0f,
			Vec2(-400, -300.0f),
			1, 1
			);
		wstring Path = App::GetApp()->GetDataDirWString();
		//�t�@�C�����̐ݒ�
		wstring Map = Path + L"\\StageSelect\\";
		//Chaera1�̍쐬
		AddGameObject<StageSelectSS>(Map);

		m_FadeSprite = ObjectFactory::Create<Fade>(
			GetThis<Stage>(),
			L"FADE_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);

	}

	void StageSelect::CreateDrawObjects() {
		//SimplePCTStaticRenderer�`��I�u�W�F�N�g�̍쐬
		AddGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
	}

	void StageSelect::OnUpdateStage() {
		//�X�v���C�g�̍X�V
		m_MessageSprite->OnUpdate();
		for (auto& v : GetGameObjectVec()) {
			//�e�I�u�W�F�N�g�̍X�V
			v->OnUpdate();
		}
		for (auto& v : GetGameObjectVec()) {
			//�e�I�u�W�F�N�g�̍ŏI�X�V
			v->OnUpdate2();
		}
		m_FadeSprite->OnUpdate();
		//�������g�̍X�V
		this->OnUpdate();
	}
	void StageSelect::OnUpdate() {
		FindTagGameObject<StageSelectSS>(L"StageSelectSS")->SetStageNum(Selecter);
		switch (Selecter) {
		case 0:
			m_kaguya->SetPos(Vec2(-400, -350));
			break;
		case 1:
			m_kaguya->SetPos(Vec2(0, -250));
			break;
		case 2:
			m_kaguya->SetPos(Vec2(380, 0));
			break;
		}
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (!FadeFlag) {
				if (CntlVec[0].fThumbLX < -0.5) {
					if (onectrl == false)
					{
						onectrl = true;
						Selecter += -1;
					}
				}
				else if (CntlVec[0].fThumbLX > 0.5) {
					if (onectrl == false)
					{
						onectrl = true;
						Selecter += 1;
					}
				}
				else
				{
					onectrl = false;
				}
				if (Selecter < 0) {
					Selecter = 2;
				}
				else if (Selecter > 2) {
					Selecter = 0;
				}
				//B�{�^��
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					m_AudioObjectPtr->AddAudioResource(L"PRESS_SE");
					m_AudioObjectPtr->Start(L"PRESS_SE", 0, 0.5f);
					m_AudioObjectPtr->Stop(L"STAGESELECT_BGM");
					FadeFlag = true;
					//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				}
			}
		}
		if (FadeFlag)
		{
			m_FadeSprite->SetFadeFlag(true);
		}
		if (m_FadeSprite->GetChangeFlag())
		{
			App::GetApp()->GetScene<Scene>()->SetStageNumber(Selecter+1);
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
		for (auto& v : GetGameObjectVec()) {
			//�e�I�u�W�F�N�g�̕`��
			v->OnDraw();
		}
		m_FadeSprite->OnDraw();
		//�������g�̕`��
		this->OnDraw();
		//�f�t�H���g�`��̏I��
		Dev->EndDefaultDraw();
	}


	void StageSelect::OnDraw() {
		//�������Ȃ�
	}

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	StageSelectSS::StageSelectSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir) :
		SS5ssae(StagePtr, BaseDir, L"StageSelect_Ver2.1.ssae", L"Stage1")
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//������
	void StageSelectSS::OnCreate() {
		AddTag(L"StageSelectSS");
		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		auto PtrT = GetTransform();
		PtrT->SetScale(3.23f*1.2f, 3.62f*1.2f, 3.75f);
		PtrT->SetPosition(Vec3(-2.65f, -3.15f, 1.0f));
		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(90.0f);
		//ChangeAnimation(L"Fly");
		SetLooped(false);
	}

	//�X�V
	void StageSelectSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		if (IsAnimeEnd()) {
			switch (StageNum)
			{
			case 0:
				GetTransform()->SetPosition(Vec3(-2.65f, -3.15f, 1.0f));
				ChangeAnimation(L"Stage1");
				SetFps(90.0f);
				SetLooped(false);
				break;
			case 1:
				GetTransform()->SetPosition(Vec3(3.66f, -2.05f, 1.0f));
				ChangeAnimation(L"Stage2");
				SetFps(90.0f);
				SetLooped(false);
				break;
			case 2:
				GetTransform()->SetPosition(Vec3(9.24f, 1.99f, 1.0f));
				ChangeAnimation(L"Stage3");
				SetFps(90.0f);
				SetLooped(false);
				break;
			default:
				GetTransform()->SetPosition(Vec3(-2.65f, -3.15f, 1.0f));
				ChangeAnimation(L"Stage1");
				SetFps(90.0f);
				SetLooped(false);
				break;
			}
		}
		UpdateAnimeTime(ElapsedTime);
	}

}