/*!
@file GameStage.h
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���X�e�[�W
	//--------------------------------------------------------------------------------------
	GameStage::GameStage():
		m_LightDir(0.5f, -1.0f, 0.5f, 1.0f)
	{
		m_LightDir.normalize();
	}

	void GameStage::OnCreate() {

		//���ʂ̍쐬
		Quat Qt;
		Qt.rotationX(XM_PIDIV2);
		AddGameObject<SquareObject>(
			L"SKY_TX",
			Vec3(50.0f, 50.0f, 1.0f),
			Qt,
			Vec3(0.0f, 0.0f, 0.0f)
			);

		//�v���C���[�̍쐬
		AddGameObject<Player>(
			L"TRACE_TX", 
			true, 
			Vec3(0.0f, 0.125f, 0.0f)
			);

		//PNT�`��I�u�W�F�N�g�̍쐬
		AddGameObject<PNTDrawObject>();

		//��]����X�v���C�g�̍쐬
		AddGameObject<RotateSprite>(
			L"TRACE_TX",
			Vec2(160, 160),
			0.0f,
			Vec2(-480, 260),
			4, 4
			);


		//���b�Z�[�W��\������X�v���C�g�̍쐬
		AddGameObject<MessageSprite>(
			L"MESSAGE_TX",
			Vec2(256, 64),
			0.0f,
			Vec2(480, 260),
			1, 1
			);

	}

	void GameStage::OnUpdateStage() {
		for (auto& v : GetGameObjectVec()) {
			//�e�I�u�W�F�N�g�̍X�V
			v->OnUpdate();
		}
		//�������g�̍X�V
		this->OnUpdate();
	}


	void GameStage::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {

			//D�p�b�h��
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				//�J�����ʒu������
				m_Camera.m_CameraArmLen += 0.1f;
				if (m_Camera.m_CameraArmLen >= 50.0f) {
					m_Camera.m_CameraArmLen = 50.0f;
				}
			}
			//D�p�b�h��
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				//�J�����ʒu�����
				m_Camera.m_CameraArmLen -= 0.1f;
				if (m_Camera.m_CameraArmLen <= 2.0f) {
					m_Camera.m_CameraArmLen = 2.0f;
				}
			}

			if (CntlVec[0].fThumbRX != 0) {
				m_Camera.m_CameraXZRad += CntlVec[0].fThumbRX * 0.02f;
				if (abs(m_Camera.m_CameraXZRad) >= XM_2PI) {
					m_Camera.m_CameraXZRad = 0;
				}
			}
			if (CntlVec[0].fThumbRY != 0) {
				m_Camera.m_CameraYRad -= CntlVec[0].fThumbRY * 0.02f;
				if (m_Camera.m_CameraYRad >= XM_PIDIV2 - 0.1f) {
					m_Camera.m_CameraYRad = XM_PIDIV2 - 0.1f;
				}
				else if (m_Camera.m_CameraYRad <= 0.2) {
					m_Camera.m_CameraYRad = 0.2;
				}
			}

			m_Camera.m_CamerAt = FindTagGameObject<GameObject>(L"Player")->GetPosition();
			Vec3 CameraLocalEye =
				Vec3(
					sin(m_Camera.m_CameraXZRad) * m_Camera.m_CameraArmLen * sin(m_Camera.m_CameraYRad),
					cos(m_Camera.m_CameraYRad) * m_Camera.m_CameraArmLen,
					-cos(m_Camera.m_CameraXZRad) * m_Camera.m_CameraArmLen * sin(m_Camera.m_CameraYRad)
				);
			m_Camera.m_CamerEye = m_Camera.m_CamerAt + CameraLocalEye;
			//B�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToEmptyStage");
			}
		}
	}

	void GameStage::OnDrawStage() {
		//�`��f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//�f�t�H���g�`��̊J�n
		Dev->StartDefaultDraw();
		for (auto& v : GetGameObjectVec()) {
			//�e�I�u�W�F�N�g�̕`��
			v->OnDraw();
		}
		//�������g�̕`��
		this->OnDraw();
		//�f�t�H���g�`��̏I��
		Dev->EndDefaultDraw();
	}


	void GameStage::OnDraw() {
		//�������Ȃ�
	}

	//--------------------------------------------------------------------------------------
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	void EmptyStage::OnCreate() {
		//���b�Z�[�W�X�v���C�g
		m_MessageSprite = ObjectFactory::Create<MessageSprite>(
			GetThis<Stage>(),
			L"MESSAGE_TX",
			Vec2(256, 64),
			0.0f,
			Vec2(0, 0),
			1, 1);
	}
	void EmptyStage::OnUpdateStage() {
		//�X�v���C�g�̍X�V
		m_MessageSprite->OnUpdate();
		//�������g�̍X�V
		this->OnUpdate();
	}
	void EmptyStage::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//B�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
	}

	void EmptyStage::OnDrawStage() {
		//�`��f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->ClearDefaultViews(Col4(0, 0, 0, 1.0f));
		//�f�t�H���g�`��̊J�n
		Dev->StartDefaultDraw();
		//�X�v���C�g�`��
		m_MessageSprite->OnDraw();
		//�������g�̕`��
		this->OnDraw();
		//�f�t�H���g�`��̏I��
		Dev->EndDefaultDraw();
	}


	void EmptyStage::OnDraw() {
		//�������Ȃ�
	}


}
//end basecross
