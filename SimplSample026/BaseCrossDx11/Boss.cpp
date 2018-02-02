#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class BossEnemy : public Boss;
	//	用途: ボス
	//--------------------------------------------------------------------------------------

	BossEnemy::BossEnemy(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"rasubosu.ssae", L"Wait"),
		m_Posision(Pos),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 1.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void BossEnemy::OnCreate() {

		//タグの追加
		AddTag(L"Boss");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(3.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(1.0f, 1.0f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);

		//ChangeAnimation(L"run");
		SetLooped(true);

		Def = m_Rigidbody->m_Pos;
	}

	Vec3 BossEnemy::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void BossEnemy::SetMutekiTime(float time, int CntNum)
	{
		if (!m_isNullHit[CntNum])
		{
			ChangeAnimation(L"Damege");
			SetFps(20.0f);
			SetLooped(true);
			m_Life += -1;
			m_isNullHit[CntNum] = true;
			m_Interval[CntNum] = time;
		}
	}

	//更新
	void BossEnemy::OnUpdate() {
		Startflag = GetStage<GameStage>()->getStartFlag();
		Def.x = m_Rigidbody->m_Pos.x;
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				if (rightMove)
					m_Rigidbody->m_Velocity.x = Speed.x;
				if (!rightMove)
					m_Rigidbody->m_Velocity.x = -Speed.x;
			}
			/*if (IsAnimeEnd())
			{
			ChangeAnimation(L"Jump");
			SetLooped(false);
			}
			if (IsAnimeEnd()&&A)
			{
			ChangeAnimation(L"Attack");
			SetLooped(true);
			}*/
		}

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrT = GetTransform();
		PtrT->SetPosition(m_Rigidbody->m_Pos);
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}

	void BossEnemy::OnUpdate2() {
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				if (m_Rigidbody->m_Pos.x >= m_BaseX) {
				rightMove = false;
				}
				if (m_Rigidbody->m_Pos.x <= -m_BaseX) {
				rightMove = true;
				}
			}
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			Time += ElapsedTime;
			if (Time > 6.0f&&Startflag) {
				Attackflg = true;
				m_Rigidbody->m_Pos.x = Def.x;
				Speed.x = 0.0f;
				Vec3 v = m_Rigidbody->m_Pos;
				ChangeAnimation(L"Attack");
				SetFps(30.0f);
				SetLooped(false);
				//if (IsAnimeEnd()) {
					wstring Path = App::GetApp()->GetDataDirWString();

					//ファイル名の設定
					wstring Map = Path + L"\\Enemy\\";
					GetStage<Stage>()->AddGameObject<BossBullet>(
						Map, v
						);
				//}
				Time = 0;
			}
			else if (Time>5.0f) {
				Attackflg = false;
				ChangeAnimation(L"Wait");
				SetFps(30.0f);
				SetLooped(true);
				Speed.x = 1.5f;
			}
		}

		m_Rigidbody->m_Pos.y = Def.y;
		m_Rigidbody->m_Pos.z = Def.z;

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Destにボックスタグがあるかどうか調べる
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						if (Attackflg) {
							gamestage->StartDestroySE();
							SetMutekiTime(2.0f);
						}
					}
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Blue")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Red")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				//if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
				//	auto gamestage = GetStage<GameStage>();
				//	gamestage->StartDestroySE();
				//	gamestage->AddEnemyBreak();
				//	ThisDelete();
				//}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Srcにボックスタグがあるかどうか調べる
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						if (Attackflg) {
							gamestage->StartDestroySE();
							SetMutekiTime(2.0f);
						}
					}
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Blue")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Red")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
					if (rightMove) {
						rightMove = false;
					}
					else if (!rightMove) {
						rightMove = true;
					}
				}
				//if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
				//	auto gamestage = GetStage<GameStage>();
				//	gamestage->StartDestroySE();
				//	gamestage->AddEnemyBreak();
				//	ThisDelete();
				//}
				break;
			}
		}

		if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) - 7) {
			//auto gamestage = GetStage<GameStage>();
			//gamestage->StartDestroySE();
			ThisDelete();
		}
		if (m_Life <= 0) {
			ThisDelete();
		}
		for (int i = 0; i < ARRAYSIZE(m_isNullHit); i++)
		{
			if (m_isNullHit[i])
			{
				float delta = App::GetApp()->GetElapsedTime();
				m_Count[i] += delta;

				//if (m_Alphaflag) {
				//	m_PtrObj->m_Alpha += -0.3f;
				//}
				//else if (!m_Alphaflag) {
				//	m_PtrObj->m_Alpha += 0.3f;
				//}

				//if (m_PtrObj->m_Alpha >= 1.0f) {
				//	m_Alphaflag = true;
				//}
				//else if (m_PtrObj->m_Alpha <= 0.4f) {
				//	m_Alphaflag = false;
				//}

				if (m_Count[i] > m_Interval[i])
				{
					//m_PtrObj->m_Alpha = 1.0f;
					m_isNullHit[i] = false;
					m_Count[i] = 0;
				}
			}
		}

	}

	void BossEnemy::ThisDelete()
	{
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Time += ElapsedTime;
		ChangeAnimation(L"Die");
		SetFps(20.0f);
		SetLooped(false);
		GetStage<GameStage>()->SetBossNulltrue();
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		if (Time > 1.0f) {
			GetStage<GameStage>()->RemoveGameObject<BossEnemy>(GetThis<BossEnemy>());
			GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<BossEnemy>());
		}
	}

	//--------------------------------------------------------------------------------------
	//	class BossBullet : public Bullet;
	//	用途: ボスが撃つ弾
	//--------------------------------------------------------------------------------------
	BossBullet::BossBullet(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"Beem.ssae", L"Charge_Rainbow"),
		m_Posision(Pos),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.2f, 1.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0.35f, 0.0f)
		);

	}

	Vec3 BossBullet::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	//初期化
	void BossBullet::OnCreate() {
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		//タグの追加
		AddTag(L"Enemy_Bullet");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(2.0f,10.0f,2.0f);
		body.m_Quat = Quat();
		body.m_Pos = Vec3(m_Posision.x, m_Posision.y-5, m_Posision.z+0.5f);
		body.m_CollType = CollType::typeOBB;
		//body.m_IsDrawActive = true;
		body.m_IsCollisionActive = false;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(10.0f, 10.0f, 10.0f);
		PtrT->SetPosition(m_Posision.x, m_Posision.y, m_Posision.z);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(15.0f);

		//ChangeAnimation(L"run");
		SetLooped(false);

		Def = m_Rigidbody->m_Pos;

	}

	//更新
	void BossBullet::OnUpdate() {
		if (Time > 2.0f) {
			m_Rigidbody->m_IsCollisionActive = true;
			m_AudioObjectPtr->AddAudioResource(L"BEEM_SE");
			m_AudioObjectPtr->Start(L"BEEM_SE", 0, 0.5f);
		}
		m_Rigidbody->m_Pos = Def;
		if (IsAnimeEnd()) {
			ChangeAnimation(L"Fire_Rainbow");
			SetLooped(true);
		}
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrT = GetTransform();
		PtrT->SetPosition(m_Rigidbody->m_Pos);
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}

	void BossBullet::OnUpdate2() {
		m_Rigidbody->m_Pos = Def;
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Time += ElapsedTime;
		if (Time > 3.0f) {
			ThisDelete();
		}
	}

	void BossBullet::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<BossBullet>(GetThis<BossBullet>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<BossBullet>());
	}

	//--------------------------------------------------------------------------------------
	// Bosuusaスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
	BossusaSS::BossusaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"bosuusa.ssae", L"anime_1"),
		m_Posision(Pos),
		m_BaseX(5.5f),
		m_BaseY(0.25f / 2.0f)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 1.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void BossusaSS::OnCreate() {

		//タグの追加
		AddTag(L"Enemy");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(0.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(1.0f, 1.0f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);

		//ChangeAnimation(L"run");
		SetLooped(true);


	}

	//更新
	void BossusaSS::OnUpdate() {

		Startflag = GetStage<GameStage>()->getStartFlag();
		if (Startflag) {
			m_Rigidbody->m_Velocity.y = 1.0f;
			/*if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
			if (rightMove)
			m_Rigidbody->m_Velocity.x = Speed.x;
			if (!rightMove)
			m_Rigidbody->m_Velocity.x = -Speed.x;
			}*/
			/*if (IsAnimeEnd())
			{
			ChangeAnimation(L"Jump");
			SetLooped(false);
			}
			if (IsAnimeEnd()&&A)
			{
			ChangeAnimation(L"attack");
			SetLooped(true);
			}*/
		}

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrT = GetTransform();
		PtrT->SetPosition(m_Rigidbody->m_Pos);
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}

	void BossusaSS::OnUpdate2() {
		if (Startflag) {
			if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) + 7) {
				/*if (m_Rigidbody->m_Pos.x >= m_BaseX) {
				rightMove = false;
				}
				if (m_Rigidbody->m_Pos.x <= -m_BaseX) {
				rightMove = true;
				}*/
			}
		}

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Destにボックスタグがあるかどうか調べる
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						gamestage->AddEnemyBreak();
						ThisDelete();
					}
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
				}
				if (shptr && shptr->FindTag(L"Blue")) {
				}
				if (shptr && shptr->FindTag(L"Red")) {
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
				}
				if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					auto gamestage = GetStage<GameStage>();
					gamestage->StartDestroySE();
					gamestage->AddEnemyBreak();
					ThisDelete();
				}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Srcにボックスタグがあるかどうか調べる
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()) {
						auto gamestage = GetStage<GameStage>();
						gamestage->StartDestroySE();
						gamestage->AddEnemyBreak();
						ThisDelete();
					}
				}
				if (shptr && shptr->FindTag(L"Yellow")) {
				}
				if (shptr && shptr->FindTag(L"Blue")) {
				}
				if (shptr && shptr->FindTag(L"Red")) {
				}
				if (shptr && shptr->FindTag(L"Bamboo")) {
				}
				if (shptr && shptr->FindTag(L"BambooB")) {
				}
				if (shptr && shptr->FindTag(L"Enemy")) {
				}
				if (shptr && shptr->FindTag(L"Enemy_Bullet")) {
					auto gamestage = GetStage<GameStage>();
					gamestage->StartDestroySE();
					gamestage->AddEnemyBreak();
					ThisDelete();
				}
				break;
			}
		}

		if (m_Rigidbody->m_Pos.y <= (GetStage<GameStage>()->GetmaxPosition()) - 7) {
			//auto gamestage = GetStage<GameStage>();
			//gamestage->StartDestroySE();
			//ThisDelete();
		}

	}

	void BossusaSS::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<BossusaSS>(GetThis<BossusaSS>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<BossusaSS>());
	}
}