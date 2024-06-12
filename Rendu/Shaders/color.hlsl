cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld; // Matrice du monde
};

cbuffer cbPerCamera : register(b1)
{
    float4x4 gView;
    float4x4 gProj;
};

struct VertexIn
{
    float3 PosL : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    // Transform to homogeneous clip space using gWorld, gView, and gProj matrices.
    vout.PosH = mul(mul(float4(vin.PosL, 1.0f), gWorld), mul(gView, gProj));
    
    // Just pass vertex color into the pixel shader.
    vout.Color = vin.Color;
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    /*float4 diffuseAlbedo = float4(1.0f, 1.0f, 1.0f, 1.0f); // Diffuse/albedo color
    float3 fresnelR0 = float3(1.0f, 1.0f, 1.0f); // Fresnel R0
    float roughness = 1.0f; // Roughness of the material

    // Use material properties for lighting and shading calculations
    float3 lightDirection = normalize(float3(1.0f, 1.0f, 1.0f)); // Example light direction
    float diffuseFactor = max(0.0f, dot(pin.Color.rgb, lightDirection));
    float3 diffuseColor = pin.Color.rgb;

    // Specular reflection calculation using roughness
    float3 viewDirection = normalize(float3(0.0f, 0.0f, 1.0f)); // Example view direction (towards the camera)
    float3 halfVector = normalize(lightDirection + viewDirection);
    float specularFactor = pow(max(0.0f, dot(halfVector, pin.Color.rgb)), 1.0f / max(roughness, 0.0001f)); // Clamp roughness to avoid division by zero
    float3 specularColor = fresnelR0 * specularFactor;

    // Combine diffuse and specular colors
    float3 finalColor = diffuseColor * (1.0f - specularFactor) + specularColor;

    return float4(finalColor, 1.0f); // Alpha value is set to 1.0f (opaque)*/
    return pin.Color;
}
