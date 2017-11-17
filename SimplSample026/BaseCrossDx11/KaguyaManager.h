#pragma once
#include "stdafx.h"

namespace basecross {

	class KaguyaManager : public GameObject
	{
		Vec3 m_Pos;

		unique_ptr<StateMachine<KaguyaManager>> m_StateMachine;	// �X�e�[�g�}�V��

	public:
		// �\�z�Ɣj��
		KaguyaManager(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~KaguyaManager() {}

		// �X�e�[�g�}�V��
		unique_ptr<StateMachine<KaguyaManager>>& GetStateMachine()
		{
			return m_StateMachine;
		}

		// ������
		virtual void OnCreate() override;

		// �X�V
		virtual void OnUpdate() override;

		// ��X�V
		virtual void OnUpdate2() override;

	};
	class overJumpState : public ObjState<KaguyaManager>
	{
		overJumpState() {}

	public:
		DECLARE_SINGLETON_INSTANCE(overJumpState)
		virtual void Enter(const shared_ptr<KaguyaManager>& Obj) override;
		virtual void Execute(const shared_ptr<KaguyaManager>& Obj) override;
		virtual void Exit(const shared_ptr<KaguyaManager>& Obj) override;
	};
	class underJumpState : public ObjState<KaguyaManager>
	{
		underJumpState() {}

	public:
		DECLARE_SINGLETON_INSTANCE(underJumpState)
		virtual void Enter(const shared_ptr<KaguyaManager>& Obj) override;
		virtual void Execute(const shared_ptr<KaguyaManager>& Obj) override;
		virtual void Exit(const shared_ptr<KaguyaManager>& Obj) override;
	};
}