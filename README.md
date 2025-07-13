![logo](https://github.com/djcel/VirtualDJ-VideoRotation-Win64/blob/main/VideoRotation.JPG?raw=true "")
# VideoRotation
A VirtualDJ Video Effect for Windows 64-bit

DLL compilation (64bit):
- Output filepath: C:\Users\\{your_username}\AppData\Local\VirtualDJ\Plugins64\VideoEffect\VideoRotation.dll

You need to download [DirectXMath](https://github.com/Microsoft/DirectXMath) (at least version 2025.4.3.1) in Visual Studio 2022 with NuGet 

It uses a [Vertex Shader](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/blob/main/src/Shaders/VertexShader.hlsl) and a [Pixel Shader](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/blob/main/src/Shaders/PixelShader.hlsl) (with Shader Model 5.0)

The compiled shader files (.cso) in [src/Shaders](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/tree/main/src/Shaders) are then included in [Plugin.rc](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/blob/main/src/Plugin.rc) with the ResourceNames VERTEXSHADER8_CSO and PIXELSHADER8_CSO

For the Vertex Buffer, we use 4 vertices with D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP but we could have also used 6 vertices with D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST

We use a Constant Buffer in the Vertex Shader. We define:
- WVPMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix
  
with WorldMatrix = TranslationMatrix1 * RotationMatrix * TranslationMatrix2

(Both TranslationMatrix are used to center the rotation in the middle of the texture)
