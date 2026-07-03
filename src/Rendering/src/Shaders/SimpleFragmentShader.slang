import Transform;
import Camera;

import SimpleVertexShader;

[[vk::binding(0)]]
ConstantBuffer<Camera> camera;

[[vk::binding(1)]]
ConstantBuffer<Transform> transform;

[shader("fragment")]
float4 fsMain(VSOutput input)
{
    float3 lightDirection = float3(1.f, 1.f, 1.f);
    float3 lightColor     = float3(1.f, 1.f, 1.f);

    float3 N = normalize(input.normalWS);
    float3 L = normalize(lightDirection);
 
    float NdotL = max(dot(N, L), 0.f);

    float3 baseColor = float3(1.f, 1.f, 1.f);
    float3 litColor = baseColor * lightColor * NdotL;

    return float4(litColor, 1.f);
}
