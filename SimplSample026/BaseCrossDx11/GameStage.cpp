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
		wstring Map = Path +L"\\CSV\\" + L"Stage_" + Util::IntToWStr(ScenePtr->GetStageNumber()) + L".csv";
		/*+ L"Stage_1.csv";*/
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
				wstring Path = App::GetApp()->GetDataDirWString();
				//ファイル名の設定
				wstring Map = Path + L"\\Subaru\\";
				//Chaera1の作成
				AddGameObject<SubaruSS>(Map);
				auto a = AddGameObject<Player>(
					L"SUBARU_Y_TX", 
					false, 
					Vec3(Pos.x - 3.0f, Pos.y - 1.5f,0)
					);
				wstring Path2 = App::GetApp()->GetDataDirWString();
				//ファイル名の設定
				wstring StarMap = Path2 + L"\\Star\\";
				wstring TextureResName;
				AnimeName = L"Star_Y";
				TextureResName = L"SUBARU_Y_TX";
				PointDeleteflag = false;
				AddGameObject<StarSS>(StarMap, AnimeName, Vec3(Pos.x + 3.0f, Pos.y - 1.5f, 0));
				auto b = AddGameObject<P_child>(
					TextureResName,
					true,
					Vec3(0.1f, 1.0f, 0.0f)
					);
				b->setPos(Vec3(Pos.x + 3.0f, Pos.y - 1.5f, 0));
				PointPos1 = Vec3(Pos.x + 3.0f, Pos.y - 1.5f, 0);
				PointCount++;
			}

			if (MapVec[0] == L"Kaguya")
			{
				stringflag = true;
				wstring Path = App::GetApp()->GetDataDirWString();
				//ファイル名の設定
				wstring Map = Path + L"\\Kaguya\\";
				//Chaera1の作成
				AddGameObject<KaguyaSS>(Map);
				AddGameObject<Kaguya>(
					L"KAGUYA_TX",
					false,
					Pos
					);
			}

			if (MapVec[0] == L"Rabbit")
			{
				stringflag = true;
				/*AddGameObject<Rabbit>(
					L"RABBIT_TX",
					true,
					Pos
					);*/
				wstring Path = App::GetApp()->GetDataDirWString();

				//ファイル名の設定
				wstring Map = Path + L"\\Enemy\\";

				AddGameObject<RabbitSS>(Map, Pos);
			}

			if (MapVec[0] == L"KineRabbit")
			{
				stringflag = true;
				/*AddGameObject<KineRabbit>(
					L"RABBIT_TX",
					true,
					Pos
					);*/
				wstring Path = App::GetApp()->GetDataDirWString();

				//ファイル名の設定
				wstring Map = Path + L"\\Enemy\\";

				AddGameObject<KineRabbitSS>(Map, Pos);
			}

			if (MapVec[0] == L"Wisp")
			{
				stringflag = true;
				/*AddGameObject<KineRabbit>(
				L"RABBIT_TX",
				true,
				Pos
				);*/
				wstring Path = App::GetApp()->GetDataDirWString();

				//ファイル名の設定
				wstring Map = Path + L"\\Enemy\\";

				AddGameObject<WispSS>(Map, Pos);
			}

			if (MapVec[0] == L"Goal")
			{
				stringflag = true;
				AddGameObject<Goal>(
					L"GOAL2_TX",
					true,
					Pos
					);
				GoalPos = Pos.y;
				
			}

			if (MapVec[0] == L"Bamboo")
			{
				stringflag = true;
				AddGameObject<Bamboo>(
					L"WALL_TX",
					true,
					Pos
					);
				stringflag = true;
				/*auto a = AddGameObject<Bomboo2>(
					L"WALL_TX",
					true,
					Pos
					);*/
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

			if (MapVec[0] == L"CloudA")
			{
				stringflag = true;
				AddGameObject<Cloud>(
					L"CLOUDA_TX",
					true,
					Pos
					);
			}
			if (MapVec[0] == L"CloudB")
			{
				stringflag = true;
				AddGameObject<Cloud>(
					L"CLOUDB_TX",
					true,
					Pos
					);
			}
			if (MapVec[0] == L"CloudC")
			{
				stringflag = true;
				AddGameObject<Cloud>(
					L"CLOUDC_TX",
					true,
					Pos
					);
			}
			if (MapVec[0] == L"CloudD")
			{
				stringflag = true;
				AddGameObject<Cloud>(
					L"CLOUDD_TX",
					true,
					Pos
					);
			}

			if (MapVec[0] == L"StageCloudA")
			{
				stringflag = true;
				AddGameObject<StageCloud>(
					L"CLOUDA_TX",
					true,
					Pos
					);
			}
			if (MapVec[0] == L"StageCloudB")
			{
				stringflag = true;
				AddGameObject<StageCloud>(
					L"CLOUDB_TX",
					true,
					Pos
					);
			}
			if (MapVec[0] == L"StageCloudC")
			{
				stringflag = true;
				AddGameObject<StageCloud>(
					L"CLOUDC_TX",
					true,
					Pos
					);
			}
			if (MapVec[0] == L"StageCloudD")
			{
				stringflag = true;
				AddGameObject<StageCloud>(
					L"CLOUDD_TX",
					true,
					Pos
					);
			}

			if (MapVec[0] == L"Heel")
			{
				stringflag = true;
				/*AddGameObject<LightHeel>(
					L"STAR_TX",
					true,
					Pos
					);*/
				wstring Path = App::GetApp()->GetDataDirWString();

				//ファイル名の設定
				wstring Map = Path + L"\\Item\\";

				AddGameObject<HeelSS>(Map, Pos);
				
			}
			if (MapVec[0] == L"Tamanoeda")
			{
				stringflag = true;
				/*AddGameObject<LightHeel>(
				L"STAR_TX",
				true,
				Pos
				);*/
				wstring Path = App::GetApp()->GetDataDirWString();

				//ファイル名の設定
				wstring Map = Path + L"\\Item\\";

				AddGameObject<TamanoedaSS>(Map, Pos);

			}

			if (MapVec[0] == L"Boss")
			{
				BossNull = false;
				stringflag = true;
				wstring Path = App::GetApp()->GetDataDirWString();

				//ファイル名の設定
				wstring Map = Path + L"\\Enemy\\";

				AddGameObject<BossEnemy>(Map, Pos);
			}

			if (MapVec[0] == L"Bossusa")
			{
				stringflag = true;
				wstring Path = App::GetApp()->GetDataDirWString();

				//ファイル名の設定
				wstring Map = Path + L"\\Enemy\\";
				AddGameObject<BossusaSS>(Map, Pos);
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
		if (App::GetApp()->GetScene<Scene>()->GetStageNumber() == 9) {
			m_AudioObjectPtr->AddAudioResource(L"BOSS_BGM");
			m_AudioObjectPtr->Start(L"BOSS_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
		}
		else {
			m_AudioObjectPtr->AddAudioResource(L"GAMESTAGE_BGM");
			m_AudioObjectPtr->Start(L"GAMESTAGE_BGM", XAUDIO2_LOOP_INFINITE, 0.3f);
		}
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
			Vec2(480, 0),
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
		AddGameObject<StageSprite>(
			L"TAIRYOKU_TX",
			Vec2(110, 25),
			0.0f,
			Vec2(380, 150),
			1, 1
			);
		auto kaguya = FindTagGameObject<Kaguya>(L"Kaguya");
		auto life = kaguya->GetLife();
		for (int i = 1; i <= life; i++) {
			AddGameObject<Life>(
				L"EMP_LIFE_TX",
				Vec2(50, 50),
				0.0f,
				Vec2(360.0f + life_x, 110.0f),
				1, 1
				);
			lifeobj = AddGameObject<Life>(
				L"LIFE_TX",
				Vec2(35.0f, 35.0f),
				0.0f,
				Vec2(360.5f + life_x, 110.5f),
				1, 1
				);
			life_x += 50.0f;
			lifegroup.push_back(lifeobj);
		}

		//メッセージを表示するスプライトの作成
		m_MessageSprite = AddGameObject<MessageSprite>(
			L"PUSH_A_TX",
			Vec2(600, 100),
			0.0f,
			Vec2(-150, -250),
			1, 1);
		m_MessageSprite->SetFlashingFlag(true);

		//文字列描画オブジェクトの作成
		AddGameObject<StringDrawObject>();

		AddGameObject<StageSprite>(
			L"KEIKAZIKAN_TX",
			Vec2(110, 25),
			0.0f,
			Vec2(390, 40),
			1, 1
			);
		TimeNum_1 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(60, 60),
			0.0f,
			Vec2(530, -10),
			1.0f,
			1, 1
			);
		TimeNum_2 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(60, 60),
			0.0f,
			Vec2(490, -10),
			10.0f,
			1, 1
			);
		Collon = AddGameObject<StageSprite>(
			L"CORRON_TX",
			Vec2(20, 60),
			0.0f,
			Vec2(460, -10),
			1, 1
			);
		TimeNum_3 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(60, 60),
			0.0f,
			Vec2(430, -10),
			1.0f,
			1, 1
			);
		TimeNum_4 = AddGameObject<NumSprite>(
			L"NUMBER_TX",
			Vec2(60, 60),
			0.0f,
			Vec2(390, -10),
			10.0f,
			1, 1
			);

		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (ScenePtr->GetStageNumber()==1)
		{
			m_HintSprite = AddGameObject<MessageSprite>(
				L"HINT_1_TX",
				Vec2(600, 150),
				0.0f,
				Vec2(-150, 250),
				1, 1);
			HintFlag = true;
		}
		if (ScenePtr->GetStageNumber() == 2)
		{
			m_HintSprite = AddGameObject<MessageSprite>(
				L"HINT_2_TX",
				Vec2(600, 150),
				0.0f,
				Vec2(-150, 250),
				1, 1);
			HintFlag = true;
		}
		if (ScenePtr->GetStageNumber() == 3)
		{
			m_HintSprite = AddGameObject<MessageSprite>(
				L"HINT_3_TX",
				Vec2(600, 150),
				0.0f,
				Vec2(-150, 250),
				1, 1);
			HintFlag = true;
		}
		if (ScenePtr->GetStageNumber() == 5)
		{
			m_HintSprite = AddGameObject<MessageSprite>(
				L"HINT_5_TX",
				Vec2(600, 150),
				0.0f,
				Vec2(-150, 250),
				1, 1);
			HintFlag = true;
		}
		if (ScenePtr->GetStageNumber() == 8)
		{
			m_HintSprite = AddGameObject<MessageSprite>(
				L"HINT_8_TX",
				Vec2(600, 150),
				0.0f,
				Vec2(-150, 250),
				1, 1);
			HintFlag = true;
		}
		if (ScenePtr->GetStageNumber() == 9)
		{
			m_HintSprite = AddGameObject<MessageSprite>(
				L"HINT_9_TX",
				Vec2(600, 150),
				0.0f,
				Vec2(-150, 250),
				1, 1);
			HintFlag = true;
		}

		m_FadeSprite = ObjectFactory::Create<Fade>(
			GetThis<Stage>(),
			L"FADE_TX",
			Vec2(1280, 830),
			0.0f,
			Vec2(0, 0),
			1, 1);
		//wstring Path = App::GetApp()->GetDataDirWString();
		//ファイル名の設定
		//wstring GameOverMap = Path + L"\\GameOver\\";
		//AddGameObject<KaguyaGOSS>(GameOverMap, Vec3(1280 / 2, 830 / 2, 1));
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

		if(Startflag){
			if (!ClearFlag) {
				m_Time_Sec += Time;
			}
			interval_Time += Time;
		}

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			
		}

		if (Startflag&&CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
		{
			Startflag = false;
		}
		
		if (!Startflag&&CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
		{
			//wstring Path
			//	= App::GetApp()->GetDataDirWString();
			////ファイル名の設定
			//wstring LineMap = Path + L"\\Line\\";
			//auto Startbar=AddGameObject<BarSS>(LineMap, L"Yellow_line", Vec3(0.0f, -1.5f, 0.0f),
			//	Vec3(2.0f, 0.1f, 2.0f),
			//	Quat(0.0f, 0.0f, 0.0f, 1.0f));
			/*auto Startbar = AddGameObject<Bar>(
				L"BARY_TX",
				Vec3(2.0f, 0.1f, 2.0f),
				Vec3(0.0f, -1.5f, 0.0f),
				Quat(0.0f, 0.0f, 0.0f, 1.0f),
				SquareDrawOption::Normal
				);*/
			/*Startbar->AddTag(L"Yellow");*/
			Startflag = true;
			m_MessageSprite->SetAlpha(0);
			if (HintFlag) {
				m_HintSprite->SetAlpha(0);
			}
		}

		
		auto& camera = GetCamera();


		camera.m_CamerAt.y = FindTagGameObject<GameObject>(L"Kaguya")->GetPosition().y;
		KaguyaPos = FindTagGameObject<GameObject>(L"Kaguya")->GetPosition();
		auto player = FindTagGameObject<Player>(L"Player");
		P_Pos = player->GetPosition();
		if (!BossNull) {
			BossPos = FindTagGameObject<GameObject>(L"Boss")->GetPosition();
			if (camera.m_CamerAt.y >= BossPos.y - 3) {
				camera.m_CamerAt.y = BossPos.y - 3;
			}
			else if (camera.m_CamerAt.y > maxPosition) {
				maxPosition = camera.m_CamerAt.y;
			}
			else if (camera.m_CamerAt.y < maxPosition) {
				camera.m_CamerAt.y = maxPosition;
				//maxPosition = camera.m_CamerAt.y;
			}
		}
		else if (ClearFlag){
			if (camera.m_CamerAt.y >= GoalPos + 3) {
				camera.m_CamerAt.y = GoalPos + 3;
			}
			else if (camera.m_CamerAt.y > maxPosition) {
				maxPosition = camera.m_CamerAt.y;
			}
			else if (camera.m_CamerAt.y < maxPosition) {
				camera.m_CamerAt.y = maxPosition;
				//maxPosition = camera.m_CamerAt.y;
			}
		}
		else {
			if (camera.m_CamerAt.y >= 84) {
				camera.m_CamerAt.y = 84;
			}
			else if(camera.m_CamerAt.y > maxPosition) {
				maxPosition = camera.m_CamerAt.y;
			}
			else if (camera.m_CamerAt.y < maxPosition) {
				camera.m_CamerAt.y = maxPosition;
				//maxPosition = camera.m_CamerAt.y;
			}
		}
		Vec3 CameraLocalEye =
			Vec3(
				sin(camera.m_CameraXZRad) * camera.m_CameraArmLen * sin(camera.m_CameraYRad),
				cos(camera.m_CameraYRad) * camera.m_CameraArmLen,
				-cos(camera.m_CameraXZRad) * camera.m_CameraArmLen * sin(camera.m_CameraYRad)
			);
		camera.m_CamerEye = camera.m_CamerAt + CameraLocalEye;

		if (Startflag) {
			//コントローラの取得
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
			if (FindTagGameObject<GameObject>(L"Kaguya")->GetPosition().y <= (maxPosition - 7.0f)) {
				m_AudioObjectPtr->AddAudioResource(L"VOICE_SONNAA");
				m_AudioObjectPtr->Start(L"VOICE_SONNAA", 0, 0.5f);
				if (App::GetApp()->GetScene<Scene>()->GetStageNumber() == 9) {
					m_AudioObjectPtr->Stop(L"BOSS_BGM");
				}
				else {
					m_AudioObjectPtr->Stop(L"GAMESTAGE_BGM");
				}
				FadeFlag = true;
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
			}


			//Bボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
				if (App::GetApp()->GetScene<Scene>()->GetStageNumber() == 9) {
					m_AudioObjectPtr->Stop(L"BOSS_BGM");
				}
				else {
					m_AudioObjectPtr->Stop(L"GAMESTAGE_BGM");
				}
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitle");
			}

			if (m_Time_Sec >= 60) {
				m_Time_Sec = 0;
				m_Time_Min += 1;
			}

			/*auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
			wstring FPS(L"FPS: ");
			FPS += Util::FloatToWStr(CntlVec[0].fThumbRX);
			FPS += L"\nTime: ";
			FPS += Util::FloatToWStr(m_Time_Sec);*/
			TimeNum_1->SetNum(m_Time_Sec);
			TimeNum_2->SetNum(m_Time_Sec);
			TimeNum_3->SetNum(m_Time_Min);
			TimeNum_4->SetNum(m_Time_Min);
			//FPS += FindTagGameObject<Kaguya>(L"Kaguya")->GetHitObj();
			/*FPS += L"\n";
			FPS += Util::FloatToWStr(EnemyBreak);
			FPS += L"\n";
			if (!m_StringDrawObject) {
				m_StringDrawObject = FindTagGameObject<StringDrawObject>(L"StringDrawObject");
			}
			m_StringDrawObject->SetText(FPS);*/

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

			
			P_color = player->getP_color();
			wstring TextureResName;
			switch (P_color) {
			case Yellow:
				TextureResName = L"SUBARU_Y_TX";
				AnimeName = L"Star_Y";
				break;
			case Red:
				TextureResName = L"SUBARU_R_TX";
				AnimeName = L"Star_R";
				break;
			default:
				break;
			}
			wstring Path = App::GetApp()->GetDataDirWString();
			//ファイル名の設定
			wstring StarMap = Path + L"\\Star\\";
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && PointCount == 0) {
				PointDeleteflag = false;
				m_AudioObjectPtr->AddAudioResource(L"TEN_SE");
				m_AudioObjectPtr->Start(L"TEN_SE", 0, 0.3f);
				AddGameObject<StarSS>(StarMap, AnimeName, P_Pos);
				auto a = AddGameObject<P_child>(
					TextureResName,
					true,
					Vec3(0.1f, 1.0f, 0.0f)
					);
				a->setPos(P_Pos);
				PointPos1 = P_Pos;
				PointCount++;
			}
			else if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && PointCount == 1) {
				m_AudioObjectPtr->AddAudioResource(L"TEN_SE");
				m_AudioObjectPtr->Start(L"TEN_SE", 0, 0.3f);
				AddGameObject<StarSS>(StarMap, AnimeName, P_Pos);
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
				m_AudioObjectPtr->AddAudioResource(L"SEN_SE");
				m_AudioObjectPtr->Start(L"SEN_SE", 0, 0.3f);
				CrBar();
				Barflag = false;
				PointDeleteflag = true;
			}

			if (FadeFlag)
			{
				m_FadeSprite->SetFadeFlag(true);
				m_FadeSprite->SetClearFlag(ClearFlag);
				FadeFlag = false;
			}

			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A&&ClearFlag&&FindTagGameObject<Kaguya>(L"Kaguya")->GetTtime()>=3) {
				m_FadeSprite->SetClearFlag(false);
			}


			if (m_FadeSprite->GetChangeFlag())
			{
				if (ClearFlag)
				{
					App::GetApp()->GetScene<Scene>()->SetCTime_Sec(m_Time_Sec);
					App::GetApp()->GetScene<Scene>()->SetCTime_Min(m_Time_Min);
					App::GetApp()->GetScene<Scene>()->SetEnemyBreak(EnemyBreak);
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearResult");
				}
				else
				{
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
				}

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
		float vec = atan2(PointPos1.y - PointPos2.y, PointPos1.x-PointPos2.x);
		Quat qt(Vec3(0, 0, 1), vec);

		float s = ((PointPos2.x - PointPos1.x)*(PointPos2.x - PointPos1.x)) + ((PointPos2.y - PointPos1.y)*(PointPos2.y - PointPos1.y));

		float Scale = sqrt(s);

		if (Scale >= 1.0f) {

			P_color = player->getP_color();

			if (P_color == Yellow && lightbar >= Scale * 5) {
				wstring Path = App::GetApp()->GetDataDirWString();
				//ファイル名の設定
				wstring LineMap = Path + L"\\Line\\";
				//Chaera1の作成
				auto a = AddGameObject<BarSS>(LineMap, L"Yellow_line", Vec3((PointPos2.x + PointPos1.x) / 2, (PointPos2.y + PointPos1.y) / 2, 0), Vec3(Scale*1.3f, 0.2, 1), qt);
				/*auto a = AddGameObject<Bar>(
					L"Skeleton_TX",
					Vec3(Scale, 0.1f, 2.0f),
					Vec3((PointPos2.x + PointPos1.x) / 2, (PointPos2.y + PointPos1.y) / 2, 0),
					qt,
					SquareDrawOption::Normal);*/
				a->AddTag(L"Yellow");
				if (startF) {
					lightbar -= Scale * 5*1.2f;
				}
				startF = true;
				player->setP_LightGage(lightbar);
			}
			else if (P_color == Red && lightbar >= Scale * 10) {
				wstring Path = App::GetApp()->GetDataDirWString();
				//ファイル名の設定
				wstring LineMap = Path + L"\\Line\\";
				//Chaera1の作成
				auto a = AddGameObject<BarSS>(LineMap, L"Red_line", Vec3((PointPos2.x + PointPos1.x) / 2, (PointPos2.y + PointPos1.y) / 2, 0), Vec3(Scale*1.3f, 0.2, 1), qt);
				/*auto a = AddGameObject<Bar>(
					L"Skeleton_TX",
					Vec3(Scale, 0.1f, 2.0f),
					Vec3((PointPos2.x + PointPos1.x) / 2, (PointPos2.y + PointPos1.y) / 2, 0),
					qt,
					SquareDrawOption::Normal);*/
				a->AddTag(L"Red");
				lightbar -= Scale * 10*1.2f;
				player->setP_LightGage(lightbar);
			}
		}
	}

	void GameStage::StartDestroySE() {
		m_AudioObjectPtr->AddAudioResource(L"DEST_SE");
		m_AudioObjectPtr->Start(L"DEST_SE", 0, 0.5f);
	}

	void GameStage::StopBGM() {
		if (App::GetApp()->GetScene<Scene>()->GetStageNumber() == 9) {
			m_AudioObjectPtr->Stop(L"BOSS_BGM");
		}
		else {
			m_AudioObjectPtr->Stop(L"GAMESTAGE_BGM");
		}
	}


	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	void EmptyStage::OnCreate() {
		//メッセージスプライト
		m_MessageSprite = ObjectFactory::Create<MessageSprite>(
			GetThis<Stage>(),
			L"PUSH_A_TX",
			Vec2(200, 200),
			0.0f,
			Vec2(0, -250),
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
