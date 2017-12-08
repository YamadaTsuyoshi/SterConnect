/*!
@file Vibration.cpp
@author ŽR“cŒ’Žs
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	IMPLEMENT_SINGLETON_INSTANCE(Vibration);

	void Vibration::SetVibration(float time, float left, float right, int CntNum)
	{
		if (!m_isVib[CntNum])
		{
			m_isVib[CntNum] = true;
			m_VibInterval[CntNum] = time;

			const WORD MAX_VIB = 65535;

			XINPUT_VIBRATION state;
			state.wLeftMotorSpeed = (WORD)(MAX_VIB * left);
			state.wRightMotorSpeed = (WORD)(MAX_VIB * right);

			XInputSetState(CntNum, &state);
		}
	}

	void Vibration::Update()
	{
		for (int i = 0; i < ARRAYSIZE(m_isVib); i++)
		{
			if (m_isVib[i])
			{
				float delta = App::GetApp()->GetElapsedTime();
				m_VibCount[i] += delta;

				if (m_VibCount[i] > m_VibInterval[i])
				{
					m_isVib[i] = false;
					m_VibCount[i] = 0;

					XINPUT_VIBRATION state;
					state.wLeftMotorSpeed = 0;
					state.wRightMotorSpeed = 0;
					XInputSetState(0, &state);
				}
			}
		}
	}
}