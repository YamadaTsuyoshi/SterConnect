/*!
@file Scene.cpp
@brief シーンなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ステージ（シーンで管理するインターフェイス）
	//--------------------------------------------------------------------------------------
	void Stage::OnPreCreate() {
		//Rigidbodyマネージャの初期化
		m_RigidbodyManager
			= ObjectFactory::Create<RigidbodyManager>(GetThis<Stage>());
	}


	//追加オブジェクトの指定
	void Stage::PushBackGameObject(const shared_ptr<GameObject>& Ptr) {
		//このステージはクリエイト後である
		if (IsCreated()) {
			m_WaitAddObjectVec.push_back(Ptr);
		}
		else {
			//クリエイト前
			m_GameObjectVec.push_back(Ptr);
		}
	}
	//削除オブジェクトの指定
	void Stage::RemoveBackGameObject(const shared_ptr<GameObject>& Ptr) {
		m_WaitRemoveObjectVec.push_back(Ptr);
	}
	//オブジェクトの削除
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
	//追加や削除待ちになってるオブジェクトを追加削除する
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
	//	コンポーネントImplクラス
	//--------------------------------------------------------------------------------------
	struct Transform::Impl {
		weak_ptr<GameObject> m_GameObject;
		bool m_UpdateActive{ true };	//updateするかどうか
		bool m_DrawActive{ true };		//Drawするかどうか




		bool m_Init{ false };	//初期化済みかどうか（1回目のUpdateで、Beforeに値を入れる）
								//1つ前の変数
		bsm::Vec3 m_BeforeScale;
		bsm::Vec3 m_BeforePivot;
		bsm::Quat m_BeforeQuaternion;
		bsm::Vec3 m_BeforePosition;
		//再計算抑制用変数
		bool m_BeforeChangeed;
		bsm::Mat4x4 m_BeforeWorldMatrix;
		//現在の変数
		bsm::Vec3 m_Scale;
		bsm::Vec3 m_Pivot;
		bsm::Quat m_Quaternion;
		bsm::Vec3 m_Position;
		//再計算抑制用変数
		bool m_Changeed;
		bsm::Mat4x4 m_WorldMatrix;
		//親オブジェクト
		weak_ptr<GameObject> m_Parent;
		Impl() :
			//スケールのみ初期化（他はデフォルト処理でよい）
			m_BeforeScale(1.0f, 1.0f, 1.0f),
			m_Scale(1.0f, 1.0f, 1.0f),
			m_BeforeChangeed(true),
			m_Changeed(true)
		{}
		~Impl() {}
	};


	//--------------------------------------------------------------------------------------
	///	変換オブジェクト
	//--------------------------------------------------------------------------------------

	//アクセサ
	shared_ptr<GameObject> Transform::GetGameObject() const {
		auto shptr = pImpl->m_GameObject.lock();
		if (!shptr) {
			throw BaseException(
				L"GameObjectは有効ではありません",
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

	//アクセサ
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
			//nullptrが渡された
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
		//前回のターンからの時間
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

	//操作
	void Transform::OnUpdate() {
		if (!pImpl->m_Init) {
			SetToBefore();
			pImpl->m_Init = true;
		}
	}

	//--------------------------------------------------------------------------------------
	///	ゲームオブジェクトの親
	//--------------------------------------------------------------------------------------
	void GameObject::OnPreCreate() {
		m_Transform = ObjectFactory::Create<Transform>(GetThis<GameObject>());
	}





	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	Scene::Scene() :
		SceneInterface()
	{
	}

	void Scene::CreateResources() {
		wstring DataDir;
		//サンプルのためアセットディレクトリを取得
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"Texture\\kaguya-01.png";
		App::GetApp()->RegisterTexture(L"KAGUYA_TX", strTexture);
		strTexture = DataDir + L"Texture\\StageMessage.png";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		strTexture = DataDir + L"Texture\\SUBARU_noAnime.png";
		App::GetApp()->RegisterTexture(L"SUBARU_TX", strTexture);
		strTexture = DataDir + L"Texture\\BackGr.png";
		App::GetApp()->RegisterTexture(L"BG_TX", strTexture);
		strTexture = DataDir + L"Texture\\UIspace.png";
		App::GetApp()->RegisterTexture(L"UI_BG_TX", strTexture);
		strTexture = DataDir + L"Texture\\go-ru.png";
		App::GetApp()->RegisterTexture(L"GOAL_TX", strTexture);

		strTexture = DataDir + L"Texture\\hoshi_title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"Texture\\stage_select.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_TX", strTexture);
		strTexture = DataDir + L"Texture\\clear.PNG";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		strTexture = DataDir + L"Texture\\gameover.PNG";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);

		strTexture = DataDir + L"Texture\\anybo.png";
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

		//敵
		strTexture = DataDir + L"Texture\\WhiteRabbit_noAnime.png";
		App::GetApp()->RegisterTexture(L"RABBIT_TX", strTexture);
		strTexture = DataDir + L"Texture\\dango.png";
		App::GetApp()->RegisterTexture(L"RABBIT_BULLET_TX", strTexture);

		//光ゲージ
		strTexture = DataDir + L"Texture\\Hikarigage_Base.png";
		App::GetApp()->RegisterTexture(L"LIGHTGAGE_A_TX", strTexture);
		strTexture = DataDir + L"Texture\\Hikarigage_gage.png";
		App::GetApp()->RegisterTexture(L"LIGHTGAGE_B_TX", strTexture);
		strTexture = DataDir + L"Texture\\Hikarigage_gage_R.png";
		App::GetApp()->RegisterTexture(L"LIGHTGAGE_B_R_TX", strTexture);
		
		//ライフ
		strTexture = DataDir + L"Texture\\LifeHeal.png";
		App::GetApp()->RegisterTexture(L"LIFE_TX", strTexture);

		//goal
		strTexture = DataDir + L"Texture\\Cloud&Ship.png";
		App::GetApp()->RegisterTexture(L"GOAL2_TX", strTexture);

		//Take
		strTexture = DataDir + L"Texture\\take_B.png";
		App::GetApp()->RegisterTexture(L"Bamboo_B_TX", strTexture);
		


		//ボーンモデルのリソース
		auto ModelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"temp\\Chara_R.bmf");
		App::GetApp()->RegisterResource(L"Chara_R_MESH", ModelMesh);
		//ボーンモデルのタンジェント付きリソース
		ModelMesh = MeshResource::CreateBoneModelMeshWithTangent(DataDir, L"temp\\Chara_R.bmf");
		App::GetApp()->RegisterResource(L"Chara_R_MESH_WITH_TAN", ModelMesh);
		//法線マップ
		strTexture = DataDir + L"temp\\Chara_R_narmal.png";
		App::GetApp()->RegisterTexture(L"Chara_R_NORMAL_TX", strTexture);

		//スタティックモデルのリソースとして読み込み
		auto StaticModelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"temp\\Character_01.bmf");
		App::GetApp()->RegisterResource(L"MODEL_MESH", StaticModelMesh);

		//スタティックモデルのタンジェント付きリソースとして読み込み
		StaticModelMesh = MeshResource::CreateStaticModelMeshWithTangent(DataDir, L"temp\\Character_01.bmf");
		App::GetApp()->RegisterResource(L"MODEL_MESH_WITH_TAN", StaticModelMesh);
		//法線マップ
		strTexture = DataDir + L"temp\\Character_2_normal.png";
		App::GetApp()->RegisterTexture(L"MODEL_NORMAL_TX", strTexture);
		//エフェクト
		strTexture = DataDir + L"temp\\spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = DataDir + L"temp\\fire.png";
		App::GetApp()->RegisterTexture(L"FIRE_TX", strTexture);

		//サウンド
		wstring CursorWav = DataDir + L"Sound\\se1.wav";
		App::GetApp()->RegisterWav(L"SE", CursorWav);
		//タイトルBGM
		wstring strMusic = DataDir + L"Sound\\Title.wav";
		App::GetApp()->RegisterWav(L"TITLE_BGM", strMusic);
		//ステージセレクトBGM
		strMusic = DataDir + L"Sound\\StageSelect.wav";
		App::GetApp()->RegisterWav(L"STAGESELECT_BGM", strMusic);
		//ゲームBGM
		strMusic = DataDir + L"Sound\\GameStage.wav";
		App::GetApp()->RegisterWav(L"GAMESTAGE_BGM", strMusic);
	}


	void Scene::OnCreate() {
		CreateResources();
		//自分自身にイベントを送る
		//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
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
			//アクティブステージをEmptyStageに設定
			ResetActiveStage<Title>();
		}
		else if (event->m_MsgStr == L"ToStageSelect") {
			//アクティブステージをEmptyStageに設定
			ResetActiveStage<StageSelect>();
		}
		else if (event->m_MsgStr == L"ToGameStage") {
			//アクティブステージをGameStageに設定
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToClearResult") {
			//アクティブステージをGameStageに設定
			ResetActiveStage<ClearResult>();
		}
		else if (event->m_MsgStr == L"ToGameover") {
			//アクティブステージをGameStageに設定
			ResetActiveStage<Gameover>();
		}
		else if (event->m_MsgStr == L"ToEmptyStage") {
			//アクティブステージをEmptyStageに設定
			ResetActiveStage<EmptyStage>();
		}
	}

	


}
//end basecross
