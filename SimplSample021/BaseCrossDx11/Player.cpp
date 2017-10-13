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
		m_Velocity(0, 0, 0),
		m_Gravity(0, -9.8f, 0),
		m_GravityVelocity(0, 0, 0),
		m_JumpLock(false),
		m_BeforePos(Pos),
		m_Mass(1.0f)
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
				Front.y = 0;
				Front.normalize();
				//�i�s������������̊p�x���Z�o
				float FrontAngle = atan2(Front.z, Front.x);
				//�R���g���[���̌����v�Z
				float MoveX = CntlVec[0].fThumbLX;
				float MoveZ = CntlVec[0].fThumbLY;
				Vec2 MoveVec(MoveX, MoveZ);
				float MoveSize = length(MoveVec);
				//�R���g���[���̌�������p�x���v�Z
				float CntlAngle = atan2(-MoveX, MoveZ);
				//�g�[�^���̊p�x���Z�o
				float TotalAngle = FrontAngle + CntlAngle;
				//�p�x����x�N�g�����쐬
				Angle = Vec3(cos(TotalAngle), 0, sin(TotalAngle));
				//���K������
				Angle.normalize();
				//�ړ��T�C�Y��ݒ�B
				Angle *= MoveSize;
				//Y���͕ω������Ȃ�
				Angle.y = 0;
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
	}
	void Player::OnUpdate() {
		//1�O�̈ʒu������Ă���
		m_BeforePos = m_Pos;
		//�O��̃^�[������̌o�ߎ��Ԃ����߂�
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (!m_JumpLock) {
				//A�{�^��
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					m_BeforePos.y += 0.01f;
					m_Pos.y += 0.01f;
					m_GravityVelocity = Vec3(0, 4.0f, 0);
					m_JumpLock = true;
				}
			}
			Vec3 Direction = GetMoveVector();
			if (length(Direction) < 0.1f) {
				m_Velocity *= 0.9f;
			}
			else {
				m_Velocity = Direction * 5.0f;
			}
		}
		m_Pos += (m_Velocity * ElapsedTime);
		m_GravityVelocity += m_Gravity * ElapsedTime;
		m_Pos += m_GravityVelocity * ElapsedTime;
		if (m_Pos.y <= m_BaseY) {
			m_Pos.y = m_BaseY;
			m_GravityVelocity = Vec3(0, 0, 0);
			m_JumpLock = false;
		}
		RotToHead(0.1f);
	}


	void Player::RotToHead(float LerpFact) {
		if (LerpFact <= 0.0f) {
			//��ԌW����0�ȉ��Ȃ牽�����Ȃ�
			return;
		}
		//��]�̍X�V
		//Velocity�̒l�ŁA��]��ύX����
		Vec3 Temp = m_Velocity;
		Temp.normalize();
		float ToAngle = atan2(Temp.x, Temp.z);
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(0, ToAngle, 0));
		Qt.normalize();
		//���݂ƖڕW����
		if (LerpFact >= 1.0f) {
			m_Qt = Qt;
		}
		else {
			m_Qt = XMQuaternionSlerp(m_Qt, Qt, LerpFact);
		}
	}


	void Player::OnDraw() {
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		auto PtrGameStage = GetStage<GameStage>();
		//���[���h�s��̌���
		Mat4x4 World;
		World.affineTransformation(m_Scale, Vec3(0, 0, 0),
			m_Qt, m_Pos);
		auto shptr = PtrGameStage->FindTagGameObject<PNTDrawObject>(L"PNTDrawObject");
		shptr->AddDrawMesh(
			m_SphereMesh,
			TexPtr,
			World,
			true
		);
	}


}
//end basecross
