/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	コントローラのボタンのハンドラ
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//コントローラの取得
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected) {
				// Aボタン
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					Obj->OnPushL();
				}
				// Bボタン
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					Obj->OnPushR();
				}
			}
		}
	};
}

//end basecross

