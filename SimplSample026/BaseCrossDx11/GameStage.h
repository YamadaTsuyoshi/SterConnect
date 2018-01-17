/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {



	//--------------------------------------------------------------------------------------
	///	ゲームステージ
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//描画オブジェクトの追加
		void CreateDrawObjects();
		//以下、別に保存しておく
		//文字列描画オブジェクト
		shared_ptr<StringDrawObject> m_StringDrawObject;
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		//PCTボックスの登録（リソース登録する）
		void RegisterPctlBox();

		float maxPosition;

		Vec3 P_Pos;

		float m_Time;

		float interval_Time;

		bool Pointflag = false;
		bool Barflag = false;
		int PointCount = 0;

		Vec3 PointPos1;
		Vec3 PointPos2;

		typedef enum {
			Yellow,
			Red,
			Blue
		} eMenu;

		int P_color = 0;
		bool PointDeleteflag = false;

		//CSV
		CsvFile m_Csv;

		//DataIDを管理するフラグ
		bool dataIdFlag = false;

		float life_x = 0;

		float lightbar;
		shared_ptr<Life> lifeobj;
		vector<shared_ptr<Life>> lifegroup;

		shared_ptr<Fade> m_FadeSprite;
		
		bool Startflag = false;

		Vec3 KaguyaPos;

		wstring AnimeName;

	public:
		bool FadeFlag = false;
		bool FadeFlag2 = false;
		bool ClearFlag = false;
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		GameStage();
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameStage() {}
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

		vector<shared_ptr<Life>> Getlifegroup(){ return lifegroup; };

		Vec3 GetP_Pos() { return P_Pos; }

		void CrBar();

		bool getPointDeleteFlag() { return PointDeleteflag; };

		float GetmaxPosition() { return maxPosition; }

		void Csv();

		void StopBGM();

		void StartDestroySE();

		bool getStartFlag() { return Startflag; };

		Vec3 GetKaguyaPos() { return KaguyaPos; }

	};


	//--------------------------------------------------------------------------------------
	///	空のステージ（メッセージのみある）
	//--------------------------------------------------------------------------------------
	class EmptyStage : public Stage {
		shared_ptr<MessageSprite> m_MessageSprite;		///<メッセージを表示するスプライト
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		EmptyStage() {}
		virtual ~EmptyStage() {}
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
//end basecross
