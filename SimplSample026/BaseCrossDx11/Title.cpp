#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	void Title::OnCreate() {
		//BGMの再生
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"TITLE_BGM");
		m_AudioObjectPtr->Start(L"TITLE_BGM", XAUDIO2_LOOP_INFINITE, 1.5f);
		//メッセージスプライト
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
		//スプライトの更新
		m_MessageSprite->OnUpdate();
		m_PushSprite->OnUpdate();
		m_FadeSprite->OnUpdate();
		//自分自身の更新
		this->OnUpdate();
	}
	void Title::OnUpdate() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (!FadeFlag) {
				//Bボタン
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
		//描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//デフォルト描画の開始
		Dev->StartDefaultDraw();
		//スプライト描画
		m_MessageSprite->OnDraw();
		m_PushSprite->OnDraw();
		m_FadeSprite->OnDraw();
		//自分自身の描画
		this->OnDraw();
		//デフォルト描画の終了
		Dev->EndDefaultDraw();
	}


	void Title::OnDraw() {
		//何もしない
	}

}