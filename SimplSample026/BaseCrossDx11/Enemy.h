#pragma once
#include"stdafx.h"
namespace basecross {
	
	class Enemy :public GameObject
	{
	public:
		Enemy(const shared_ptr<Stage> stagePtr) :
			GameObject(stagePtr)
		{
		}
	};

	class Bullet :public GameObject
	{
	public:
		Bullet(const shared_ptr<Stage> stagePtr) :
			GameObject(stagePtr)
		{
		}
	};

	//--------------------------------------------------------------------------------------
	//	class Rabbit : public Enemy;
	//	�p�r: �E�T�M�̓G
	//--------------------------------------------------------------------------------------
	class Rabbit : public Enemy {
		///���b�V��
		shared_ptr<MeshResource> m_SphereMesh;
		///�e�N�X�`�����\�[�X��
		wstring m_TextureResName;
		//��
		float m_BaseX;
		///�X�P�[�����O�x�[�X�̍ŉ��n�_
		float m_BaseY;
		///�ʒu
		Vec3 m_Posision;
		///�����������邩�ǂ���
		bool m_Trace;
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

		Vec3 Speed=Vec3(1.5f,1.5f,1.5f);

		bool rightMove = true;

		float Time = 0;

		bool Startflag = false;

	public:
		//�\�z�Ɣj��
		Rabbit(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, bool Trace, const Vec3& Pos);

		virtual ~Rabbit();
		virtual Vec3 GetPosition() override;
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDrawShadowmap() override;
		virtual void OnDraw()override;
		void ThisDelete();
	};

	//--------------------------------------------------------------------------------------
	//	class RabbitBullet : public Bullet;
	//	�p�r: �E�T�M�̓G�����e
	//--------------------------------------------------------------------------------------
	class RabbitBullet : public Bullet {
		///���b�V��
		shared_ptr<MeshResource> m_SphereMesh;
		///�e�N�X�`�����\�[�X��
		wstring m_TextureResName;
		//��
		float m_BaseX;
		///�X�P�[�����O�x�[�X�̍ŉ��n�_
		float m_BaseY;
		///�ʒu
		Vec3 m_Posision;
		///�����������邩�ǂ���
		bool m_Trace;
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

		Vec3 Speed = Vec3(1.5f, 1.5f, 1.5f);

		bool rightMove = true;

		float Time = 0;

	public:
		//�\�z�Ɣj��
		RabbitBullet(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, bool Trace, const Vec3& Pos);

		virtual ~RabbitBullet();
		virtual Vec3 GetPosition() override;
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDrawShadowmap() override;
		virtual void OnDraw()override;
		void ThisDelete();
	};

	//--------------------------------------------------------------------------------------
	//	�E�T�M�X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	class RabbitSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
		Vec3 m_Posision;
	public:
		//�\�z�Ɣj��
		RabbitSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos);
		virtual ~RabbitSS() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}
//end basecross