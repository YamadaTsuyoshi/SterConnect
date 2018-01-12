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
		m_BaseX(6.25f),
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
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//���b�V���̍쐬�i�ύX�ł��Ȃ��j
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//�^�O�̒ǉ�
		AddTag(L"Player");
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
	}
	void Player::OnUpdate() {
		Startflag = GetStage<GameStage>()->getStartFlag();
		if (Startflag) {
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

			if (m_Rigidbody->m_Pos.x >= m_BaseX) {
				m_Rigidbody->m_Pos.x = m_BaseX;
				m_Rigidbody->m_Velocity.x = m_Rigidbody->m_Velocity.x;
			}
			else if (m_Rigidbody->m_Pos.x <= -m_BaseX) {
				m_Rigidbody->m_Pos.x = -m_BaseX;
				m_Rigidbody->m_Velocity.x = m_Rigidbody->m_Velocity.x;
			}

			ColorChanger();
			L_Now = CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
			R_Now = CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;

			//auto PtrStage = GetStage<Stage>();
			////�J�����̈ʒu
			//Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
			//m_Rigidbody->m_Pos.y = CameraEye.y;
		}
	}

		void Player::OnUpdate2() {
			if(Startflag){
			//�v���C���[�̂y�ʒu�͋����I��0.0�ɂ���
			m_Rigidbody->m_Pos.z = 2.0f;

			if (P_LightGage <= P_MaxLightGage) {
				P_LightGage += 0.1f;
			}
			if (P_LightGage >= P_MaxLightGage) {
				P_LightGage = P_MaxLightGage;
			}


			switch (P_color) {
			case Yellow:
				m_TextureResName = L"SUBARU_Y_TX";
				break;
			case Red:
				m_TextureResName = L"SUBARU_R_TX";
				break;
			default:
				break;
			}
			auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
			m_PtrObj->m_TextureRes = TexPtr;

		}

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

	void Player::ColorChanger()
	{
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && 
				L_Now == 0) {
					P_color += 1;
			}
			else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER &&
			    R_Now == 0) {
					P_color -= 1;
			}

		}
		if (P_color < Yellow) {
			P_color = Red;
		}
		if (P_color > Red) {
			P_color = Yellow;
		}
	}

	SubaruSS::SubaruSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir) :
		SS5ssae(StagePtr, BaseDir, L"SUBARU_1027.ssae", L"Walk_Right_Y")
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 1.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//������
	void SubaruSS::OnCreate() {

		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(1.4f, 1.4f, 1.0f);
		//PtrT->SetPosition(Vec3(0, 5.0f, 1.0f));
		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(30.0f);

		//ChangeAnimation(L"run");
		SetLooped(true);


	}

	//�X�V
	void SubaruSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		auto PtrGameStage = GetStage<GameStage>();
		GetTransform()->SetPosition(PtrGameStage->GetP_Pos());
		UpdateAnimeTime(ElapsedTime);
	}

}
//end basecross
