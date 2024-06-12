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
    return pin.Color;
    //bool isMatching = (gWorld[3][0] == 3.0f);

    //if (isMatching)
    //{
    //    return float4(1.0f, 0.0f, 0.0f, 1.0f);
    //}
    //else
    //{
    //    return pin.Color;
    //}
}

