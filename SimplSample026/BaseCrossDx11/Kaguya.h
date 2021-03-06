#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	///	球体のプレイヤー
	//--------------------------------------------------------------------------------------
	class Kaguya : public GameObject {
		///メッシュ
		shared_ptr<MeshResource> m_SphereMesh;
		///テクスチャリソース名
		wstring m_TextureResName;
		///壁の地点
		float m_BaseX;
		///スケーリングベースの最下地点
		float m_BaseY;
		///位置
		Vec3 m_Posision;
		///透明処理するかどうか
		bool m_Trace;
		///ジャンプのロック
		bool m_JumpLock;
		bool m_UnderRefLock;
		bool m_LeftRefLock;
		bool m_RightRefLock;
		//ライフ
		int m_Life;
		//色
		wstring m_HitObj;
		//アタックフラグ
		bool m_Attackflag;
		float m_AttackTime = 0;
		bool m_Alphaflag;
		//Rigidbodyのshared_ptr
		shared_ptr<Rigidbody> m_Rigidbody;
		///描画データ
		shared_ptr<BcDrawObject> m_PtrObj;
		//描画オブジェクト(weak_ptr)
		weak_ptr<BcPNTStaticRenderer> m_Renderer;
		///シャドウマップ用描画データ
		shared_ptr<ShadowmapObject> m_PtrShadowmapObj;
		//シャドウマップ描画オブジェクト(weak_ptr)
		weak_ptr<ShadowmapRenderer> m_ShadowmapRenderer;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

		bool StartFlag=false;
		float Ttime = 0;
		bool ClearFlag = false;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コントローラから方向ベクトルを得る
		@return	方向ベクトル
		*/
		//--------------------------------------------------------------------------------------
		Vec3 GetMoveVector();
		bool StarFlag = false;
		float StarTime = 10;
	protected:
		float m_Count[4] = {};
		float m_Interval[4] = {};
		bool m_isNullHit[4] = {};
	public:
		bool GetAttack();
		int GetLife();
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージのポインタ
		@param[in]	TextureResName	テクスチャリソース名
		@param[in]	Trace	透明処理するかどうか
		@param[in]	Pos	位置
		*/
		//--------------------------------------------------------------------------------------
		Kaguya(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, bool Trace, const Vec3& Pos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Kaguya();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 位置を得る
		@return	位置
		*/
		//--------------------------------------------------------------------------------------
		virtual Vec3 GetPosition() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		virtual void SetMutekiTime(float time, int CntNum=0);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate2()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	シャドウマップの描画処理(仮想関数)
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDrawShadowmap() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;

		virtual void RndJampVo();

		virtual void RndDamageVo();

		virtual int GetRandom(int min, int max);

		shared_ptr<Rigidbody> GetRigidbody()
		{
			return m_Rigidbody;
		}
		float GetTtime() { return Ttime; };
		void SetStarFlag(bool Flag) { StarFlag = Flag; };
		bool GetStarFlag() { return StarFlag; };
		bool GetClearFlag() { return ClearFlag; };
		void SetLife(int L) { m_Life = L; };
	};

	//--------------------------------------------------------------------------------------
	//	かぐやスプライトスタジオ
	//--------------------------------------------------------------------------------------
	class KaguyaSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
		bool DamageFlag = false;
		float DamageTime;
		bool ClearFlag = false;
		bool GameOverFlag = false;
	public:
		//構築と破棄
		KaguyaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		virtual ~KaguyaSS() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		void SetDamageFlag(bool Flag) { DamageFlag = Flag; };
		void SetClearFlag(bool Flag) { ClearFlag = Flag; };
		void SetGameOverFlag(bool Flag) { GameOverFlag = Flag; };

	};

	//--------------------------------------------------------------------------------------
	//	かぐやスプライトスタジオ（ゲームオーバー）
	//--------------------------------------------------------------------------------------
	class GameoverKaguyaSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
	public:
		//構築と破棄
		GameoverKaguyaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		virtual ~GameoverKaguyaSS() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	かぐやスプライトスタジオ（ステセレ）
	//--------------------------------------------------------------------------------------
	class StageSelectKaguyaSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
		int StageNum = 0;
		bool StartFlag = false;
	public:
		//構築と破棄
		StageSelectKaguyaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		virtual ~StageSelectKaguyaSS() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		void SetStageNum(int num) { StageNum = num; };
	};


}
//end basecross
