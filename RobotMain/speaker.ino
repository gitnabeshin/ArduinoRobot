/********************************************************************
 * [Sub] 圧電スピーカー制御プログラム
 * 
 *                                                @author  watanabe
 *                                                @date    2019/06/26
 ********************************************************************/

//-------------------
// 各種定義
//-------------------
// PIN番号
#define PIN_SPEAKER (13)  //D13 圧電スピーカのピン番号
// 音の長さ
#define SOUND_TIME (200) //200ms

// 音階(see. http://arduino.cc/en/Tutorial/tone)
// 以下は抜粋。かなり広い範囲の音を鳴らすことができる
#define FQ_DO (131) // ド
#define FQ_RE (147) // レ
#define FQ_MI (165) // ミ
#define FQ_FA (175) // ファ
#define FQ_SO (196) // ソ
#define FQ_RA (220) // ラ
#define FQ_SI (247) // シ

//----------------------------------------------------------------------
// セットアップ関数
//----------------------------------------------------------------------
void _speaker_setup() {
    Serial.println("SPEAKER initialized.");
}

//----------------------------------------------------------------------
// クロック音を鳴らします。
//----------------------------------------------------------------------
void _speaker_ClockSound() {
#ifdef DISABLE_SOUND
    return; //音を出さない
#endif
    tone( PIN_SPEAKER, FQ_DO, SOUND_TIME);  // ド
    delay( SOUND_TIME );                    // 音がなっている間待機
    tone( PIN_SPEAKER, FQ_MI, SOUND_TIME);  // ミ
    delay( SOUND_TIME);
    tone( PIN_SPEAKER, FQ_SO, SOUND_TIME);  // ソ
    delay( SOUND_TIME );
    Serial.println(__FUNCTION__);
}

//----------------------------------------------------------------------
// [Template] XXX音を鳴らします。
//----------------------------------------------------------------------
/*
void _speaker_XXXXSound() {
#ifdef DISABLE_SOUND
    return; //音を出さない
#endif
      //ここからメロディーを鳴らすプログラムを書く    
//    tone( PIN_SPEAKER, FQ_DO, SOUND_TIME);  // ド
//    delay( SOUND_TIME );                    // 音がなっている間待機
    Serial.println(__FUNCTION__);
}
*/
