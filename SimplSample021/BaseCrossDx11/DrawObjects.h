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
		vector<DrawObject> m_DrawObjectVec;
		vector<DrawObject> m_TraceDrawObjectVec;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`��T�u����
		@param[in]	ObjectVec	�`�悷��z��
		@param[in]	sb	�R���X�^���g�o�b�t�@
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void OnDrawSub(vector<DrawObject>& ObjectVec, SimpleConstants& sb);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		*/
		//--------------------------------------------------------------------------------------
		PNTDrawObject(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PNTDrawObject();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`�悷��I�u�W�F�N�g��ǉ�����
		@param[in]	MeshRes	���b�V��
		@param[in]	TextureRes �e�N�X�`��
		@param[in]	WorldMat ���[���h�s��
		@param[in]	Trace �����������邩�ǂ���
		@param[in]	Wrap ���b�s���O�������邩�ǂ���
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void AddDrawMesh(const shared_ptr<MeshResource>& MeshRes,
			const shared_ptr<TextureResource>& TextureRes,
			const Mat4x4& WorldMat,
			bool Trace, bool Wrap = false);
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
