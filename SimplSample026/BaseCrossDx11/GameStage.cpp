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

	void GameStage::Csv()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		// CSVファイルの決定,
		//-------------------------------------------------
		//ディレクトリパス
		wstring Path = App::GetApp()->GetDataDirWString();

		//ファイル名の設定
		wstring Map = Path +L"\\CSV\\" + L"Stage_1.csv";
			//+ Util::IntToWStr(ScenePtr->GetStageNumber()) + L".csv";

		//ファイルの指定
		m_Csv.SetFileName(Map);

		if (!m_Csv.ReadCsv())
		{
			//ファイルが存在しなかったとき
			throw BaseException(
				L"ファイルが見つかりませんでした",
				Map,
				L"パスが間違っているorファイルが存在しない"
			);
		}
		else {
			//CSVファイルが存在したときにフラグをtrueにする
			dataIdFlag = true;
		}

		//Csvを読み込んでくる----------
		int RowNum = 1;//行番号
					   //行を記憶させるための配列
		vector<wstring>MapVec;
		//最初の行を配列へ保存
		m_Csv.GetRowVec(RowNum, MapVec);

		//角度のラジアン変換用
		//float DegToRad = 3.14159265f / 180.0f;

		int Wcount = 0;
		//最後まで読み込む
		while (MapVec[0] != L"end")
		{
			//文字列があったかを判断
			bool stringflag = false;
			//ポジション、ローテーション、スケール
			//オブジェクトをそれぞれ生成する
			//TransformのCsvファイル列番号対応
			//--------------------
			//1:PosX 2:PosY 3:PosZ
			//4:RotX 5:RotY 6:RotZ 
			//7:SclX 8:SclY 9:SclZ
			//--------------------
			//_wtof(文字列を数値として読み取る)
			//ポジションを格納
			Vec3 Pos = Vec3((float)_wtof(MapVec[1].c_str()), (float)_wtof(MapVec[2].c_str()), (float)_wtof(MapVec[3].c_str()));
			//ローテーションを格納(この時にラジアンに変換)
			Vec3 Rot = Vec3((float)_wtof(MapVec[4].c_str()), (float)_wtof(MapVec[5].c_str()), (float)_wtof(MapVec[6].c_str()));
			//スケールを格納
			Vec3 Scl = Vec3((float)_wtof(MapVec[7].c_str()), (float)_wtof(MapVec[8].c_str()), (float)_wtof(MapVec[9].c_str()));
			//auto UpGroup = GetSharedObjectGroup(L"UpdateObjectGroup");

			if (MapVec[0] == L"Player")
			{
				stringflag = true;
				AddGameObject<Player>(
					L"SUBARU_Y_TX", 
					true, 
					Pos
					);
			}

			if (MapVec[0] == L"Kaguya")
			{
				stringflag = true;
				AddGameObject<Kaguya>(
					L"KAGUYA_TX",
					true,
					Pos
					);
			}

			if (MapVec[0] == L"Rabbit")
			{
				stringflag = true;
				AddGameObject<Rabbit>(
					L"RABBIT_TX",
					true,
					Pos
					);
			}

			if (MapVec[0] == L"Goal")
			{
				stringflag = true;
				AddGameObject<Goal>(
				L"GOAL2_TX",
					Vec3(1, 1, 1.0f),
					Pos,
					Quat(0.0f, 0.0f, 0.0f, 1.0f),
					SquareDrawOption::Normal);
			}

			if (MapVec[0] == L"Bamboo")
			{
				stringflag = true;
				AddGameObject<Bamboo>(
					L"WALL_TX",
					true,
					Pos
					);
			}

			if (MapVec[0] == L"BambooB")
			{
				stringflag = true;
				auto bamboo = AddGameObject<Bamboo>(
					L"Bamboo_B_TX",
					true,
					Pos
					);
				bamboo->AddTag(L"BambooB");
			}

			if (MapVec[0] == L"Heel")
			{
				stringflag = true;
				AddGameObject<LightHeel>(
					L"STAR_TX",
					true,
					Pos
					);
			}

			if (!stringflag)
			{
				throw BaseException
				(
					Util::IntToWStr(RowNum + 1) + L"行目",
					MapVec[0].c_str(),
					L"使用不可のオブジェクトです"
				);
			}
			//行データ更新
			RowNum++;
			m_Csv.GetRowVec(RowNum, MapVec);

		}

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
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"GAMESTAGE_BGM");
		m_AudioObjectPtr->Start(L"GAMESTAGE_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);

		float v = 0;
		int BGS = 5;

		Csv();
		//シャドウマップの描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->GetShadowMapRenderTarget(2048.0f);

		//PCTボックスの登録（リソース登録する）
		RegisterPctlBox();

		auto R_WALL = AddGameObject<Wall>(
			L"WALL_TX",
			Vec3(1.0f, 100.0f, 2.0f),
			Vec3(7.0f, 40.0f, 0.0f),
			Quat(0.0f, 0.0f, 0.0f, 1.0f), 
			SquareDrawOption::Normal
			);
		auto L_WALL = AddGameObject<Wall>(
			L"WALL_TX",
			Vec3(1.0f, 100.0f, 2.0f),
			Vec3(-7.0f, 40.0f, 0.0f),
			Quat(0.0f, 0.0f, 0.0f, 1.0f),
			SquareDrawOption::Normal
			);
		

		auto Startbar = AddGameObject<Bar>(
			L"BARY_TX",
			Vec3(2.0f, 0.1f, 2.0f),
			Vec3(0.0f, -1.5f, 0.0f),
			Quat(0.0f, 0.0f, 0.0f, 1.0f),
			SquareDrawOption::Normal
			);
		Startbar->AddTag(L"Yellow");

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
			Vec3(15.0f, 100.0f, 1.0f),
			Vec3(0, 40.0f, 10),
			Quat(0.0f, 0.0f, 0.0f, 1.0f),
			SquareDrawOption::Normal
			);

		/*AddGameObject<BG>(
			L"UI_S_TX",
			Vec3(25.0f, 15.0f, 1.0f),
			Vec3(0, 0.0f, 20),
			Quat(0.0f, 0.0f, 0.0f, 1.0f),
			SquareDrawOption::Normal
			);*/

		////プレイヤーの作成
		//AddGameObject<Player>(
		//	L"SUBARU_TX", 
		//	true, 
		//	Vec3(1.0f, 0.25f, 0.0f)
		//	);

		///*AddGameObject<P_child>(
		//	L"SUBARU_TX",
		//	true,
		//	Vec3(1.0f, 0.25f, 0.0f)
		//	);*/

		//AddGameObject<Kaguya>(
		//	L"KAGUYA_TX",
		//	true,
		//	Vec3(0.0f, 0.125f, 0.0f)
		//	);

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

		AddGameObject<LightGage_F>(
			L"UI_S_TX",
			Vec2(310,800),
			0.0f,
			Vec2(490, 0),
			1, 1
			);

		AddGameObject<LightGage_F>(
			L"LIGHTGAGE_A_TX",
			Vec2(256 * 1.2, 64 * 1.2),
			0.0f,
			Vec2(490, 200),
			1, 1
			);
		AddGameObject<LightGage_B>(
			L"LIGHTGAGE_B_TX",
			Vec2(278.0f, 6.0f),
			0.0f,
			Vec2(502, 190.8f),
			1, 1
			);
		auto kaguya = FindTagGameObject<Kaguya>(L"Kaguya");
		auto life = kaguya->GetLife();
		for (int i = 1; i <= life; i++) {
			AddGameObject<Life>(
				L"EMP_LIFE_TX",
				Vec2(50, 50),
				0.0f,
				Vec2(360.0f + life_x, 120.0f),
				1, 1
				);
			lifeobj = AddGameObject<Life>(
				L"LIFE_TX",
				Vec2(35.0f, 35.0f),
				0.0f,
				Vec2(360.5f + life_x, 120.5f),
				1, 1
				);
			life_x += 50.0f;
			lifegroup.push_back(lifeobj);
		}

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


		wstring Path = App::GetApp()->GetDataDirWString();

		//ファイル名の設定
		wstring Map = Path + L"\\Kaguya\\";

		//Chaera1の作成
		auto m_Kaguya=AddGameObject<Chara1>(Map);

		m_FadeSprite = ObjectFactory::Create<Fade>(
			GetThis<Stage>(),
			L"FADE_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);

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
		m_FadeSprite->OnUpdate();
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

		auto kaguya = FindTagGameObject<Kaguya>(L"Kaguya");
		auto life = kaguya->GetLife();
		switch (life)
		{
		case 0:
			lifegroup[0]->ScaleChangeD();
			lifegroup[1]->ScaleChangeD();
			lifegroup[2]->ScaleChangeD();
			lifegroup[3]->ScaleChangeD();
			lifegroup[4]->ScaleChangeD();
			break;
		case 1:
			lifegroup[0]->ScaleChangeH();
			lifegroup[1]->ScaleChangeD();
			lifegroup[2]->ScaleChangeD();
			lifegroup[3]->ScaleChangeD();
			lifegroup[4]->ScaleChangeD();
			break;
		case 2:
			lifegroup[0]->ScaleChangeH();
			lifegroup[1]->ScaleChangeH();
			lifegroup[2]->ScaleChangeD();
			lifegroup[3]->ScaleChangeD();
			lifegroup[4]->ScaleChangeD();
			break;
		case 3:
			lifegroup[0]->ScaleChangeH();
			lifegroup[1]->ScaleChangeH();
			lifegroup[2]->ScaleChangeH();
			lifegroup[3]->ScaleChangeD();
			lifegroup[4]->ScaleChangeD();
			break;
		case 4:
			lifegroup[0]->ScaleChangeH();
			lifegroup[1]->ScaleChangeH();
			lifegroup[2]->ScaleChangeH();
			lifegroup[3]->ScaleChangeH();
			lifegroup[4]->ScaleChangeD();
			break;
		case 5:
			lifegroup[0]->ScaleChangeH();
			lifegroup[1]->ScaleChangeH();
			lifegroup[2]->ScaleChangeH();
			lifegroup[3]->ScaleChangeH();
			lifegroup[4]->ScaleChangeH();
			break;
		}

		camera.m_CamerAt.y = FindTagGameObject<GameObject>(L"Kaguya")->GetPosition().y;
		if (camera.m_CamerAt.y > maxPosition) {
			maxPosition = camera.m_CamerAt.y;
		}

		else if (camera.m_CamerAt.y < maxPosition) {
			camera.m_CamerAt.y= maxPosition;
			//maxPosition = camera.m_CamerAt.y;
		}

		if (maxPosition >= 83.0f) {
			camera.m_CamerAt.y = 83.0f;
		}
		if (FindTagGameObject<GameObject>(L"Kaguya")->GetPosition().y <= (maxPosition - 7.0f) ) {
			m_AudioObjectPtr->Stop(L"GAMESTAGE_BGM");
			FadeFlag = true;
			//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
		}


			Vec3 CameraLocalEye =
				Vec3(
					sin(camera.m_CameraXZRad) * camera.m_CameraArmLen * sin(camera.m_CameraYRad),
					cos(camera.m_CameraYRad) * camera.m_CameraArmLen,
					-cos(camera.m_CameraXZRad) * camera.m_CameraArmLen * sin(camera.m_CameraYRad)
				);
			camera.m_CamerEye = camera.m_CamerAt + CameraLocalEye;
			//Bボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
				m_AudioObjectPtr->Stop(L"GAMESTAGE_BGM");
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
			}
		

		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::FloatToWStr(CntlVec[0].fThumbRX);
		FPS += L"\nTime: ";
		FPS += Util::FloatToWStr(m_Time);
		//FPS += FindTagGameObject<Kaguya>(L"Kaguya")->GetHitObj();
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
		P_color = player->getP_color();
		wstring TextureResName;
		switch (P_color) {
		case Yellow:
			TextureResName = L"SUBARU_Y_TX";
			break;
		case Red:
			TextureResName = L"SUBARU_R_TX";
			break;
		default:
			break;
		}
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && PointCount==0) {
			PointDeleteflag = false;
			auto a = AddGameObject<P_child>(
				TextureResName,
				true,
				Vec3(0.1f, 1.0f, 0.0f)
				);
			a->setPos(P_Pos);
			PointPos1 = P_Pos;
			PointCount++;
		}
		else if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && PointCount== 1) {
			auto a = AddGameObject<P_child>(
				TextureResName,
				true,
				Vec3(1.0f, 0.5f, 0.0f)
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

		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
		{
			PointCount = 0;
		}

		if (Barflag)
		{
			CrBar();
			Barflag=false;
			PointDeleteflag = true;
		}

		if (FadeFlag)
		{
			m_FadeSprite->SetFadeFlag(true);
		}
		if (m_FadeSprite->GetChangeFlag())
		{
			if (ClearFlag)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearResult");
			}
			else
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
			}
			
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
		m_FadeSprite->OnDraw();
		//デフォルト描画の終了
		Dev->EndDefaultDraw();
	}


	void GameStage::OnDraw() {
		m_RigidbodyManager->OnDraw();

	}

	void GameStage::CrBar()
	{
		auto player = FindTagGameObject<Player>(L"Player");
		lightbar = player->getP_LightGage();
		Vec3 P_Pos = player->GetPosition();
		float vec = atan2(PointPos1.y- PointPos2.y, PointPos1.x-PointPos2.x);
		Quat qt(Vec3(0, 0, 1), vec);

		float s = ((PointPos2.x - PointPos1.x)*(PointPos2.x - PointPos1.x)) + ((PointPos2.y - PointPos1.y)*(PointPos2.y - PointPos1.y));

		float Scale = sqrt(s);

		if (Scale >= 1.0f) {

			P_color = player->getP_color();

			if (P_color == Yellow && lightbar >= Scale * 5) {
				auto a = AddGameObject<Bar>(
					L"BARY_TX",
					Vec3(Scale, 0.1f, 2.0f),
					Vec3((PointPos2.x + PointPos1.x) / 2, (PointPos2.y + PointPos1.y) / 2, 0),
					qt,
					SquareDrawOption::Normal);
				a->AddTag(L"Yellow");
				lightbar -= Scale*5;
				player->setP_LightGage(lightbar);
			}
			else if (P_color == Red && lightbar >= Scale * 10) {
				auto a = AddGameObject<Bar>(
					L"BARR_TX",
					Vec3(Scale, 0.1f, 2.0f),
					Vec3((PointPos2.x + PointPos1.x) / 2, (PointPos2.y + PointPos1.y) / 2, 0),
					qt,
					SquareDrawOption::Normal);
				a->AddTag(L"Red");
				lightbar -= Scale * 10;
				player->setP_LightGage(lightbar);
			}
		}
	}

	void GameStage::StartDestroySE() {
		m_AudioObjectPtr->AddAudioResource(L"DEST_SE");
		m_AudioObjectPtr->Start(L"DEST_SE", 0, 0.5f);
	}

	void GameStage::StopBGM() {
		m_AudioObjectPtr->Stop(L"GAMESTAGE_BGM");
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
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
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
