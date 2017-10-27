/*!
@file Player.cpp
@brief プレイヤー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	プレイヤー実体
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
		m_Velocity(0, 0, 0)
	{}
	Player::~Player() {}

	Vec3 Player::GetMoveVector() const {
		Vec3 Angle(0, 0, 0);
		auto PtrGameStage = GetStage<GameStage>();
		Vec3 CameraEye, CameraAt;
		PtrGameStage->GetCamera().GetCameraEyeAt(CameraEye, CameraAt);

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0 || CntlVec[0].fThumbLY != 0) {
				float MoveLength = 0;	//動いた時のスピード
										//進行方向の向きを計算
				Vec3 Front = m_Pos - CameraEye;
				Front.z = 0;
				Front.normalize();
				if (m_Pos.x <= 0) {
					//進行方向向きからの角度を算出
					float FrontAngle = atan2(Front.y, Front.x);
					//コントローラの向き計算
					float MoveX = CntlVec[0].fThumbLX;
					float MoveY = CntlVec[0].fThumbLY;
					Vec2 MoveVec(MoveX, MoveY);
					float MoveSize = length(MoveVec);
					//コントローラの向きから角度を計算
					float CntlAngle = atan2(-MoveX, MoveY);
					//トータルの角度を算出
					float TotalAngle = FrontAngle + CntlAngle;
					//角度からベクトルを作成
					Angle = Vec3(cos(TotalAngle), sin(TotalAngle), 0);
					//正規化する
					Angle.normalize();
					//移動サイズを設定。
					Angle *= MoveSize;
					//Y軸は変化させない
					Angle.z = 0;
				}
				else {
					//進行方向向きからの角度を算出
					float FrontAngle = atan2(Front.y, Front.x);
					//コントローラの向き計算
					float MoveX = CntlVec[0].fThumbLX;
					float MoveY = CntlVec[0].fThumbLY;
					Vec2 MoveVec(MoveX, MoveY);
					float MoveSize = length(MoveVec);
					//コントローラの向きから角度を計算
					float CntlAngle = atan2(MoveX, -MoveY);
					//トータルの角度を算出
					float TotalAngle = FrontAngle + CntlAngle;
					//角度からベクトルを作成
					Angle = Vec3(cos(TotalAngle), sin(TotalAngle), 0);
					//正規化する
					Angle.normalize();
					//移動サイズを設定。
					Angle *= MoveSize;
					//Y軸は変化させない
					Angle.z = 0;
				}
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
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//タグの追加
		AddTag(L"Player");

		//ワールド行列の決定
		Mat4x4 World;
		World.affineTransformation(m_Scale, Vec3(0, 0, 0),
			m_Qt, m_Pos);
		//データの初期化
		m_PtrObj = make_shared<DrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Trace = true;
		m_PtrObj->m_Wrap = true;

	}
	void Player::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			Vec3 Direction = GetMoveVector();
			if (length(Direction) < 0.1f) {
				m_Velocity *= 0.9f;
			}
			else {
				m_Velocity = Direction * 5.0f;
			}
		m_Pos += (m_Velocity * ElapsedTime);
	}





	void Player::OnDraw() {
		auto PtrGameStage = GetStage<GameStage>();
		//ワールド行列の決定
		Mat4x4 World;
		World.affineTransformation(m_Scale, Vec3(0, 0, 0),
			m_Qt, m_Pos);
		m_PtrObj->m_WorldMatrix = World;
		auto shptr = PtrGameStage->FindTagGameObject<PNTDrawObject>(L"PNTDrawObject");
		shptr->AddDrawMesh(m_PtrObj);
	}


}
//end basecross
