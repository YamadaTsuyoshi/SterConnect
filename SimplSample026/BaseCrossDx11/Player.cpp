/*!
@file Player.cpp
@brief プレイヤー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	球体のプレイヤー実体
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

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0|| CntlVec[0].fThumbLY != 0) {
				float MoveLength = 0;	//動いた時のスピード
										//進行方向の向きを計算
				//Vec3 Front = m_Rigidbody->m_Pos - CameraEye;
				//Front.z = 0;
				//Front.normalize();
				////進行方向向きからの角度を算出
				//float FrontAngle = atan2(Front.z, Front.x);
				////コントローラの向き計算
				//float MoveX = CntlVec[0].fThumbLX;
				//float MoveY = CntlVec[0].fThumbLY;
				//Vec2 MoveVec(MoveX, MoveY);
				//float MoveSize = length(MoveVec);
				////コントローラの向きから角度を計算
				//float CntlAngle = atan2(MoveX, MoveY);
				////トータルの角度を算出
				//float TotalAngle = FrontAngle + CntlAngle;
				////角度からベクトルを作成
				//Angle = Vec3(sin(TotalAngle), cos(TotalAngle), 0);
				////正規化する
				//Angle.normalize();
				////移動サイズを設定。
				//Angle *= MoveSize;
				////Y軸は変化させない
				//Angle.z = 0;

				Vec3 Front = m_Rigidbody->m_Pos;
				Front.z = 0;
				Front.normalize();
				//進行方向向きからの角度を算出
				//float FrontAngle = atan2(Front.z, Front.x);
				//コントローラの向き計算
				float MoveX = CntlVec[0].fThumbLX;
				float MoveY = CntlVec[0].fThumbLY;
				Vec2 MoveVec(MoveX, MoveY);
				float MoveSize = length(MoveVec);
				//コントローラの向きから角度を計算
				float CntlAngle = atan2(MoveX, MoveY);
				//トータルの角度を算出
				float TotalAngle =+ CntlAngle;
				//角度からベクトルを作成
				Angle = Vec3(sin(TotalAngle), cos(TotalAngle), 0);
				//正規化する
				Angle.normalize();
				//移動サイズを設定。
				Angle *= MoveSize;
				//Y軸は変化させない
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
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//タグの追加
		AddTag(L"Player");
		//Rigidbodyの初期化
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

		//行列の定義
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

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}
	void Player::OnUpdate() {
		Startflag = GetStage<GameStage>()->getStartFlag();
		if (Startflag) {
			//前回のターンからの経過時間を求める
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			//コントローラの取得
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected) {
				//Aボタン
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
			////カメラの位置
			//Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
			//m_Rigidbody->m_Pos.y = CameraEye.y;
		}
	}

		void Player::OnUpdate2() {
			if(Startflag){
			//プレイヤーのＺ位置は強制的に0.0にする
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
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
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
		//行列の定義
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

	//初期化
	void SubaruSS::OnCreate() {

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(1.4f, 1.4f, 1.0f);
		//PtrT->SetPosition(Vec3(0, 5.0f, 1.0f));
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);

		//ChangeAnimation(L"run");
		SetLooped(true);


	}

	//更新
	void SubaruSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		auto PtrGameStage = GetStage<GameStage>();
		GetTransform()->SetPosition(PtrGameStage->GetP_Pos());
		UpdateAnimeTime(ElapsedTime);
	}

}
//end basecross
