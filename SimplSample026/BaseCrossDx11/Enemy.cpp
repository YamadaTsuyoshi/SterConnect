#include "stdafx.h"
#include "Project.h"


namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Rabbit : public Enemy;
	//	�p�r: �E�T�M�̓G
	//--------------------------------------------------------------------------------------
	Rabbit::Rabbit(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		Enemy(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f),
		m_Posision(Pos)
	{}
	Rabbit::~Rabbit() {}

	Vec3 Rabbit::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void Rabbit::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//���b�V���̍쐬�i�ύX�ł��Ȃ��j
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//�^�O�̒ǉ�
		AddTag(L"Enemy");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(1.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//�s��̒�`
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

		//�V���h�E�}�b�v�`��f�[�^�̍\�z
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//�`��f�[�^�̍s����R�s�[
		m_PtrShadowmapObj->m_WorldMatrix = World;

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		wstring Path = App::GetApp()->GetDataDirWString();

		//�t�@�C�����̐ݒ�
		wstring Map = Path + L"\\Enemy\\";

		GetStage<Stage>()->AddGameObject<RabbitSS>(Map, m_Posision);

	}
	void Rabbit::OnUpdate() {
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

	void Rabbit::OnUpdate2() {
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				if (m_Rigidbody->m_Pos.x >= m_BaseX) {
					rightMove = false;
				}
				if (m_Rigidbody->m_Pos.x <= -m_BaseX) {
					rightMove = true;
				}
				float ElapsedTime = App::GetApp()->GetElapsedTime();
				Time += ElapsedTime;
				if (Time > 4.0f&&Startflag) {
					Vec3 v = m_Rigidbody->m_Pos;
					v.y -= 0.8f;
					GetStage<Stage>()->AddGameObject<RabbitBullet>(
						L"RABBIT_BULLET_TX",
						true,
						v
						);
					Time = 0;
				}
			}
		}

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Dest�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
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
				//Src�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
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

	void Rabbit::OnDrawShadowmap() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//�`��f�[�^�̍s����R�s�[
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}


	void Rabbit::OnDraw() {
		//�s��̒�`
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

	void Rabbit::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerk�̑��o
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<Rabbit>(GetThis<Rabbit>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<Rabbit>());
	}
	//--------------------------------------------------------------------------------------
	//	class RabbitBullet : public Bullet;
	//	�p�r: �E�T�M�̓G�����e
	//--------------------------------------------------------------------------------------
	RabbitBullet::RabbitBullet(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		Bullet(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.65f),
		m_BaseY(0.25f / 2.0f),
		m_Posision(Pos)
	{}
	RabbitBullet::~RabbitBullet() {}

	Vec3 RabbitBullet::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void RabbitBullet::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//���b�V���̍쐬�i�ύX�ł��Ȃ��j
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//�^�O�̒ǉ�
		AddTag(L"Enemy_Bullet");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(0.3f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
		body.SetToBefore();
		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//�s��̒�`
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

		//�V���h�E�}�b�v�`��f�[�^�̍\�z
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//�`��f�[�^�̍s����R�s�[
		m_PtrShadowmapObj->m_WorldMatrix = World;

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}
	void RabbitBullet::OnUpdate() {
		m_Rigidbody->m_Velocity.y = -Speed.y;
	}

	void RabbitBullet::OnUpdate2() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Time += ElapsedTime;
		if (Time > 5.0f) {
			ThisDelete();
		}

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Dest�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					ThisDelete();
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Blue")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Red")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					Speed.y *= -1;
				}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Src�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					ThisDelete();
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Blue")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Red")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
					Speed.y *= -1;
				}
				if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					Speed.y *= -1;
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

	void RabbitBullet::OnDrawShadowmap() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//�`��f�[�^�̍s����R�s�[
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}


	void RabbitBullet::OnDraw() {
		//�s��̒�`
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

	void RabbitBullet::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerk�̑��o
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<RabbitBullet>(GetThis<RabbitBullet>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<RabbitBullet>());
	}

	//--------------------------------------------------------------------------------------
	//	class KineRabbit : public Enemy;
	//	�p�r: �n�����E�T�M�̓G
	//--------------------------------------------------------------------------------------
	KineRabbit::KineRabbit(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		Enemy(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f),
		m_Posision(Pos)
	{}
	KineRabbit::~KineRabbit() {}

	Vec3 KineRabbit::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void KineRabbit::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//���b�V���̍쐬�i�ύX�ł��Ȃ��j
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//�^�O�̒ǉ�
		AddTag(L"Enemy");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(1.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//�s��̒�`
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

		//�V���h�E�}�b�v�`��f�[�^�̍\�z
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//�`��f�[�^�̍s����R�s�[
		m_PtrShadowmapObj->m_WorldMatrix = World;

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		wstring Path = App::GetApp()->GetDataDirWString();

		//�t�@�C�����̐ݒ�
		wstring Map = Path + L"\\Enemy\\";

		GetStage<Stage>()->AddGameObject<KineRabbitSS>(Map, m_Posision);

	}
	void KineRabbit::OnUpdate() {
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

	void KineRabbit::OnUpdate2() {
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

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Dest�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
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
				//Src�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
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

	void KineRabbit::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerk�̑��o
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<KineRabbit>(GetThis<KineRabbit>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<KineRabbit>());
	}

	void KineRabbit::OnDrawShadowmap() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//�`��f�[�^�̍s����R�s�[
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}


	void KineRabbit::OnDraw() {
		//�s��̒�`
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


	//--------------------------------------------------------------------------------------
	//	�������X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	RabbitSS::RabbitSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"WhiteRabbit.ssae", L"fly_full"),
		m_Posision(Pos),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//������
	void RabbitSS::OnCreate() {

		//�^�O�̒ǉ�
		AddTag(L"Enemy");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(1.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(0.35f, 0.35f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(30.0f);

		//ChangeAnimation(L"run");
		SetLooped(false);


	}

	//�X�V
	void RabbitSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Startflag = GetStage<GameStage>()->getStartFlag();
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				if (rightMove) {
					m_Rigidbody->m_Velocity.x = Speed.x;
				}
				if (!rightMove) {
					m_Rigidbody->m_Velocity.x = -Speed.x;
				}
				if (IsAnimeEnd()&&Startflag&&Bulletflag2) {
					Vec3 v = m_Rigidbody->m_Pos;
					v.y -= 0.8f;
					GetStage<Stage>()->AddGameObject<RabbitBullet>(
						L"RABBIT_BULLET_TX",
						true,
						v
						);
					Bulletflag2 = false;
				}
				BulletTime += ElapsedTime;
				if (IsAnimeEnd()&&!Bulletflag)
				{
					wstring Anime = L"fly_-";
					Anime += Util::FloatToWStr(BulletCount);
				if (BulletCount == 0)
				{
					Anime = L"fly_full";
					ChangeAnimation(Anime);
					SetLooped(true);
					Bulletflag = true;
				}
					else if (BulletCount == 6)
					{
						Anime += L"_0";
						ChangeAnimation(Anime);
						SetLooped(true);
					}
					else {
						ChangeAnimation(Anime);
						SetLooped(true);
						Bulletflag = true;
					}
					if (BulletCount < 6) {
						BulletCount++;
					}
				}
				else if (Bulletflag&&BulletTime>=5)
				{
					BulletTime = 0;
					wstring Anime = L"Throw_";
					Anime += Util::FloatToWStr(BulletCount);
					if (BulletCount == 6)
					{
						ChangeAnimation(Anime);
						SetLooped(false);
						Bulletflag = false;
						Bulletflag2 = true;
					}
					else {
						ChangeAnimation(Anime);
						SetLooped(false);
						Bulletflag = false;
						Bulletflag2 = true;
					}
				}
			}
		}
		auto PtrT = GetTransform();
		PtrT->SetPosition(m_Rigidbody->m_Pos);
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
	}

	void RabbitSS::OnUpdate2() {
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

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Dest�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						gamestage->EnemyBreak++;
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
					gamestage->EnemyBreak++;
					ThisDelete();
				}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Src�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						gamestage->EnemyBreak++;
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
					gamestage->EnemyBreak++;
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


	void RabbitSS::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerk�̑��o
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<RabbitSS>(GetThis<RabbitSS>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<RabbitSS>());
	}

	//--------------------------------------------------------------------------------------
	//	�n�������X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	KineRabbitSS::KineRabbitSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"kineusa_Sp.ssae", L"attack"),
		m_Posision(Pos),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 1.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//������
	void KineRabbitSS::OnCreate() {

		//�^�O�̒ǉ�
		AddTag(L"Enemy");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(1.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(0.35f, 0.35f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(10.0f);

		//ChangeAnimation(L"run");
		SetLooped(true);


	}

	//�X�V
	void KineRabbitSS::OnUpdate() {

		Startflag = GetStage<GameStage>()->getStartFlag();
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				if (rightMove)
					m_Rigidbody->m_Velocity.x = Speed.x;
				if (!rightMove)
					m_Rigidbody->m_Velocity.x = -Speed.x;
			}
		}

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrT = GetTransform();
		PtrT->SetPosition(m_Rigidbody->m_Pos);
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
	}

	void KineRabbitSS::OnUpdate2() {
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

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Dest�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						gamestage->EnemyBreak++;
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
					gamestage->EnemyBreak++;
					ThisDelete();
				}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Src�Ƀ{�b�N�X�^�O�����邩�ǂ������ׂ�
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						gamestage->EnemyBreak++;
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
					gamestage->EnemyBreak++;
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

	void KineRabbitSS::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerk�̑��o
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<KineRabbitSS>(GetThis<KineRabbitSS>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<KineRabbitSS>());
	}
}
//end basecross