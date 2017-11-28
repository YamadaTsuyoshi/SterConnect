#pragma once
#include "stdafx.h"

namespace basecross {

	class Title : public Stage {
		shared_ptr<StageSprite> m_MessageSprite;		///<���b�Z�[�W��\������X�v���C�g
		//shared_ptr<StageSprite> m_HutonSprite;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Title() {}
		virtual ~Title() {}
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