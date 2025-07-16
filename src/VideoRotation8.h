#ifndef VIDEOROTATION8_H
#define VIDEOROTATION8_H


#include "vdjVideo8.h"
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <string_view>  // ISO C++17 Standard (/std:c++17)
#include <stdio.h>
#include <atlbase.h> //we use atl for the CComPtr<ID3D11xxxxxx> smart pointer, but this is optional

#pragma comment(lib, "d3d11.lib")   // Direct3D11 library
#pragma comment(lib, "d3dcompiler.lib") // Direct3D shader compiler


//////////////////////////////////////////////////////////////////////////
// Class definition
//////////////////////////////////////////////////////////////////////////
class CVideoRotation8 : public IVdjPluginVideoFx8
{
public:
	CVideoRotation8();
	~CVideoRotation8();
	HRESULT VDJ_API OnLoad();
	HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8 *info);
	ULONG   VDJ_API Release();
	HRESULT VDJ_API OnParameter(int id);
	HRESULT VDJ_API OnGetParameterString(int id, char* outParam, int outParamSize);
	HRESULT VDJ_API OnDeviceInit();
	HRESULT VDJ_API OnDeviceClose();
	HRESULT VDJ_API OnStart();
	HRESULT VDJ_API OnStop();
	HRESULT VDJ_API OnDraw();
	HRESULT VDJ_API OnAudioSamples(float* buffer, int nb);

private:
	struct D3DXPOSITION
	{
		float x;
		float y;
		float z;
	};
	struct D3DXCOLOR
	{
	public:
		D3DXCOLOR() = default;
		D3DXCOLOR(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		operator FLOAT* ()
		{
			return &r;
		}

		FLOAT r, g, b, a;
	};
	struct D3DXTEXCOORD
	{
		float tu;
		float tv;
	};
	struct TLVERTEX
	{
		D3DXPOSITION position;
		D3DXCOLOR color;
		D3DXTEXCOORD texture;
	};

	#pragma pack(push,1)
	struct VS_CONSTANTBUFFER
	{
		DirectX::XMMATRIX m_WVPMatrix;
	};
	#pragma pack(pop)

	void OnResizeVideo();
	void OnSlider(int id);
	std::string_view getResource(const WCHAR* resourceType, const WCHAR* resourceName);
	HRESULT D3DXReadResourceToBlob(const WCHAR* resourceType, const WCHAR* resourceName, ID3DBlob** ppContents);

	HRESULT Initialize_D3D11(ID3D11Device* pDevice);
	HRESULT Rendering_D3D11(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, ID3D11RenderTargetView* pRenderTargetView, ID3D11ShaderResourceView* pTextureView, TVertex8* pVertices);
	HRESULT Create_InputLayout_D3D11(ID3D11Device* pDevice);
	HRESULT Create_VertexBufferDynamic_D3D11(ID3D11Device* pDevice);
	HRESULT Create_ConstantBufferDynamic_D3D11(ID3D11Device* pDevice);
	HRESULT Create_VertexShader_D3D11(ID3D11Device* pDevice);
	HRESULT Create_PixelShader_D3D11(ID3D11Device* pDevice);
	HRESULT Create_VertexShaderFromResourceCSOFile_D3D11(ID3D11Device* pDevice, const WCHAR* resourceType, const WCHAR* resourceName);
	HRESULT Create_PixelShaderFromResourceCSOFile_D3D11(ID3D11Device* pDevice, const WCHAR* resourceType, const WCHAR* resourceName);
	HRESULT Create_RasterizerState_D3D11(ID3D11Device* pDevice);
	HRESULT Update_VertexBufferDynamic_D3D11(ID3D11DeviceContext* ctx);
	HRESULT Update_ConstantBufferDynamic_D3D11(ID3D11DeviceContext* ctx);
	HRESULT Update_NewVertices_D3D11();
	HRESULT Update_ConstantBufferData_D3D11();
	HRESULT GetInfoFromShaderResourceView(ID3D11ShaderResourceView* pShaderResourceView);
	HRESULT GetInfoFromRenderTargetView(ID3D11RenderTargetView* pRenderTargetView);

	DirectX::XMMATRIX SetViewMatrix_D3D11();
	DirectX::XMMATRIX SetProjectionMatrix_D3D11();
	DirectX::XMMATRIX SetWorldMatrix_D3D11();

	ID3D11Device* pD3DDevice;
	ID3D11DeviceContext* pD3DDeviceContext;
	ID3D11RenderTargetView* pD3DRenderTargetView;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pConstantBuffer;
	ID3D11InputLayout* pInputLayout;
	ID3D11VertexShader* pVertexShader;
	ID3D11PixelShader* pPixelShader;
	ID3DBlob* pVertexShaderBlob;
	ID3D11RasterizerState* pRasterizerState;

	VS_CONSTANTBUFFER m_ConstantBufferData;

	TLVERTEX pNewVertices[4];
	UINT m_VertexCount;
	UINT m_VertexStride;
	UINT m_VertexOffset;
	bool m_Direct3D_On;
	int m_Width;
	int m_Height;
	float m_SliderValue[4];
	float m_Alpha;
	float m_Zoom;
	float m_Speed;
	float m_Angle;
	int m_RotationAxe;
	int m_RotationInverted;
	int m_RotationDisk;
	int m_BackgroundColor;
	int m_HoldDisk;

	typedef enum _ID_Interface
	{
		ID_INIT,
		ID_SLIDER_1,
		ID_SLIDER_2,
		ID_SLIDER_3,
		ID_SLIDER_4,
		ID_RADIO_1,
		ID_RADIO_2,
		ID_RADIO_3,
		ID_SWITCH_1,
		ID_SWITCH_2,
		ID_SWITCH_3
	} ID_Interface;

	#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(x) { if (x!=nullptr) { x->Release(); x=nullptr; } }
	#endif

	#ifndef SAFE_RELEASE_CCOMPTR
	#define SAFE_RELEASE_CCOMPTR(x) { if (x!=nullptr) { x.Release(); x=nullptr; } }
	#endif
};

#endif
