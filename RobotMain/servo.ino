/********************************************************************
 * [Sub] ロボット上半身サーボ制御プログラム
 *  PCA9685ボード用
 * 
 *                                                @author  watanabe
 *                                                @date    2019/06/26
 ********************************************************************/
//-----------------------------
//外部ヘッダファイルの取り込み
//-----------------------------
#include <Wire.h>
#include <PCA9685.h>

//-------------------
// 各種定義
//-------------------
//PCA9685のアドレス指定
PCA9685 pwm = PCA9685(0x40);

//サーボ番号定義(PCA9685の接続ピン番号)
#define ARM_RIGHT_SHOULDER ( 5 )  // 左肩
#define ARM_RIGHT_ELBOW    ( 4 )  // 左ひじ
#define ARM_LEFT_SHOULDER  ( 10 )  // 右肩
#define ARM_LEFT_ELBOW     ( 11 )  // 右ひじ
/*
//TODO:下半身も同様に設定
#define LEG_RIGHT_ROOT ( 2 )  // 左足の付け根
#define LEG_RIGHT_KNEE ( 1 )  // 左膝
#define LEG_RIGHT_FOOT ( 0 )  // 左足首
#define LEG_LEFT_ROOT  ( 13 )  // 右足の付け根
#define LEG_LEFT_KNEE  ( 14 )  // 右膝
#define LEG_LEFT_FOOT  ( 15 )  // 右足首
*/

//サーボ初期設定(角度の可動範囲)
#define SERVOMIN ( 150 )    //最小パルス幅 (標準的なサーボパルスに設定)
#define SERVOMAX ( 600 )    //最大パルス幅 (標準的なサーボパルスに設定)

//サーボ初期姿勢定義
#define OFFSET_SHOULDER ( 20 ) //「気を付け」状態から、肩が背中側に曲がる角度
#define OFFSET_ARM      ( 20 ) //「気を付け」状態から、肘が内側　に曲がる角度

//----------------------------------------------------------------------
// セットアップ関数
//----------------------------------------------------------------------
void _servo_setup() {
    pwm.begin();                   //初期設定 (アドレス0x40用)
    pwm.setPWMFreq(60);            //PWM周期を60Hzに設定 (アドレス0x40用)
    Serial.println("SERVO start.");
}

//-------------------------------------------------------------------
// chで指定された番号のサーボをang度になるまで動かします。
// @param ch PCA9685のサーボ番号(0〜15)
// @param ang 角度（0～180）
//-------------------------------------------------------------------
void servo_write(int ch, int ang){ 
    ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～600）に変換
    pwm.setPWM(ch, 0, ang);
    delay(80); //wait 80ms
}

//-------------------------------------------------------------------
// 初期姿勢にします。
//-------------------------------------------------------------------
void _servo_initArms(){
    Serial.println("initArms");
    servo_write( ARM_RIGHT_SHOULDER,  0 + OFFSET_SHOULDER ); //肩は少し背中側に曲げる
    servo_write( ARM_RIGHT_ELBOW,     0 + OFFSET_ARM);       //肘も少し内側
    servo_write( ARM_LEFT_SHOULDER, 180 - OFFSET_SHOULDER ); //肩は少し背中側に曲げる
    servo_write( ARM_LEFT_ELBOW,    180 - OFFSET_ARM);       //肘も少し内側
    //TODO: 足の姿勢制御を追加
    //servo_write( LEG_RIGHT_ROOT,  XXXX ); //TODO
    //servo_write( LEG_RIGHT_KNEE,  XXXX ); //TODO
    //servo_write( LEG_RIGHT_FOOT,  XXXX ); //TODO
    //servo_write( LEG_LEFT_ROOT,   XXXX ); //TODO
    //servo_write( LEG_LEFT_KNEE,   XXXX ); //TODO
    //servo_write( LEG_LEFT_FOOT,   XXXX ); //TODO
}

//-------------------------------------------------------------------
// 右腕を最も下に下げた姿勢にします。(直立状態)
//-------------------------------------------------------------------
void _servo_minRightArm(){
#ifdef DISABLE_RIGHT
    return; //動かさない
#endif
    Serial.print("  ");            //インデントを付けてデバッグ情報を階層化する
    Serial.println(__FUNCTION__);  //関数名を埋め込む. Serial.println("minRightArm");と同じ結果になる。
    servo_write( ARM_RIGHT_SHOULDER,  0 );
    servo_write( ARM_RIGHT_ELBOW,     0 );
}

//-------------------------------------------------------------------
// 左腕を最も下に下げた姿勢にします。(直立状態)
//-------------------------------------------------------------------
void _servo_minLeftArm(){
#ifdef DISABLE_LEFT
    return; //動かさない
#endif
    Serial.print("  ");
    Serial.println(__FUNCTION__);
    servo_write( ARM_LEFT_SHOULDER, 180 );
    servo_write( ARM_LEFT_ELBOW,    180 );
}

//-------------------------------------------------------------------
// 右腕を最も上に上げた姿勢にします。
//-------------------------------------------------------------------
void _servo_maxRightArm(){
#ifdef DISABLE_RIGHT
    return; //動かさない
#endif
    Serial.print("  ");
    Serial.println(__FUNCTION__);
    servo_write( ARM_RIGHT_SHOULDER,  180 );
    servo_write( ARM_RIGHT_ELBOW,     100 );
}

//-------------------------------------------------------------------
// 左腕を最も上に上げた姿勢にします。
//-------------------------------------------------------------------
void _servo_maxLeftArm(){
#ifdef DISABLE_LEFT
    return; //動かさない
#endif
    Serial.print("  ");
    Serial.println(__FUNCTION__);
    servo_write( ARM_LEFT_SHOULDER, 0 );
    servo_write( ARM_LEFT_ELBOW,    80 );
}

//-------------------------------------------------------------------
// 両腕を最も下に下げた姿勢にします。(直立状態)
//-------------------------------------------------------------------
void _servo_minBothArms(){
    Serial.println(__FUNCTION__);
    _servo_minRightArm();
    _servo_minLeftArm();
}
//-------------------------------------------------------------------
// 両腕を最も上に挙げた姿勢にします。
//-------------------------------------------------------------------
void _servo_maxBothArms(){
    Serial.println(__FUNCTION__);
    _servo_maxRightArm();
    _servo_maxRightArm();
}
