# SmartCalc v1.0

## Introduction

В данном проекте реализована расширенная версия обычного калькулятора на польской нотации. Помимо базовых арифметических операций, как плюс-минус и умножить-поделить, реализована возможность вычисления арифметических выражений с учетом приоритетов, а так же некоторыми математическими функциями (синус, косинус, логарифм и т.д.). Помимо вычисления выражений калькулятор поддерживает использование переменной _x_ и построение графика соответствующей функции. В качестве дополнительных улучшений предусмотрен кредитный калькулятор.
<br/><br/>
### Паттерн MVC

![Pattern MVC](./images/MVC-Process.png)

Паттерн MVC (Model-View-Controller, Модель-Представление-Контроллер) представляет из себя схему разделения модулей приложения на три отдельных макрокомпонента: модель, содержащую в себе бизнес-логику, представление - форму пользовательского интерфейса для осуществления взаимодействия с программой и контроллер, осуществляющий модификацию модели по действию пользователя.

Модель хранит и осуществляет доступ к основным данным, производит по запросам операции, определенные бизнес-логикой программы, то есть отвечает за ту часть программы, которая отвечает за все алгоритмы и процессы обработки информации. Данные модели, изменяясь под действием контроллера, влияют на отображение информации на представлении пользовательского интерфейса. В качестве модели в данной программе должна выступить библиотека классов, осуществляющая вычисления калькулятора. Эта библиотека должна предоставлять все необходимые классы и методы для осуществления подсчетов. Это и есть бизнес-логика данной программы, так как предоставляет средства для решения задачи. 

Контроллер - тонкий макрокомпонент, который осуществляет модификацию модели. Через него формируются запросы на изменение модели. В коде это выглядит как некий "фасад" для модели, то есть набор методов, которые уже работают напрямую с моделью. Тонким он называется потому, что идеальный контроллер не содержит в себе никакой дополнительной логики, кроме вызова одного или нескольких методов модели. Контроллер выполняет функцию связующего элемента между интерфейсом и моделью. Это позволяет полностью инкапсулировать модель от отображения. Такое разделение полезно в силу того, что позволяет коду представления ничего не знать о коде модели и обращаться к одному лишь контроллеру, интерфейс предоставляемых функций которого, вероятно, не будет значительно меняться. Модель же может претерпевать значительные изменения, и, при "переезде" на другие алгоритмы, технологии или даже языки программирования в модели, потребуется поменять лишь небольшой участок кода в контроллере, непосредственно связанный с моделью. В противном случае, вероятнее всего, пришлось бы переписывать значительную часть кода интерфейса, так как он сильно зависел бы от реализации модели. Таким обазом, взаимодействуя с интерфейсом, пользователь вызывает методы контроллера, которые модифицируют модель.

К представлению относится весь код, связанный с интерфейсом программы. В коде идеального интерфейса не должно быть никакой бизнес-логики. Он только представляет форму для взаимодействия с пользователем.
<br/><br/>

#### Программа тестировалась на Mac OS
#### Графическая библиотека (фреймворк) - qt_6 на языке С++
#### Логика польской нотации написана на языке С++<br/><br/>
#### Для быстрой сборки проекта достаточно использовать команду:
`make install`

### Алгоритм вычисления выражения основан на обратной польской нотации.

#### Реализация алгоритма

Пока в исходной строке есть необработанные лексемы, считываем очередную:

Если лексема:
- Число - добавляем в строку вывода.
- Функция или открывающая скобка - помещаем в стек.
- Разделитель аргументов функции (например, запятая):         
    - Перекладываем операторы из стека в выходную очередь пока лексемой на вершине стека не станет открывающая скобка. Если в стеке не окажется открывающей скобки - в выражении допущена ошибка.
- Оператор (O1):
    - Пока присутствует на вершине стека лексема-оператор (O2) чей приоритет выше приоритета O1, либо при равенстве приоритетов O1 является левоассоциативным:
        - Перекладываем O2 из стека в выходную очередь.
    - Помещаем O1 в стек.
- Закрывающая скобка:
    - Пока лексема на вершине стека не станет открывающей скобкой, перекладываем лексемы-операторы из стека в выходную очередь.
    - Удаляем из стека открывающую скобку.
    - Если лексема на вершине стека — функция, перекладываем её в выходную очередь.
    - Если стек закончился до того, как была встречена открывающая скобка - в выражении содержится ошибка.

Если во входной строке больше не осталось лексем:
- Пока есть операторы в стеке:
    - Если на вершине стека скобка - в выражении допущена ошибка.
    - Перекладываем оператор из стека в выходную очередь.

Конец.

- **Арифметические операторы**:

    | Название оператора | Инфиксная нотация <br /> (Классическая) | Префиксная нотация <br /> (Польская нотация) |  Постфиксная нотация <br /> (Обратная польская нотация) |
    | ------ | ------ | ------ | ------ |
    | Скобки | (a + b) | (+ a b) | a b + |
    | Сложение | a + b | + a b | a b + |
    | Вычитание | a - b | - a b | a b - |
    | Умножение | a * b | * a b | a b * |
    | Деление | a / b | / a b | a b \ |
    | Возведение в степень | a ^ b | ^ a b | a b ^ |
    | Остаток от деления | a mod b | mod a b | a b mod |
    | Унарный плюс | +a | +a | a+ |
    | Унарный минус | -a | -a | a- |

- **Функции**:

    | Описание функции | Функция |   
    | ---------------- | ------- |  
    | Вычисляет косинус | cos(x) |   
    | Вычисляет синус | sin(x) |  
    | Вычисляет тангенс | tan(x) |  
    | Вычисляет арккосинус | acos(x) | 
    | Вычисляет арксинус | asin(x) | 
    | Вычисляет арктангенс | atan(x) |
    | Вычисляет квадратный корень | sqrt(x) |
    | Вычисляет натуральный логарифм | ln(x) | 
    | Вычисляет десятичный логарифм | log(x) |


#### Дополнительно реализован Кредитный калькулятор.
<br/><br/>

<details>
    <summary>Не много скриншотов SmartCalc</summary>
<br/>

- ![](./ScreenShot_SmartCalc/Screenshot%20from%202023-05-03%2002-18-33.png)
<br/><br/><br/>

- ![](./ScreenShot_SmartCalc/Screenshot%20from%202023-05-03%2002-19-19.png)
<br/><br/><br/>

- ![](./ScreenShot_SmartCalc/Screenshot%20from%202023-05-03%2002-20-17.png)
<br/><br/><br/>

- ![](./ScreenShot_SmartCalc/Screenshot%20from%202023-05-03%2002-20-38.png)
</details>
