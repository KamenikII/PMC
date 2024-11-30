#define TEMP_SENSOR A0
#define RED 13
#define BLUE 8
#define GREEN 12

const float BETA = 3950;
void setup() {
    Serial.begin(9600);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(TEMP_SENSOR, INPUT);
}
// ФУНКЦИЯ, ПЕРЕВОДЯЩАЯ ТЕМПЕРАТУРУ В ЦЕЛЬСИИ
int calculating_temp() { 
    int pretemp = analogRead(TEMP_SENSOR);
    int celsius = 1 / (log(1 / (1023. / pretemp - 1)) / BETA + 1.0 / 298.15) - 273.15; // из документации к датчику
    return celsius;
}
//работа светодиода
void rgb(
    bool r = false,
    bool g = false,
    bool b = false
) {
    digitalWrite(RED, r);
    digitalWrite(GREEN, g);
    digitalWrite(BLUE, b);
}
void loop() {
    int temp = calculating_temp();
    Serial.println(String(temp) + "\u2103");
    
    if (temp < -10) { // СИНИЙ
        rgb(false,false,true);
    }
    else if ((temp >= -10) && (temp < 5)) { // ЖЁЛТЫЙ
        rgb(true,true,false);
    }
    else if ((temp >=5) && (temp < 25)) { // ЗЕЛЁНЫЙ
        rgb(false,true,false);
    }
    else if (temp >=25) { // КРАСНЫЙ
        rgb(true,false,false);
    }
}