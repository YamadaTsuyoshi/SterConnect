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
		/*m_kaguya = AddGameObject<DefSp>(
			L"KAGUYA_TX",
			Vec2(100.0f, 100.0f),
			0.0f,
			Vec2(-400, -300.0f),
			1, 1
			);*/
		wstring Path = App::GetApp()->GetDataDirWString();
		//ファイル名の設定
		wstring Map = Path + L"\\Kaguya\\";
		//Chaera1の作成
		AddGameObject<StageSelectKaguyaSS>(Map);

		wstring Path2 = App::GetApp()->GetDataDirWString();
		//ファイル名の設定
		wstring Map2 = Path2 + L"\\StageSelect\\";
		//Chaera1の作成
		AddGameObject<StageSelectSS>(Map2);

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
		//ターン毎の初期化
		GetRigidbodyManager()->InitRigidbody();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの更新
			v->OnUpdate();
		}
		//Rigidbodyマネージャの更新（衝突判定など）
		GetRigidbodyManager()->OnUpdate();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの最終更新
			v->OnUpdate2();
		}
		//自分自身の更新(カメラ)
		this->OnUpdate();
		//Rigidbodyマネージャの最終更新（衝突判定情報のクリア）
		GetRigidbodyManager()->OnUpdate2();
		m_FadeSprite->OnUpdate();
	}
	void StageSelect::OnUpdate() {
		FindTagGameObject<StageSelectSS>(L"StageSelectSS")->SetStageNum(Selecter);
		FindTagGameObject<StageSelectKaguyaSS>(L"StageSelectKaguya")->SetStageNum(Selecter);
		switch (Selecter) {
		case 0:
			//m_kaguya->SetPos(Vec2(-400, -350));
			break;
		case 1:
			//m_kaguya->SetPos(Vec2(0, -250));
			break;
		case 2:
			//m_kaguya->SetPos(Vec2(380, 0));
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
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
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
			switch (Selecter) {
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect_S1");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect_S2");
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect_S3");
				break;
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
	///	1つ目のステージ
	//--------------------------------------------------------------------------------------
	void Tikurin::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"STAGESELECT_BGM");
		m_AudioObjectPtr->Start(L"STAGESELECT_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
		//描画オブジェクトの追加
		CreateDrawObjects();
		//メッセージスプライト
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"STAGESELECT_S1BG_TX",
			Vec2(1280, 800),
			0.0f,
			Vec2(0, 0),
			1, 1);
		L1 = AddGameObject<DefSp>(
			L"STAGESELECT_S1L1_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(-405, -70.0f),
			1, 1
			);
		L2 = AddGameObject<DefSp>(
			L"STAGESELECT_S1L2_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(0, -70.0f),
			1, 1
			);
		L3 = AddGameObject<DefSp>(
			L"STAGESELECT_S1L3_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(405, -70.0f),
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

	void Tikurin::CreateDrawObjects() {
		//SimplePCTStaticRenderer描画オブジェクトの作成
		AddGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
	}

	void Tikurin::OnUpdateStage() {
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
	void Tikurin::OnUpdate() {
		switch (Selecter) {
		case 0:
			L1->S1_ScaleControl(0.75f);
			L2->S1_ScaleControl(0.0f);
			L3->S1_ScaleControl(0.0f);
			break;
		case 1:
			L1->S1_ScaleControl(0.0f);
			L2->S1_ScaleControl(0.75f);
			L3->S1_ScaleControl(0.0f);
			break;
		case 2:
			L1->S1_ScaleControl(0.0f);
			L2->S1_ScaleControl(0.0f);
			L3->S1_ScaleControl(0.75f);
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
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
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
			App::GetApp()->GetScene<Scene>()->SetStageNumber(Selecter + 1);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}

	void Tikurin::OnDrawStage() {
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


	void Tikurin::OnDraw() {
		//何もしない
	}

	//--------------------------------------------------------------------------------------
	///	2つ目のステージ
	//--------------------------------------------------------------------------------------
	void Yama::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"STAGESELECT_BGM");
		m_AudioObjectPtr->Start(L"STAGESELECT_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
		//描画オブジェクトの追加
		CreateDrawObjects();
		//メッセージスプライト
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"STAGESELECT_S2BG_TX",
			Vec2(1280, 800),
			0.0f,
			Vec2(0, 0),
			1, 1);
		L1 = AddGameObject<DefSp>(
			L"STAGESELECT_S2L1_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(-350, -320.0f),
			1, 1
			);
		L2 = AddGameObject<DefSp>(
			L"STAGESELECT_S2L2_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(-180, -190.0f),
			1, 1
			);
		L3 = AddGameObject<DefSp>(
			L"STAGESELECT_S2L3_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(20, -55.0f),
			1, 1
			);
		L4 = AddGameObject<DefSp>(
			L"STAGESELECT_S2L4_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(205, 80.5f),
			1, 1
			);
		L5 = AddGameObject<DefSp>(
			L"STAGESELECT_S2L5_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(360, 220.0f),
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

	void Yama::CreateDrawObjects() {
		//SimplePCTStaticRenderer描画オブジェクトの作成
		AddGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
	}

	void Yama::OnUpdateStage() {
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
	void Yama::OnUpdate() {
		switch (Selecter) {
		case 0:
			L1->S2_ScaleControl(0.65f);
			L2->S2_ScaleControl(0.0f);
			L3->S2_ScaleControl(0.0f);
			L4->S2_ScaleControl(0.0f);
			L5->S2_ScaleControl(0.0f);
			break;
		case 1:
			L1->S2_ScaleControl(0.0f);
			L2->S2_ScaleControl(0.65f);
			L3->S2_ScaleControl(0.0f);
			L4->S2_ScaleControl(0.0f);
			L5->S2_ScaleControl(0.0f);
			break;
		case 2:
			L1->S2_ScaleControl(0.0f);
			L2->S2_ScaleControl(0.0f);
			L3->S2_ScaleControl(0.65f);
			L4->S2_ScaleControl(0.0f);
			L5->S2_ScaleControl(0.0f);
			break;
		case 3:
			L1->S2_ScaleControl(0.0f);
			L2->S2_ScaleControl(0.0f);
			L3->S2_ScaleControl(0.0f);
			L4->S2_ScaleControl(0.65f);
			L5->S2_ScaleControl(0.0f);
			break;
		case 4:
			L1->S2_ScaleControl(0.0f);
			L2->S2_ScaleControl(0.0f);
			L3->S2_ScaleControl(0.0f);
			L4->S2_ScaleControl(0.0f);
			L5->S2_ScaleControl(0.65f);
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
					Selecter = 4;
				}
				else if (Selecter > 4) {
					Selecter = 0;
				}
				//Bボタン
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
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
			App::GetApp()->GetScene<Scene>()->SetStageNumber(Selecter + 4);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}

	void Yama::OnDrawStage() {
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


	void Yama::OnDraw() {
		//何もしない
	}

	//--------------------------------------------------------------------------------------
	///	2つ目のステージ
	//--------------------------------------------------------------------------------------
	void Moon::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"STAGESELECT_BGM");
		m_AudioObjectPtr->Start(L"STAGESELECT_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
		//描画オブジェクトの追加
		CreateDrawObjects();
		//メッセージスプライト
		m_MessageSprite = ObjectFactory::Create<StageSprite>(
			GetThis<Stage>(),
			L"STAGESELECT_S3BG_TX",
			Vec2(1280, 800),
			0.0f,
			Vec2(0, 0),
			1, 1);
		L1 = AddGameObject<DefSp>(
			L"STAGESELECT_S3L1_TX",
			Vec2(410.0f, 600.0f),
			0.0f,
			Vec2(0, -240.0f),
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

	void Moon::CreateDrawObjects() {
		//SimplePCTStaticRenderer描画オブジェクトの作成
		AddGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
	}

	void Moon::OnUpdateStage() {
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
	void Moon::OnUpdate() {
			L1->S2_ScaleControl(0.65f);
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (!FadeFlag) {
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
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
			App::GetApp()->GetScene<Scene>()->SetStageNumber(9);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}

	void Moon::OnDrawStage() {
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


	void Moon::OnDraw() {
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