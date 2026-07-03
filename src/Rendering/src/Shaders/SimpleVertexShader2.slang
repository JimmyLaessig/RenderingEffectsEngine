import Transform;
import Camera;


struct InstanceData
{
    // Index of the MeshData for this instance
    uint meshIndex;
    // Index of the MaterialData for this instance
    uint materialIndex;
    // Index of the TransformData for this instance
    uint transformIndex;

    uint2 _pad;
};

struct MeshData
{
    // Index of the index buffer
    uint indexBufferIndex; 
    // Index of the vertex buffers
    uint vertexBufferIndex;
    // Starting index in that index buffer
    uint firstIndex;
    // Added to index to get vertex index
    uint vertexOffset; 
};

struct MaterialData
{
    float4 baseColor;
    uint   baseColorTextureIndex;
    uint   normalTextureIndex;
    uint2   _pad;
};

ConstantBuffer<Camera> gCamera;

StructuredBuffer<InstanceData> gInstances;

StructuredBuffer<MeshData> gMeshes;

StructuredBuffer<Transform> gTransforms;

StructuredBuffer<MaterialData> gMaterials;

StructuredBuffer<float3> gPositions[];

StructuredBuffer<float3> gNormals[];

StructuredBuffer<float2> gTexcoord0[];

StructuredBuffer<uint> gIndices[];

Texture2D<float4> gTextures[];

SamplerState gSampler;


struct VSInput
{
    uint vertexId   : SV_VertexID;
    uint instanceId : SV_InstanceID;
};


struct VSOutput
{
    float4 position    : SV_Position;
    float3 normalWS    : NORMAL;
    float2 texcoord0   : TEXCOORD0;
    uint materialIndex : TEXCOORD1;
};


VSOutput vsMain(VSInput input)
{
    VSOutput output;

    // Get the InstanceData for the current instance
    InstanceData instance   = gInstances[input.instanceId];
    // Get the TransformData for the current instance
    TransformData transform = gTransforms[instance.transformIndex];
    // Get the MeshData of the current instance
    MeshData mesh           = gMeshes[instance.meshIndex];
    // Get the MaterialData of the current instance
    MaterialData material   = gMaterials[instance.materialIndex];

    // Get the index of the vertex
    uint index = mesh.vertexOffset + gIndices[mesh.indexBufferIndex][mesh.firstIndex + input.vertexId];

    // Get the vertex attributes
    float3 position  = gPositions[mesh.vertexBufferIndex][index];
    float3 normal    = gNormals[mesh.vertexBufferIndex][index];
    float2 texcoord0 = gTexcoord0[mesh.vertexBufferIndex][index];

    float4 worldPos    = mul(transform.localToWorldMatrix, float4(position, 1.0));
    float3 worldNormal = mul(transform.normalMatrix, normal);

    output.position      = mul(gCamera.viewProjectionMatrix, worldPos);
    output.normalWS      = worldNormal;
    output.texcoord0     = texcoord0;
    output.materialIndex = instance.materialIndex;

    return output;
}


float4 psMain(VSOutput input)
{
    MaterialData material = gMaterials[input.materialIndex];

    // Base color texture (optional)
    float4 baseColor = material.baseColor;
    if (material.baseColorTextureIndex != 0xFFFFFFFF)
    {
        baseColor *= gTextures[material.baseColorTextureIndex].Sample(gSampler, input.texcoord0);
    }

    // Simple lambert with a hard-coded light
    float3 lightDir = normalize(float3(0.3, 0.7, 0.2));
    float NdotL = saturate(dot(input.normalWS, lightDir));

    return float4(baseColor.rgb * NdotL, baseColor.a);
}
