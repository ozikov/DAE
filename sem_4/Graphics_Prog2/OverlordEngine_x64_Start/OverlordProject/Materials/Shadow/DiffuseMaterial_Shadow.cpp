#include "stdafx.h"
#include "DiffuseMaterial_Shadow.h"

DiffuseMaterial_Shadow::DiffuseMaterial_Shadow():
	Material(L"Effects/Shadow/PosNormTex3D_Shadow.fx")
{}

void DiffuseMaterial_Shadow::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
	SetVariable_Texture(L"gDiffuseMap", m_pDiffuseTexture);
}

void DiffuseMaterial_Shadow::InitializeEffectVariables()
{
}

void DiffuseMaterial_Shadow::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const
{
	
	//Update The Shader Variables
	//1. Update the LightWVP > Used to Transform a vertex into Light clipping space
	//	LightWVP = model_world * light_viewprojection
	//	(light_viewprojection [LightVP] can be acquired from the ShadowMapRenderer)
	const XMMATRIX lightWVP{ XMLoadFloat4x4(&pModel->GetTransform()->GetWorld()) * XMLoadFloat4x4(&ShadowMapRenderer::Get()->GetLightVP()) };
	
	XMFLOAT4X4 fLightWVP{};
	XMStoreFloat4x4(&fLightWVP, lightWVP);

	SetVariable_Matrix(L"gWorldViewProj_Light", reinterpret_cast<const float*>(&fLightWVP));

	//2. Update the ShadowMap texture
	SetVariable_Texture(L"gShadowMap", ShadowMapRenderer::Get()->GetShadowMap());
	
	//3. Update the Light Direction (retrieve the direction from the LightManager > sceneContext)
	SetVariable_Vector(L"gLightDirection", sceneContext.pLights->GetDirectionalLight().direction);
}
