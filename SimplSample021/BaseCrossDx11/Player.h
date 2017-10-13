/*!
@file Player.h
@brief プレイヤー
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		//メッシュ
		shared_ptr<MeshResource> m_SphereMesh;
		wstring m_TextureResName;		///<テクスチャリソース名
		Vec3 m_Scale;				///<スケーリング
		float m_BaseY;				///<スケーリングベースの最下地点
		Quat m_Qt;			///<回転
		Vec3 m_Pos;				///<位置
		bool m_Trace;					///<透明処理するかどうか
		Vec3 m_Velocity;		//速度
		Vec3 m_Gravity;		//自由落下加速度
		Vec3 m_GravityVelocity;		//自由落下による速度
		bool m_JumpLock;	//ジャンプのロック
		Vec3 m_BeforePos;	//1つ前の位置
		float m_Mass;

		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラから方向ベクトルを得る
		@return	方向ベクトル
		*/
		//--------------------------------------------------------------------------------------
		Vec3 GetMoveVector() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 進行方向を向く
		@param[in]	LerpFact	補間係数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void RotToHead(float LerpFact);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージのポインタ
		@param[in]	TextureResName	テクスチャリソース名
		@param[in]	Trace	透明処理するかどうか
		@param[in]	Pos	位置
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, bool Trace, const Vec3& Pos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player();
		//--------------------------------------------------------------------------------------
		/*!
		@brief SPHEREを得る
		@return	SPHERE
		*/
		//--------------------------------------------------------------------------------------
		SPHERE GetSPHERE()const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 位置を得る
		@return	位置
		*/
		//--------------------------------------------------------------------------------------
		virtual Vec3 GetPosition() override {
			return m_Pos;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 1つ前の位置を得る
		@return	1つ前の位置
		*/
		//--------------------------------------------------------------------------------------
		Vec3 GetBeforePos()const {
			return m_BeforePos;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};



}
//end basecross
