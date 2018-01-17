/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {



	//--------------------------------------------------------------------------------------
	///	�Q�[���X�e�[�W
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�`��I�u�W�F�N�g�̒ǉ�
		void CreateDrawObjects();
		//�ȉ��A�ʂɕۑ����Ă���
		//������`��I�u�W�F�N�g
		shared_ptr<StringDrawObject> m_StringDrawObject;
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		//PCT�{�b�N�X�̓o�^�i���\�[�X�o�^����j
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

		//DataID���Ǘ�����t���O
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
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		GameStage();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameStage() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�e�[�W�X�V�i�������z�֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdateStage() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�e�[�W�`��i�������z�֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDrawStage() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`��
		@return	�Ȃ�
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
	///	��̃X�e�[�W�i���b�Z�[�W�݂̂���j
	//--------------------------------------------------------------------------------------
	class EmptyStage : public Stage {
		shared_ptr<MessageSprite> m_MessageSprite;		///<���b�Z�[�W��\������X�v���C�g
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		EmptyStage() {}
		virtual ~EmptyStage() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�e�[�W�X�V�i�������z�֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdateStage() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�e�[�W�`��i�������z�֐��j
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDrawStage() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};




}
//end basecross
