![logo](https://github.com/djcel/VirtualDJ-VideoRotation-Win64/blob/main/VideoRotation.JPG?raw=true "")
# VideoRotation
A VirtualDJ Video Effect for Windows 64-bit

You need to download [DirectXMath](https://github.com/Microsoft/DirectXMath) (at least version 2025.4.3.1) in Visual Studio 2022 with NuGet 

It uses a [Vertex Shader](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/blob/main/src/Shaders/VertexShader.hlsl) and a [Pixel Shader](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/blob/main/src/Shaders/PixelShader.hlsl) (with Shader Model 5.0)

The compiled shader files (.cso) in [src/Shaders](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/tree/main/src/Shaders) are then included in [Plugin.rc](https://github.com/DJCEL/VirtualDJ-VideoRotation-Win64/blob/main/src/Plugin.rc) with the ResourceNames VERTEXSHADER8_CSO and PIXELSHADER8_CSO

We use a Constant Buffer in the Vertex Shader 

We define:
- WVPMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix
  
(with WorldMatrix = TranslationMatrix1 * RotationMatrix * TranslationMatrix2)
(Both TranslationMatrix are used to center the rotation in the middle of the texture)
