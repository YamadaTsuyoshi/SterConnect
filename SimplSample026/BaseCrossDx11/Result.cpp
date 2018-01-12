#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	void ClearResult::OnCreate() {
		//メッセージスプライト
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"BG_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
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
		//スプライトの更新
		m_MessageSprite->OnUpdate();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの更新
			v->OnUpdate();
		}
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの最終更新
			v->OnUpdate2();
		}
		m_FadeSprite->OnUpdate();
		//自分自身の更新
		this->OnUpdate();
	}
	void ClearResult::OnUpdate() {
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
		//コントローラの取得
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
		//描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//デフォルト描画の開始
		Dev->StartDefaultDraw();
		//スプライト描画
		m_MessageSprite->OnDraw();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの描画
			v->OnDraw();
		}
		m_FadeSprite->OnDraw();
		//自分自身の描画
		this->OnDraw();
		//デフォルト描画の終了
		Dev->EndDefaultDraw();
	}


	void ClearResult::OnDraw() {
		//何もしない
	}

	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	void Gameover::OnCreate() {
		//BGMの再生
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"GAMEOVER_BGM");
		m_AudioObjectPtr->Start(L"GAMEOVER_BGM", 0, 1.0f);
		//メッセージスプライト
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
			Vec2(1250.0f, 100.0f),
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

		 m_FadeSprite = ObjectFactory::Create<Fade>(
			 GetThis<Stage>(),
			 L"FADE_TX",
			 Vec2(1280, 830),
			 0.0f,
			 Vec2(0, 0),
			 1, 1);

	}
	void Gameover::OnUpdateStage() {
		//スプライトの更新
		m_BG->OnUpdate();
		m_Text->OnUpdate();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの更新
			v->OnUpdate();
		}
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの最終更新
			v->OnUpdate2();
		}
		m_FadeSprite->OnUpdate();
		//自分自身の更新
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
		//コントローラの取得
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
			////Bボタン
			//if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			//	m_AudioObjectPtr->Stop(L"GAMEOVER_BGM");
			//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
			//}
	}

	void Gameover::OnDrawStage() {
		//描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//デフォルト描画の開始
		Dev->StartDefaultDraw();
		//スプライト描画
		m_BG->OnDraw();
		m_Text->OnDraw();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの描画
			v->OnDraw();
		}
		m_FadeSprite->OnDraw();
		//自分自身の描画
		this->OnDraw();
		//デフォルト描画の終了
		Dev->EndDefaultDraw();
	}


	void Gameover::OnDraw() {
		//何もしない
	}

}