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

		strTexture = DataDir + L"Texture\\take_A.png";
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
