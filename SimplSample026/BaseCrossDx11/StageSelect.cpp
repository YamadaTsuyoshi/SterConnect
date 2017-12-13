#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	void StageSelect::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"STAGESELECT_BGM");
		m_AudioObjectPtr->Start(L"STAGESELECT_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
		//メッセージスプライト
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"STAGESELECT_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
	}
	void StageSelect::OnUpdateStage() {
		//スプライトの更新
		m_MessageSprite->OnUpdate();
		//自分自身の更新
		this->OnUpdate();
	}
	void StageSelect::OnUpdate() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//Bボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_AudioObjectPtr->Stop(L"STAGESELECT_BGM");
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
	}

	void StageSelect::OnDrawStage() {
		//描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//デフォルト描画の開始
		Dev->StartDefaultDraw();
		//スプライト描画
		m_MessageSprite->OnDraw();
		//自分自身の描画
		this->OnDraw();
		//デフォルト描画の終了
		Dev->EndDefaultDraw();
	}


	void StageSelect::OnDraw() {
		//何もしない
	}

}