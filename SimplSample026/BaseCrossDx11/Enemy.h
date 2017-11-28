#pragma once
#include"stdafx.h"
namespace basecross {
	//食べ物のインターフェース
	class Enemy :public GameObject
	{
	public:
		Enemy(const shared_ptr<Stage> stagePtr) :
			GameObject(stagePtr)
		{
		}
	};

	//--------------------------------------------------------------------------------------
	//	class Rabbit : public Enemy;
	//	用途: ウサギの敵
	//--------------------------------------------------------------------------------------
	class Rabbit : public Enemy {
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

	public:
		//構築と破棄
		Rabbit(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureResName, bool Trace, const Vec3& Pos);

		virtual ~Rabbit();
		virtual Vec3 GetPosition() override;
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnDrawShadowmap() override;
		virtual void OnDraw()override;
	};

}
//end basecross