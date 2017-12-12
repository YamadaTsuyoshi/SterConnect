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


	void Kaguya::OnCreate() {
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
		m_PtrObj->m_OwnShadowmapActive = false;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;

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
			Vibration::Instance()->SetVibration(0.25f, 1.0f, 1.0f);
			m_Life += -1;
			m_isNullHit[CntNum] = true;
			m_Interval[CntNum] = time;
		}
	}
	void Kaguya::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (!m_JumpLock) {
			if (!m_UnderRefLock) {
				if (m_HitObj == L"blue") {
					m_Rigidbody->m_BeforePos.y += 0.01f;
					m_Rigidbody->m_Pos.y -= 0.01f;
					m_Rigidbody->m_Velocity += Vec3(0.0f, -1.0f, 0);
					m_UnderRefLock = true;
					m_JumpLock = true;
				}
				else if (m_HitObj == L"yellow") {
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
				if (m_HitObj == L"blue") {
					m_Rigidbody->m_BeforePos.y += 0.01f;
					m_Rigidbody->m_Pos.y += 0.01f;
					m_Rigidbody->m_Velocity += Vec3(0.0f, 15.0f, 0);
					m_JumpLock = true;
				}
				else if (m_HitObj == L"yellow") {
					m_Rigidbody->m_BeforePos.y += 0.01f;
					m_Rigidbody->m_Pos.y += 0.01f;
					m_Rigidbody->m_Velocity += Vec3(0, 10.0f, 0);
					m_JumpLock = true;
				}
				else if (m_HitObj == L"red") {
					m_Rigidbody->m_BeforePos.y += 0.01f;
					m_Rigidbody->m_Pos.y += 0.01f;
					m_Rigidbody->m_Velocity += Vec3(0, 5.0f, 0);
					m_JumpLock = true;
				}
				else if (m_HitObj == L"enemy") {
					//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
					m_Rigidbody->m_BeforePos.y += 0.01f;
					m_Rigidbody->m_Pos.y += 0.01f;
					m_Rigidbody->m_Velocity += Vec3(0, 5.0f, 0);
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
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearResult");
		}
		if (m_Life <= 0) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameover");
		}
		for (int i = 0; i < ARRAYSIZE(m_isNullHit); i++)
		{
			if (m_isNullHit[i])
			{
				float delta = App::GetApp()->GetElapsedTime();
				m_Count[i] += delta;

				if (m_Count[i] > m_Interval[i])
				{
					m_isNullHit[i] = false;
					m_Count[i] = 0;

					if (m_HitObj == L"enemy") {
						m_HitObj = L"Red";
					}
				}
			}
		}
	}

	void Kaguya::OnUpdate2() {
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
				}
				else if (shptr && shptr->FindTag(L"Blue")) {
					m_HitObj = L"blue";
					m_Attackflag = false;
				}
				else if (shptr && shptr->FindTag(L"Red")) {
					m_HitObj = L"red";
					m_Attackflag = true;
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
					m_HitObj = L"enemy";
					SetMutekiTime(3.0f);
				}
				else if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					m_HitObj = L"enemy";
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
				}
				else if (shptr && shptr->FindTag(L"Blue")) {
					m_HitObj = L"blue";
				}
				else if (shptr && shptr->FindTag(L"Red")) {
					m_HitObj = L"red";
				}
				else if (shptr && shptr->FindTag(L"Enemy")) {
					m_HitObj = L"enemy";
					SetMutekiTime(3.0f);
				}
				else if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					m_HitObj = L"enemy";
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




}
//end basecross