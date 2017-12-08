/*!
@file Vibration.h
@author ŽR“cŒ’Žs
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class Vibration
	{
	protected:
		float m_VibCount[4] = {};
		float m_VibInterval[4] = {};
		bool m_isVib[4] = {};
	public:
		DECLARE_SINGLETON_INSTANCE(Vibration)

		void SetVibration(float time, float left, float right, int CntNum = 0);

		void Update();
	};
}