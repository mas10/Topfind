#pragma once
// リンカーの入力を設定
// デバッグとリリースで入力するファイルが違うでこのようにしています。
#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_core320" CV_EXT)       //画像・行列データ構造の提供、ユーティリティ機能など
#pragma comment(lib, "opencv_highgui320" CV_EXT)    //GUI（ウィンドウ表示など）
#pragma comment(lib, "opencv_imgcodecs320" CV_EXT)  //画像ファイル入出力
#pragma comment(lib, "opencv_imgproc320" CV_EXT)    //フィルター処理、エッジ検出など
