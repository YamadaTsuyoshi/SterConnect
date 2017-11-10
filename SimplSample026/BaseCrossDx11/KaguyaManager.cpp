#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームステージ
	//--------------------------------------------------------------------------------------
	// 構築と破棄
	KaguyaManager::KaguyaManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	// 初期化
	void KaguyaManager::OnCreate()
	{
	}

	// 更新
	void KaguyaManager::OnUpdate()
	{
	}

	// 後更新
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