#pragma once
#include "stdafx.h"

namespace basecross {

	class ClearResult : public Stage {
		shared_ptr<StageSprite> m_MessageSprite;		///<メッセージを表示するスプライト
		shared_ptr<DefSp> L1;
		shared_ptr<DefSp> L2;
		shared_ptr<DefSp> L3;
		shared_ptr<NumSprite> TimeNum_1;
		shared_ptr<NumSprite> TimeNum_2;
		shared_ptr<NumSprite> TimeNum_3;
		shared_ptr<NumSprite> TimeNum_4;
		shared_ptr<NumSprite> EnemyNum;
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		shared_ptr<Fade> m_FadeSprite;
		bool FadeFlag = false;
		bool FadeFlag2 = false;
		bool onectrl;
		int Selecter = 0;
		float m_Time_Sec;
		float m_Time_Min;
		float m_EnemyBreak;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		ClearResult() {}
		virtual ~ClearResult() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージ更新（純粋仮想関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdateStage() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージ描画（純粋仮想関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDrawStage() override;
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

	class Gameover : public Stage {
		//描画オブジェクトの追加
		void CreateDrawObjects();
		shared_ptr<StageSprite> m_BG;
		shared_ptr<StageSprite> m_Text;
		shared_ptr<DefSp> L1;
		shared_ptr<DefSp> L2;
		shared_ptr<DefSp> L3;
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		shared_ptr<Fade> m_FadeSprite;
		bool FadeFlag = false;
		bool FadeFlag2 = false;
		bool onectrl;
		int Selecter=0;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Gameover() {}
		virtual ~Gameover() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージ更新（純粋仮想関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdateStage() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ステージ描画（純粋仮想関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDrawStage() override;
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