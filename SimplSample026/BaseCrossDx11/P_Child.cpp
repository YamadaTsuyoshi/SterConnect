#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	���̂̃v���C���[����
	//--------------------------------------------------------------------------------------
	P_child::P_child(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.35f),
		m_BaseY(0.25f / 2.0f),
		m_Posision(Pos),
		m_JumpLock(false)
	{}
	P_child::~P_child() {}

	Vec3 P_child::GetMoveVector() {
		flg = true;
		auto PtrGameStage = GetStage<GameStage>();
		Vec3 Angle = m_Posision;
		//Vec3 Angle = Vec3(0, 0, 0);
		 //Vec3 Angle = PtrGameStage->GetP_Pos();
		//Vec3 CameraEye, CameraAt;
		//PtrGameStage->GetCamera().GetCameraEyeAt(CameraEye, CameraAt);

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
				float MoveLength = 0;	//���������̃X�s�[�h
				Vec3 Front = m_Rigidbody->m_Pos;
				Front.z = 0;
				Front.normalize();
				//�i�s������������̊p�x���Z�o
				//float FrontAngle = atan2(Front.z, Front.x);
				//�R���g���[���̌����v�Z
				float MoveX = CntlVec[0].fThumbRX;
				float MoveY = CntlVec[0].fThumbRY;
				Vec2 MoveVec(MoveX, MoveY);
				float MoveSize = length(MoveVec);
				//�R���g���[���̌�������p�x���v�Z
				float CntlAngle = atan2(MoveX, MoveY);
				//�g�[�^���̊p�x���Z�o
				float TotalAngle = +CntlAngle;
				_angle = TotalAngle;
				//�p�x����x�N�g�����쐬
				Angle = Vec3(sin(TotalAngle), cos(TotalAngle), 0);
				//���K������
				Angle.normalize();
				//�ړ��T�C�Y��ݒ�B
				Angle *= 2;
				//Y���͕ω������Ȃ�
				Angle.z = 0;

			}
		}
		return Angle;
	}

	Vec3 P_child::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void P_child::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSphere(1.0f, 18, vertices, indices);
		//���b�V���̍쐬�i�ύX�ł��Ȃ��j
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//�^�O�̒ǉ�
		AddTag(L"P_child");
		//Rigidbody�̏�����
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(0.25f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
				//body.m_IsDrawActive = true;
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
	void P_child::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
		//	m_Rigidbody->m_Pos = m_Posision + GetMoveVector();
		//}
		//else
		//{
		//	if (flg == true)
		//	{
		//		CrBarflg = true;
		//		flg = false;
		//		P_pos2 = P_pos + (m_Rigidbody->m_Pos - P_pos)/2;
		//	}
		//	else {
		//		CrBarflg = false;
		//	}
		m_Rigidbody->m_Pos = m_Posision;
		//	m_Rigidbody->m_Pos.x += 0.2f;
		//	m_Rigidbody->m_Pos.y -= 0.2f;
		//}
		////m_Rigidbody->m_Pos = m_Posision;
		//if (m_Rigidbody->m_Pos.x >= m_BaseX) {
		//	m_Rigidbody->m_Pos.x = m_BaseX;
		//	m_Rigidbody->m_Velocity.x = m_Rigidbody->m_Velocity.x;
		//}
		//else if (m_Rigidbody->m_Pos.x <= -m_BaseX) {
		//	m_Rigidbody->m_Pos.x = -m_BaseX;
		//	m_Rigidbody->m_Velocity.x = m_Rigidbody->m_Velocity.x;
		//}
		m_Rigidbody->m_Pos.z = 3.0f;

		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X ||
			GetStage<GameStage>()->getPointDeleteFlag())
		{
			ThisDelete();
		}
	}

	void P_child::OnUpdate2() {
		m_Rigidbody->m_Pos.z = 3.0f;
	}

	void P_child::OnDrawShadowmap() {
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


	void P_child::OnDraw() {
		
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

	void P_child::ThisDelete()
	{
		GetStage<GameStage>()->RemoveGameObject<P_child>(GetThis<P_child>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<P_child>());
	}



}
//end basecross