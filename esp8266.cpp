#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /*clock=*/14, /*data=*/12, /*reset=*/U8X8_PIN_NONE);

#define buzzer D8
#define ledVerde D0
#define ledAmarelo D1
#define ledVermelho D2

void acessoPermitido()
{
    digitalWrite(ledVerde, HIGH);

    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);

    digitalWrite(ledVerde, LOW);
}

void acessoNegado()
{
  tone(buzzer, 300);

  digitalWrite(ledVermelho, HIGH);
  delay(600);
  digitalWrite(ledVermelho, LOW);

  noTone(buzzer);
  delay(100);
}

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  Serial.println("ESP8266: Aguardando dados do ESP32");

  pinMode(buzzer, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

}

void loop() {
  if (Serial.available() > 0)
  {
    String serialCardID = Serial.readStringUntil('\n');

    if (serialCardID.startsWith("CARD:"))
    {
        String cardID = serialCardID.substring(5); //Remove o "CARD:"
        //Exibir o ID do cartão no display OLED
        u8g2.clearBuffer();
        u8g2.setCursor(0, 24);
        u8g2.print("Cartao lido:");
        u8g2.setCursor(0, 48);
        u8g2.print(cardID);

        u8g2.sendBuffer();
        
        acessoPermitido();
        //acessoNegado();

        Serial.print("ID do Cartao Recebido: ");
        Serial.println(cardID);
    }
  }
}