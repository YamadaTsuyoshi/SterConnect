/*!
@file Player.cpp
@brief �v���C���[����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�v���C���[����
	//--------------------------------------------------------------------------------------
	Player::Player(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_Scale(0.25f, 0.25f, 0.25f),
		m_BaseY(m_Scale.y / 2.0f),
		m_Qt(),
		m_Pos(Pos),
		m_Velocity(0, 0, 0)
	{}
	Player::~Player() {}

	Vec3 Player::GetMoveVector() const {
		Vec3 Angle(0, 0, 0);
		auto PtrGameStage = GetStage<GameStage>();
		Vec3 CameraEye, CameraAt;
		PtrGameStage->GetCamera().GetCameraEyeAt(CameraEye, CameraAt);

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0 || CntlVec[0].fThumbLY != 0) {
				float MoveLength = 0;	//���������̃X�s�[�h
										//�i�s�����̌������v�Z
				Vec3 Front = m_Pos - CameraEye;
				Front.z = 0;
				Front.normalize();
				if (m_Pos.x <= 0) {
					//�i�s������������̊p�x���Z�o
					float FrontAngle = atan2(Front.y, Front.x);
					//�R���g���[���̌����v�Z
					float MoveX = CntlVec[0].fThumbLX;
					float MoveY = CntlVec[0].fThumbLY;
					Vec2 MoveVec(MoveX, MoveY);
					float MoveSize = length(MoveVec);
					//�R���g���[���̌�������p�x���v�Z
					float CntlAngle = atan2(-MoveX, MoveY);
					//�g�[�^���̊p�x���Z�o
					float TotalAngle = FrontAngle + CntlAngle;
					//�p�x����x�N�g�����쐬
					Angle = Vec3(cos(TotalAngle), sin(TotalAngle), 0);
					//���K������
					Angle.normalize();
					//�ړ��T�C�Y��ݒ�B
					Angle *= MoveSize;
					//Y���͕ω������Ȃ�
					Angle.z = 0;
				}
				else {
					//�i�s������������̊p�x���Z�o
					float FrontAngle = atan2(Front.y, Front.x);
					//�R���g���[���̌����v�Z
					float MoveX = CntlVec[0].fThumbLX;
					float MoveY = CntlVec[0].fThumbLY;
					Vec2 MoveVec(MoveX, MoveY);
					float MoveSize = length(MoveVec);
					//�R���g���[���̌�������p�x���v�Z
					float CntlAngle = atan2(MoveX, -MoveY);
					//�g�[�^���̊p�x���Z�o
					float TotalAngle = FrontAngle + CntlAngle;
					//�p�x����x�N�g�����쐬
					Angle = Vec3(cos(TotalAngle), sin(TotalAngle), 0);
					//���K������
					Angle.normalize();
					//�ړ��T�C�Y��ݒ�B
					Angle *= MoveSize;
					//Y���͕ω������Ȃ�
					Angle.z = 0;
				}
			}
		}
		return Angle;
	}


	SPHERE Player::GetSPHERE()const {
		SPHERE sp;
		sp.m_Center = (XMFLOAT3)m_Pos;
		sp.m_Radius = m_Scale.y * 0.5f;
		return sp;
	}

	void Player::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSphere(1.0f, 18, vertices, indices);
		//���b�V���̍쐬�i�ύX�ł��Ȃ��j
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//�^�O�̒ǉ�
		AddTag(L"Player");

		//���[���h�s��̌���
		Mat4x4 World;
		World.affineTransformation(m_Scale, Vec3(0, 0, 0),
			m_Qt, m_Pos);
		//�f�[�^�̏�����
		m_PtrObj = make_shared<DrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Trace = true;
		m_PtrObj->m_Wrap = true;

	}
	void Player::OnUpdate() {
		//�O��̃^�[������̌o�ߎ��Ԃ����߂�
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			Vec3 Direction = GetMoveVector();
			if (length(Direction) < 0.1f) {
				m_Velocity *= 0.9f;
			}
			else {
				m_Velocity = Direction * 5.0f;
			}
		m_Pos += (m_Velocity * ElapsedTime);
	}





	void Player::OnDraw() {
		auto PtrGameStage = GetStage<GameStage>();
		//���[���h�s��̌���
		Mat4x4 World;
		World.affineTransformation(m_Scale, Vec3(0, 0, 0),
			m_Qt, m_Pos);
		m_PtrObj->m_WorldMatrix = World;
		auto shptr = PtrGameStage->FindTagGameObject<PNTDrawObject>(L"PNTDrawObject");
		shptr->AddDrawMesh(m_PtrObj);
	}


}
//end basecross
