#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	球体のプレイヤー実体
	//--------------------------------------------------------------------------------------
	Kaguya::Kaguya(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.4f),
		m_BaseY(-5.0f),
		m_Posision(Pos),
		m_JumpLock(false),
		m_UnderRefLock(false),
		m_LeftRefLock(false),
		m_RightRefLock(false),
		m_HitObj(L""),
		m_Life(5),
		m_Attackflag(false)
	{}
	Kaguya::~Kaguya() {}

	Vec3 Kaguya::GetMoveVector() {
		Vec3 Angle(0, 0, 0);
		auto PtrGameStage = GetStage<GameStage>();
		Vec3 CameraEye, CameraAt;
		PtrGameStage->GetCamera().GetCameraEyeAt(CameraEye, CameraAt);

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0) {
				
			}
		}
		return Angle;
	}

	Vec3 Kaguya::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	bool Kaguya::GetAttack() {
		return m_Attackflag;
	}

	int Kaguya::GetLife() {
		return m_Life;
	}

	void Kaguya::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//タグの追加
		AddTag(L"Kaguya");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 0.75f;
		body.m_Scale = Vec3(1.8f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		m_PtrObj = make_shared<BcDrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_OwnShadowmapActive = true;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;
		m_PtrObj->m_Alpha = 1.0f;

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;


	}
	void Kaguya::SetMutekiTime(float time, int CntNum)
	{
		if (!m_isNullHit[CntNum])
		{
			RndDamageVo();
			Vibration::Instance()->SetVibration(0.25f, 1.0f, 1.0f);
			m_Life += -1;
			m_isNullHit[CntNum] = true;
			m_Interval[CntNum] = time;
		}
	}
	void Kaguya::OnUpdate() {
		StartFlag = GetStage<GameStage>()->getStartFlag();
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		if (StartFlag) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (!m_JumpLock) {
				if (!m_UnderRefLock) {
					if (m_HitObj == L"yellow") {
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y -= 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, -0.5f, 0);
						m_UnderRefLock = true;
						m_JumpLock = true;
					}
					else if (m_HitObj == L"red") {
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y -= 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, -0.1f, 0);
						m_UnderRefLock = true;
						m_JumpLock = true;
					}
					else if (m_HitObj == L"enemy") {
						//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y -= 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, -0.1f, 0);
						m_UnderRefLock = true;
						m_JumpLock = true;
					}
					else if (m_HitObj == L"bamboo") {
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y -= 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, -0.2f, 0);
						m_UnderRefLock = true;
						m_JumpLock = true;
					}
					//if (!m_LeftRefLock) {
					//	m_Rigidbody->m_BeforePos.x += 0.01f;
					//	m_Rigidbody->m_Pos.x += 0.01f;
					//	m_Rigidbody->m_Velocity += Vec3(1.0f, 0.0f, 0);
					////	m_Rigidbody->m_Velocity.x *= -1;
					//	m_LeftRefLock = true;
					//}
					//else if (!m_RightRefLock) {
					//	m_Rigidbody->m_BeforePos.x += 0.01f;
					//	m_Rigidbody->m_Pos.x -= 0.01f;
					//	m_Rigidbody->m_Velocity += Vec3(-1.0f, 0.0f, 0);
					////	m_Rigidbody->m_Velocity.x *= -1;
					//	m_RightRefLock = true;
					//}
				}
				else {
					if (m_HitObj == L"yellow") {
						RndJampVo();
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y += 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, 10.0f / 2, 0);
						m_JumpLock = true;
					}
					else if (m_HitObj == L"red") {
						RndJampVo();
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y += 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, 10.0f / 2, 0);
						m_JumpLock = true;
					}
					else if (m_HitObj == L"enemy") {
						//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y += 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, 5.0f / 2, 0);
						m_JumpLock = true;
					}
					else if (m_HitObj == L"bamboo") {
						m_Rigidbody->m_BeforePos.y += 0.01f;
						m_Rigidbody->m_Pos.y += 0.01f;
						m_Rigidbody->m_Velocity += Vec3(0, 5.0f / 2, 0);
						m_JumpLock = true;
					}
					//if (!m_LeftRefLock) {
					//	m_Rigidbody->m_BeforePos.x += 0.01f;
					//	m_Rigidbody->m_Pos.x += 0.01f;
					//	m_Rigidbody->m_Velocity += Vec3(1.0f, 0.0f, 0);
					//	//	m_Rigidbody->m_Velocity.x *= -1;
					//	m_LeftRefLock = true;
					//}
					//else if (!m_RightRefLock) {
					//	m_Rigidbody->m_BeforePos.x += 0.01f;
					//	m_Rigidbody->m_Pos.x -= 0.01f;
					//	m_Rigidbody->m_Velocity += Vec3(-1.0f, 0.0f, 0);
					//	//	m_Rigidbody->m_Velocity.x *= -1;
					//	m_RightRefLock = true;
					//}
				}

				Vec3 Direction = GetMoveVector();
				if (length(Direction) < 0.1f) {
					m_Rigidbody->m_Velocity.x *= 1.0f;
					m_Rigidbody->m_Velocity.z *= 0.9f;
				}
				else {
					//フォースで変更する場合は以下のように記述
					//m_Rigidbody->m_Force += Direction * 10.0f;
					//速度で変更する場合は以下のように記述
					m_Rigidbody->m_Velocity += Direction * 1.0f;
					Vec2 TempVelo(m_Rigidbody->m_Velocity.x, m_Rigidbody->m_Velocity.z);
					TempVelo = XMVector2ClampLength(TempVelo, 0, 5.0f);
					m_Rigidbody->m_Velocity.x = TempVelo.x;
					m_Rigidbody->m_Velocity.z = TempVelo.y;
				}
			}
			m_Rigidbody->m_Force += m_Rigidbody->m_Gravity * m_Rigidbody->m_Mass;

			if (m_Rigidbody->m_Pos.y >= 85) {
				auto gamestage = GetStage<GameStage>();
				gamestage->StopBGM();
				gamestage->FadeFlag = true;
				gamestage->ClearFlag = true;
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearResult");
			}
			if (m_Life <= 0) {
				auto gamestage = GetStage<GameStage>();
				gamestage->StopBGM();
				m_AudioObjectPtr->AddAudioResource(L"VOICE_SONNAA");
				m_AudioObjectPtr->Start(L"VOICE_SONNAA", 0, 0.5f);
				gamestage->FadeFlag = true;
				//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
			}
			for (int i = 0; i < ARRAYSIZE(m_isNullHit); i++)
			{
				if (m_isNullHit[i])
				{
					float delta = App::GetApp()->GetElapsedTime();
					m_Count[i] += delta;

					if (m_HitObj == L"enemy") {
						m_HitObj = L"Red";
					}

					if (m_Alphaflag) {
						m_PtrObj->m_Alpha += -0.3f;
					}
					else if (!m_Alphaflag) {
						m_PtrObj->m_Alpha += 0.3f;
					}

					if (m_PtrObj->m_Alpha >= 1.0f) {
						m_Alphaflag = true;
					}
					else if (m_PtrObj->m_Alpha <= 0.4f) {
						m_Alphaflag = false;
					}

					if (m_Count[i] > m_Interval[i])
					{
						m_isNullHit[i] = false;
						m_Count[i] = 0;
						m_PtrObj->m_Alpha = 1.0f;
					}
				}
			}
		}
	}

	void Kaguya::OnUpdate2() {
		if (StartFlag) {
			if (m_Rigidbody->m_Pos.y <= m_BaseY) {
				m_Rigidbody->m_Pos.y = m_BaseY;
				m_Rigidbody->m_Velocity.y = 0;
				m_JumpLock = false;
			}

			if (m_Rigidbody->m_Pos.x >= m_BaseX) {
				m_Rigidbody->m_Pos.x = m_BaseX;
				m_Rigidbody->m_Velocity.x *= -1;
			}
			else if (m_Rigidbody->m_Pos.x <= -m_BaseX) {
				m_Rigidbody->m_Pos.x = -m_BaseX;
				m_Rigidbody->m_Velocity.x *= -1;
			}
			m_HitObj = L"";

			auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
			for (auto& v : StateVec) {
				if (v.m_Src == m_Rigidbody.get()) {
					//Destにボックスタグがあるかどうか調べる
					auto shptr = v.m_Dest->m_Owner.lock();
					if (shptr && shptr->FindTag(L"Yellow")) {
						m_HitObj = L"yellow";
						m_Attackflag = false;
						shared_ptr<Bar> a = dynamic_pointer_cast<Bar>(shptr);
						a->SetD_flag(true);
					}
					else if (shptr && shptr->FindTag(L"Red")) {
						m_HitObj = L"red";
						m_Attackflag = true;
						shared_ptr<Bar> a = dynamic_pointer_cast<Bar>(shptr);
						a->SetD_flag(true);
					}
					else if (shptr && shptr->FindTag(L"Bamboo")) {
						m_HitObj = L"bamboo";
						//m_Attackflag = false;
					}
					else if (shptr && shptr->FindTag(L"BambooB")) {
						m_HitObj = L"bamboo";
						//m_Attackflag = false;
					}
					if (shptr && shptr->FindTag(L"Enemy")) {
						m_HitObj = L"enemy";
						if (m_Attackflag) {
							break;
						}
						SetMutekiTime(3.0f);
					}
					else if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
						m_HitObj = L"enemy";
						if (m_Attackflag) {
							break;
						}
						SetMutekiTime(3.0f);
					}
					m_JumpLock = false;
					break;
				}
				if (v.m_Dest == m_Rigidbody.get()) {
					//Srcにボックスタグがあるかどうか調べる
					auto shptr = v.m_Src->m_Owner.lock();
					if (shptr && shptr->FindTag(L"Yellow")) {
						m_HitObj = L"yellow";
						m_Attackflag = false;
						shared_ptr<Bar> a = dynamic_pointer_cast<Bar>(shptr);
						a->SetD_flag(true);
					}
					else if (shptr && shptr->FindTag(L"Red")) {
						m_HitObj = L"red";
						m_Attackflag = true;
						shared_ptr<Bar> a = dynamic_pointer_cast<Bar>(shptr);
						a->SetD_flag(true);
					}
					else if (shptr && shptr->FindTag(L"Bamboo")) {
						m_HitObj = L"yellow";
						//m_Attackflag = false;
					}
					else if (shptr && shptr->FindTag(L"BambooB")) {
						m_HitObj = L"yellow";
						//m_Attackflag = false;
					}
					else if (shptr && shptr->FindTag(L"Enemy")) {
						m_HitObj = L"enemy";
						if (m_Attackflag) {
							break;
						}
						SetMutekiTime(3.0f);
					}
					else if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
						m_HitObj = L"enemy";
						if (m_Attackflag) {
							break;
						}
						SetMutekiTime(3.0f);
					}
					m_JumpLock = false;
					break;
				}
			}

			auto LenVec = m_Rigidbody->m_Pos - m_Rigidbody->m_BeforePos;
			if (LenVec.y > 0) {
				m_UnderRefLock = false;
			}
			//if (LenVec.x < 0) {
			//	m_LeftRefLock = false;
			//}
			//if (LenVec.x > 0) {
			//	m_RightRefLock = false;
			//}
			LenVec.y = 0;
			//プレイヤーのＺ位置は強制的に0.0にする
			m_Rigidbody->m_Pos.z = 0.0f;
			AddTag(L"Kaguya");
		}
	}

	void Kaguya::OnDrawShadowmap() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}

	void Kaguya::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			auto PtrGameStage = GetStage<GameStage>();
			shptr = PtrGameStage->FindTagGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	void Kaguya::RndJampVo()
	{
		int i;
		i = GetRandom(0, 3);
		switch (i)
		{
		case 0:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_EI");
			m_AudioObjectPtr->Start(L"VOICE_EI", 0, 0.5f);
			break;
		case 1:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_TOU");
			m_AudioObjectPtr->Start(L"VOICE_TOU", 0, 0.5f);
			break;
		case 2:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_YAA");
			m_AudioObjectPtr->Start(L"VOICE_YAA", 0, 0.5f);
			break;
		case 3:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_YO");
			m_AudioObjectPtr->Start(L"VOICE_YO", 0, 0.5f);
			break;
		default:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_TOU");
			m_AudioObjectPtr->Start(L"VOICE_TOU", 0, 0.5f);
			break;
		}
	}
	void Kaguya::RndDamageVo()
	{
		int i;
		i = GetRandom(0, 2);
		switch (i)
		{
		case 0:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_UU");
			m_AudioObjectPtr->Start(L"VOICE_UU", 0, 0.5f);
			break;
		case 1:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_HYAA");
			m_AudioObjectPtr->Start(L"VOICE_HYAA", 0, 0.5f);
			break;
		case 2:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_NANISURUNO");
			m_AudioObjectPtr->Start(L"VOICE_NANISURUNO", 0, 0.5f);
			break;
		default:
			m_AudioObjectPtr->AddAudioResource(L"VOICE_HYAA");
			m_AudioObjectPtr->Start(L"VOICE_HYAA", 0, 0.5f);
			break;
		}
	}

	int Kaguya::GetRandom(int min, int max)
	{
		static int flag;

		if (flag == 0) {
			srand((unsigned int)time(NULL));
			flag = 1;
		}

		return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
	}

	//--------------------------------------------------------------------------------------
	//	かぐやスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
	KaguyaSS::KaguyaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir) :
		SS5ssae(StagePtr, BaseDir, L"kaguyaanimeyou.ssae", L"clear")
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 1.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void KaguyaSS::OnCreate() {

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(0.7f, 0.7f, 1.0f);
		//PtrT->SetPosition(Vec3(0, 5.0f, 1.0f));
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(5.0f);

		//ChangeAnimation(L"run");
		SetLooped(true);
		

	}

	//更新
	void KaguyaSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		auto PtrGameStage = GetStage<GameStage>();
		GetTransform()->SetPosition(PtrGameStage->GetKaguyaPos());
		UpdateAnimeTime(ElapsedTime);
	}

	//--------------------------------------------------------------------------------------
	//	かぐやスプライトスタジオ（ゲームオーバー）
	//--------------------------------------------------------------------------------------
	//構築と破棄
	GameoverKaguyaSS::GameoverKaguyaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir) :
		SS5ssae(StagePtr, BaseDir, L"GameOver_Kaguya.ssae", L"Anime")
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 1.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void GameoverKaguyaSS::OnCreate() {

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(3.0f, 3.0f, 1.0f);
		//PtrT->SetPosition(Vec3(0, 5.0f, 1.0f));
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(60.0f);

		//ChangeAnimation(L"run");
		SetLooped(true);


	}

	//更新
	void GameoverKaguyaSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		GetTransform()->SetPosition(Vec3(2.0f,0.0f,1.0f));
		UpdateAnimeTime(ElapsedTime);
	}

}
//end basecross