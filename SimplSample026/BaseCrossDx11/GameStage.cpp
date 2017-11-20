/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームステージ
	//--------------------------------------------------------------------------------------
	GameStage::GameStage()
	{
	}

	void GameStage::RegisterPctlBox() {
		if (!App::GetApp()->CheckResource<MeshResource>(L"DEFAULT_PCT_BOX")) {
			vector<VertexPositionNormalTexture> vertices;
			vector<VertexPositionColorTexture> new_vertices;
			vector<uint16_t> indices;
			MeshUtill::CreateCube(1.0f, vertices, indices);
			for (auto&v : vertices) {
				VertexPositionColorTexture vertex;
				vertex.position = v.position;
				vertex.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex.textureCoordinate = v.textureCoordinate;
				if (vertex.textureCoordinate.x == 1.0f) {
					vertex.textureCoordinate.x = 50.0f;
				}
				new_vertices.push_back(vertex);
			}
			App::GetApp()->RegisterResource(L"DEFAULT_PCT_BOX",
				MeshResource::CreateMeshResource(new_vertices, indices, false));
		}
	}

	void GameStage::OnCreate() {

		float v = 0;
		int BGS = 5;

		//シャドウマップの描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->GetShadowMapRenderTarget(2048.0f);

		//PCTボックスの登録（リソース登録する）
		RegisterPctlBox();

		auto R_WALL = AddGameObject<Wall>(
			L"WALL_TX",
			Vec3(2.0f, 16.0f, 2.0f),
			Vec3(6.5f, 0.0f, 0.0f),
			Quat(0.0f, 0.0f, 0.0f, 1.0f), 
			SquareDrawOption::Normal
			);
		auto L_WALL = AddGameObject<Wall>(
			L"WALL_TX",
			Vec3(2.0f, 16.0f, 2.0f),
			Vec3(-6.5f, 0.0f, 0.0f),
			Quat(0.0f, 0.0f, 0.0f, 1.0f),
			SquareDrawOption::Normal
			);

		AddGameObject<SquareSprite>(
			L"BAR_TX",
			Vec3(2.0f, 0.5f, 2.0f),
			Vec3(0.0f, -0.5f, 0.0f),
			Quat(0.0f, 0.0f, 0.0f, 1.0f),
			SquareDrawOption::Normal
			);

		//for (int i = 0; i < BGS; i++)
		//{
			//AddGameObject<SimpleSquare>(
			//	L"BG_TX",
			//	Vec3(15.0f, 15.0f, 1.0f),
			//	Vec3(0, 0.0f+v, 10),
			//	Quat(0.0f, 0.0f, 0.0f, 1.0f),
			//	SquareDrawOption::Normal
			//	);
			//v += 15.0f;
		//}
		AddGameObject<SimpleSquare>(
			L"BG_TX",
			Vec3(15.0f, 60.0f, 1.0f),
			Vec3(0, 20.0f, 10),
			Quat(0.0f, 0.0f, 0.0f, 1.0f),
			SquareDrawOption::Normal
			);



		//プレイヤーの作成
		AddGameObject<Player>(
			L"SUBARU_TX", 
			true, 
			Vec3(1.0f, 0.25f, 0.0f)
			);

		/*AddGameObject<P_child>(
			L"SUBARU_TX",
			true,
			Vec3(1.0f, 0.25f, 0.0f)
			);*/

		AddGameObject<Kaguya>(
			L"KAGUYA_TX",
			true,
			Vec3(0.0f, 0.125f, 0.0f)
			);

		//スパークエフェクト
		AddGameObject<MultiSpark>();
		//ファイアエフェクト
		AddGameObject<MultiFire>();

		//描画オブジェクトの追加
		CreateDrawObjects();


		////回転するスプライトの作成
		//AddGameObject<RotateSprite>(
		//	L"TRACE_TX",
		//	Vec2(160, 160),
		//	0.0f,
		//	Vec2(-480, 260),
		//	4, 4
		//	);


		//メッセージを表示するスプライトの作成
		AddGameObject<MessageSprite>(
			L"MESSAGE_TX",
			Vec2(256, 64),
			0.0f,
			Vec2(480, 260),
			1, 1
			);

		//文字列描画オブジェクトの作成
		AddGameObject<StringDrawObject>();


	}

	//描画オブジェクトの追加
	void GameStage::CreateDrawObjects() {
		//シャドウマップ描画オブジェクトの作成
		AddGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");

		//SimplePCTStaticRenderer描画オブジェクトの作成
		AddGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");

		//SimplePNTStaticRenderer描画オブジェクトの作成
		AddGameObject<SimplePNTStaticRenderer>(L"SimplePNTStaticRenderer");
		//SimplePNTStaticRenderer2描画オブジェクトの作成
		AddGameObject<SimplePNTStaticRenderer2>(L"SimplePNTStaticRenderer2");

		//SimplePNTStaticModelRenderer描画オブジェクトの作成
		AddGameObject<SimplePNTStaticModelRenderer>(L"SimplePNTStaticModelRenderer");
		//SimplePNTStaticModelRenderer2描画オブジェクトの作成
		AddGameObject<SimplePNTStaticModelRenderer2>(L"SimplePNTStaticModelRenderer2");

		//SimplePNTBoneModelRenderer描画オブジェクトの作成
		AddGameObject<SimplePNTBoneModelRenderer>(L"SimplePNTBoneModelRenderer");
		//SimplePNTBoneModelRenderer2描画オブジェクトの作成
		AddGameObject<SimplePNTBoneModelRenderer2>(L"SimplePNTBoneModelRenderer2");


		//BcPNTStaticDrawObject描画オブジェクトの作成
		AddGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
		//BcPNTnTStaticDrawObject描画オブジェクトの作成
		AddGameObject<BcPNTnTStaticRenderer>(L"BcPNTnTStaticRenderer");

		//BcPNTStaticModelDrawObject描画オブジェクトの作成
		AddGameObject<BcPNTStaticModelRenderer>(L"BcPNTStaticModelRenderer");
		//BcPNTnTStaticModelDrawObject描画オブジェクトの作成
		AddGameObject<BcPNTnTStaticModelRenderer>(L"BcPNTnTStaticModelRenderer");

		//BcPNTBoneModelDrawObject描画オブジェクトの作成
		AddGameObject<BcPNTBoneModelRenderer>(L"BcPNTBoneModelRenderer");
		//BcPNTnTBoneModelDrawObject描画オブジェクトの作成
		AddGameObject<BcPNTnTBoneModelRenderer>(L"BcPNTnTBoneModelRenderer");

		//Particle描画オブジェクトの作成(加算処理しない)
		AddGameObject<ParticleDrawObject>(false);
		//Particle描画オブジェクトの作成(加算処理する)
		AddGameObject<ParticleDrawObject>(true);

	}


	void GameStage::OnUpdateStage() {
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
	}


	void GameStage::OnUpdate() {

		auto Time = App::GetApp()->GetElapsedTime();
		m_Time += Time;
		interval_Time += Time;
		auto& camera = GetCamera();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//if (CntlVec[0].bConnected) {

		//	//Dパッド下
		//	if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		//		//カメラ位置を引く
		//		camera.m_CameraArmLen += 0.1f;
		//		if (GetCamera().m_CameraArmLen >= 50.0f) {
		//			GetCamera().m_CameraArmLen = 50.0f;
		//		}
		//	}
		//	//Dパッド上
		//	if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		//		//カメラ位置を寄る
		//		camera.m_CameraArmLen -= 0.1f;
		//		if (GetCamera().m_CameraArmLen <= 2.0f) {
		//			camera.m_CameraArmLen = 2.0f;
		//		}
		//	}
			//camera.m_CamerAt = FindTagGameObject<GameObject>(L"Kaguya")->GetPosition();
			//camera.m_CamerAt.y += 0.25f;
		/*auto kaguya = FindTagGameObject<Kaguya>(L"Kaguya");
		auto Body = kaguya->GetRigidbody();
		if (Body->m_Force.y <= 0.0f) {
			maxPosition = camera.m_CamerAt;
			camera.m_CamerAt = maxPosition;
		}
		else if (kaguya->GetPosition().y >= camera.m_CamerAt.y) {
			camera.m_CamerAt.y +=  Body->m_Force.y;
		}*/
		camera.m_CamerAt.y = FindTagGameObject<GameObject>(L"Kaguya")->GetPosition().y;
		if (camera.m_CamerAt.y > maxPosition) {
			maxPosition = camera.m_CamerAt.y;
		}

		else if (camera.m_CamerAt.y < maxPosition) {
			camera.m_CamerAt.y= maxPosition;
			//maxPosition = camera.m_CamerAt.y;
		}

			Vec3 CameraLocalEye =
				Vec3(
					sin(camera.m_CameraXZRad) * camera.m_CameraArmLen * sin(camera.m_CameraYRad),
					cos(camera.m_CameraYRad) * camera.m_CameraArmLen,
					-cos(camera.m_CameraXZRad) * camera.m_CameraArmLen * sin(camera.m_CameraYRad)
				);
			camera.m_CamerEye = camera.m_CamerAt + CameraLocalEye;
			//Bボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToEmptyStage");
			}
		

		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::FloatToWStr(CntlVec[0].fThumbRX);
		FPS += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		FPS += Util::FloatToWStr(maxPosition);
		FPS += L"\n";
		if (!m_StringDrawObject) {
			m_StringDrawObject = FindTagGameObject<StringDrawObject>(L"StringDrawObject");
		}
		m_StringDrawObject->SetText(FPS);

		/*//子供がついてくる
		auto Player = FindTagGameObject<GameObject>(L"Player");
		Vec3 P_Pos = Player->GetPosition();
		auto C_Prayer = FindTagGameObject<P_child>(L"P_child");
		C_Prayer->setPos(P_Pos);
		C_Prayer->setP_Pos(P_Pos);
		auto angle = C_Prayer->getAngle();
		if (C_Prayer->getBarflg()&& interval_Time > 0.2f)
		{
			Quat qt(Vec3(0, 0, 1), (angle - 1.5f)*-1);

			    auto a =AddGameObject<Bar>(
				L"LINE_TX",
				Vec3(2.0f, 0.1f, 2.0f),
				C_Prayer->getP_Pos(),
				qt,
				SquareDrawOption::Normal
				);
			interval_Time = 0;
		}*/

		auto player = FindTagGameObject<Player>(L"Player");
		Vec3 P_Pos = player->GetPosition();
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && PointCount==0) {
			auto a = AddGameObject<P_child>(
				L"SUBARU_TX",
				true,
				Vec3(1.0f, 0.25f, 0.0f)
				);
			a->setPos(P_Pos);
			PointPos1 = P_Pos;
			PointCount++;
		}
		else if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && PointCount== 1) {
			auto a = AddGameObject<P_child>(
				L"SUBARU_TX",
				true,
				Vec3(1.0f, 0.25f, 0.0f)
				);
			a->setPos(P_Pos);
			PointPos2 = P_Pos;
			PointCount++;
		}
		else if (PointCount == 2)
		{
			Barflag = true;
			PointCount = 0;
		}

		if (Barflag)
		{
			CrBar();
			Barflag=false;
		}
	}

	void GameStage::OnDrawStage() {
		//描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));

		//シャドオウマップ描画の開始
		Dev->ClearShadowmapViews();
		Dev->StartShadowmapDraw();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの描画
			v->OnDrawShadowmap();
		}
		Dev->EndShadowmapDraw();

		//デフォルト描画の開始
		Dev->StartDefaultDraw();
		for (auto& v : GetGameObjectVec()) {
			//各オブジェクトの描画
			v->OnDraw();
		}
		//自分自身の描画
		this->OnDraw();
		//デフォルト描画の終了
		Dev->EndDefaultDraw();
	}


	void GameStage::OnDraw() {
		m_RigidbodyManager->OnDraw();
	}

	void GameStage::CrBar()
	{
		auto player = FindTagGameObject<Player>(L"Player");
		Vec3 P_Pos = player->GetPosition();
		float vec = atan2(PointPos1.y- PointPos2.y, PointPos1.x-PointPos2.x);
		Quat qt(Vec3(0, 0, 1), vec);

		float s = ((PointPos2.x - PointPos1.x)*(PointPos2.x - PointPos1.x)) + ((PointPos2.y - PointPos1.y)*(PointPos2.y - PointPos1.y));

		float Scale = sqrt(s);

		auto a = AddGameObject<Bar>(
			L"LINE_TX",
			Vec3(Scale, 0.1f, 2.0f),
			Vec3((PointPos2.x + PointPos1.x) / 2, (PointPos2.y + PointPos1.y) / 2,0),
			qt,
			SquareDrawOption::Normal);
	}

	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	void EmptyStage::OnCreate() {
		//メッセージスプライト
		m_MessageSprite = ObjectFactory::Create<MessageSprite>(
			GetThis<Stage>(),
			L"MESSAGE_TX",
			Vec2(256, 64),
			0.0f,
			Vec2(0, 0),
			1, 1);
	}
	void EmptyStage::OnUpdateStage() {
		//スプライトの更新
		m_MessageSprite->OnUpdate();
		//自分自身の更新
		this->OnUpdate();
	}
	void EmptyStage::OnUpdate() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//Bボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
	}

	void EmptyStage::OnDrawStage() {
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


	void EmptyStage::OnDraw() {
		//何もしない
	}


}
//end basecross
