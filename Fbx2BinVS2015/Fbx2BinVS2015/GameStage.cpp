/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------


	//���\�[�X�̍쐬
	void GameStage::CreateResourses() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
	}



	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrLookAtCamera = ObjectFactory::Create<LookAtCamera>(10.0f);
		PtrView->SetCamera(PtrLookAtCamera);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}


	//�v���[�g�̍쐬
	void GameStage::CreatePlate() {
		//�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(XM_PIDIV2, 0, 0));
		Mat4x4 WorldMat;
		WorldMat.affineTransformation(
			Vec3(200.0f, 200.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Qt,
			Vec3(0.0f, 0.0f, 0.0f)
		);
		PtrTrans->SetScale(200.0f, 200.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		//�`��R���|�[�l���g�̒ǉ�
		auto DrawComp = Ptr->AddComponent<PNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//�����ɉe���f�肱�ނ悤�ɂ���
		DrawComp->SetOwnShadowActive(true);

		//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		DrawComp->SetTextureResource(L"SKY_TX");
	}

	//FbxMeshObject�̍쐬
	void GameStage::CreateFbxMeshObject() {
		auto FbxMeshObjectPtr = AddGameObject<FbxMeshObject>();
		//�V�F�A�z��ɒǉ�
		SetSharedGameObject(L"FbxMeshObject", FbxMeshObjectPtr);

	}

	void GameStage::OnCreate() {
		try {
			//���\�[�X�̍쐬
			CreateResourses();
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�v���[�g�̍쐬
			CreatePlate();
			//FbxMeshObject�̍쐬
			CreateFbxMeshObject();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::ReadFbxFile(const wstring& Dir, const wstring& FileName, size_t MeshIndex, float Scale, const Vec3& Position,
		bool IsReadStatic, bool WithTangent, const wstring& NormalFileName, bool TextureWrap) {
		try {
			auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
			PtrFbxObj->ResetFbxMesh(Dir, FileName, MeshIndex, Scale, Position, IsReadStatic, WithTangent, NormalFileName, TextureWrap);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::SaveStaticBinFile(const wstring& Dir, const wstring& FileName, size_t MeshIndex, float Scale) {
		try {
			auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
			PtrFbxObj->SaveStaticBinFile(Dir, FileName, MeshIndex, Scale);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::SaveSkinBinFile(const wstring& Dir, const wstring& FileName, size_t MeshIndex, float Scale,
		UINT FrameParSec, UINT Start, UINT End) {
		try {
			auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
			PtrFbxObj->SaveSkinBinFile(Dir, FileName, MeshIndex, Scale, FrameParSec, Start, End);
		}
		catch (...) {
			throw;
		}
	}



	void GameStage::ClearFbxMesh() {
		auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
		PtrFbxObj->ClearFbxMesh();
	}


	bool GameStage::CheckSkinMesh() {
		auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
		return PtrFbxObj->CheckSkinMesh();
	}

	bool GameStage::CheckMesh() {
		auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
		return PtrFbxObj->CheckMesh();
	}

	void GameStage::MoveFbxFile(UINT FrameRate, UINT StartTime, UINT EndTime, bool IsLoop) {
		auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
		PtrFbxObj->MoveFbxMesh(FrameRate, StartTime, EndTime, IsLoop);
	}

	void GameStage::AnimePoseStart() {
		auto PtrFbxObj = GetSharedGameObject<FbxMeshObject>(L"FbxMeshObject");
		PtrFbxObj->AnimePoseStart();
	}




}
//end basecross
