#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	///	���̂̃v���C���[
	//--------------------------------------------------------------------------------------
	class Kaguya : public GameObject {
		///���b�V��
		shared_ptr<MeshResource> m_SphereMesh;
		///�e�N�X�`�����\�[�X��
		wstring m_TextureResName;
		///�ǂ̒n�_
		float m_BaseX;
		///�X�P�[�����O�x�[�X�̍ŉ��n�_
		float m_BaseY;
		///�ʒu
		Vec3 m_Posision;
		///�����������邩�ǂ���
		bool m_Trace;
		///�W�����v�̃��b�N
		bool m_JumpLock;
		bool m_UnderRefLock;
		bool m_LeftRefLock;
		bool m_RightRefLock;
		//���C�t
		int m_Life;
		//�F
		wstring m_HitObj;
		//�A�^�b�N�t���O
		bool m_Attackflag;
		bool m_Alphaflag;
		//Rigidbody��shared_ptr
		shared_ptr<Rigidbody> m_Rigidbody;
		///�`��f�[�^
		shared_ptr<BcDrawObject> m_PtrObj;
		//�`��I�u�W�F�N�g(weak_ptr)
		weak_ptr<BcPNTStaticRenderer> m_Renderer;
		///�V���h�E�}�b�v�p�`��f�[�^
		shared_ptr<ShadowmapObject> m_PtrShadowmapObj;
		//�V���h�E�}�b�v�`��I�u�W�F�N�g(weak_ptr)
		weak_ptr<ShadowmapRenderer> m_ShadowmapRenderer;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

		bool StartFlag=false;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���g���[����������x�N�g���𓾂�
		@return	�����x�N�g��
		*/
		//--------------------------------------------------------------------------------------
		Vec3 GetMoveVector();
	protected:
		float m_Count[4] = {};
		float m_Interval[4] = {};
		bool m_isNullHit[4] = {};
	public:
		bool GetAttack();
		int GetLife();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		@param[in]	TextureResName	�e�N�X�`�����\�[�X��
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	Pos	�ʒu
		*/
		//--------------------------------------------------------------------------------------
		Kaguya(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, bool Trace, const Vec3& Pos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Kaguya();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �ʒu�𓾂�
		@return	�ʒu
		*/
		//--------------------------------------------------------------------------------------
		virtual Vec3 GetPosition() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		virtual void SetMutekiTime(float time, int CntNum=0);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate2()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�V���h�E�}�b�v�̕`�揈��(���z�֐�)
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDrawShadowmap() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`��
		@return	�Ȃ�
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
	};

	//--------------------------------------------------------------------------------------
	//	������X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	class KaguyaSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
	public:
		//�\�z�Ɣj��
		KaguyaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		virtual ~KaguyaSS() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	������X�v���C�g�X�^�W�I�i�Q�[���I�[�o�[�j
	//--------------------------------------------------------------------------------------
	class GameoverKaguyaSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
	public:
		//�\�z�Ɣj��
		GameoverKaguyaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		virtual ~GameoverKaguyaSS() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};


}
//end basecross
