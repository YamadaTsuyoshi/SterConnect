#pragma once
#include "stdafx.h"

namespace basecross {

	class StageSelect : public Stage {
		//描画オブジェクトの追加
		void CreateDrawObjects();
		shared_ptr<StageSprite> m_MessageSprite;		///<メッセージを表示するスプライト
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		shared_ptr<Fade> m_FadeSprite;
		shared_ptr<DefSp> m_kaguya;
		bool FadeFlag = false;
		bool FadeFlag2 = false;
		bool onectrl;
		int Selecter = 0;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		StageSelect() {}
		virtual ~StageSelect() {}
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

	//--------------------------------------------------------------------------------------
	//	ステージセレクトスプライトスタジオ
	//--------------------------------------------------------------------------------------
	class StageSelectSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
		int StageNum = 0;
	public:
		//構築と破棄
		StageSelectSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		virtual ~StageSelectSS() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		void SetStageNum(int num) { StageNum = num; };
	};

}