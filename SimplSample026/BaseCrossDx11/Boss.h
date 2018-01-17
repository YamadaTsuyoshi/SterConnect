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
	//	用途: ボス
	//--------------------------------------------------------------------------------------
	class BossEnemy : public Boss {
		///メッシュ
		shared_ptr<MeshResource> m_SphereMesh;
		///テクスチャリソース名
		wstring m_TextureResName;
		//壁
		float m_BaseX;
		///スケーリングベースの最下地点
		float m_BaseY;
		///位置
		Vec3 m_Posision;
		///透明処理するかどうか
		bool m_Trace;
		//Rigidbodyのshared_ptr
		shared_ptr<Rigidbody> m_Rigidbody;
		///描画データ
		shared_ptr<BcDrawObject> m_PtrObj;
		//描画オブジェクト(weak_ptr)
		weak_ptr<BcPNTStaticRenderer> m_Renderer;
		///シャドウマップ用描画データ
		shared_ptr<ShadowmapObject> m_PtrShadowmapObj;
		//シャドウマップ描画オブジェクト(weak_ptr)
		weak_ptr<ShadowmapRenderer> m_ShadowmapRenderer;

		Vec3 Speed = Vec3(1.5f, 1.5f, 1.5f);

		bool rightMove = true;

		float Time = 0;

		bool Startflag = false;

		Vec3 Def;

	public:
		//構築と破棄
		BossEnemy(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, bool Trace, const Vec3& Pos);

		virtual ~BossEnemy();
		virtual Vec3 GetPosition() override;
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDrawShadowmap() override;
		virtual void OnDraw()override;
		void ThisDelete();
	};
}