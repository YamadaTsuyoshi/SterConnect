/*!
@file DrawObjects.h
@brief �`��I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Scene;
	class Stage;
	class GameObject;

	//--------------------------------------------------------------------------------------
	///	PNT���_�`��Ɏg�p����\����
	//--------------------------------------------------------------------------------------
	struct DrawObject {
		shared_ptr<MeshResource> m_MeshRes;
		shared_ptr<TextureResource> m_TextureRes;
		Mat4x4 m_WorldMatrix;
		bool m_Trace;
		bool m_Wrap;
		DrawObject() :
			m_MeshRes(nullptr),
			m_TextureRes(nullptr),
			m_WorldMatrix(),
			m_Trace(false),
			m_Wrap(false)
		{}
	};


	//--------------------------------------------------------------------------------------
	///	PNT���_�I�u�W�F�N�g�̕`��N���X
	//--------------------------------------------------------------------------------------
	class PNTDrawObject : public GameObject {
		vector<shared_ptr<DrawObject>> m_DrawObjectVec;
		vector<shared_ptr<DrawObject>> m_TraceDrawObjectVec;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`��T�u����
		@param[in]	ObjectVec	�`�悷��z��
		@param[in]	sb	�R���X�^���g�o�b�t�@
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void OnDrawSub(const vector<shared_ptr<DrawObject>>& ObjectVec, SimpleConstants& sb);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		*/
		//--------------------------------------------------------------------------------------
		explicit PNTDrawObject(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNTDrawObject();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�悷��I�u�W�F�N�g��ǉ�����
		@param[in]	Obj	�`�悷��I�u�W�F�N�g�̃|�C���^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AddDrawMesh(const shared_ptr<DrawObject>& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
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
