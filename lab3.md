### Закраска граней
#### Задание
* Написать программу, рисующую освещённый трёхмерный объект;
* Реализовать модель освещения Блинна-Фонга (с halfway-вектором);
* Реализовать любую другую модель освещения, принцип работы которой отличается от модели Блинна-Фонга (например, Кука-Торренса).

#### Требования
* При запуске программы сразу должен быть виден красиво освещенный объект в хорошем ракурсе;
* Грани объекта рисуются с помощью доступных функций закраски грани в координатах окна;
* Геометрия объекта должна генерироваться в программе, а не откуда-то считываться;
* У объекта должны быть изменяемые параметры (см. ЛР #2);
* Ориентация объекта хранится с помощью матрицы. Объект можно вращать в 3 или хотя бы 2 степенях свободы;
* Параметры, которые нельзя использовать для настройки текущей (выбранной) фигуры, должны быть скрыты или отключены;
* Программа не должна лагать, у неё не должна течь память.

#### Требования к освещению
* Освещение «наклеено» на фигуру, т.е. остается неизменным при вращении «камеры» (но меняется при движении источника/наблюдателя);
* Положение источника света и наблюдателя должны быть как-то обозначены в пространстве (напр., небольшими кружками);
* Все важные параметры освещения должны быть изменяемы. Под важными параметрами понимаются:
  * Цвет каждой из трёх компонент освещения (фоновой, рассеянной и бликовой);
  * Параметры модели освещения (напр., коэффициент гладкости фигуры в модели Кука-Торренса);
  * Положение источника и наблюдателя.


#### Варианты
Первые две фигуры у всех одинаковы:

1. Сфера;
2. Тор.

Третья фигура -- своя для каждого варианта:

|Вариант|Фигура                            |
|-------|----------------------------------|
|1      |шаровой сектор, «арбуз без дольки»|
|2      |пешка                             |
|3      |рулон туалетной бумаги            |
|4      |буква Х                           |
|5      |Круглая гантеля                   |
|6      |p-орбиталь, «песочные часы»       |
|7      |буква П                           |
|8      |пальчиковая батарейка             |
|9      |меч                               |
|10     |цилиндрическая гантеля            |
|11     |буква Y                           |
|12     |мензурка                          |
|13     |линза без сектора                 |
|14     |батарейка 4.5 В  (прямоугольная)  |
|15     |рюмка                             |
|16     |цилиндр без сектора               |
|17     |болт                              |
|18     |гайка                             |
|19     |таблетка (ломающаяся на 2 части)  |
|20     |сектор бочки,  «кусок сыра»       |
|21     |шляпа (цилиндр)                   |
|22     |катушка для ниток                 |
|23     |корона                            |
|24     |канцелярская кнопка               |
|25     |скалка                            |
|26     |тостер                            |
|27     |молоток                           |
|28     |воронка                           |
|29     |табуретка                         |
|30     |буква T                           |

### Комментарии
Первое требование к освещению можно выполнить, если применять к положению наблюдателя и источника ту же трансформацию, что и к фигуре.
