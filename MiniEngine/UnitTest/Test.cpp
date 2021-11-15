#include "stdafx.h"
#include "engineMath.h"
#include <iostream>

using namespace std;

int main()
{
    Vector2 x(1, 1);
    Vector2 y(2, 2);
    Vector2 z = Vector2::Lerp(x, y, 0.5f);
    cout << z.x << endl;
}

