#include <Adafruit_GFX.h>//библиотека дисплея
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);//пины дисплея
#include "Keypad.h" //Библиотека  клавиотурі

const uint8_t pwnPin = 11;  	//пины шима выход
const uint8_t analogPin = A8;  	//пин вход резистора А8
const uint8_t k_res = 100;		//коэфициент резистора

uint16_t ADCval = 0;       		//обналяетя переменая
double pwm = 0; 		//

//---------------------------------------------------------------------
// Клавиатура
//---------------------------------------------------------------------
const byte Rows= 4; // количество строк на клавиатуре, 4
const byte Cols= 4; // количество столбцов на клавиатуре, 4

// определяем массив символов соответствующий распределению кнопок на клавиатуре:
char keymap[Rows][Cols]=
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// соединения клавиатуры с выводами Arduino задаются так:
byte rPins[Rows]= {A7,A6,A5,A4}; // строки с 0 по 3
byte cPins[Cols]= {A3,A2,A1,A0};    // столбцы с 0 по 3

// команда для библиотеки клавиатуры
// инициализирует экземпляр класса Keypad
Keypad kpd= Keypad(makeKeymap(keymap), rPins, cPins, Rows, Cols);

uint8_t start_LCD = 0, last_start_LCD; //переменная таймера дисплея
//---------------------------------------------------------------------
// Цикл настроек при старте
//---------------------------------------------------------------------
void setup()
{
	Serial.begin(9600);  // инициализация монитора последовательного порта
	inicial_LCD(); //Старт LCD
	
	pinMode(pwnPin, OUTPUT);       //присваеваю пину выхо
}

//---------------------------------------------------------------------
// Цикл программы
//---------------------------------------------------------------------
  void loop()
{
	
	
	char keypressed = kpd.getKey(); // Если кнопка нажата, эта кнопка сохраняется в переменной keypressed.
	if (keypressed != NO_KEY)		// Если keypressed не равна NO_KEY, то выводим значение в последовательный порт.
	{ 
		Serial.println(keypressed);
	}

	ADCval = analogRead(analogPin);  	//вал присвается считывание аналового ввода 0-1024
	ADCval = ADCval/1024.0*k_res;
	//pwm = (pwnPin, ADCval/ 10.24);     //проценті шима переменая шим
	analogWrite(pwnPin, ADCval / 4);   //выход шима 11 порт 0-256
	start_LCD = millis();
	if (start_LCD - last_start_LCD) < 1000) // если прошла 1 сек.(1000 циклов) вівести на экран
	{
		display.clearDisplay();         //очистка дисплея
		display.print(F("nkodep  "));      //вывод на єкран слова єнкодер
		display.println(ADCval);        //вывод на экран переменой вал
		display.print(F("pwm     "));      //вівод на єкран слова шим
		display.print(pwm);             //значения на єкране шим 0-100%
		display.print(F(" %"));             //на єкране %
		display.print(keypressed);
		delay(400);                    	//временая задержка
		display.display();              //инициолизация дисплея
		last_start_LCD = millis();
	}
}

void inicial_LCD ()
{
	// инициализация и очистка дисплея
	display.begin();              //инециолизация драйвера дисплея 
	display.clearDisplay();       //очистка дисплея
    display.display();            //функция передачи информации на икран
    display.setContrast(50);      // установка контраста
    //delay(1000);                 //временая задержка
    display.setTextSize(1);      // установка размера шрифта
    display.setTextColor(BLACK); // установка цвета текста
    display.setCursor(0,0);      // установка позиции курсора
}


