#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���X�e�[�W
	//--------------------------------------------------------------------------------------
	// �\�z�Ɣj��
	KaguyaManager::KaguyaManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	// ������
	void KaguyaManager::OnCreate()
	{
	}

	// �X�V
	void KaguyaManager::OnUpdate()
	{
	}

	// ��X�V
	void KaguyaManager::OnUpdate2()
	{
	}

	IMPLEMENT_SINGLETON_INSTANCE(overJumpState)

	void overJumpState::Enter(const shared_ptr<KaguyaManager>& Obj)
	{
	}

	void overJumpState::Execute(const shared_ptr<KaguyaManager>& Obj)
	{
	}

	void overJumpState::Exit(const shared_ptr<KaguyaManager>& Obj)
	{
	}

	IMPLEMENT_SINGLETON_INSTANCE(underJumpState)

	void underJumpState::Enter(const shared_ptr<KaguyaManager>& Obj)
	{
	}

	void underJumpState::Execute(const shared_ptr<KaguyaManager>& Obj)
	{
	}

	void underJumpState::Exit(const shared_ptr<KaguyaManager>& Obj)
	{
	}
}