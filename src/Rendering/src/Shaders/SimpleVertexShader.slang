import Transform;
import Camera;

[[vk::binding(0)]]
ConstantBuffer<Camera> camera;

[[vk::binding(1)]]
ConstantBuffer<Transform> transform;


struct VSInput
{
    float3 position  : POSITION;
    float3 normal    : NORMAL;
    float2 texcoord0 : TEXCOORD0;
};


struct VSOutput
{
    float4 position    : SV_Position;
    float3 positionWS  : POSITION;
    float3 normalWS    : NORMAL;
    float2 texcoord0   : TEXCOORD0;
};


[shader("vertex")]
VSOutput vsMain(VSInput input)
{
    float4 positionWS = mul(transform.localToWorldMatrix, float4(input.position, 1.f));
    
    VSOutput output;
    output.position   = mul(camera.viewProjectionMatrix, positionWS);
    output.positionWS = positionWS.xyz / positionWS.w;
    output.normalWS   = mul(transform.normalMatrix, input.normal);
    output.texcoord0  = input.texcoord0;
    return output;
}
