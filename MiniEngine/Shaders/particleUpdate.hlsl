#include "Constants.hlsl"

struct MyInput
{
    float3 velocity;
    float3 pos;
    float timer;
};
StructuredBuffer<MyInput> myInput : register(t0);

struct MyOutput
{
    float3 position : SV_POSITION;
    float size : SIZE;
    float3 velocity : VELOCITY;
    float timer : TIMER;
    float alpha : ALPHA;
};
RWStructuredBuffer<MyOutput> myOutput : register(u0);

[numthreads(1, 1, 1)]
void CS(uint3 num : SV_DispatchThreadID)
{
    myOutput[num.x].velocity = myInput[num.x].velocity - float3(0.0, 0.0, 1.0) * c_gravity * c_deltaTime;
    myOutput[num.x].timer = myInput[num.x].timer - c_deltaTime;
    myOutput[num.x].position = myInput[num.x].pos + myInput[num.x].velocity * c_deltaTime;
    myOutput[num.x].size = lerp(c_endSize, c_startSize, myOutput[num.x].timer / c_timeOut);
    myOutput[num.x].alpha = lerp(0.0, 1.0, myOutput[num.x].timer / c_timeOut);
}

