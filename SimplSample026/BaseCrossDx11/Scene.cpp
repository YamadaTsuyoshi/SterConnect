/*!
@file Scene.cpp
@brief �V�[���Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�X�e�[�W�i�V�[���ŊǗ�����C���^�[�t�F�C�X�j
	//--------------------------------------------------------------------------------------
	void Stage::OnPreCreate() {
		//Rigidbody�}�l�[�W���̏�����
		m_RigidbodyManager
			= ObjectFactory::Create<RigidbodyManager>(GetThis<Stage>());
	}

	//�ǉ��I�u�W�F�N�g�̎w��
	void Stage::PushBackGameObject(const shared_ptr<GameObject>& Ptr) {
		//���̃X�e�[�W�̓N���G�C�g��ł���
		if (IsCreated()) {
			m_WaitAddObjectVec.push_back(Ptr);
		}
		else {
			//�N���G�C�g�O
			m_GameObjectVec.push_back(Ptr);
		}
	}
	//�폜�I�u�W�F�N�g�̎w��
	void Stage::RemoveBackGameObject(const shared_ptr<GameObject>& Ptr) {
		m_WaitRemoveObjectVec.push_back(Ptr);
	}
	//�I�u�W�F�N�g�̍폜
	void Stage::RemoveTargetGameObject(const shared_ptr<GameObject>& targetobj) {
		auto it = m_GameObjectVec.begin();
		while (it != m_GameObjectVec.end()) {
			if (*it == targetobj) {
				m_GameObjectVec.erase(it);
				return;
			}
			it++;
		}
		m_RigidbodyManager->RemoveOwnRigidbody(targetobj);
	}
	//�ǉ���폜�҂��ɂȂ��Ă�I�u�W�F�N�g��ǉ��폜����
	void Stage::SetWaitToObjectVec() {
		if (!m_WaitRemoveObjectVec.empty()) {
			for (auto Ptr : m_WaitRemoveObjectVec) {
				RemoveTargetGameObject(Ptr);
			}
		}
		m_WaitRemoveObjectVec.clear();
		if (!m_WaitAddObjectVec.empty()) {
			for (auto Ptr : m_WaitAddObjectVec) {
				m_GameObjectVec.push_back(Ptr);
			}
		}
		m_WaitAddObjectVec.clear();
	}

	void Stage::FindTagGameObjectVec(const wstring& TagName, vector<shared_ptr<GameObject>>& Ret) const {
		Ret.clear();
		for (auto& v : GetGameObjectVec()) {
			if (v->FindTag(TagName)) {
				Ret.push_back(v);
			}
		}
	}

	shared_ptr<RigidbodyManager> Stage::GetRigidbodyManager() const {
		return m_RigidbodyManager;
	}

	shared_ptr<Rigidbody> Stage::AddRigidbody(const Rigidbody& body) {
		return m_RigidbodyManager->AddRigidbody(body);
	}

	void Stage::RemoveOwnRigidbody(const shared_ptr<GameObject>& OwnerPtr) {
		m_RigidbodyManager->RemoveOwnRigidbody(OwnerPtr);
	}

	const vector<shared_ptr<Rigidbody>>& Stage::GetRigidbodyVec()const {
		return m_RigidbodyManager->GetRigidbodyVec();
	}
	const vector<CollisionState>& Stage::GetCollisionStateVec()const {
		return m_RigidbodyManager->GetCollisionStateVec();
	}
	shared_ptr<Rigidbody> Stage::GetOwnRigidbody(const shared_ptr<GameObject>& OwnerPtr) {
		return m_RigidbodyManager->GetOwnRigidbody(OwnerPtr);
	}




	//--------------------------------------------------------------------------------------
	//	�R���|�[�l���gImpl�N���X
	//--------------------------------------------------------------------------------------
	struct Transform::Impl {
		weak_ptr<GameObject> m_GameObject;
		bool m_UpdateActive{ true };	//update���邩�ǂ���
		bool m_DrawActive{ true };		//Draw���邩�ǂ���




		bool m_Init{ false };	//�������ς݂��ǂ����i1��ڂ�Update�ŁABefore�ɒl������j
								//1�O�̕ϐ�
		bsm::Vec3 m_BeforeScale;
		bsm::Vec3 m_BeforePivot;
		bsm::Quat m_BeforeQuaternion;
		bsm::Vec3 m_BeforePosition;
		//�Čv�Z�}���p�ϐ�
		bool m_BeforeChangeed;
		bsm::Mat4x4 m_BeforeWorldMatrix;
		//���݂̕ϐ�
		bsm::Vec3 m_Scale;
		bsm::Vec3 m_Pivot;
		bsm::Quat m_Quaternion;
		bsm::Vec3 m_Position;
		//�Čv�Z�}���p�ϐ�
		bool m_Changeed;
		bsm::Mat4x4 m_WorldMatrix;
		//�e�I�u�W�F�N�g
		weak_ptr<GameObject> m_Parent;
		Impl() :
			//�X�P�[���̂ݏ������i���̓f�t�H���g�����ł悢�j
			m_BeforeScale(1.0f, 1.0f, 1.0f),
			m_Scale(1.0f, 1.0f, 1.0f),
			m_BeforeChangeed(true),
			m_Changeed(true)
		{}
		~Impl() {}
	};


	//--------------------------------------------------------------------------------------
	///	�ϊ��I�u�W�F�N�g
	//--------------------------------------------------------------------------------------

	//�A�N�Z�T
	shared_ptr<GameObject> Transform::GetGameObject() const {
		auto shptr = pImpl->m_GameObject.lock();
		if (!shptr) {
			throw BaseException(
				L"GameObject�͗L���ł͂���܂���",
				L"if (!shptr)",
				L"Transform::GetGameObject()"
			);
		}
		else {
			return shptr;
		}
	}

	shared_ptr<Stage> Transform::GetStage() const {
		return GetGameObject()->GetStage();
	}


	bool Transform::IsUpdateActive() const {
		return pImpl->m_UpdateActive;
	}
	bool Transform::GetUpdateActive() const {
		return pImpl->m_UpdateActive;
	}
	void Transform::SetUpdateActive(bool b) {
		pImpl->m_UpdateActive = b;
	}

	bool Transform::IsDrawActive() const {
		return pImpl->m_DrawActive;
	}
	bool Transform::GetDrawActive() const {
		return pImpl->m_DrawActive;
	}
	void Transform::SetDrawActive(bool b) {
		pImpl->m_DrawActive = b;
	}


	Transform::Transform(const shared_ptr<GameObject>& GameObjectPtr) :
		pImpl(new Impl())
	{
		pImpl->m_GameObject = GameObjectPtr;
	}
	Transform::~Transform() {}

	//�A�N�Z�T
	//BeforeGetter
	bsm::Vec3 Transform::GetBeforeScale() const {
		return pImpl->m_BeforeScale;
	}

	bsm::Vec3 Transform::GetBeforePivot() const {
		return pImpl->m_BeforePivot;
	}

	bsm::Quat Transform::GetBeforeQuaternion() const {
		return pImpl->m_BeforeQuaternion;
	}

	bsm::Vec3 Transform::GetBeforeRotation() const {
		return pImpl->m_BeforeQuaternion.toRotVec();
	}

	bsm::Vec3 Transform::GetBeforePosition() const {
		return pImpl->m_BeforePosition;
	}

	bool Transform::IsSameBeforeWorldMatrix(const bsm::Mat4x4& mat) const {
		return mat.equalInt(GetBeforeWorldMatrix());
	}


	const bsm::Mat4x4& Transform::GetBeforeWorldMatrix() const {
		auto ParPtr = GetParent();
		if (pImpl->m_BeforeChangeed || ParPtr) {
			pImpl->m_BeforeWorldMatrix.affineTransformation(
				pImpl->m_BeforeScale,
				pImpl->m_BeforePivot,
				pImpl->m_BeforeQuaternion,
				pImpl->m_BeforePosition
			);
			pImpl->m_BeforeChangeed = false;
			if (ParPtr) {
				auto ParBeforeWorld = ParPtr->GetTransform()->GetBeforeWorldMatrix();
				ParBeforeWorld.scaleIdentity();
				pImpl->m_BeforeWorldMatrix = pImpl->m_BeforeWorldMatrix * ParBeforeWorld;
			}
		}
		return pImpl->m_BeforeWorldMatrix;
	}


	//Getter&Setter

	bsm::Vec3 Transform::GetScale() const {
		return pImpl->m_Scale;
	}

	void Transform::SetScale(const bsm::Vec3& Scale) {
		pImpl->m_Changeed = true;
		pImpl->m_Scale = Scale;
	}
	void Transform::SetScale(float x, float y, float z) {
		SetScale(bsm::Vec3(x, y, z));
	}

	bsm::Vec3 Transform::GetPivot() const {
		return pImpl->m_Pivot;
	}
	void Transform::SetPivot(const bsm::Vec3& Pivot) {
		pImpl->m_Changeed = true;
		pImpl->m_Pivot = Pivot;
	}
	void Transform::SetPivot(float x, float y, float z) {
		SetPivot(bsm::Vec3(x, y, z));
	}

	bsm::Quat Transform::GetQuaternion() const {
		return pImpl->m_Quaternion;
	}
	void Transform::SetQuaternion(const bsm::Quat& quaternion) {
		pImpl->m_Changeed = true;
		pImpl->m_Quaternion = quaternion;
		pImpl->m_Quaternion.normalize();
	}
	bsm::Vec3 Transform::GetRotation() const {
		return pImpl->m_Quaternion.toRotVec();
	}

	void Transform::SetRotation(const bsm::Vec3& Rot) {
		pImpl->m_Changeed = true;
		bsm::Quat Qt;
		Qt.rotationRollPitchYawFromVector(Rot);
		SetQuaternion(Qt);
	}
	void Transform::SetRotation(float x, float y, float z) {
		SetRotation(bsm::Vec3(x, y, z));
	}

	bsm::Vec3 Transform::GetPosition() const {
		return pImpl->m_Position;
	}

	void Transform::SetPosition(const bsm::Vec3& Position) {
		pImpl->m_Changeed = true;
		pImpl->m_Position = Position;
	}
	void Transform::SetPosition(float x, float y, float z) {
		SetPosition(bsm::Vec3(x, y, z));
	}

	void Transform::ResetPosition(const bsm::Vec3& Position) {
		pImpl->m_BeforeChangeed = true;
		pImpl->m_BeforePosition = Position;
		pImpl->m_Changeed = true;
		pImpl->m_Position = Position;
	}

	bsm::Vec3 Transform::GetWorldPosition() const {
		return GetWorldMatrix().transInMatrix();
	}
	void Transform::SetWorldPosition(const bsm::Vec3& Position) {
		auto SetPos = Position;
		auto ParPtr = GetParent();
		if (ParPtr) {
			auto ParWorldPos = ParPtr->GetTransform()->GetWorldMatrix().transInMatrix();
			SetPos -= ParWorldPos;
			auto ParQt = ParPtr->GetTransform()->GetWorldMatrix().quatInMatrix();
			ParQt = bsm::inverse(ParQt);
			bsm::Mat4x4 ParQtMat(ParQt);
			SetPos *= ParQtMat;
		}
		SetPosition(SetPos);
	}
	void Transform::ResetWorldPosition(const bsm::Vec3& Position) {
		auto SetPos = Position;
		auto ParPtr = GetParent();
		if (ParPtr) {
			auto ParWorldPos = ParPtr->GetTransform()->GetWorldMatrix().transInMatrix();
			SetPos -= ParWorldPos;
			auto ParQt = ParPtr->GetTransform()->GetWorldMatrix().quatInMatrix();
			ParQt = bsm::inverse(ParQt);
			bsm::Mat4x4 ParQtMat(ParQt);
			SetPos *= ParQtMat;
		}
		ResetPosition(SetPos);
	}

	bool Transform::IsSameWorldMatrix(const bsm::Mat4x4& mat) const {
		return mat.equalInt(GetWorldMatrix());
	}


	const bsm::Mat4x4& Transform::GetWorldMatrix() const {
		auto ParPtr = GetParent();
		if (pImpl->m_Changeed || ParPtr) {
			pImpl->m_WorldMatrix.affineTransformation(
				pImpl->m_Scale,
				pImpl->m_Pivot,
				pImpl->m_Quaternion,
				pImpl->m_Position
			);
			pImpl->m_Changeed = false;
			if (ParPtr) {
				auto ParWorld = ParPtr->GetTransform()->GetWorldMatrix();
				ParWorld.scaleIdentity();
				pImpl->m_WorldMatrix = pImpl->m_WorldMatrix * ParWorld;
			}
		}
		return pImpl->m_WorldMatrix;
	}

	const bsm::Mat4x4& Transform::Get2DWorldMatrix() const {
		auto ParPtr = GetParent();
		if (pImpl->m_Changeed || ParPtr) {
			pImpl->m_Scale.z = 1.0f;
			bsm::Vec4 temp_z(pImpl->m_Position.z);
			temp_z = XMVector4ClampLength(temp_z, 0.0f, 1.0f);
			pImpl->m_Position.z = temp_z.z;
			pImpl->m_Pivot.z = 0;
			pImpl->m_WorldMatrix.affineTransformation(
				pImpl->m_Scale,
				pImpl->m_Pivot,
				pImpl->m_Quaternion,
				pImpl->m_Position
			);
			pImpl->m_Changeed = false;
			if (ParPtr) {
				auto ParWorld = ParPtr->GetTransform()->Get2DWorldMatrix();
				ParWorld.scaleIdentity();
				pImpl->m_WorldMatrix = pImpl->m_WorldMatrix * ParWorld;
			}
		}
		return pImpl->m_WorldMatrix;
	}


	const shared_ptr<GameObject> Transform::GetParent()const {
		auto ShPtr = pImpl->m_Parent.lock();
		if (ShPtr) {
			return ShPtr;
		}
		return nullptr;
	}
	void Transform::SetParent(const shared_ptr<GameObject>& Obj) {
		if (GetParent() == Obj) {
			return;
		}
		if (Obj) {
			ClearParent();
			pImpl->m_Parent = Obj;
			auto ParWorld = Obj->GetTransform()->GetWorldMatrix();
			ParWorld.scaleIdentity();
			auto PosSpan = GetPosition() - ParWorld.transInMatrix();
			auto QtSpan = ParWorld.quatInMatrix();
			QtSpan = bsm::inverse(QtSpan);
			bsm::Mat4x4 ParQtMat(QtSpan);
			PosSpan *= ParQtMat;

			bsm::Mat4x4 Mat = GetWorldMatrix() * ParWorld;
			bsm::Vec3 Scale, Pos;
			bsm::Quat Qt;
			Mat.decompose(Scale, Qt, Pos);
			SetScale(Scale);
			SetQuaternion(Qt);
			SetPosition(PosSpan);
			SetToBefore();

		}
		else {
			//nullptr���n���ꂽ
			ClearParent();
		}
	}

	void Transform::ClearParent() {
		if (auto ParPtr = GetParent()) {
			auto Pos = GetWorldPosition();
			SetPosition(Pos);
			SetToBefore();
		}
		pImpl->m_Parent.reset();
	}
	bsm::Vec3 Transform::GetVelocity() const {
		//�O��̃^�[������̎���
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		bsm::Vec3 Velocity = pImpl->m_Position - pImpl->m_BeforePosition;
		Velocity /= ElapsedTime;
		return Velocity;
	}
	void Transform::SetToBefore() {
		if (pImpl->m_BeforeScale != pImpl->m_Scale) {
			pImpl->m_BeforeChangeed = true;
			pImpl->m_BeforeScale = pImpl->m_Scale;
		}
		if (pImpl->m_BeforePivot != pImpl->m_Pivot) {
			pImpl->m_BeforeChangeed = true;
			pImpl->m_BeforePivot = pImpl->m_Pivot;
		}
		if (pImpl->m_BeforeQuaternion != pImpl->m_Quaternion) {
			pImpl->m_BeforeChangeed = true;
			pImpl->m_BeforeQuaternion = pImpl->m_Quaternion;
		}
		if (pImpl->m_BeforePosition != pImpl->m_Position) {
			pImpl->m_BeforeChangeed = true;
			pImpl->m_BeforePosition = pImpl->m_Position;
		}
	}

	//����
	void Transform::OnUpdate() {
		if (!pImpl->m_Init) {
			SetToBefore();
			pImpl->m_Init = true;
		}
	}

	//--------------------------------------------------------------------------------------
	///	�Q�[���I�u�W�F�N�g�̐e
	//--------------------------------------------------------------------------------------
	void GameObject::OnPreCreate() {
		m_Transform = ObjectFactory::Create<Transform>(GetThis<GameObject>());
	}





	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	Scene::Scene() :
		SceneInterface()
	{
	}

	void Scene::CreateResources() {
		wstring DataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"Texture\\kaguya-01.png";
		App::GetApp()->RegisterTexture(L"KAGUYA_TX", strTexture);
		strTexture = DataDir + L"Texture\\StageMessage.png";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		strTexture = DataDir + L"Texture\\BackGr.png";
		App::GetApp()->RegisterTexture(L"BG_TX", strTexture);
		strTexture = DataDir + L"Texture\\UIspace.png";
		App::GetApp()->RegisterTexture(L"UI_BG_TX", strTexture);
		strTexture = DataDir + L"Texture\\go-ru.png";
		App::GetApp()->RegisterTexture(L"GOAL_TX", strTexture);

		strTexture = DataDir + L"Texture\\hoshi_title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"Texture\\StageSelect_Ver2.0.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_TX", strTexture);
		strTexture = DataDir + L"Texture\\clear.PNG";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		strTexture = DataDir + L"Texture\\gameover_Back.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_BG_TX", strTexture);
		strTexture = DataDir + L"Texture\\GameOverText.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TEXT_TX", strTexture);
		strTexture = DataDir + L"Texture\\L1.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_L1_TX", strTexture);
		strTexture = DataDir + L"Texture\\L2.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_L2_TX", strTexture);
		strTexture = DataDir + L"Texture\\L3.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_L3_TX", strTexture);
		strTexture = DataDir + L"Texture\\N1.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_N1_TX", strTexture);
		strTexture = DataDir + L"Texture\\N2.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_N2_TX", strTexture);
		strTexture = DataDir + L"Texture\\N3.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_N3_TX", strTexture);
		strTexture = DataDir + L"Texture\\Side.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_SIDE_TX", strTexture);

		strTexture = DataDir + L"Texture\\gameover.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		strTexture = DataDir + L"Texture\\kagu_futon.png";
		App::GetApp()->RegisterTexture(L"HUTON_TX", strTexture);

		strTexture = DataDir + L"Texture\\take_C.png";
		App::GetApp()->RegisterTexture(L"WALL_TX", strTexture);
		strTexture = DataDir + L"Texture\\wall_normal.png";
		App::GetApp()->RegisterTexture(L"WALL_NORMAL_TX", strTexture);

		strTexture = DataDir + L"Texture\\Brown.png";
		App::GetApp()->RegisterTexture(L"BROWN_TX", strTexture);
		strTexture = DataDir + L"Texture\\normal2.png";
		App::GetApp()->RegisterTexture(L"NORMAL2_TX", strTexture);

		//Bar
		strTexture = DataDir + L"Texture\\Line_Blue.png";
		App::GetApp()->RegisterTexture(L"BARB_TX", strTexture);
		strTexture = DataDir + L"Texture\\Line_Yellow.png";
		App::GetApp()->RegisterTexture(L"BARY_TX", strTexture);
		strTexture = DataDir + L"Texture\\Line_Red.png";
		App::GetApp()->RegisterTexture(L"BARR_TX", strTexture);

		//�G
		strTexture = DataDir + L"Texture\\WhiteRabbit_noAnime.png";
		App::GetApp()->RegisterTexture(L"RABBIT_TX", strTexture);
		strTexture = DataDir + L"Texture\\dango.png";
		App::GetApp()->RegisterTexture(L"RABBIT_BULLET_TX", strTexture);

		//���Q�[�W
		strTexture = DataDir + L"Texture\\Hikarigage_Base.png";
		App::GetApp()->RegisterTexture(L"LIGHTGAGE_A_TX", strTexture);
		strTexture = DataDir + L"Texture\\Hikarigage_gage.png";
		App::GetApp()->RegisterTexture(L"LIGHTGAGE_B_TX", strTexture);
		strTexture = DataDir + L"Texture\\Hikarigage_gage_R.png";
		App::GetApp()->RegisterTexture(L"LIGHTGAGE_B_R_TX", strTexture);
		
		//���C�t
		strTexture = DataDir + L"Texture\\heart1218.png";
		App::GetApp()->RegisterTexture(L"LIFE_TX", strTexture);
		strTexture = DataDir + L"Texture\\Hart_0.png";
		App::GetApp()->RegisterTexture(L"EMP_LIFE_TX", strTexture);
		strTexture = DataDir + L"UI\\Tairyoku.png";
		App::GetApp()->RegisterTexture(L"TAIRYOKU_TX", strTexture);

		//goal
		strTexture = DataDir + L"Texture\\hune.png";
		App::GetApp()->RegisterTexture(L"GOAL2_TX", strTexture);

		//�_A
		strTexture = DataDir + L"Texture\\Cloud1218_A.png";
		App::GetApp()->RegisterTexture(L"CLOUDA_TX", strTexture);
		//�_B
		strTexture = DataDir + L"Texture\\Cloud1218_B.png";
		App::GetApp()->RegisterTexture(L"CLOUDB_TX", strTexture);
		//�_C
		strTexture = DataDir + L"Texture\\Cloud1218_C.png";
		App::GetApp()->RegisterTexture(L"CLOUDC_TX", strTexture);
		//�_D
		strTexture = DataDir + L"Texture\\Cloud1218_D.png";
		App::GetApp()->RegisterTexture(L"CLOUDD_TX", strTexture);

		//Take
		strTexture = DataDir + L"Texture\\take_Ba.png";
		App::GetApp()->RegisterTexture(L"Bamboo_B_TX", strTexture);

		//�X�o��
		strTexture = DataDir + L"Texture\\SUBARU_noAnime.png";
		App::GetApp()->RegisterTexture(L"SUBARU_Y_TX", strTexture);
		strTexture = DataDir + L"Texture\\ao.png";
		App::GetApp()->RegisterTexture(L"SUBARU_B_TX", strTexture);
		strTexture = DataDir + L"Texture\\aka.png";
		App::GetApp()->RegisterTexture(L"SUBARU_R_TX", strTexture);

		//UISpace aaaaaaaaaaaaaaa
		strTexture = DataDir + L"Texture\\aaaaaaaaaaaaaaa.png";
		App::GetApp()->RegisterTexture(L"UI_S_TX", strTexture);

		strTexture = DataDir + L"Texture\\kuria.PNG";
		App::GetApp()->RegisterTexture(L"KURIA_TX", strTexture);

		//���Q�[�W�A�C�e��
		strTexture = DataDir + L"Texture\\Star.png";
		App::GetApp()->RegisterTexture(L"STAR_TX", strTexture);

		//�t�F�[�h�p�X�v���C�g
		strTexture = DataDir + L"Texture\\BackSprite.png";
		App::GetApp()->RegisterTexture(L"FADE_TX", strTexture);

		strTexture = DataDir + L"Texture\\skeleton.png";
		App::GetApp()->RegisterTexture(L"Skeleton_TX", strTexture);
		
		//����
		strTexture = DataDir + L"UI\\Time_0.png";
		App::GetApp()->RegisterTexture(L"KEIKAZIKAN_TX", strTexture);
		strTexture = DataDir + L"UI\\Time_corron.png";
		App::GetApp()->RegisterTexture(L"CORRON_TX", strTexture);
		strTexture = DataDir + L"UI\\TimeCount.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = DataDir + L"Enemy\\RabbitBOX.png";
		App::GetApp()->RegisterTexture(L"RABBITBOX_TX", strTexture);

		strTexture = DataDir + L"UI\\PushA.png";
		App::GetApp()->RegisterTexture(L"PUSH_A_TX", strTexture);
		

		//�{�[�����f���̃��\�[�X
//		auto ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"temp\\Chara_R.bmf");
//		App::GetApp()->RegisterResource(L"Chara_R_MESH", ModelMesh);
		//�{�[�����f���̃^���W�F���g�t�����\�[�X
//		ModelMesh = MeshResource::CreateBoneModelMeshWithTangent(DataDir, L"temp\\Chara_R.bmf");
//		App::GetApp()->RegisterResource(L"Chara_R_MESH_WITH_TAN", ModelMesh);
		//�@���}�b�v
//		strTexture = DataDir + L"temp\\Chara_R_narmal.png";
//		App::GetApp()->RegisterTexture(L"Chara_R_NORMAL_TX", strTexture);

		//�X�^�e�B�b�N���f���̃��\�[�X�Ƃ��ēǂݍ���
//		auto StaticModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"temp\\Character_01.bmf");
//		App::GetApp()->RegisterResource(L"MODEL_MESH", StaticModelMesh);

		//�X�^�e�B�b�N���f���̃^���W�F���g�t�����\�[�X�Ƃ��ēǂݍ���
//		StaticModelMesh = MeshResource::CreateStaticModelMeshWithTangent(DataDir, L"temp\\Character_01.bmf");
//		App::GetApp()->RegisterResource(L"MODEL_MESH_WITH_TAN", StaticModelMesh);
		//�@���}�b�v
		strTexture = DataDir + L"temp\\Character_2_normal.png";
		App::GetApp()->RegisterTexture(L"MODEL_NORMAL_TX", strTexture);
		//�G�t�F�N�g
		strTexture = DataDir + L"temp\\spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = DataDir + L"temp\\fire.png";
		App::GetApp()->RegisterTexture(L"FIRE_TX", strTexture);

		//�^�C�g��BGM
		wstring strMusic = DataDir + L"BGM\\Title.wav";
		App::GetApp()->RegisterWav(L"TITLE_BGM", strMusic);
		//�X�e�[�W�Z���N�gBGM
		strMusic = DataDir + L"BGM\\StageSelect.wav";
		App::GetApp()->RegisterWav(L"STAGESELECT_BGM", strMusic);
		//�Q�[��BGM
		strMusic = DataDir + L"BGM\\GameStage.wav";
		App::GetApp()->RegisterWav(L"GAMESTAGE_BGM", strMusic);
		//�Q�[���I�[�o�[BGM
		strMusic = DataDir + L"BGM\\Gameover.wav";
		App::GetApp()->RegisterWav(L"GAMEOVER_BGM", strMusic);
		//���ˎ���SE
		wstring SeWav = DataDir + L"SE\\Refrect.wav";
		App::GetApp()->RegisterWav(L"REF_SE", SeWav);
		//���莞��SE
		SeWav = DataDir + L"SE\\Pressbutton.wav";
		App::GetApp()->RegisterWav(L"PRESS_SE", SeWav);
		//�G��|��������SE
		SeWav = DataDir + L"SE\\damage.wav";
		App::GetApp()->RegisterWav(L"DEST_SE", SeWav);
		//�����������Ƃ���SE
		SeWav = DataDir + L"SE\\decision22.wav";
		App::GetApp()->RegisterWav(L"TEN_SE", SeWav);
		//�����������Ƃ���SE
		SeWav = DataDir + L"SE\\decision25.wav";
		App::GetApp()->RegisterWav(L"SEN_SE", SeWav);
		//�{�C�X�F�����I
		wstring VoiceWav = DataDir + L"Voice\\line-girl1_ei1.wav";
		App::GetApp()->RegisterWav(L"VOICE_EI", VoiceWav);
		//�{�C�X�F�Ƃ��I
		VoiceWav = DataDir + L"Voice\\line-girl1_tou1.wav";
		App::GetApp()->RegisterWav(L"VOICE_TOU", VoiceWav);
		//�{�C�X�F�₠�I
		VoiceWav = DataDir + L"Voice\\line-girl1_yaa2.wav";
		App::GetApp()->RegisterWav(L"VOICE_YAA", VoiceWav);
		//�{�C�X�F��I
		VoiceWav = DataDir + L"Voice\\line-girl1_yo1.wav";
		App::GetApp()->RegisterWav(L"VOICE_YO", VoiceWav);
		//�{�C�X�F�����c
		VoiceWav = DataDir + L"Voice\\line-girl1_uu1.wav";
		App::GetApp()->RegisterWav(L"VOICE_UU", VoiceWav);
		//�{�C�X�F�ЂႠ
		VoiceWav = DataDir + L"Voice\\line-girl1_hyaa1.wav";
		App::GetApp()->RegisterWav(L"VOICE_HYAA", VoiceWav);
		//�{�C�X�F�������
		VoiceWav = DataDir + L"Voice\\line-girl1_nanbisuruno1.wav";
		App::GetApp()->RegisterWav(L"VOICE_NANISURUNO", VoiceWav);
		//�{�C�X�F����Ȃ��[
		VoiceWav = DataDir + L"Voice\\line-girl1_sonnaa1.wav";
		App::GetApp()->RegisterWav(L"VOICE_SONNAA", VoiceWav);
	}


	void Scene::OnCreate() {
		CreateResources();
		//�������g�ɃC�x���g�𑗂�
		//����ɂ��e�X�e�[�W��Create���ɃV�[���ɃA�N�Z�X�ł���
		PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitle");
	}

	void Scene::OnUpdate() {
		GetActiveStage()->OnPreUpdateStage();
		GetActiveStage()->OnUpdateStage();
	}
	void Scene::OnDraw() {
		GetActiveStage()->OnDrawStage();
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitle") {
			//�A�N�e�B�u�X�e�[�W��EmptyStage�ɐݒ�
			ResetActiveStage<Title>();
		}
		else if (event->m_MsgStr == L"ToStageSelect") {
			//�A�N�e�B�u�X�e�[�W��EmptyStage�ɐݒ�
			ResetActiveStage<StageSelect>();
		}
		else if (event->m_MsgStr == L"ToGameStage") {
			//�A�N�e�B�u�X�e�[�W��GameStage�ɐݒ�
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToClearResult") {
			//�A�N�e�B�u�X�e�[�W��GameStage�ɐݒ�
			ResetActiveStage<ClearResult>();
		}
		else if (event->m_MsgStr == L"ToGameover") {
			//�A�N�e�B�u�X�e�[�W��GameStage�ɐݒ�
			ResetActiveStage<Gameover>();
		}
		else if (event->m_MsgStr == L"ToEmptyStage") {
			//�A�N�e�B�u�X�e�[�W��EmptyStage�ɐݒ�
			ResetActiveStage<EmptyStage>();
		}
	}

}
//end basecross
