#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	void StageSelect::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"STAGESELECT_BGM");
		m_AudioObjectPtr->Start(L"STAGESELECT_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
		//描画オブジェクトの追加
		CreateDrawObjects();
		//メッセージスプライト
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
		//ファイル名の設定
		wstring Map = Path + L"\\StageSelect\\";
		//Chaera1の作成
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
		//SimplePCTStaticRenderer描画オブジェクトの作成
		AddGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
	}

	void StageSelect::OnUpdateStage() {
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
				//Bボタン
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


	void StageSelect::OnDraw() {
		//何もしない
	}

	//--------------------------------------------------------------------------------------
	//	ステージセレクトスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
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

	//初期化
	void StageSelectSS::OnCreate() {
		AddTag(L"StageSelectSS");
		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		auto PtrT = GetTransform();
		PtrT->SetScale(3.23f*1.2f, 3.62f*1.2f, 3.75f);
		PtrT->SetPosition(Vec3(-2.65f, -3.15f, 1.0f));
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(90.0f);
		//ChangeAnimation(L"Fly");
		SetLooped(false);
	}

	//更新
	void StageSelectSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
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