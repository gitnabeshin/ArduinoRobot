/***********************************************************************************
 * [Main] ロボット制御メインプログラム
 *  このメインプログラムは、以下のサブプログラム群を呼び出し結合する事でロボット動作を実現します。
 *    - [Sub] led_eys.ino : LED制御
 *    - [Sub] servo.ino   : サーボ制御
 *    - [Sub] speaker.ino : スピーカー制御
 *  サブプログラムが公開する関数には以下の命名規約を設けます。
 *     _[モジュール名]_[関数名]
 *  サブプログラム間には依存関係を持たせず独立した構成とします。
 *                                                             @author  watanabe
 *                                                             @date    2019/06/26
 **********************************************************************************/

//-----------------------------
// 各種定義(共通 Mainファイル内)
//-----------------------------
#define CLOCK_TIME (1500) //ロボットのベースクロック(ms)

//------------------------------------------
//デバッグ用
// - 問題切り分けのため、ここの機能を無効化することができます
// - 本番動作では必ずコメントアウトしておく事
//------------------------------------------
//#define DISABLE_SOUND  //音を出さない
//#define DISABLE_RIGHT  //右腕を動かさない
//#define DISABLE_LEFT   //左腕を動かさない
//------------------------------------------


//----------------------------------------------------------------------
// セットアップ関数(起動時に１回だけ実行されます)
// the setup function runs once when you press reset or power the board
//----------------------------------------------------------------------
void setup() {

    Serial.begin(9600); // 9600bpsでシリアルポートを開く
    Serial.println("Main start."); //コンソールにメッセージを出力

    //[led_eyes]の初期化
    _led_eye_setup();
    //起動時に目を光らせます
    _led_eyes_ON();

    //[speaker]の初期化
    _speaker_setup();

    //[servo]の初期化
    _servo_setup();
}

//----------------------------------------------------------------------
// ループ関数(setup関数実行の後、無限回繰り返し実行されます)
// the loop function runs over and over again forever
//----------------------------------------------------------------------
void loop() {

    Serial.println("Action Start...");

    /**************************************** 
     *  ロボットの繰り返し動作プログラム
     *  全てのアクション時にクロック音を鳴らす
     * 1. 目を点滅させる
     * 2. 初期姿勢をとらせる
     * 3. 両腕をあげる
     * 4. 両腕を下げる
     * 5. 初期姿勢へ
     * 6. 右手だけ上げる
     * 7. 左手だけ上げる
     * 8. 初期姿勢に戻る
     *
     ****************************************/
    //++++++++++++++++++++++++++++++++++++++ ここから

    //動作クロック音
    _speaker_ClockSound();
    //LED点滅
    _led_eyes_Blink();

    _servo_initArms();     //初期姿勢
    _speaker_ClockSound();
    delay(CLOCK_TIME);
    _servo_minBothArms();  //両腕下げる
    _speaker_ClockSound();
    delay(CLOCK_TIME);
    _servo_maxBothArms();  //両腕上げる
    _speaker_ClockSound();
    delay(CLOCK_TIME);

    _servo_initArms();     //初期姿勢
    _speaker_ClockSound();
    delay(CLOCK_TIME);
    _servo_maxRightArm();  //右上げる
    _servo_minLeftArm();   //左下げる
    _speaker_ClockSound();
    delay(CLOCK_TIME);
    _servo_minRightArm();  //右下げる
    _servo_maxLeftArm();   //左上げる
    _speaker_ClockSound();
    delay(CLOCK_TIME);

    _servo_initArms();     //初期姿勢
    delay(CLOCK_TIME);

    //++++++++++++++++++++++++++++++++++++++ ここまで

    Serial.println("Action End...\n\n");
}
