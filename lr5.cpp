#define PHOTO_SENSOR A0
#define RED A5
#define BLUE A3
#define GREEN A4

const float GAMMA = 0.7; // Наклон графика log(R) / log(lux)
const float RL10 = 50; // Сопротивление LDR 10lux (in kilo-ohms)
void setup() {
    Serial.begin(9600);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(PHOTO_SENSOR, INPUT);
}
void loop() {
    String str1 = "Value of light = ";
    int val = analogRead(PHOTO_SENSOR); // СЧИТЫВАЕМ ДАННЫЕ С ДАТЧИКА
    float voltage = val / 1024. * 5; // НАПРЯЖЕНИЕ
    float resistance = 2000 * voltage / (1 - voltage / 5); // СОПРОТИВЛЕНИЕ
    float lucs = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA)); // ПЕРЕВОДИМ В ЛЮКСЫ
    int color = map(val,1023,0,0,255); // ОПРЕДЕЛЯЕМ ЦВЕТ ДЛЯ СВЕТОДИОДА
    Serial.println("\nValue in bytes : " + String(val)); // ВЫВОДИМ В БАЙТАХ
    Serial.println(str1 + lucs + "Lk"); // ВЫВОДИМ В ЛЮКСАХ
    Serial.println("Value in color : " + String(color)); // ВЫВОДИМ ЦВЕТ
    analogWrite(RED,color);
    analogWrite(BLUE,color);
}