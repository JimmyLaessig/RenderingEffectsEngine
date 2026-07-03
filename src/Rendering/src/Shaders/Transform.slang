
struct Transform
{
    /*!
     * Matrix to transform vertices from local to world space
     */
    float4x4 localToWorldMatrix;
    
    /*!
     * Matrix to transform normals from local to world space
     */
    float3x3 normalMatrix;

}; // struct Transform
