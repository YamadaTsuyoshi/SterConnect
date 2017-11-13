/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Scene;
	class Stage;
	class GameObject;


	//--------------------------------------------------------------------------------------
	//class MultiSpark : public MultiParticle;
	//�p�r: �����̃X�p�[�N�N���X
	//--------------------------------------------------------------------------------------
	class MultiSpark : public MultiParticle {
	public:
		//�\�z�Ɣj��
		MultiSpark(shared_ptr<Stage>& StagePtr);
		virtual ~MultiSpark();
		//������
		virtual void OnCreate() override;
		void InsertSpark(const Vec3& Pos);
		virtual void OnUpdate() override;

	};

	//--------------------------------------------------------------------------------------
	//class MultiFire : public MultiParticle;
	//�p�r: �����̉��N���X
	//--------------------------------------------------------------------------------------
	class MultiFire : public MultiParticle {
	public:
		//�\�z�Ɣj��
		MultiFire(shared_ptr<Stage>& StagePtr);
		virtual ~MultiFire();
		//������
		virtual void OnCreate() override;
		void InsertFire(const Vec3& Pos);
	};

	//--------------------------------------------------------------------------------------
	//Square�`��̃I�v�V����
	//--------------------------------------------------------------------------------------
	enum class SquareDrawOption {
		Billboard,	//�r���{�[�h
		Faceing,	//�t�F�C�V���O
		FaceingY,	//�t�F�C�V���O(Y���̂�)
		Normal		//�ʏ�(�蓮�B��]�͐��K���̂ݍs��)
	};

	//--------------------------------------------------------------------------------------
	///	�V���v����3D��̕���
	//--------------------------------------------------------------------------------------
	class SimpleSquare : public GameObject {
		//�o�b�N�A�b�v���Ă������_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;
		//���b�V��
		shared_ptr<MeshResource> m_SquareMesh;
		//�e�N�X�`�����\�[�X��
		wstring m_TextureResName;
		//��]�̕`��I�v�V����
		SquareDrawOption m_DrawOption;
		Vec3 m_Scale;				///<�X�P�[�����O
		Quat m_Qt;			///<��]
		Vec3 m_Pos;				///<�ʒu
		float m_TotalTime;
		//�`��f�[�^
		shared_ptr<SimpleDrawObject> m_PtrObj;
		//�`��I�u�W�F�N�g(weak_ptr)
		weak_ptr<SimplePCTStaticRenderer> m_Renderer;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���_�̍쐬
		@param[in]	WrapX	X�����̃^�C�����O
		@param[in]	WrapY	Y�����̃^�C�����O
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void CreateBuffers(float WrapX, float WrapY);
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���_�̕ύX
		@param[in]	ElapsedTime	�^�[������
		@param[out]	vertices	�}�b�v���ꂽ���_�f�[�^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		@param[in]	TextureResName	�e�N�X�`�����\�[�X��
		@param[in]	Scale	�X�P�[�����O
		@param[in]	Pos	�ʒu
		@param[in]	Option	�`��I�v�V����
		*/
		//--------------------------------------------------------------------------------------
		SimpleSquare(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName,
			const Vec3& Scale, const Vec3& Pos, const Quat& Qt, SquareDrawOption Option);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SimpleSquare();
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
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};


	//--------------------------------------------------------------------------------------
	///	�V���v����3D��̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class SimpleBox : public GameObject {
		//�e�N�X�`�����\�[�X��
		wstring m_TextureResName;
		Vec3 m_Scale;				///<�X�P�[�����O
		Quat m_Qt;			///<��]
		Vec3 m_Pos;				///<�ʒu
		//�`��f�[�^
		shared_ptr<SimpleDrawObject> m_PtrObj;
		//�`��I�u�W�F�N�g(weak_ptr)
		weak_ptr<SimplePCTStaticRenderer> m_Renderer;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		@param[in]	TextureResName	�e�N�X�`�����\�[�X��
		@param[in]	Scale	�X�P�[�����O
		@param[in]	Pos	�ʒu
		*/
		//--------------------------------------------------------------------------------------
		SimpleBox(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName,
			const Vec3& Scale, const Vec3& Pos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SimpleBox();
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



	//--------------------------------------------------------------------------------------
	///	���b�s���O�������ꂽ�X�v���C�g�i�e�j
	//--------------------------------------------------------------------------------------
	class SpriteBase : public GameObject {
	public:
		//�u�����h���@
		enum class BlendState {
			Opaque,
			Trace,
			Additive
		};
	protected:
		//���b�V��
		shared_ptr<MeshResource> m_SquareMesh;
		//�o�b�N�A�b�v���Ă������_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;
		wstring m_TextureResName;		///<�e�N�X�`�����\�[�X��
		Vec2 m_Scale;				///<�X�P�[�����O
		float m_Rot;				///<��]
		Vec2 m_Pos;				///<�ʒu
		UINT m_XWrap;		//X�����̃��b�v��
		UINT m_YWrap;		//Y�����̃��b�v��
		Col4 m_Emissive;	//�G�~�b�V�u�F
		BlendState m_BlendState;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		@param[in]	TextureResName	�����e�N�X�`�����\�[�X��
		@param[in]	StartScale	�����傫��
		@param[in]	StartRot	������]
		@param[in]	StartPos	�����ʒu
		@param[in]	XWrap	X�����̃��b�v��
		@param[in]	YWrap	Y�����̃��b�v��
		*/
		//--------------------------------------------------------------------------------------
		SpriteBase(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName,
			const Vec2& StartScale,
			float StartRot,
			const Vec2& StartPos,
			UINT XWrap,UINT YWrap);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SpriteBase() {}
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �o�b�N�A�b�v���_�̏C��(���z�֐�)�B�h���N���X�͓Ǝ��̒��_�����C��������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AdjustVertex() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���_�̕ύX(���z�֐�)�B�h���N���X�͓Ǝ��̒��_�ύX������
		@param[in]	ElapsedTime	�^�[������
		@param[out]	vertices	�}�b�v���ꂽ���_�f�[�^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void UpdateVertex(float ElapsedTime,VertexPositionColorTexture* vertices) {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �e�N�X�`�����\�[�X���̎擾
		@return	�e�N�X�`�����\�[�X��
		*/
		//--------------------------------------------------------------------------------------
		const wstring& GetTextureResName() const {
			return m_TextureResName;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �e�N�X�`�����\�[�X���̕ύX
		@param[in]	col	���\�[�X��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTextureResName(const wstring& textureResName) {
			m_TextureResName = textureResName;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �u�����h���@�̎擾
		@return	�u�����h���@
		*/
		//--------------------------------------------------------------------------------------
		const BlendState& GetBlendState() const {
			return m_BlendState;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �u�����h���@�̕ύX
		@param[in]	col	�ύX�F
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetBlendState(BlendState blendState) {
			m_BlendState = blendState;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �G�~�b�V�u�F�̎擾
		@return	�G�~�b�V�u�F
		*/
		//--------------------------------------------------------------------------------------
		const Col4& GetEmissive() const {
			return m_Emissive;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �G�~�b�V�u�F�̕ύX
		@param[in]	col	�ύX�F
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetEmissive(const Col4& col) {
			m_Emissive = col;
		}
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
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �`��
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};


	//--------------------------------------------------------------------------------------
	///	��]����X�v���C�g
	//--------------------------------------------------------------------------------------
	class RotateSprite : public SpriteBase {
		float m_TotalTime;	//���_�ύX�Ɏg�p����^�C��
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �o�b�N�A�b�v���_�̏C��(���z�֐�)�B�h���N���X�͓Ǝ��̒��_�����C��������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AdjustVertex() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���_�̕ύX
		@param[in]	ElapsedTime	�^�[������
		@param[out]	vertices	�}�b�v���ꂽ���_�f�[�^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		@param[in]	TextureResName	�����e�N�X�`�����\�[�X��
		@param[in]	StartScale	�����傫��
		@param[in]	StartRot	������]
		@param[in]	StartPos	�����ʒu
		@param[in]	XWrap	X�����̃��b�v��
		@param[in]	YWrap	Y�����̃��b�v��
		*/
		//--------------------------------------------------------------------------------------
		RotateSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, 
			const Vec2& StartScale,
			float StartRot,
			const Vec2& StartPos,
			UINT XWrap, UINT YWrap);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~RotateSprite() {}
	};

	//--------------------------------------------------------------------------------------
	///	���b�Z�[�W��\������X�v���C�g
	//--------------------------------------------------------------------------------------
	class MessageSprite : public SpriteBase {
		float m_TotalTime;	//���_�ύX�Ɏg�p����^�C��
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �o�b�N�A�b�v���_�̏C��(���z�֐�)�B�h���N���X�͓Ǝ��̒��_�����C��������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void AdjustVertex() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���_�̕ύX
		@param[in]	ElapsedTime	�^�[������
		@param[out]	vertices	�}�b�v���ꂽ���_�f�[�^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		@param[in]	TextureResName	�����e�N�X�`�����\�[�X��
		@param[in]	StartScale	�����傫��
		@param[in]	StartRot	������]
		@param[in]	StartPos	�����ʒu
		@param[in]	XWrap	X�����̃��b�v��
		@param[in]	YWrap	Y�����̃��b�v��
		*/
		//--------------------------------------------------------------------------------------
		MessageSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, 
			const Vec2& StartScale,
			float StartRot,
			const Vec2& StartPos,
			UINT XWrap, UINT YWrap);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~MessageSprite() {}
	};

	//--------------------------------------------------------------------------------------
	///	Bar
	//--------------------------------------------------------------------------------------
	class Bar : public GameObject {
		//�o�b�N�A�b�v���Ă������_�f�[�^
		vector<VertexPositionColorTexture> m_BackupVertices;
		//���b�V��
		shared_ptr<MeshResource> m_SquareMesh;
		//�e�N�X�`�����\�[�X��
		wstring m_TextureResName;
		//��]�̕`��I�v�V����
		SquareDrawOption m_DrawOption;
		Vec3 m_Scale;				///<�X�P�[�����O
		Quat m_Qt;			///<��]
		Vec3 m_Pos;				///<�ʒu
		float m_TotalTime;
		//�`��f�[�^
		shared_ptr<SimpleDrawObject> m_PtrObj;
		//�`��I�u�W�F�N�g(weak_ptr)
		weak_ptr<SimplePCTStaticRenderer> m_Renderer;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���_�̍쐬
		@param[in]	WrapX	X�����̃^�C�����O
		@param[in]	WrapY	Y�����̃^�C�����O
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void CreateBuffers(float WrapX, float WrapY);
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���_�̕ύX
		@param[in]	ElapsedTime	�^�[������
		@param[out]	vertices	�}�b�v���ꂽ���_�f�[�^
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices);
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W�̃|�C���^
		@param[in]	TextureResName	�e�N�X�`�����\�[�X��
		@param[in]	Scale	�X�P�[�����O
		@param[in]	Pos	�ʒu
		@param[in]	Option	�`��I�v�V����
		*/
		//--------------------------------------------------------------------------------------
		Bar(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName,
			const Vec3& Scale, const Vec3& Pos, const Quat& Qt, SquareDrawOption Option);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Bar();
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
