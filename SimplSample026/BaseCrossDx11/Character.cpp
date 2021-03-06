/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//class MultiSpark : public MultiParticle;
	//用途: 複数のスパーククラス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MultiSpark::MultiSpark(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiSpark::~MultiSpark() {}

	//初期化
	void MultiSpark::OnCreate() {
		//加算描画処理をする
		SetAddType(true);
		//タグの追加
		AddTag(L"MultiSpark");
	}


	void MultiSpark::InsertSpark(const Vec3& Pos) {
		auto ParticlePtr = InsertParticle(64);
		ParticlePtr->m_EmitterPos = Pos;
		ParticlePtr->SetTextureResource(L"SPARK_TX");
		ParticlePtr->m_MaxTime = 0.5f;
		vector<ParticleSprite>& pSpriteVec = ParticlePtr->GetParticleSpriteVec();
		for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalScale = Vec2(0.2, 0.2);
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 30.0f,
				rParticleSprite.m_LocalPos.y * 30.0f,
				rParticleSprite.m_LocalPos.z * 30.0f
			);
			//色の指定
			int r = (int)((Util::RandZeroToOne() * 0.5f + 0.3f) * 256.0f);
			int g = (int)((Util::RandZeroToOne() * 0.5f + 0.3f) * 256.0f);
			int b = (int)((Util::RandZeroToOne() * 0.5f + 0.3f) * 256.0f);
			r = r >> 7;
			g = g >> 7;
			b = b >> 7;
			rParticleSprite.m_Color = Col4((float)r, (float)g, (float)b, 1.0f);
		}
	}

	void MultiSpark::OnUpdate() {
		MultiParticle::OnUpdate();
		float ElapsedTime = App::GetApp()->GetElapsedTime();

		for (auto ParticlePtr : GetParticleVec()) {
			for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
				if (rParticleSprite.m_Active) {
					rParticleSprite.m_Color += 0.01f;
					rParticleSprite.m_Color.w = 1.0f;
					if (rParticleSprite.m_Color.x >= 1.0f) {
						rParticleSprite.m_Color.x = 1.0f;
					}
					if (rParticleSprite.m_Color.y >= 1.0f) {
						rParticleSprite.m_Color.y = 1.0f;
					}
					if (rParticleSprite.m_Color.z >= 1.0f) {
						rParticleSprite.m_Color.z = 1.0f;
					}
				}
			}
		}

	}


	//--------------------------------------------------------------------------------------
	//class MultiFire : public MultiParticle;
	//用途: 複数の炎クラス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MultiFire::MultiFire(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiFire::~MultiFire() {}

	//初期化
	void MultiFire::OnCreate() {
		//タグの追加
		AddTag(L"MultiFire");
	}

	void MultiFire::InsertFire(const Vec3& Pos) {
		auto ParticlePtr = InsertParticle(16);
		ParticlePtr->m_EmitterPos = Pos;
		ParticlePtr->SetTextureResource(L"FIRE_TX");
		ParticlePtr->m_MaxTime = 0.5f;
		vector<ParticleSprite>& pSpriteVec = ParticlePtr->GetParticleSpriteVec();
		for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 5.0f,
				rParticleSprite.m_LocalPos.y * 5.0f,
				rParticleSprite.m_LocalPos.z * 5.0f
			);
			//色の指定
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}


	//--------------------------------------------------------------------------------------
	///	シンプルな3D上の平面
	//--------------------------------------------------------------------------------------
	void SimpleSquare::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//メッシュの作成（変更できる）
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//構築と破棄
	SimpleSquare::SimpleSquare(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option):
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	SimpleSquare::~SimpleSquare() {}

	//初期化
	void SimpleSquare::OnCreate() {
		CreateBuffers(5.0f, 30.0f);

		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		//body.m_IsDrawActive = true;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//描画データの構築
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void SimpleSquare::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void SimpleSquare::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//頂点の変更
		//D3D11_MAP_WRITE_DISCARDは重要。この処理により、GPUに邪魔されない
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//頂点のマップ
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map失敗
			throw BaseException(
				L"頂点のMapに失敗しました。",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//頂点の変更
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//関数呼び出し
		UpdateVertex(ElapsedTime, vertices);
		//アンマップ
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//カメラの位置
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}
	}

	void SimpleSquare::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	//--------------------------------------------------------------------------------------
	///	3D上の平面
	//--------------------------------------------------------------------------------------
	void SquareSprite::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//メッシュの作成（変更できる）
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//構築と破棄
	SquareSprite::SquareSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	SquareSprite::~SquareSprite() {}

	//初期化
	void SquareSprite::OnCreate() {
		CreateBuffers(1.0f, 1.0f);

		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = true;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//描画データの構築
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void SquareSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void SquareSprite::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//頂点の変更
		//D3D11_MAP_WRITE_DISCARDは重要。この処理により、GPUに邪魔されない
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//頂点のマップ
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map失敗
			throw BaseException(
				L"頂点のMapに失敗しました。",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//頂点の変更
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//関数呼び出し
		UpdateVertex(ElapsedTime, vertices);
		//アンマップ
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//カメラの位置
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}
	}

	void SquareSprite::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	//--------------------------------------------------------------------------------------
	///	シンプルな3D上のボックス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	SimpleBox::SimpleBox(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(),
		m_Pos(Pos)
	{}
	SimpleBox::~SimpleBox() {}

	//初期化
	void SimpleBox::OnCreate() {

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		//メッシュの取得
		auto MeshPtr = App::GetApp()->GetResource<MeshResource>(L"DEFAULT_PCT_BOX");

		//描画データの構築
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = MeshPtr;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void SimpleBox::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	//--------------------------------------------------------------------------------------
	///	ラッピング処理されたスプライト
	//--------------------------------------------------------------------------------------
	SpriteBase::SpriteBase(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, 
		const Vec2& StartScale, 
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(StartScale),
		m_Rot(StartRot),
		m_Pos(StartPos),
		m_XWrap(XWrap),
		m_YWrap(YWrap),
		m_Emissive(0,0,0,0),
		m_BlendState(BlendState::Opaque)
	{}
	void SpriteBase::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横指定数ずつ表示)
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2((float)m_XWrap, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, (float)m_YWrap)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2((float)m_XWrap, (float)m_YWrap)) },
		};
		//頂点の初期修正（仮想関数呼びだし）
		AdjustVertex();
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//メッシュの作成（変更できる）
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);
	}

	void SpriteBase::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//頂点の変更
		//D3D11_MAP_WRITE_DISCARDは重要。この処理により、GPUに邪魔されない
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//頂点のマップ
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map失敗
			throw BaseException(
				L"頂点のMapに失敗しました。",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"WrappedSprite::UpdateVertex()"
			);
		}
		//頂点の変更
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//仮想関数呼び出し
		UpdateVertex(ElapsedTime, vertices);
		//アンマップ
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);
	}



	void SpriteBase::OnDraw() {
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		//ワールド行列の決定
		Mat4x4 World;
		World.affineTransformation2D(
			m_Scale,			//スケーリング
			Vec2(0, 0),		//回転の中心（重心）
			m_Rot,				//回転角度
			m_Pos				//位置
		);
		//射影行列の決定
		float w = static_cast<float>(App::GetApp()->GetGameWidth());
		float h = static_cast<float>(App::GetApp()->GetGameHeight());
		Mat4x4 Proj(XMMatrixOrthographicLH(w, h, -1.0, 1.0f));
		//行列の合成
		World *= Proj;
		//コンスタントバッファの準備
		SpriteConstantBuffer sb;
		//エミッシブ加算。
		sb.Emissive = m_Emissive;
		//行列の設定
		sb.World = World;
		//コンスタントバッファの更新
		pD3D11DeviceContext->UpdateSubresource(CBSprite::GetPtr()->GetBuffer(), 0, nullptr, &sb, 0, 0);

		//ストライドとオフセット
		UINT stride = sizeof(VertexPositionColorTexture);
		UINT offset = 0;
		//頂点バッファのセット
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, m_SquareMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);
		//インデックスバッファのセット
		pD3D11DeviceContext->IASetIndexBuffer(m_SquareMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);

		//描画方法（3角形）
		pD3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//コンスタントバッファの設定
		ID3D11Buffer* pConstantBuffer = CBSprite::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//頂点シェーダに渡す
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//ピクセルシェーダに渡す
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//シェーダの設定
		pD3D11DeviceContext->VSSetShader(VSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		pD3D11DeviceContext->PSSetShader(PSPCTSprite::GetPtr()->GetShader(), nullptr, 0);
		//インプットレイアウトの設定
		pD3D11DeviceContext->IASetInputLayout(VSPCTSprite::GetPtr()->GetInputLayout());
		//ブレンドステート
		switch (m_BlendState) {
		case BlendState::Opaque:
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetOpaque(), nullptr, 0xffffffff);
			break;
		case BlendState::Trace:
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(), nullptr, 0xffffffff);
			break;
		case BlendState::Additive:
			pD3D11DeviceContext->OMSetBlendState(RenderState->GetAdditive(), nullptr, 0xffffffff);
			break;
		}
		//デプスステンシルステート
		pD3D11DeviceContext->OMSetDepthStencilState(RenderState->GetDepthNone(), 0);
		//ラスタライザステート
		pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());

		//テクスチャとサンプラーの設定
		ID3D11ShaderResourceView* pNull[1] = { 0 };
		pD3D11DeviceContext->PSSetShaderResources(0, 1, TexPtr->GetShaderResourceView().GetAddressOf());
		//ラッピングサンプラー
		ID3D11SamplerState* pSampler = RenderState->GetLinearWrap();
		pD3D11DeviceContext->PSSetSamplers(0, 1, &pSampler);

		//描画
		pD3D11DeviceContext->DrawIndexed(m_SquareMesh->GetNumIndicis(), 0, 0);
		//後始末
		Dev->InitializeStates();
	}
	//--------------------------------------------------------------------------------------
	///	回転するスプライト
	//--------------------------------------------------------------------------------------
	RotateSprite::RotateSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, 
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap):
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Additive);
	}

	void RotateSprite::AdjustVertex() {
		//頂点色を変更する
		for (size_t i = 0; i < m_BackupVertices.size();i++) {
			switch (i) {
			case 0:
				m_BackupVertices[i].color = Col4(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			case 1:
				m_BackupVertices[i].color = Col4(0.0f, 1.0f, 0.0f, 1.0f);
				break;
			case 2:
				m_BackupVertices[i].color = Col4(0.0f, 0.0f, 1.0f, 1.0f);
				break;
			case 3:
				m_BackupVertices[i].color = Col4(1.0f, 1.0f, 0, 1.0);
				break;
			}
		}
	}

	void RotateSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_Rot += ElapsedTime;
		if (m_Rot >= XM_2PI) {
			m_Rot = 0;
		}
		m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}


	}

	//--------------------------------------------------------------------------------------
	///	スプライト
	//--------------------------------------------------------------------------------------
	StageSprite::StageSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void StageSprite::AdjustVertex() {
		//ここでは何もしない
	}

	void  StageSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}

	//--------------------------------------------------------------------------------------
	///	メッセージを表示するスプライト
	//--------------------------------------------------------------------------------------
	MessageSprite::MessageSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void MessageSprite::AdjustVertex() {
		//ここでは何もしない
	}

	void  MessageSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		Col4 UpdateCol;
		if (FlashingFlag)
		{
			float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
			Col4 UpdateCol(1.0f, 1.0f, 1.0f, sin_val*A);

			for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
				vertices[i] = VertexPositionColorTexture(
					m_BackupVertices[i].position,
					UpdateCol,
					m_BackupVertices[i].textureCoordinate
				);
			}
		}
		else
		{
			Col4 UpdateCol(1.0f, 1.0f, 1.0f, A);

			for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
				vertices[i] = VertexPositionColorTexture(
					m_BackupVertices[i].position,
					UpdateCol,
					m_BackupVertices[i].textureCoordinate
				);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	///	Bar
	//--------------------------------------------------------------------------------------
	void Bar::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,0.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,0.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,0.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,0.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//メッシュの作成（変更できる）
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//構築と破棄
	Bar::Bar(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	Bar::~Bar() {}

	//初期化
	void Bar::OnCreate() {
		CreateBuffers(0.0f, 0.0f);

		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//描画データの構築
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;
	}

	void Bar::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = 0;
			}
			/*else if (UV.x == 4.0f) {
				UV.x += m_TotalTime;
			}*/
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void Bar::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext(); 
		Time += ElapsedTime;
		if (D_flag)
		{
			D_Time += ElapsedTime;
		}
		//頂点の変更
		//D3D11_MAP_WRITE_DISCARDは重要。この処理により、GPUに邪魔されない
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//頂点のマップ
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map失敗
			throw BaseException(
				L"頂点のMapに失敗しました。",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//頂点の変更
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//関数呼び出し
		UpdateVertex(ElapsedTime, vertices);
		//アンマップ
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//カメラの位置
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}

		if (Time >4.0f) {
			D_flag = true;
		}

		if (D_Time >0.3f) {
			ThisDelete();
		}
	}

	void Bar::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	void Bar::ThisDelete()
	{
		Vec3 Emitter = m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<Bar>(GetThis<Bar>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<Bar>());
	}

	//--------------------------------------------------------------------------------------
	///	Wall
	//--------------------------------------------------------------------------------------
	void Wall::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//メッシュの作成（変更できる）
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//構築と破棄
	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	Wall::~Wall() {}

	//初期化
	void Wall::OnCreate() {
		CreateBuffers(1.0f, 20.0f);
		AddTag(L"Bamboo");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//描画データの構築
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void Wall::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void Wall::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//頂点の変更
		//D3D11_MAP_WRITE_DISCARDは重要。この処理により、GPUに邪魔されない
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//頂点のマップ
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map失敗
			throw BaseException(
				L"頂点のMapに失敗しました。",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//頂点の変更
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//関数呼び出し
		UpdateVertex(ElapsedTime, vertices);
		//アンマップ
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		//auto PtrStage = GetStage<Stage>();
		////カメラの位置
		//Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		//Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		//m_Pos.y = CameraEye.y;
		//switch (m_DrawOption) {
		//case SquareDrawOption::Billboard:
		//{
		//	m_Qt.facing(CameraAt - CameraEye);
		//}
		//break;
		//case SquareDrawOption::Faceing:
		//{
		//	m_Qt.facing(m_Pos - CameraEye);
		//}
		//break;
		//case SquareDrawOption::FaceingY:
		//	m_Qt.facingY(m_Pos - CameraEye);
		//	break;
		//default:
		//	m_Qt.normalize();
		//	break;
		//}
		
	}

	void Wall::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	///	BG
	//--------------------------------------------------------------------------------------
	void BG::CreateBuffers(float WrapX, float WrapY) {
		float HelfSize = 0.5f;
		m_BackupVertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, WrapY)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(WrapX, WrapY)) },

		};
		vector<uint16_t> indices = {
			0, 1, 2,
			1, 3, 2,
		};
		//メッシュの作成（変更できる）
		m_SquareMesh = MeshResource::CreateMeshResource(m_BackupVertices, indices, true);

	}

	//構築と破棄
	BG::BG(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec3& Scale, const Vec3& Pos, const Quat& Qt,
		SquareDrawOption Option) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Pos(Pos),
		m_DrawOption(Option),
		m_TotalTime(0)
	{}
	BG::~BG() {}

	//初期化
	void BG::OnCreate() {
		CreateBuffers(1.0f, 1.0f);
		AddTag(L"BG");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();

		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qt;
		body.m_Pos = m_Pos;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);

		//描画データの構築
		m_PtrObj = make_shared<SimpleDrawObject>();
		m_PtrObj->m_MeshRes = m_SquareMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_SamplerState = SamplerState::LinearWrap;

	}

	void BG::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_TotalTime += ElapsedTime;
		if (m_TotalTime >= 1.0f) {
			m_TotalTime = 0;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			Vec2 UV(m_BackupVertices[i].textureCoordinate);
			if (UV.x == 0.0f) {
				UV.x = m_TotalTime;
			}
			else if (UV.x == 4.0f) {
				//UV.x += m_TotalTime;
			}
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				UV
			);
		}
	}


	void BG::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		//頂点の変更
		//D3D11_MAP_WRITE_DISCARDは重要。この処理により、GPUに邪魔されない
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		D3D11_MAPPED_SUBRESOURCE mappedBuffer;
		//頂点のマップ
		if (FAILED(pD3D11DeviceContext->Map(m_SquareMesh->GetVertexBuffer().Get(), 0, mapType, 0, &mappedBuffer))) {
			// Map失敗
			throw BaseException(
				L"頂点のMapに失敗しました。",
				L"if(FAILED(pID3D11DeviceContext->Map()))",
				L"SimpleSquare::OnUpdate()"
			);
		}
		//頂点の変更
		VertexPositionColorTexture* vertices
			= (VertexPositionColorTexture*)mappedBuffer.pData;
		//関数呼び出し
		UpdateVertex(ElapsedTime, vertices);
		//アンマップ
		pD3D11DeviceContext->Unmap(m_SquareMesh->GetVertexBuffer().Get(), 0);


		auto PtrStage = GetStage<Stage>();
		//カメラの位置
		Vec3 CameraEye = PtrStage->GetCamera().m_CamerEye;
		Vec3 CameraAt = PtrStage->GetCamera().m_CamerAt;
		//m_Pos.y = CameraEye.y;
		switch (m_DrawOption) {
		case SquareDrawOption::Billboard:
		{
			m_Qt.facing(CameraAt - CameraEye);
		}
		break;
		case SquareDrawOption::Faceing:
		{
			m_Qt.facing(m_Pos - CameraEye);
		}
		break;
		case SquareDrawOption::FaceingY:
			m_Qt.facingY(m_Pos - CameraEye);
			break;
		default:
			m_Qt.normalize();
			break;
		}

		

	}

	void BG::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qt,
			m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<SimplePCTStaticRenderer>(L"SimplePCTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	/// LightGage
	//--------------------------------------------------------------------------------------
	LightGage_F::LightGage_F(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void LightGage_F::AdjustVertex() {
		//ここでは何もしない
	}

	void  LightGage_F::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}

	//--------------------------------------------------------------------------------------
	/// LightGage_Bar
	//--------------------------------------------------------------------------------------
	LightGage_B::LightGage_B(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void LightGage_B::AdjustVertex() {
		//ここでは何もしない
	}

	void  LightGage_B::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}

	}

	void LightGage_B::OnUpdate()
	{
		auto player = GetStage<GameStage>()->FindTagGameObject<Player>(L"Player");
		float HP = player->getP_LightGage();
		float MaxHP = player->getP_MaxLightGage();
		float Width = HP / MaxHP;
		this->m_Scale = Vec2(278.0f* Width, 6.0f);
		if (!(w== Width)) {
			float a = (278.0f - 278.0f * Width)*0.5f;
			this->m_Pos.x = 502-a;
			w = Width;
		}
		if (Width>0.2)
		this->m_TextureResName= wstring(L"LIGHTGAGE_B_TX");
		else
		this->m_TextureResName = wstring(L"LIGHTGAGE_B_R_TX");
	}

	//--------------------------------------------------------------------------------------
	/// Life
	//--------------------------------------------------------------------------------------
	Life::Life(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void Life::AdjustVertex() {
		//ここでは何もしない
	}

	void Life::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}

	void Life::ScaleChangeH(){
		this->m_Scale += 2.0f;
		if (this->m_Scale.x >= 35.0f&&this->m_Scale.y >= 35.0f) {
			this->m_Scale = Vec2(35.0f,35.0f);
		}
	}

	void Life::ScaleChangeD(){
		this->m_Scale -= 2.0f;
		if (this->m_Scale.x <= 0.0f&&this->m_Scale.y <= 0.0f) {
			this->m_Scale = Vec2(0.0f);
		}
	}

	//--------------------------------------------------------------------------------------
	///数字のスプライト
	//--------------------------------------------------------------------------------------
	NumSprite::NumSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		const float& waru,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0),
		m_waru(waru)
	{
		SetBlendState(BlendState::Trace);
	}

	void NumSprite::AdjustVertex() {
		float XPiecesize = 1.0f / 4.0f;
		float HelfSize = 0.5f;

		for (UINT i = 0; i < 4.0f; i++) {
			float Vertex0 = -HelfSize + XPiecesize * (float)i;
			float Vertex1 = Vertex0 + XPiecesize;
			//0
			m_BackupVertices.push_back(
				VertexPositionColorTexture(Vec3(Vertex0, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f))
			);
			//1
			m_BackupVertices.push_back(
				VertexPositionColorTexture(Vec3(Vertex1, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.1f, 0.0f))
			);
			//2
			m_BackupVertices.push_back(
				VertexPositionColorTexture(Vec3(Vertex0, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f))
			);
			//3
			m_BackupVertices.push_back(
				VertexPositionColorTexture(Vec3(Vertex1, -HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.1f, 1.0f))
			);
		}
		auto PtrTransform = GetTransform();;
		PtrTransform->SetScale(m_Scale.x, m_Scale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_Pos.x, m_Pos.y, 0.0f);
	}

	void  NumSprite::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		//m_Time = GetStage<GameStage>()->GetTime();
		vector<VertexPositionColorTexture> NewVertices;
		UINT Num;
		int VerNum = 0;
		m_Num /= m_waru;
		for (UINT i = 4; i > 0; i--) {
			UINT Base = (UINT)pow(10, i);
			Num = ((UINT)m_Num) % Base;
			//Num = Num / (Base / 10);
			Vec2 UV0 = m_BackupVertices[VerNum].textureCoordinate;
			UV0.x = (float)Num / 10.0f;
			//ドラムロール
			//UV0.x = (float)m_Num / 10.0f;
			auto v = VertexPositionColorTexture(
				m_BackupVertices[VerNum].position,
				m_BackupVertices[VerNum].color,
				UV0
			);
			NewVertices.push_back(v);

			Vec2 UV1 = m_BackupVertices[VerNum + 1].textureCoordinate;
			UV1.x = UV0.x + 0.1f;
			v = VertexPositionColorTexture(
				m_BackupVertices[VerNum + 1].position,
				m_BackupVertices[VerNum+1].color,
				UV1
			);
			NewVertices.push_back(v);

			Vec2 UV2 = m_BackupVertices[VerNum + 2].textureCoordinate;
			UV2.x = UV0.x;

			v = VertexPositionColorTexture(
				m_BackupVertices[VerNum + 2].position,
				m_BackupVertices[VerNum+2].color,
				UV2
			);
			NewVertices.push_back(v);

			Vec2 UV3 = m_BackupVertices[VerNum + 3].textureCoordinate;
			UV3.x = UV0.x + 0.1f;

			v = VertexPositionColorTexture(
				m_BackupVertices[VerNum + 3].position,
				m_BackupVertices[VerNum+3].color,
				UV3
			);
			NewVertices.push_back(v);

			VerNum += 4;
		}

		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = NewVertices[i];
		}
	}

	void NumSprite::SetPos(Vec2& pos) {
		this->m_Pos = Vec2(pos.x, pos.y);
	}

	//--------------------------------------------------------------------------------------
	/// defaltsprite
	//--------------------------------------------------------------------------------------
	DefSp::DefSp(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void DefSp::AdjustVertex() {
		//ここでは何もしない
	}

	void DefSp::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, 1.0f);
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				m_BackupVertices[i].color,
				m_BackupVertices[i].textureCoordinate
			);

		}
	}
	void DefSp::SetPos(Vec2& pos) {
		this->m_Pos = Vec2(pos.x,pos.y);
	}
	void DefSp::S1_ScaleControl(float r) {
		this->m_Scale = Vec2(550 * r, 786 * r);
	}
	void DefSp::S2_ScaleControl(float r) {
		this->m_Scale = Vec2(835 * r, 210 * r);
	}
	void DefSp::Result_ScaleControl(float r) {
		this->m_Scale = Vec2(400 * r, 100 * r);
	}

	//--------------------------------------------------------------------------------------
	///	Goal
	//--------------------------------------------------------------------------------------
	Goal::Goal(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.4f),
		m_BaseY(-5.0f),
		m_Posision(Pos)
	{}
	Goal::~Goal() {}

	Vec3 Goal::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void Goal::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 0.75f;
		body.m_Scale = Vec3(5.0f, 5.0f, 0.1f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		m_PtrObj = make_shared<BcDrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_OwnShadowmapActive = false;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;


	}

	void Goal::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void Goal::OnUpdate2() {
		//プレイヤーのＺ位置は強制的に0.0にする
		m_Rigidbody->m_Pos = m_Posision;
	}

	void Goal::OnDrawShadowmap() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}

	void Goal::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			auto PtrGameStage = GetStage<GameStage>();
			shptr = PtrGameStage->FindTagGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	///	竹
	//--------------------------------------------------------------------------------------
	Bamboo::Bamboo(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.4f),
		m_BaseY(-5.0f),
		m_Posision(Pos)
	{}
	Bamboo::~Bamboo() {}

	Vec3 Bamboo::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void Bamboo::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//タグの追加
		AddTag(L"Bamboo");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 0.75f;
		body.m_Scale = Vec3(0.35f,0.7f,1);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);
		body.m_Pos.z -= 7;
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		m_PtrObj = make_shared<BcDrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_OwnShadowmapActive = false;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;


	}

	void Bamboo::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void Bamboo::OnUpdate2() {

		if (D_flag)
		{
			ThisDelete();
		}

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		if (this->FindTag(L"BambooB")) {
			if (GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetAttack()){
			//for (auto& v : StateVec) {
			//	if (v.m_Src == m_Rigidbody.get()) {
			//		//Destにボックスタグがあるかどうか調べる
			//		auto shptr = v.m_Dest->m_Owner.lock();
			//		if (shptr && shptr->FindTag(L"Kaguya")) {
			//			ThisDelete();
			//		}
			//		break;
			//	}
			//	if (v.m_Dest == m_Rigidbody.get()) {
			//		//Srcにボックスタグがあるかどうか調べる
			//		auto shptr = v.m_Src->m_Owner.lock();
			//		if (shptr && shptr->FindTag(L"Kaguya")) {
			//			ThisDelete();
			//			}
			//		break;
			//		}
			//	}
				SPHERE t;
				t.m_Center = m_Rigidbody->m_Pos;
				t.m_Center.z = 0;
				t.m_Radius = 0.25;

				SPHERE p;
				p.m_Center = GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetPosition();
				p.m_Center.z = 0;
				p.m_Radius = 1;

				if (HitTest::SPHERE_SPHERE(t, p)){
					ThisDelete();
				}
			}
		}
		//プレイヤーのＺ位置は強制的に0.0にする
		m_Rigidbody->m_Pos = m_Posision;
	}

	void Bamboo::OnDrawShadowmap() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}

	void Bamboo::OnDraw() {
		//行列の定義
		Mat4x4 World;
		
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			Vec3(m_Rigidbody->m_Pos.x, m_Rigidbody->m_Pos.y, m_Rigidbody->m_Pos.z-7)
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			auto PtrGameStage = GetStage<GameStage>();
			shptr = PtrGameStage->FindTagGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	void Bamboo::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<Bamboo>(GetThis<Bamboo>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<Bamboo>());
	}

	//--------------------------------------------------------------------------------------
	///	光ゲージ回復
	//--------------------------------------------------------------------------------------
	LightHeel::LightHeel(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.4f),
		m_BaseY(-5.0f),
		m_Posision(Pos)
	{}
	LightHeel::~LightHeel() {}

	Vec3 LightHeel::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void LightHeel::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//タグの追加
		AddTag(L"LightHeel");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 0.75f;
		body.m_Scale = Vec3(1.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		m_PtrObj = make_shared<BcDrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_OwnShadowmapActive = false;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;


	}

	void LightHeel::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void LightHeel::OnUpdate2() {
		SPHERE t;
		t.m_Center = m_Rigidbody->m_Pos;
		t.m_Center.z = 0;
		t.m_Radius = 0.5;

		SPHERE p;
		p.m_Center = GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetPosition();
		p.m_Center.z = 0;
		p.m_Radius = 1;
		
		if (HitTest::SPHERE_SPHERE(t, p))
		{
			auto player = GetStage<GameStage>()->FindTagGameObject<Player>(L"Player");
			auto gage = player->getP_LightGage() + 50;
			player->setP_LightGage(gage);
			ThisDelete();
		}

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
				for (auto& v : StateVec) {
					if (v.m_Src == m_Rigidbody.get()) {
						//Destにボックスタグがあるかどうか調べる
						auto shptr = v.m_Dest->m_Owner.lock();
						if (shptr && shptr->FindTag(L"Kaguya")) {
							ThisDelete();
						}
						break;
					}
					if (v.m_Dest == m_Rigidbody.get()) {
						//Srcにボックスタグがあるかどうか調べる
						auto shptr = v.m_Src->m_Owner.lock();
						if (shptr && shptr->FindTag(L"Kaguya")) {
							ThisDelete();
						}
						break;
					}
					//m_Rigidbody->m_Pos = m_Posision;
				}
		//プレイヤーのＺ位置は強制的に0.0にする
		m_Rigidbody->m_Pos.z = 10;
	}

	void LightHeel::OnDrawShadowmap() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}

	void LightHeel::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			auto PtrGameStage = GetStage<GameStage>();
			shptr = PtrGameStage->FindTagGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}


	void LightHeel::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<LightHeel>(GetThis<LightHeel>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<LightHeel>());
	}

	//--------------------------------------------------------------------------------------
	///	雲
	//--------------------------------------------------------------------------------------
	Cloud::Cloud(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.4f),
		m_BaseY(-5.0f),
		m_Posision(Pos)
	{}
	Cloud::~Cloud() {}

	Vec3 Cloud::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void Cloud::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 0.75f;
		body.m_Scale = Vec3(5.0f, 5.0f, 0.1f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		m_PtrObj = make_shared<BcDrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_OwnShadowmapActive = false;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;


	}

	void Cloud::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void Cloud::OnUpdate2() {
		//プレイヤーのＺ位置は強制的に0.0にする
		m_Rigidbody->m_Pos = m_Posision;
	}

	void Cloud::OnDrawShadowmap() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}

	void Cloud::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			auto PtrGameStage = GetStage<GameStage>();
			shptr = PtrGameStage->FindTagGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	///	途中の雲
	//--------------------------------------------------------------------------------------
	StageCloud::StageCloud(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.4f),
		m_BaseY(-5.0f),
		m_Posision(Pos)
	{}
	StageCloud::~StageCloud() {}

	Vec3 StageCloud::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void StageCloud::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 0.75f;
		body.m_Scale = Vec3(5.0f,5.0f,0.1f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		m_PtrObj = make_shared<BcDrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_OwnShadowmapActive = false;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;
		m_PtrObj->m_Alpha = 0.5f;

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;


	}

	void StageCloud::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void StageCloud::OnUpdate2() {
		//プレイヤーのＺ位置は強制的に0.0にする
		m_Rigidbody->m_Pos = m_Posision;
	}

	void StageCloud::OnDrawShadowmap() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}

	void StageCloud::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			auto PtrGameStage = GetStage<GameStage>();
			shptr = PtrGameStage->FindTagGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	///	Fade
	//--------------------------------------------------------------------------------------
	Fade::Fade(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName,
		const Vec2& StartScale,
		float StartRot,
		const Vec2& StartPos,
		UINT XWrap, UINT YWrap) :
		SpriteBase(StagePtr, TextureResName, StartScale, StartRot, StartPos, XWrap, YWrap),
		m_TotalTime(0)
	{
		SetBlendState(BlendState::Trace);
	}

	void Fade::AdjustVertex() {
		//ここでは何もしない
	}

	void  Fade::UpdateVertex(float ElapsedTime, VertexPositionColorTexture* vertices) {
		m_TotalTime += (ElapsedTime * 5.0f);
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		float sin_val = sin(m_TotalTime) * 0.5f + 0.5f;
		Col4 UpdateCol(1.0f, 1.0f, 1.0f, a);
		if (Fadeflag&&!Clearflag) {
			a += 0.015;
		}
		for (size_t i = 0; i < m_SquareMesh->GetNumVertices(); i++) {
			vertices[i] = VertexPositionColorTexture(
				m_BackupVertices[i].position,
				UpdateCol,
				m_BackupVertices[i].textureCoordinate
			);
		}
		if (a >= 1)
		{
			Fadeflag2 = true;
		}
	}

	//--------------------------------------------------------------------------------------
	//	Starスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
	JumpEffectSS::JumpEffectSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos,const wstring& Anime_Name) :
		SS5ssae(StagePtr, BaseDir, L"Effect_jump.ssae", Anime_Name),
		m_Posision(Pos)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void JumpEffectSS::OnCreate() {

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(1.5f, 1.5f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);
		//ChangeAnimation(L"Fly");
		SetLooped(false);
	}

	//更新
	void JumpEffectSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		time += ElapsedTime;
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (time>=0.55)
		{
			ThisDelete();
		}
	}

	void JumpEffectSS::ThisDelete()
	{
		GetStage<GameStage>()->RemoveGameObject<JumpEffectSS>(GetThis<JumpEffectSS>());
	}

	//--------------------------------------------------------------------------------------
	//	Hellスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
	HeelSS::HeelSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"LightItem2.ssae", L"aLight"),
		m_Posision(Pos)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void HeelSS::OnCreate() {
		//タグの追加
		AddTag(L"Item");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(1.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);
		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(1.5f, 1.5f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);
		//ChangeAnimation(L"Fly");
		SetLooped(true);
	}

	//更新
	void HeelSS::OnUpdate() {
		SPHERE t;
		t.m_Center = m_Rigidbody->m_Pos;
		t.m_Center.z = 0;
		t.m_Radius = 0.5;

		SPHERE p;
		p.m_Center = GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetPosition();
		p.m_Center.z = 0;
		p.m_Radius = 1;

		if (HitTest::SPHERE_SPHERE(t, p))
		{
			auto player = GetStage<GameStage>()->FindTagGameObject<Player>(L"Player");
			auto gage = player->getP_LightGage() + 50;
			player->setP_LightGage(gage);
			ThisDelete();
		}

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Destにボックスタグがあるかどうか調べる
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					ThisDelete();
				}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Srcにボックスタグがあるかどうか調べる
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					ThisDelete();
				}
				break;
			}
			//m_Rigidbody->m_Pos = m_Posision;
		}
		//プレイヤーのＺ位置は強制的に0.0にする
		m_Rigidbody->m_Pos.z = 10;
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void HeelSS::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<HeelSS>(GetThis<HeelSS>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<HeelSS>());
	}

	//--------------------------------------------------------------------------------------
	//	Barスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
	BarSS::BarSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const wstring& Anime, const Vec3& Pos, const Vec3& Scale, const Quat Qua) :
		Anime(),
		SS5ssae(StagePtr, BaseDir, L"Line.ssae", Anime),
		m_Posision(Pos),
		m_Scale(Scale),
		m_Qua(Qua)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void BarSS::OnCreate() {
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = m_Scale;
		body.m_Quat = m_Qua;
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeOBB;
		body.m_IsFixed = true;
		body.m_IsDrawActive  = false;
		body.SetToBefore();
		PtrGameStage->AddRigidbody(body);


		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Scale,
			Vec3(0, 0, 0),
			m_Qua,
			m_Posision
		);

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(Vec3(m_Scale.x*1.3f,5,1)*-1);
		PtrT->SetPosition(m_Posision);
		PtrT->SetQuaternion(m_Qua);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(60.0f);

		
		//ChangeAnimation(L"Fly");
		SetLooped(false);
	}

	//更新
	void BarSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		Time += ElapsedTime;
		if (D_flag)
		{
			D_Time += ElapsedTime;
		}
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (Time >4.0f) {
			D_flag = true;
		}

		if (D_Time >0.3f) {
			ThisDelete();
		}
	}

	void BarSS::ThisDelete()
	{
		Vec3 Emitter = m_Posision;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<BarSS>(GetThis<BarSS>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<BarSS>());
	}

	//--------------------------------------------------------------------------------------
	//	Effectスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
	RedEffectSS::RedEffectSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"KaguyaEF.ssae", L"Red_E"),
		m_Posision(Pos)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void RedEffectSS::OnCreate() {

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(3.0f, 3.0f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);
		//ChangeAnimation(L"Fly");
		SetLooped(false);
	}
	void RedEffectSS::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		time += ElapsedTime;
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PtrGameStage = GetStage<GameStage>();
		GetTransform()->SetPosition(PtrGameStage->GetKaguyaPos());
		if (time >= 3.0)
		{
			ThisDelete();
		}
	}

	void RedEffectSS::ThisDelete()
	{
		GetStage<GameStage>()->RemoveGameObject<RedEffectSS>(GetThis<RedEffectSS>());
	}

	//--------------------------------------------------------------------------------------
	///	途中の雲
	//--------------------------------------------------------------------------------------
	Bomboo2::Bomboo2(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureResName, bool Trace, const Vec3& Pos) :
		GameObject(StagePtr),
		m_TextureResName(TextureResName),
		m_Trace(Trace),
		m_BaseX(5.4f),
		m_BaseY(-5.0f),
		m_Posision(Pos)
	{}
	Bomboo2::~Bomboo2() {}

	Vec3 Bomboo2::GetPosition() {
		return m_Rigidbody->m_Pos;
	}

	void Bomboo2::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateSquare(1.0f, vertices, indices);
		//メッシュの作成（変更できない）
		m_SphereMesh = MeshResource::CreateMeshResource(vertices, indices, false);
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 0.75f;
		body.m_Scale = Vec3(1.0f, 1.0f, 0.1f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);

		m_PtrObj = make_shared<BcDrawObject>();
		auto TexPtr = App::GetApp()->GetResource<TextureResource>(m_TextureResName);
		m_PtrObj->m_MeshRes = m_SphereMesh;
		m_PtrObj->m_TextureRes = TexPtr;
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		m_PtrObj->m_OwnShadowmapActive = false;
		m_PtrObj->m_ShadowmapUse = true;
		m_PtrObj->m_BlendState = BlendState::AlphaBlend;
		m_PtrObj->m_RasterizerState = RasterizerState::DoubleDraw;
		m_PtrObj->m_Alpha = 0.5f;

		//シャドウマップ描画データの構築
		m_PtrShadowmapObj = make_shared<ShadowmapObject>();
		m_PtrShadowmapObj->m_MeshRes = m_SphereMesh;
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;


	}

	void Bomboo2::OnUpdate() {
		//前回のターンからの経過時間を求める
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void Bomboo2::OnUpdate2() {
		//プレイヤーのＺ位置は強制的に0.0にする
		//m_Rigidbody->m_Pos.z = m_Posision.z-8;
	}

	void Bomboo2::OnDrawShadowmap() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		//描画データの行列をコピー
		m_PtrShadowmapObj->m_WorldMatrix = World;
		m_PtrShadowmapObj->m_Camera = GetStage<Stage>()->GetCamera();

		auto shptr = m_ShadowmapRenderer.lock();
		if (!shptr) {
			shptr = GetStage<Stage>()->FindTagGameObject<ShadowmapRenderer>(L"ShadowmapRenderer");
			m_ShadowmapRenderer = shptr;
		}
		shptr->AddDrawObject(m_PtrShadowmapObj);
	}

	void Bomboo2::OnDraw() {
		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			m_Rigidbody->m_Scale,
			Vec3(0, 0, 0),
			m_Rigidbody->m_Quat,
			m_Rigidbody->m_Pos
		);
		m_PtrObj->m_WorldMatrix = World;
		m_PtrObj->m_Camera = GetStage<Stage>()->GetCamera();
		auto shptr = m_Renderer.lock();
		if (!shptr) {
			auto PtrGameStage = GetStage<GameStage>();
			shptr = PtrGameStage->FindTagGameObject<BcPNTStaticRenderer>(L"BcPNTStaticRenderer");
			m_Renderer = shptr;
		}
		shptr->AddDrawObject(m_PtrObj);
	}

	//--------------------------------------------------------------------------------------
	//	Hellスプライトスタジオ
	//--------------------------------------------------------------------------------------
	//構築と破棄
	TamanoedaSS::TamanoedaSS(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir, const Vec3& Pos) :
		SS5ssae(StagePtr, BaseDir, L"TAMA.ssae", L"Flash"),
		m_Posision(Pos)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0.0f)
		);

	}

	//初期化
	void TamanoedaSS::OnCreate() {
		//タグの追加
		AddTag(L"Item");
		//Rigidbodyの初期化
		auto PtrGameStage = GetStage<GameStage>();
		Rigidbody body;
		body.m_Owner = GetThis<GameObject>();
		body.m_Mass = 1.0f;
		body.m_Scale = Vec3(1.0f);
		body.m_Quat = Quat();
		body.m_Pos = m_Posision;
		body.m_CollType = CollType::typeSPHERE;
		//		body.m_IsDrawActive = true;
		body.SetToBefore();

		m_Rigidbody = PtrGameStage->AddRigidbody(body);

		//行列の定義
		Mat4x4 World;
		World.affineTransformation(
			body.m_Scale,
			Vec3(0, 0, 0),
			body.m_Quat,
			body.m_Pos
		);
		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		auto PtrT = GetTransform();
		PtrT->SetScale(1.5f, 1.5f, 1.0f);
		PtrT->SetPosition(m_Posision);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);
		//ChangeAnimation(L"Fly");
		SetLooped(true);
	}

	//更新
	void TamanoedaSS::OnUpdate() {
		SPHERE t;
		t.m_Center = m_Rigidbody->m_Pos;
		t.m_Center.z = 0;
		t.m_Radius = 0.5;

		SPHERE p;
		p.m_Center = GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya")->GetPosition();
		p.m_Center.z = 0;
		p.m_Radius = 1;

		if (HitTest::SPHERE_SPHERE(t, p))
		{
			auto kaguya = GetStage<GameStage>()->FindTagGameObject<Kaguya>(L"Kaguya");
			kaguya->SetStarFlag(true);
			ThisDelete();
		}

		auto& StateVec = GetStage<GameStage>()->GetCollisionStateVec();
		for (auto& v : StateVec) {
			if (v.m_Src == m_Rigidbody.get()) {
				//Destにボックスタグがあるかどうか調べる
				auto shptr = v.m_Dest->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					ThisDelete();
				}
				break;
			}
			if (v.m_Dest == m_Rigidbody.get()) {
				//Srcにボックスタグがあるかどうか調べる
				auto shptr = v.m_Src->m_Owner.lock();
				if (shptr && shptr->FindTag(L"Kaguya")) {
					ThisDelete();
				}
				break;
			}
			//m_Rigidbody->m_Pos = m_Posision;
		}
		//プレイヤーのＺ位置は強制的に0.0にする
		m_Rigidbody->m_Pos.z = 10;
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	}

	void TamanoedaSS::ThisDelete()
	{
		Vec3 Emitter = m_Rigidbody->m_Pos;
		//Spaerkの送出
		auto SpaerkPtr = GetStage<GameStage>()->FindTagGameObject<MultiSpark>(L"MultiSpark");
		SpaerkPtr->InsertSpark(Emitter);
		GetStage<GameStage>()->RemoveGameObject<TamanoedaSS>(GetThis<TamanoedaSS>());
		GetStage<GameStage>()->RemoveOwnRigidbody(GetThis<TamanoedaSS>());
	}
}
//end basecross
