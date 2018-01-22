#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	void ClearResult::OnCreate() {
		m_Time_Sec = App::GetApp()->GetScene<Scene>()->GetCTime_Sec();
		m_Time_Min = App::GetApp()->GetScene<Scene>()->GetCTime_Min();
		m_EnemyBreak = App::GetApp()->GetScene<Scene>()->GetEnemyBreak();
		//BGM�̍Đ�
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"GAMEOVER_BGM");
		m_AudioObjectPtr->Start(L"GAMEOVER_BGM", 0, 0.7f);
		//���b�Z�[�W�X�v���C�g
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"BG_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
		AddGameObject<DefSp>(
			L"KURIA_TX",
			Vec2(1000.0f, 100.0f),
			0.0f,
			Vec2(0, 250),
			1, 1);
		AddGameObject<StageSprite>(
			L"KEIKAZIKAN_TX",
			Vec2(80*4.4f, 80),
			0.0f,
			Vec2(-300, 100),
			1, 1
			);
		TimeNum_1 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(80, 80),
			0.0f,
			Vec2(440, 100),
			1.0f,
			1, 1
			);
		TimeNum_2 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(80, 80),
			0.0f,
			Vec2(380, 100),
			10.0f,
			1, 1
			);
		AddGameObject<StageSprite>(
			L"CORRON_TX",
			Vec2(80/3, 80),
			0.0f,
			Vec2(345, 100),
			1, 1
			);
		TimeNum_3 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(80, 80),
			0.0f,
			Vec2(310, 100),
			1.0f,
			1, 1
			);
		TimeNum_4 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(80, 80),
			0.0f,
			Vec2(250, 100),
			10.0f,
			1, 1
			);

		EnemyNum = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(80, 80),
			0.0f,
			Vec2(440, 10),
			1.0f,
			1, 1
			);

		AddGameObject<StageSprite>(
			L"RABBIT_BULLET_TX",
			Vec2(200, 200),
			0.0f,
			Vec2(200, -130),
			1, 1
			);

		AddGameObject<DefSp>(
			L"GAMEOVER_SIDE_TX",
			Vec2(1280.0f, 100.0f),
			0.0f,
			Vec2(-5, -300.0f),
			1, 1
			);
		AddGameObject<DefSp>(
			L"GAMEOVER_N1_TX",
			Vec2(410.0f, 100.0f),
			0.0f,
			Vec2(-405, -300.0f),
			1, 1
			);
		AddGameObject<DefSp>(
			L"GAMEOVER_N2_TX",
			Vec2(410.0f, 100.0f),
			0.0f,
			Vec2(0, -300.0f),
			1, 1
			);
		AddGameObject<DefSp>(
			L"GAMEOVER_N3_TX",
			Vec2(410.0f, 100.0f),
			0.0f,
			Vec2(405, -300.0f),
			1, 1
			);
		L1 = AddGameObject<DefSp>(
			L"GAMEOVER_L1_TX",
			Vec2(410.0f, 100.0f),
			0.0f,
			Vec2(-405, -300.0f),
			1, 1
			);
		L2 = AddGameObject<DefSp>(
			L"GAMEOVER_L2_TX",
			Vec2(410.0f, 100.0f),
			0.0f,
			Vec2(0, -300.0f),
			1, 1
			);
		L3 = AddGameObject<DefSp>(
			L"GAMEOVER_L3_TX",
			Vec2(410.0f, 100.0f),
			0.0f,
			Vec2(405, -300.0f),
			1, 1
			);

		m_FadeSprite = ObjectFactory::Create<Fade>(
			GetThis<Stage>(),
			L"FADE_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
	}
	void ClearResult::OnUpdateStage() {
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
	void ClearResult::OnUpdate() {
		TimeNum_1->SetNum(m_Time_Sec);
		TimeNum_2->SetNum(m_Time_Sec);
		TimeNum_3->SetNum(m_Time_Min);
		TimeNum_4->SetNum(m_Time_Min);
		EnemyNum->SetNum(m_EnemyBreak);
		switch (Selecter) {
		case 0:
			L1->ScaleControl(1.0f);
			L2->ScaleControl(0.0f);
			L3->ScaleControl(0.0f);
			break;
		case 1:
			L1->ScaleControl(0.0f);
			L2->ScaleControl(1.0f);
			L3->ScaleControl(0.0f);
			break;
		case 2:
			L1->ScaleControl(0.0f);
			L2->ScaleControl(0.0f);
			L3->ScaleControl(1.0f);
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
				else if(Selecter > 2) {
					Selecter = 0;
				}
			}
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_AudioObjectPtr->Stop(L"GAMEOVER_BGM");
				FadeFlag = true;
			}
		}
		if (FadeFlag)
		{
			m_FadeSprite->SetFadeFlag(true);
		}
		if (m_FadeSprite->GetChangeFlag())
		{
			switch (Selecter) {
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
				break;
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
		m_AudioObjectPtr->Start(L"GAMEOVER_BGM", 0, 0.7f);
		//�`��I�u�W�F�N�g�̒ǉ�
		CreateDrawObjects();
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

		 AddGameObject<DefSp>(
			L"GAMEOVER_SIDE_TX",
			Vec2(1280.0f, 100.0f),
			0.0f,
			Vec2(-5, -300.0f),
			1, 1
			);
		 AddGameObject<DefSp>(
			 L"GAMEOVER_N1_TX",
			 Vec2(410.0f, 100.0f),
			 0.0f,
			 Vec2(-405, -300.0f),
			 1, 1
			 );
		 AddGameObject<DefSp>(
			 L"GAMEOVER_N2_TX",
			 Vec2(410.0f, 100.0f),
			 0.0f,
			 Vec2(0, -300.0f),
			 1, 1
			 );
		 AddGameObject<DefSp>(
			 L"GAMEOVER_N3_TX",
			 Vec2(410.0f, 100.0f),
			 0.0f,
			 Vec2(405, -300.0f),
			 1, 1
			 );
		 L1=AddGameObject<DefSp>(
			 L"GAMEOVER_L1_TX",
			 Vec2(410.0f, 100.0f),
			 0.0f,
			 Vec2(-405, -300.0f),
			 1, 1
			 );
		 L2 = AddGameObject<DefSp>(
			 L"GAMEOVER_L2_TX",
			 Vec2(410.0f, 100.0f),
			 0.0f,
			 Vec2(0, -300.0f),
			 1, 1
			 );
		 L3 = AddGameObject<DefSp>(
			 L"GAMEOVER_L3_TX",
			 Vec2(410.0f, 100.0f),
			 0.0f,
			 Vec2(405, -300.0f),
			 1, 1
			 );
		 wstring Path = App::GetApp()->GetDataDirWString();
		 //�t�@�C�����̐ݒ�
		 wstring Map = Path + L"\\Kaguya\\";
		 //Chaera1�̍쐬
		 AddGameObject<GameoverKaguyaSS>(Map);

		 m_FadeSprite = ObjectFactory::Create<Fade>(
			 GetThis<Stage>(),
			 L"FADE_TX",
			 Vec2(1280, 830),
			 0.0f,
			 Vec2(0, 0),
			 1, 1);

		// wstring Path = App::GetApp()->GetDataDirWString();
		 //�t�@�C�����̐ݒ�
		 //wstring GameOverMap = Path + L"\\GameOver\\";
		//AddGameObject<KaguyaSS>(GameOverMap,Vec3(0,0,1));

	}
	void Gameover::CreateDrawObjects() {
		//SimplePCTStaticRenderer�`��I�u�W�F�N�g�̍쐬
		AddGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
	}
	void Gameover::OnUpdateStage() {
		//�X�v���C�g�̍X�V
		m_BG->OnUpdate();
		m_Text->OnUpdate();
		for (auto& v : GetGameObjectVec()) {
			//�e�I�u�W�F�N�g�̍X�V
			v->OnUpdate();
		}
		for (auto& v : GetGameObjectVec()) {
			//�e�I�u�W�F�N�g�̍ŏI�X�V
			v->OnUpdate2();
		}
		m_FadeSprite->OnUpdate();
		//Kaguya->OnUpdate();
		//�������g�̍X�V
		this->OnUpdate();
	}
	void Gameover::OnUpdate() {
		switch (Selecter) {
		case 0:
			L1->ScaleControl(1.0f);
			L2->ScaleControl(0.0f);
			L3->ScaleControl(0.0f);
			break;
		case 1:
			L1->ScaleControl(0.0f);
			L2->ScaleControl(1.0f);
			L3->ScaleControl(0.0f);
			break;
		case 2:
			L1->ScaleControl(0.0f);
			L2->ScaleControl(0.0f);
			L3->ScaleControl(1.0f);
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
			}
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_AudioObjectPtr->Stop(L"GAMEOVER_BGM");
				FadeFlag = true;
			}
		}
		if (FadeFlag)
		{
			m_FadeSprite->SetFadeFlag(true);
		}
		if (m_FadeSprite->GetChangeFlag())
		{
			switch (Selecter) {
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
				break;
			}
		}
			////B�{�^��
			//if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			//	m_AudioObjectPtr->Stop(L"GAMEOVER_BGM");
			//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
			//}
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
		//Kaguya->OnDraw();
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


	void Gameover::OnDraw() {
		//�������Ȃ�
	}

}