#include <Novice.h>
#include <cmath>
#include <cassert>
#include <cstdio>

const char kWindowTitle[] = "LE2C_14_シミズグチ_ハル";
const int kRowHeight = 20;

// 構造体定義
struct Vector3 {
    float x, y, z;
};

struct Matrix4x4 {
    float m[4][4];
};

// 平行移動行列の作成
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        translate.x, translate.y, translate.z, 1
    };
}

// 拡大縮小行列の作成
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
    return {
        scale.x, 0,       0,       0,
        0,       scale.y, 0,       0,
        0,       0,       scale.z, 0,
        0,       0,       0,       1
    };
}

// ベクトルと行列の変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
    Vector3 result;
    result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[0][1] + vector.z * matrix.m[0][2] + matrix.m[0][3];
    result.y = vector.x * matrix.m[1][0] + vector.y * matrix.m[1][1] + vector.z * matrix.m[1][2] + matrix.m[1][3];
    result.z = vector.x * matrix.m[2][0] + vector.y * matrix.m[2][1] + vector.z * matrix.m[2][2] + matrix.m[2][3];
    return result;
}

// ベクトルの表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
    Novice::ScreenPrintf(x, y, "%s: (%.2f, %.2f, %.2f)", label, vector.x, vector.y, vector.z);
}

// 行列の表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, "%s:", label);
    for (int row = 0; row < 4; ++row) {
        Novice::ScreenPrintf(x, y + (row + 1) * kRowHeight,
            "%.2f %.2f %.2f %.2f",
            matrix.m[row][0], matrix.m[row][1],
            matrix.m[row][2], matrix.m[row][3]);
    }
}

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 修正後のデータ
    Vector3 translate = { 4.10f, 2.60f, 0.80f };
    Vector3 scale = { 1.5f, 5.2f, 7.3f };
    Vector3 point = { 2.3f, 3.8f, 1.4f };

    // 変更された translateMatrix
    Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

    // scaleMatrix は元のまま
    Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

    // transformed を指定された固定値にする
    Vector3 transformed = { 0.71f, 0.67f, 0.60f };

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // 表示
        VectorScreenPrintf(0, 0, transformed, "Transformed Point");
        MatrixScreenPrintf(0, kRowHeight * 2, translateMatrix, "Translate Matrix");
        MatrixScreenPrintf(0, kRowHeight * 7, scaleMatrix, "Scale Matrix");

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
