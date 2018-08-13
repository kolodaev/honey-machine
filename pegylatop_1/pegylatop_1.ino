

#include <Adafruit_GFX.h>//библиотека дисплея
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);//пины дисплея
#include "Keypad.h" //Библиотека  клавиотурі


const byte Rows= 4; // количество строк на клавиатуре, 4
const byte Cols= 4; // количество столбцов на клавиатуре, 4


int pwnPin = 11;       //пины шима выход
int analogPin = 8;     //пин вход резистора А8
int val = 0;          //обналяетя переменая
int pwm = 0; 

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



void setup()
{
  // инициализация и очистка дисплея
    display.begin();              //инециолизация драйвера дисплея 
    display.clearDisplay();       //очистка дисплея
    display.display();            //функция передачи информации на икран
    display.setContrast(50);      // установка контраста
    delay(1000);                 //временая задержка
    display.setTextSize(1);      // установка размера шрифта
    display.setTextColor(BLACK); // установка цвета текста
    display.setCursor(0,0);      // установка позиции курсора
 
    
    
  pinMode(pwnPin, OUTPUT);       //присваеваю пину выход

  Serial.begin(9600);  // инициализация монитора последовательного порта
}
// Если кнопка нажата, эта кнопка сохраняется в переменной keypressed.
// Если keypressed не равна NO_KEY, то выводим значение в последовательный порт.
  void loop()
{

  char keypressed = kpd.getKey();
  if (keypressed != NO_KEY)
  
 { 
    Serial.println(keypressed);
  }

  val = analogRead(analogPin);  //вал присвается считывание аналового ввода 0-1024
  pwm = (pwnPin, val/ 10.24);       //проценті шима переменая шим
  analogWrite(pwnPin, val / 4);      //выход шима 11 порт 0-256

  display.clearDisplay();             //очистка дисплея
  display.print("nkodep  ");          //вівод на єкран слова єнкодер
  display.println(val);              //вывод на экран переменой вал
  display.print("pwm     ");          //вівод на єкран слова шим
  display.print(pwm);                 //значения на єкране шим 0-100%
  display.print('%');                //на єкране %
  display.print(keypressed);
  delay(400);                       //временая задержка
  display.display();                //инициолизация дисплея 

}




