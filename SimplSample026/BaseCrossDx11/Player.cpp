/*!
@file Player.cpp
@brief �v���C���[����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	���̂̃v���C���[����
	//--------------------------------------------------------------------------------------
	Player::Player(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseY(0.25f / 2.0f),
		m_Posision(Pos),
		m_JumpLock(false)
	{}
	Player::~Player() {}

	Vec3 Player::GetMoveVector() {
		Vec3 Angle(0, 0, 0);
		auto PtrGameStage = GetStage<GameStage>();
		//Vec3 CameraEye, CameraAt;
		//PtrGameStage->GetCamera().GetCameraEyeAt(CameraEye, CameraAt);

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0|| CntlVec[0].fThumbLY != 0) {
				float MoveLength = 0;	//���������̃X�s�[�h
										//�i�s�����̌������v�Z
				//Vec3 Front = m_Rigidbody->m_Pos - CameraEye;
				//Front.z = 0;
				//Front.normalize();
				////�i�s������������̊p�x���Z�o
				//float FrontAngle = atan2(Front.z, Front.x);
				////�R���g���[���̌����v�Z
				//float MoveX = CntlVec[0].fThumbLX;
				//float MoveY = CntlVec[0].fThumbLY;
				//Vec2 MoveVec(MoveX, MoveY);
				//float MoveSize = length(MoveVec);
				////�R���g���[���̌�������p�x���v�Z
				//float CntlAngle = atan2(MoveX, MoveY);
				////�g�[�^���̊p�x���Z�o
				//float TotalAngle = FrontAngle + CntlAngle;
				////�p�x����x�N�g�����쐬
				//Angle = Vec3(sin(TotalAngle), cos(TotalAngle), 0);
				////���K������
				//Angle.normalize();
				////�ړ��T�C�Y��ݒ�B
				//Angle *= MoveSize;
				////Y���͕ω������Ȃ�
				//Angle.z = 0;

				Vec3 Front = m_Rigidbody->m_Pos;
				Front.z = 0;
				Front.normalize();
				//�i�s������������̊p�x���Z�o
				//float FrontAngle = atan2(Front.z, Front.x);
				//�R���g���[���̌����v�Z
				float MoveX = CntlVec[0].fThumbLX;
				float MoveY = CntlVec[0].fThumbLY;
				Vec2 MoveVec(MoveX, MoveY);
				float MoveSize = length(MoveVec);
				//�R���g���[���̌�������p�x���v�Z
				float CntlAngle = atan2(MoveX, MoveY);
				//�g�[�^���̊p�x���Z�o
				float TotalAngle =+ CntlAngle;
				//�p�x����x�N�g�����쐬
				Angle = Vec3(sin(TotalAngle), cos(TotalAngle), 0);
				//���K������
				Angle.normalize();
				//�ړ��T�C�Y��ݒ�B
				Angle *= MoveSize;
				//Y���͕ω������Ȃ�
				Angle.z = 0;
				
			}
		}
		return Angle;
	}

	Vec3 Player::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void Player::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSphere(1.0f, 18, vertices, indices);
		//���b�V���̍쐬�i�ύX�ł��Ȃ��j
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//�^�O�̒ǉ�
		AddTag(L"Player");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(0.25f);
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


	}
	void Player::OnUpdate() {
		//�O��̃^�[������̌o�ߎ��Ԃ����߂�
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
				//A�{�^��
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_A) {
				}
			}
			Vec3 Direction = GetMoveVector();
			if (length(Direction) < 0.1f) {
				m_Rigidbody->m_Velocity *= 0.9f;
			}
			else {
				m_Rigidbody->m_Velocity = Direction * 5.0f;
			}
		m_Rigidbody->m_Pos += (m_Rigidbody->m_Velocity * ElapsedTime);
	}

	void Player::OnUpdate2() {
		//�v���C���[�̂y�ʒu�͋����I��0.0�ɂ���
		m_Rigidbody->m_Pos.z = 0.0f;
	}

	void Player::OnDrawShadowmap() {
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


	void Player::OnDraw() {
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




}
//end basecross
