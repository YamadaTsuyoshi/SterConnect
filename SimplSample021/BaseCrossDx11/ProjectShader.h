/*!
@file ProjectShader.h
@brief �v���W�F�N�g�Ŏg�p����V�F�[�_�[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�`��p�̃V�F�[�_�N���X�̐錾�i�}�N���g�p�j
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	///	SimpleConstants�R���X�^���g�o�b�t�@�\����(�V���v���R�c���L)
	//--------------------------------------------------------------------------------------
	struct SimpleConstants
	{
		/// ���[���h�s��
		Mat4x4 World;
		/// �r���[�s��
		Mat4x4 View;
		/// �ˉe�s��
		Mat4x4 Projection;
		/// �G�~�b�V�u�F
		Col4 Emissive;
		/// �f�t���[�Y�F
		Col4 Diffuse;
		/// �X�y�L�����[
		Col4 Specular;
		/// �e�N�X�`��=x���A�N�e�B�u���ǂ���
		XMUINT4 ActiveFlg;
		/// ���C�C�g����
		Vec4 LightDir;
		/// ���C�g�ʒu
		Vec4 LightPos;
		/// Eye�̈ʒu
		Vec4 EyePos;
		/// ���C�g�r���[�s��
		Mat4x4 LightView;
		/// ���C�g�ˉe�s��
		Mat4x4 LightProjection;
		/// Bone�z��
		Vec4 Bones[3 * 72];
		SimpleConstants() {
			memset(this, 0, sizeof(SimpleConstants));
			Diffuse = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};
	//CBSimple
	DECLARE_DX11_CONSTANT_BUFFER(CBSimple, SimpleConstants)
	DECLARE_DX11_VERTEX_SHADER(VSPNTStatic, VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStatic)

	//�X�v���C�g�p�R���X�^���g�o�b�t�@�\����
	struct SpriteConstantBuffer
	{
		Mat4x4 World;
		Col4 Emissive;
		SpriteConstantBuffer() {
			memset(this, 0, sizeof(SpriteConstantBuffer));
		};
	};
	DECLARE_DX11_CONSTANT_BUFFER(CBSprite, SpriteConstantBuffer)

	//PCTSprite
	DECLARE_DX11_VERTEX_SHADER(VSPCTSprite, VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPCTSprite)


}
//end basecross

