#pragma once
#include"stdafx.h"
namespace basecross {

	class Boss :public GameObject
	{
	public:
		Boss(const shared_ptr<Stage> stagePtr) :
			GameObject(stagePtr)
		{
		}
	};
	//--------------------------------------------------------------------------------------
	//	class BossEnemy : public Boss;
	//	�p�r: �{�X
	//--------------------------------------------------------------------------------------
	class BossEnemy : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
		Vec3 m_Posision;
		//��
		float m_BaseX;
		///�X�P�[�����O�x�[�X�̍ŉ��n�_
		float m_BaseY;
		//Rigidbody��shared_ptr
		shared_ptr<Rigidbody> m_Rigidbody;
		Vec3 Speed = Vec3(1.5f, 1.5f, 1.5f);
		float Time = 0;
		bool Startflag = false;
		bool Attackflg = false;
		bool rightMove = true;

		bool m_Alphaflag;

		Vec3 Def;

		int m_Life = 3;

	protected:
		float m_Count[4] = {};
		float m_Interval[4] = {};
		bool m_isNullHit[4] = {};
	public:
		//�\�z�Ɣj��
		BossEnemy(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos);

		//virtual ~BossEnemy();
		virtual Vec3 GetPosition() override;
		virtual void OnCreate() override;
		virtual void SetMutekiTime(float time, int CntNum = 0);
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		void ThisDelete();
	};
	//--------------------------------------------------------------------------------------
	//	class BossBullet : public Bullet;
	//	�p�r: �{�X�����e
	//--------------------------------------------------------------------------------------
	class BossBullet : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
		Vec3 m_Posision;
		//��
		float m_BaseX;
		///�X�P�[�����O�x�[�X�̍ŉ��n�_
		float m_BaseY;
		//Rigidbody��shared_ptr
		shared_ptr<Rigidbody> m_Rigidbody;
		Vec3 Speed = Vec3(1.5f, 1.5f, 1.5f);
		float Time = 0;
		bool Startflag = false;
		Vec3 Def;
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
	public:
		//�\�z�Ɣj��
		BossBullet(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos);
		virtual ~BossBullet() {}
		virtual Vec3 GetPosition() override;
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		virtual void OnUpdate2()override;
		void ThisDelete();
	};

	//--------------------------------------------------------------------------------------
	//	bosuusa�X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	class BossusaSS : public SS5ssae {
		Mat4x4 m_ToAnimeMatrixLeft;
		Vec3 m_Posision;
		//��
		float m_BaseX;
		///�X�P�[�����O�x�[�X�̍ŉ��n�_
		float m_BaseY;
		//Rigidbody��shared_ptr
		shared_ptr<Rigidbody> m_Rigidbody;
		Vec3 Speed = Vec3(1.5f, 1.5f, 1.5f);
		float Time = 0;
		bool Startflag = false;
	public:
		//�\�z�Ɣj��
		BossusaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos);
		virtual ~BossusaSS() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		virtual void OnUpdate2()override;
		void ThisDelete();
	};
}