/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//class MultiSpark : public MultiParticle;
	//�p�r: �����̃X�p�[�N�N���X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	MultiSpark::MultiSpark(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiSpark::~MultiSpark() {}

	//������
	void MultiSpark::OnCreate() {
		//���Z�`�揈��������
		SetAddType(true);
		//�^�O�̒ǉ�
		AddTag(L"MultiSpark");
	}


	void MultiSpark::InsertSpark(const Vec3& Pos) {
		auto ParticlePtr = InsertParticle(64);
		ParticlePtr->m_EmitterPos = Pos;
		ParticlePtr->SetTextureResource(L"SPARK_TX");
		ParticlePtr->m_MaxTime = 0.5f;
		vector<ParticleSprite>& pSpriteVec = ParticlePtr->GetParticleSpriteVec();
		for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalScale = Vec2(0.2, 0.2);
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 30.0f,
				rParticleSprite.m_LocalPos.y * 30.0f,
				rParticleSprite.m_LocalPos.z * 30.0f
			);
			//�F�̎w��
			int r = (int)((Util::RandZeroToOne() * 0.5f + 0.3f) * 256.0f);
			int g = (int)((Util::RandZeroToOne() * 0.5f + 0.3f) * 256.0f);
			int b = (int)((Util::RandZeroToOne() * 0.5f + 0.3f) * 256.0f);
			r = r >> 7;
			g = g >> 7;
			b = b >> 7;
			rParticleSprite.m_Color = Col4((float)r, (float)g, (float)b, 1.0f);
		}
	}

	void MultiSpark::OnUpdate() {
		MultiParticle::OnUpdate();
		float ElapsedTime = App::GetApp()->GetElapsedTime();

		for (auto ParticlePtr : GetParticleVec()) {
			for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
				if (rParticleSprite.m_Active) {
					rParticleSprite.m_Color += 0.01f;
					rParticleSprite.m_Color.w = 1.0f;
					if (rParticleSprite.m_Color.x >= 1.0f) {
						rParticleSprite.m_Color.x = 1.0f;
					}
					if (rParticleSprite.m_Color.y >= 1.0f) {
						rParticleSprite.m_Color.y = 1.0f;
					}
					if (rParticleSprite.m_Color.z >= 1.0f) {
						rParticleSprite.m_Color.z = 1.0f;
					}
				}
			}
		}

	}


	//--------------------------------------------------------------------------------------
	//class MultiFire : public MultiParticle;
	//�p�r: �����̉��N���X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	MultiFire::MultiFire(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiFire::~MultiFire() {}

	//������
	void MultiFire::OnCreate() {
		//�^�O�̒ǉ�
		AddTag(L"MultiFire");
	}

	void MultiFire::InsertFire(const Vec3& Pos) {
		auto ParticlePtr = InsertParticle(16);
		ParticlePtr->m_EmitterPos = Pos;
		ParticlePtr->SetTextureResource(L"FIRE_TX");
		ParticlePtr->m_MaxTime = 0.5f;
		vector<ParticleSprite>& pSpriteVec = ParticlePtr->GetParticleSpriteVec();
		for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 5.0f,
				rParticleSprite.m_LocalPos.y * 5.0f,
				rParticleSprite.m_LocalPos.z * 5.0f
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}


	//--------------------------------------------------------------------------------------
	///	�V���v����3D��̕���
	//--------------------------------------------------------------------------------------
	void SimpleSquare::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//�\�z�Ɣj��
	SimpleSquare::SimpleSquare(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option):
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	SimpleSquare::~SimpleSquare() {}

	//������
	void SimpleSquare::OnCreate() {
		CreateBuffers(5.0f, 30.0f);

		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		//body.m_IsDrawActive = true;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void SimpleSquare::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void SimpleSquare::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//�J�����̈ʒu
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}
	}

	void SimpleSquare::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	//--------------------------------------------------------------------------------------
	///	3D��̕���
	//--------------------------------------------------------------------------------------
	void SquareSprite::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//�\�z�Ɣj��
	SquareSprite::SquareSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	SquareSprite::~SquareSprite() {}

	//������
	void SquareSprite::OnCreate() {
		CreateBuffers(1.0f, 1.0f);

		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = true;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void SquareSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void SquareSprite::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//�J�����̈ʒu
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}
	}

	void SquareSprite::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	//--------------------------------------------------------------------------------------
	///	�V���v����3D��̃{�b�N�X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	SimpleBox::SimpleBox(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(),
		m_Pos(Pos)
	{}
	SimpleBox::~SimpleBox() {}

	//������
	void SimpleBox::OnCreate() {

		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		//���b�V���̎擾
		auto MeshPtr = App::GetApp()->GetResource<MeshResource>(L"DEFAULT_PCT_BOX");

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = MeshPtr;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void SimpleBox::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	//--------------------------------------------------------------------------------------
	///	���b�s���O�������ꂽ�X�v���C�g
	//--------------------------------------------------------------------------------------
	SpriteBase::SpriteBase(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, 
		const Vec2& StartScale, 
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(StartScale),
		m_Rot(StartRot),
		m_Pos(StartPos),
		m_XWrap(XWrap),
		m_YWrap(YWrap),
		m_Emissive(0,0,0,0),
		m_BlendState(BlendState::Opaque)
	{}
	void SpriteBase::OnCreate() {
		float HelfSize = 0.5f;
		//���_�z��(�c���w�萔���\��)
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2((float)m_XWrap, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, (float)m_YWrap)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2((float)m_XWrap, (float)m_YWrap)) },
		};
		//���_�̏����C���i���z�֐��Ăт����j
		AdjustVertex();
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);
	}

	void SpriteBase::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"WrappedSprite::UpdateVertex()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//���z�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);
	}



	void SpriteBase::OnDraw() {
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//���[���h�s��̌���
		Mat4x4 World;
		World.affineTransformation2D(
			m_Scale,			//�X�P�[�����O
			Vec2(0, 0),		//��]�̒��S�i�d�S�j
			m_Rot,				//��]�p�x
			m_Pos				//�ʒu
		);
		//�ˉe�s��̌���
		float w = static_cast<float>(App::GetApp()->GetGameWidth());
		float h = static_cast<float>(App::GetApp()->GetGameHeight());
		Mat4x4 Proj(XMMatrixOrthographicLH(w, h, -1.0, 1.0f));
		//�s��̍���
		World *= Proj;
		//�R���X�^���g�o�b�t�@�̏���
		SpriteConstantBuffer sb;
		//�G�~�b�V�u���Z�B
		sb.Emissive = m_Emissive;
		//�s��̐ݒ�
		sb.World = World;
		//�R���X�^���g�o�b�t�@�̍X�V
		pD3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);

		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = sizeof(VertexPositionColorTexture);
		UINT offset = 0;
		//���_�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, m_SquareMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetIndexBuffer(m_SquareMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//�`����@�i3�p�`�j
		pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//���_�V�F�[�_�ɓn��
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�V�F�[�_�̐ݒ�
		pD3D11DeviceContext->VSSetShader(VSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		pD3D11DeviceContext->PSSetShader(PSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pD3D11DeviceContext->IASetInputLayout(VSPCTSprite::GetPtr()->GetInputLayout());
		//�u�����h�X�e�[�g
		switch (m_BlendState) {
		case BlendState::Opaque:
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
			break;
		case BlendState::Trace:
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
			break;
		case BlendState::Additive:
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetAdditive(), nullptr, 0xffffffff);
			break;
		}
		//�f�v�X�X�e���V���X�e�[�g
		pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthNone(), 0);
		//���X�^���C�U�X�e�[�g
		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());

		//�e�N�X�`���ƃT���v���[�̐ݒ�
		ID3D11ShaderResourceView* pNull[1] = { 0 };
		pD3D11DeviceContext->PSSetShaderResources(0, 1, TexPtr->GetShaderResourceView().GetAddressOf());
		//���b�s���O�T���v���[
		ID3D11SamplerState* pSampler = RenderState->GetLinearWrap();
		pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);

		//�`��
		pD3D11DeviceContext->DrawIndexed(m_SquareMesh->GetNumIndicis(), 0, 0);
		//��n��
		Dev->InitializeStates();
	}
	//--------------------------------------------------------------------------------------
	///	��]����X�v���C�g
	//--------------------------------------------------------------------------------------
	RotateSprite::RotateSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, 
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap):
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Additive);
	}

	void RotateSprite::AdjustVertex() {
		//���_�F��ύX����
		for (size_t i = 0; i < m_BackupVertices.size();i++) {
			switch (i) {
			case 0:
				m_BackupVertices[i].color = Col4(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			case 1:
				m_BackupVertices[i].color = Col4(0.0f, 1.0f, 0.0f, 1.0f);
				break;
			case 2:
				m_BackupVertices[i].color = Col4(0.0f, 0.0f, 1.0f, 1.0f);
				break;
			case 3:
				m_BackupVertices[i].color = Col4(1.0f, 1.0f, 0, 1.0);
				break;
			}
		}
	}

	void RotateSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_Rot += ElapsedTime;
		if (m_Rot >= XM_2PI) {
			m_Rot = 0;
		}
		m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}


	}

	//--------------------------------------------------------------------------------------
	///	�X�v���C�g
	//--------------------------------------------------------------------------------------
	StageSprite::StageSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void StageSprite::AdjustVertex() {
		//�����ł͉������Ȃ�
	}

	void  StageSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}

	//--------------------------------------------------------------------------------------
	///	���b�Z�[�W��\������X�v���C�g
	//--------------------------------------------------------------------------------------
	MessageSprite::MessageSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void MessageSprite::AdjustVertex() {
		//�����ł͉������Ȃ�
	}

	void  MessageSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, sin_val);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}

	//--------------------------------------------------------------------------------------
	///	Bar
	//--------------------------------------------------------------------------------------
	void Bar::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//�\�z�Ɣj��
	Bar::Bar(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	Bar::~Bar() {}

	//������
	void Bar::OnCreate() {
		CreateBuffers(1.0f, 1.0f);

		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void Bar::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void Bar::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext(); 
		Time += ElapsedTime;
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//�J�����̈ʒu
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}

		if (Time >5.0f) {
			ThisDelete();
		}
	}

	void Bar::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	void Bar::ThisDelete()
	{
		GetStage<GameStage>()->RemoveGameObject<Bar>(GetThis<Bar>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<Bar>());
	}

	//--------------------------------------------------------------------------------------
	///	Wall
	//--------------------------------------------------------------------------------------
	void Wall::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//�\�z�Ɣj��
	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	Wall::~Wall() {}

	//������
	void Wall::OnCreate() {
		CreateBuffers(1.0f, 20.0f);
		AddTag(L"Wall");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void Wall::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void Wall::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		//auto PtrStage = GetStage<Stage>();
		////�J�����̈ʒu
		//Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		//Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		//m_Pos.y = CameraEye.y;
		//switch (m_DrawOption) {
		//case SquareDrawOption::Billboard:
		//{
		//	m_Qt.facing(CameraAt - CameraEye);
		//}
		//break;
		//case SquareDrawOption::Faceing:
		//{
		//	m_Qt.facing(m_Pos - CameraEye);
		//}
		//break;
		//case SquareDrawOption::FaceingY:
		//	m_Qt.facingY(m_Pos - CameraEye);
		//	break;
		//default:
		//	m_Qt.normalize();
		//	break;
		//}
		
	}

	void Wall::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	///	BG
	//--------------------------------------------------------------------------------------
	void BG::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//�\�z�Ɣj��
	BG::BG(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	BG::~BG() {}

	//������
	void BG::OnCreate() {
		CreateBuffers(1.0f, 1.0f);
		AddTag(L"BG");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();

		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void BG::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void BG::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//�J�����̈ʒu
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		m_Pos.y = CameraEye.y;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}

	}

	void BG::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	/// LightGage
	//--------------------------------------------------------------------------------------
	LightGage_F::LightGage_F(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void LightGage_F::AdjustVertex() {
		//�����ł͉������Ȃ�
	}

	void  LightGage_F::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}

	//--------------------------------------------------------------------------------------
	/// LightGage_Bar
	//--------------------------------------------------------------------------------------
	LightGage_B::LightGage_B(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void LightGage_B::AdjustVertex() {
		//�����ł͉������Ȃ�
	}

	void  LightGage_B::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}

	}

	void LightGage_B::OnUpdate()
	{
		auto player = GetStage<GameStage>()->FindTagGameObject<Player>(L"Player");
		float HP = player->getP_LightGage();
		float MaxHP = player->getP_MaxLightGage();
		float Width = HP / MaxHP;
		this->m_Scale = Vec2(278.0f* Width, 6.0f);
		if (!(w== Width)) {
			float a = (278.0f - 278.0f * Width)*0.5f;
			this->m_Pos.x = 502-a;
			w = Width;
		}
		if (Width>0.2)
		this->m_TextureResName= wstring(L"LIGHTGAGE_B_TX");
		else
		this->m_TextureResName = wstring(L"LIGHTGAGE_B_R_TX");
	}

	//--------------------------------------------------------------------------------------
	/// Life
	//--------------------------------------------------------------------------------------
	Life::Life(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void Life::AdjustVertex() {
		//�����ł͉������Ȃ�
	}

	void  Life::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}

	//--------------------------------------------------------------------------------------
	///	Goal
	//--------------------------------------------------------------------------------------
	void Goal::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//�\�z�Ɣj��
	Goal::Goal(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	Goal::~Goal() {}

	//������
	void Goal::OnCreate() {
		CreateBuffers(1.0f, 1.0f);

		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void Goal::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void Goal::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		Time += ElapsedTime;
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//�J�����̈ʒu
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}
	}

	void Goal::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	void Goal::ThisDelete()
	{
		GetStage<GameStage>()->RemoveGameObject<Bar>(GetThis<Bar>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<Bar>());
	}

	//--------------------------------------------------------------------------------------
	///	�|
	//--------------------------------------------------------------------------------------
	void Bamboo::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//���b�V���̍쐬�i�ύX�ł���j
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//�\�z�Ɣj��
	Bamboo::Bamboo(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	Bamboo::~Bamboo() {}

	//������
	void Bamboo::OnCreate() {
		CreateBuffers(1.0f,1.0f);
		AddTag(L"Bamboo");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();

		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//�`��f�[�^�̍\�z
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void Bamboo::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void Bamboo::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//���_�̕ύX
		//D3D11_MAP_WRITE_DISCARD�͏d�v�B���̏����ɂ��AGPU�Ɏז�����Ȃ�
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//���_�̃}�b�v
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map���s
			throw BaseException(
				L"���_��Map�Ɏ��s���܂����B",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//���_�̕ύX
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//�֐��Ăяo��
		UpdateVertex(ElapsedTime, vertices);
		//�A���}�b�v
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		//auto PtrStage = GetStage<Stage>();
		////�J�����̈ʒu
		//Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		//Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		//m_Pos.y = CameraEye.y;
		//switch (m_DrawOption) {
		//case SquareDrawOption::Billboard:
		//{
		//	m_Qt.facing(CameraAt - CameraEye);
		//}
		//break;
		//case SquareDrawOption::Faceing:
		//{
		//	m_Qt.facing(m_Pos - CameraEye);
		//}
		//break;
		//case SquareDrawOption::FaceingY:
		//	m_Qt.facingY(m_Pos - CameraEye);
		//	break;
		//default:
		//	m_Qt.normalize();
		//	break;
		//}

	}

	void Bamboo::OnDraw() {
		//�s��̒�`
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

}
//end basecross
