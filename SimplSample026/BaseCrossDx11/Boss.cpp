#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class BossEnemy : public Boss;
	//	用途: ボス
	//--------------------------------------------------------------------------------------
	BossEnemy::BossEnemy(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		Boss(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f),
		m_Posision(Pos)
	{}
	BossEnemy::~BossEnemy() {}

	Vec3 BossEnemy::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void BossEnemy::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//タグの追加
		AddTag(L"Enemy");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(5.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
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

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		Def = m_Rigidbody->m_Pos;
	}
	void BossEnemy::OnUpdate() {
		Startflag = GetStage<GameStage>()->getStartFlag();
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				if (rightMove)
					m_Rigidbody->m_Velocity.x = Speed.x;
				if (!rightMove)
					m_Rigidbody->m_Velocity.x = -Speed.x;
			}
		}
	}

	void BossEnemy::OnUpdate2() {
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				if (m_Rigidbody->m_Pos.x >= m_BaseX) {
					rightMove = false;
				}
				if (m_Rigidbody->m_Pos.x <= -m_BaseX) {
					rightMove = true;
				}
			}
		}

		m_Rigidbody->m_Pos.y = Def.y;
		m_Rigidbody->m_Pos.z = Def.z;

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Destにボックスタグがあるかどうか調べる
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						ThisDelete();
					}
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Blue")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Red")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					auto gamestage = GetStage<GameStage>();
					gamestage->StartDestroySE();
					ThisDelete();
				}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Srcにボックスタグがあるかどうか調べる
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						ThisDelete();
					}
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Blue")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Red")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					auto gamestage = GetStage<GameStage>();
					gamestage->StartDestroySE();
					ThisDelete();
				}
				break;
			}
		}

		if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) - 7) {
			//auto gamestage = GetStage<GameStage>();
			//gamestage->StartDestroySE();
			ThisDelete();
		}

	}

	void BossEnemy::OnDrawShadowmap() {
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


	void BossEnemy::OnDraw() {
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

	void BossEnemy::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<BossEnemy>(GetThis<BossEnemy>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<BossEnemy>());
	}
}