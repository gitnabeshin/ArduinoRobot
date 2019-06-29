/********************************************************************
 * [Sub] LED 点滅プログラム
 * 
 *                                                @author  watanabe
 *                                                @date    2019/06/26
 ********************************************************************/

//-------------------
// 各種定義
//-------------------
// PIN番号
#define LED_EYE_RIGHT (4) //D4 ロボットの右目
#define LED_EYE_LEFT  (5) //D5 ロボットの左目

// 点滅時間(ms)
#define BLINK_TIME (400)

//----------------------------------------------------------------------
// セットアップ関数
//----------------------------------------------------------------------
void _led_eye_setup() {
    pinMode( LED_EYE_RIGHT, OUTPUT );    //Pin(D4)を出力モードに設定
    pinMode( LED_EYE_LEFT, OUTPUT );     //Pin(D5)を出力モードに設定
    Serial.println("LED initialized.");
}

//----------------------------------------------------------------------
// LEDの目を光らせます
//----------------------------------------------------------------------
void _led_eyes_ON() {
    digitalWrite( LED_EYE_RIGHT, HIGH );  // turn the LED on (HIGH is the voltage level)
    digitalWrite( LED_EYE_LEFT, HIGH );   // turn the LED on (HIGH is the voltage level)
    Serial.println(__FUNCTION__);         //関数名を埋め込む. Serial.println("_led_eyes_ON");と同じ結果になる。
}

//----------------------------------------------------------------------
// LEDの目を消します　
//----------------------------------------------------------------------
void _led_eyes_OFF() {
    digitalWrite( LED_EYE_RIGHT, LOW );  // turn the LED on (HIGH is the voltage level)
    digitalWrite( LED_EYE_LEFT, LOW );   // turn the LED on (HIGH is the voltage level)
    Serial.println(__FUNCTION__);
}

//----------------------------------------------------------------------
// LEDの目を点滅させます　
//----------------------------------------------------------------------
void _led_eyes_Blink() {
    _led_eyes_ON();
    delay( BLINK_TIME );   // wait
    _led_eyes_OFF();
    delay( BLINK_TIME );   // wait
    _led_eyes_ON();
    delay( BLINK_TIME );   // wait
    _led_eyes_OFF();
    delay( BLINK_TIME );   // wait
    _led_eyes_ON();        // 光らせた状態をキープ
    //Serial.println(__FUNCTION__);
}
