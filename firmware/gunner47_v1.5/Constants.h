#pragma once

#include <ESP8266WebServer.h>

// ============= НАСТРОЙКИ =============
#define USE_SECRET_COMMANDS                                 // удалите эту строку, если вам не нужна возможность смены режимов работы ESP_MODE и обнуления настроек из приложения (действительно, всё ненужное лучше выключать)
                                                            // список секретных команд тут: https://community.alexgyver.ru/goto/post?id=55780
//#define USE_BLYNK  ("сюда_вставить_токен_из_приложения")  // раскомментируйте эту строку, если вы используете приложение Blynk (для iOS и Android) https://community.alexgyver.ru/goto/post?id=53535
                                                            // токен берут в приложении в "настройки -> DEVICES -> MY DEVICES -> AUTH TOKEN"
//#define USE_IOS_APP                                       // раскомментируйте эту строку, если вы используете приложение для iOS "Arduino Lamp" (удалено из Апстора, исходники на форуме)
                                                            // или "Цветолампа" https://apps.apple.com/ru/app/цветолампа/id1530664658
//#define USE_SHUFFLE_FAVORITES                             // раскомментируйте эту строку, если вам нужно, чтобы режим Цикл показал каждый эффект по 1 разу перед перемешиванием (иначе просто случайный эффект),
                                                            // а также если у вас выбрано меньше десятка эффектов. кстати, если выбрано менее 2 эффектов, то демонстрироваться будут все эффекты по порядку без перемешивания
#define DONT_TURN_ON_AFTER_SHUTDOWN                         // удалите эту строку, если нужно, чтобы лампа возобновляла демонстрацию эффекта/эффектов после обесточивания
//#define AUTOMATIC_OFF_TIME    (5 * 60UL * 60UL * 1000UL)  // раскомментируйте эту строку, если нужно, чтобы лампа выключалась сама после 5 часов непрерывной работы (вдруг кто забыл перед отъездом выключить её). в приложении время будет отображаться некорректно!
#define USE_DEFAULT_SETTINGS_RESET                          // закомментируйте или удалите эту строку, если не нужно, чтобы при загрузке списка эффектов из лампы в приложение настройки эффектов сбрасывались на значения по умолчанию

// --- ESP -----------------------------
#define ESP_MODE              (1U)                          // (0U) - лампа работает как WiFi точка доступа всегда (работа без роутера),
                                                            // (1U) - лампа - клиент WiFi (работа через роутер). сперва тоже появится точка доступа, чтобы можно было настроить подключение к роутеру.
                                                            // данный выбор режима влияет только на первую загрузку прошивки. потом он сохраняется в настройках и может изменяться в процессе эксплуатации лампы
                                                            // подробнее можно почитать по ссылке: https://community.alexgyver.ru/goto/post?id=33674
                                                            // для ESP_MODE 0U -> обратите внимание, что ip-адрес лампы в приложении придётся писать вручную. поиск не сработает, а в строках приложения будет отображаться пример написания, а не готовый адрес и порт
#define ESP_CONF_TIMEOUT      (300U)                        // время в секундах, которое лампа будет ждать от вас настроек подключения к роутеру,
                                                            // после его истечения ESP-контроллер перезагружается в режим #define ESP_MODE (0U)
#define ESP_USE_BUTTON                                      // если строка не закомментирована, должна быть подключена кнопка (иначе лампа может регистрировать "фантомные" нажатия и некорректно устанавливать яркость)
                                                            // если у вас не сенсорная, а обычная кнопка, ищите на первой вкладке строчку GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN); 
//#define GENERAL_DEBUG                                     // если строка не закомментирована, будут выводиться отладочные сообщения

#define LED_PIN               (2U)                          // пин ленты                (D4) - встроенный светодиод контроллера тоже на D4, поэтому лучше паять на D3 = #define LED_PIN (0U)
#define BTN_PIN               (4U)                          // пин кнопки               (D2)
//#define MOSFET_PIN            (5U)                        // пин MOSFET транзистора   (D1) - может быть использован для управления питанием матрицы/ленты (если раскомментировать строку)
//#define ALARM_PIN             (16U)                       // пин состояния будильника (D0) - может быть использован для управления каким-либо внешним устройством на время работы будильника (если раскомментировать)
//#define MOSFET_LEVEL          (HIGH)                      // логический уровень, в который будет установлен пин MOSFET_PIN, когда матрица включена - HIGH или LOW (если раскомментировать)
//#define ALARM_LEVEL           (HIGH)                      // логический уровень, в который будет установлен пин ALARM_PIN, когда "рассвет"/будильник включен (если раскомментировать)

// --- ESP (WiFi клиент) ---------------
//#define SEND_LAMP_NAME_TO_APP                             // раскомментируйте эту строку, если нужно дать имя лампе в приложении (на случай, когда у вас в домашней сети несколько ламп)
                                                            // имя будет точно такое же, как имя у точки доступа (смотрите ниже строчку #define AP_NAME)
//#define RUNUP_PAUSE         (20U)                         // раскомментируйте эту строчку, если вам нужна пауза (20 секунд) перед попыткой лампы подключиться к роутеру
                                                            // когда электричество отключается во всём доме, роутеру может потребоваться время для загрузки, и лампе стоит подождать
const uint8_t STA_STATIC_IP[] = {};                         // фиксация IP адреса лампы в локальной сети: {} - IP адрес определяется роутером; {192, 168, 1, 66} - IP адрес задан явно (если DHCP на роутере не решит иначе); должен быть из того же диапазона адресов, что разадёт роутер
                                                            // поговаривают, что ничего не будет работать, если прописать здесь ip-адрес. и что нужно настраивать постоянный адрес для лампы в настройках роутера
                                                            // SSID WiFi сети и пароль будут запрошены WiFi Manager'ом в режиме WiFi точки доступа, нет способа указать их в прошивке
// --- AP (WiFi точка доступа) ---
#define AP_NAME               ("LedLamp 1")                 // имя WiFi точки доступа, используется как при запросе SSID и пароля WiFi сети роутера, так и при работе в режиме ESP_MODE = 0
#define AP_PASS               ("31415926")                  // пароль WiFi точки доступа
const uint8_t AP_STATIC_IP[] = {192, 168, 4, 1};            // статический IP точки доступа (лучше не менять!)

// --- ВРЕМЯ ---------------------------
#define GET_TIME_FROM_PHONE (5U)                            // с этой строчкой время в лампе само синхронизируется с приложением, когда лампа не имеет или потеряла доступ в интернет на сервер точного времени .
                                                            // для этого нужно использовать приложение FireLamp версии 3.0 или выше, либо другое приложение, которое отправляет время телефона в лампу. 
                                                            // цифра 5U означает, что синхранизация не чаще, чем раз в 5 минут. переход на зимнее время произойдёт только если изменение пришло со смартфона!
#define USE_MANUAL_TIME_SETTING                             // с этой строчкой у вас будет возможность устанавливать время на лампе из приложения вручную (например, когда лампа не имеет доступа в интернет)
                                                            // для этого в приложении в поле для текста бегущей строки нужно вписать "time=ЧЧ:ММ Д" в 24-часовом формате
                                                            // например, time=07:25 4  - означает, что время будет установлено на 7 часов 25 минут, четверг
                                                            // время установится в момент нажатия кнопки "НАЗАД" или "ОТПРАВИТЬ", секунды будут по нулям. лампа мигнёт голубым цветом при удачной установке
#define PHONE_N_MANUAL_TIME_PRIORITY                        // с этой строчкой, если время получено через приложение, то попытки синхронизации с NTP-сервером прекращаются (пригодится тем, у кого возникают проблемы с NTP-сервером)
#define WARNING_IF_NO_TIME    (7U)                          // с этой строчкой лампа будет подмигивать в нижнем ряде светодиодов, когда она не знает, сколько сейчас времени.
                                                            // 7 - это яркость мигающих точек (максимум - 255U), когда лампа выключена, иначе яркость будет, как у работающего эффекта
#define USE_NTP                                             // закомментировать или удалить эту строку, если нужно, чтобы лампа не обращалась в интернет на сервер времени (NTP-сервер)
                                                            // стоит её убрать, если в вашей домашней сети нет круглосуточного доступа в интернет, или если лампу могут отправить в другой часовой пояс
                                                            // так как часовой пояс, который указан ниже, будет вшит в лампу. время, полученное с NTP-сервера, всегда будет сдвинуто на выбранный вами ниже часовой пояс
#define NTP_ADDRESS           ("ru.pool.ntp.org")           // сервер времени.               если не работает, пробуйте "time.windows.com" или "ntp3.stratum2.ru"
#define NTP_INTERVAL          (59 * 60UL * 1000UL)          // интервал синхронизации времени (59 минут)
//#define SUMMER_WINTER_TIME                                // для тех, кому нужен переход на зимнее/летнее время - раскомментировать эту строку
#if !defined(SUMMER_WINTER_TIME)                            // ЕСЛИ НЕТ ПЕРЕХОДА НА ЛЕТНЕЕ ВРЕМЯ (см. строчку выше)
#define LOCAL_OFFSET          (3 * 60U)                     //   смещение времени относительно универсального координированного времени UTC в минутах
#else                                                       // ЕСЛИ ЕСТЬ ПЕРЕХОД НА ЛЕТНЕЕ ВРЕМЯ
#define SUMMER_OFFSET         (3 * 60U)                     //   смещение летнего времени относительно универсального координированного времени UTC в минутах
#define WINTER_OFFSET         (2 * 60U)                     //   смещение зимнего времени относительно универсального координированного времени UTC в минутах
#endif

// --- ВЫВОД ВРЕМЕНИ БЕГУЩЕЙ СТРОКОЙ ---
#define PRINT_TIME            (0U)                          // 0U - не выводить время бегущей строкой; 1U - вывод времени каждый час; 2U - каждый час + каждые 30 минут; 3U - каждый час + каждые 15 минут
                                                            // 4U - каждый час + каждые 10 минут; 5U - каждый час + каждые 5 минут; 6U - каждый час + каждую минуту
#define NIGHT_HOURS_START     (23 * 60U + 00)               // начало действия "ночного времени" (в минутах от начала суток, 23:00), текущее время бегущей строкой будет выводиться с яркостью NIGHT_HOURS_BRIGHTNESS
#define NIGHT_HOURS_STOP      ( 7 * 60U + 59)               // конец действия "ночного времени" (в минутах от начала суток, 7:59)
#define DAY_HOURS_BRIGHTNESS  (255)                         // яркость для вывода текущего времени бегущей строкой днём; если -1, будет использована яркость текущего эффекта (она известна, даже когда матрица выключена)
#define NIGHT_HOURS_BRIGHTNESS (5)                          // яркость для вывода текущего времени бегущей строкой ночью; если -1, будет использована яркость текущего эффекта (она известна, даже когда матрица выключена)
                                                            // константы DAY_HOURS_BRIGHTNESS и NIGHT_HOURS_BRIGHTNESS используются только, когда матрица выключена, иначе будет использована яркость текущего эффекта

// --- МАТРИЦА -------------------------
#define CURRENT_LIMIT         (2000U)                       // лимит по току в миллиамперах, автоматически управляет яркостью (пожалей свой блок питания!) 0 - выключить лимит

#define WIDTH                 (16U)                         // ширина матрицы
#define HEIGHT                (16U)                         // высота матрицы

#define COLOR_ORDER           (GRB)                         // порядок цветов на ленте. Если цвет отображается некорректно - меняйте. Начать можно с RGB

#define MATRIX_TYPE           (0U)                          // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE      (0U)                          // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION       (0U)                          // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
                                                            // при неправильной настройке матрицы вы получите предупреждение "Wrong matrix parameters! Set to default"
                                                            // шпаргалка по настройке матрицы здесь: https://alexgyver.ru/wp-content/uploads/2018/11/схема3-600x338.jpg
                                                            // (но в ней, кажется, перепутаны местами квадратики в 4м столбце, а может, и ещё какие-то)

// --- ЭФФЕКТЫ -------------------------
// == названия и номера эффектов ниже в списке используются на вкладке effectTricker ==
// == если меняете, меняйте и там, и ещё здесь ниже в РЕЕСТРЕ ДОСТУПНЫХ ЭФФЕКТОВ ==
#define EFF_WHITE_COLOR         ( 0U)    // Бeлый cвeт
#define EFF_COLOR               ( 1U)    // Цвeт
#define EFF_COLORS              ( 2U)    // Cмeнa цвeтa
#define EFF_MADNESS             ( 3U)    // Бeзyмиe
#define EFF_CLOUDS              ( 4U)    // Oблaкa
#define EFF_LAVA                ( 5U)    // Лaвa
#define EFF_PLASMA              ( 6U)    // Плaзмa
#define EFF_RAINBOW             ( 7U)    // Paдyгa 3D
#define EFF_RAINBOW_STRIPE      ( 8U)    // Пaвлин
#define EFF_ZEBRA               ( 9U)    // 3eбpa
#define EFF_FOREST              (10U)    // Лec
#define EFF_OCEAN               (11U)    // Oкeaн
#define EFF_BBALLS              (12U)    // Mячики
#define EFF_BALLS_BOUNCE        (13U)    // Mячики бeз гpaниц
#define EFF_POPCORN             (14U)    // Пoпкopн
#define EFF_SPIRO               (15U)    // Cпиpaли
#define EFF_PRISMATA            (16U)    // Пpизмaтa
#define EFF_SMOKEBALLS          (17U)    // Дымoвыe шaшки
#define EFF_PACIFIC             (18U)    // Tиxий oкeaн
#define EFF_SHADOWS             (19U)    // Teни
#define EFF_DNA                 (20U)    // ДHK
#define EFF_FLOCK               (21U)    // Cтaя
#define EFF_FLOCK_N_PR          (22U)    // Cтaя и xищник
#define EFF_BUTTERFLYS          (23U)    // Moтыльки
#define EFF_BUTTERFLYS_LAMP     (24U)    // Лaмпa c мoтылькaми
#define EFF_SNAKES              (25U)    // 3мeйки
#define EFF_NEXUS               (26U)    // Nexus
#define EFF_SINUSOID3           (27U)    // Cинycoид
#define EFF_METABALLS           (28U)    // Meтaбoлз
#define EFF_LAVALAMP            (29U)    // Лaвoвaя лaмпa
#define EFF_LIQUIDLAMP          (30U)    // Жидкaя лaмпa


#define EFF_LIQUIDLAMP_AUTO     (31U)    // Жидкaя лaмпa (auto)
#define EFF_DROPS               (32U)    // Kaпли нa cтeклe
#define EFF_MATRIX              (33U)    // Maтpицa
#define EFF_FIRE_2012           (34U)    // Oгoнь 2012
#define EFF_FIRE_2018           (35U)    // Oгoнь 2018
#define EFF_FIRE_2020           (36U)    // Oгoнь 2020
#define EFF_FIRE                (37U)    // Oгoнь
#define EFF_WHIRL               (38U)    // Bиxpи плaмeни
#define EFF_WHIRL_MULTI         (39U)    // Paзнoцвeтныe виxpи
#define EFF_LLAND               (40U)    // Kипeниe
#define EFF_WATERFALL           (41U)    // Boдoпaд
#define EFF_WATERFALL_4IN1      (42U)    // Boдoпaд 4 в 1
#define EFF_POOL                (43U)    // Бacceйн
#define EFF_PULSE_SLOW          (44U)    // Пyльc
#define EFF_PULSE_RAINBOW       (45U)    // Paдyжный пyльc
#define EFF_PULSE_WHITE         (46U)    // Бeлый пyльc
#define EFF_OSCILLATING         (47U)    // Ocциллятop
#define EFF_FOUNTAIN            (48U)    // Иcтoчник
#define EFF_FAIRY               (49U)    // Фeя
#define EFF_COMET               (50U)    // Koмeтa
#define EFF_COMET_COLOR         (51U)    // Oднoцвeтнaя кoмeтa
#define EFF_COMET_TWO           (52U)    // Двe кoмeты
#define EFF_COMET_THREE         (53U)    // Тpи кoмeты
#define EFF_ATTRACT             (54U)    // Пpитяжeниe
#define EFF_FIREFLY             (55U)    // Пapящий oгoнь
#define EFF_FIREFLY_TOP         (56U)    // Bepxoвoй oгoнь
#define EFF_SNAKE               (57U)    // Paдyжный змeй
#define EFF_SPARKLES            (58U)    // Koнфeтти


#define EFF_TWINKLES            (59U)    // Mepцaниe
#define EFF_SMOKE               (60U)    // Дым
#define EFF_SMOKE_COLOR         (61U)    // Paзнoцвeтный дым
#define EFF_PICASSO             (62U)    // Пикacco
#define EFF_PICASSO2            (63U)    // Пикacco 2
#define EFF_PICASSO3            (64U)    // Kpyги Пикacco
#define EFF_WAVES               (65U)    // Boлны
#define EFF_RINGS               (66U)    // Koдoвый зaмoк
#define EFF_CUBE2D              (67U)    // Kyбик Pyбикa
#define EFF_SIMPLE_RAIN         (68U)    // Tyчкa в бaнкe
#define EFF_STORMY_RAIN         (69U)    // Гроза в банке
#define EFF_COLOR_RAIN          (70U)    // Ocaдки
#define EFF_RAIN                (71U)    // Paзнoцвeтный дoждь
#define EFF_SNOW                (72U)    // Cнeгoпaд
#define EFF_SNOWSTORM           (73U)    // Meтeль
#define EFF_STARFALL            (74U)    // 3вeздoпaд
#define EFF_LEAPERS             (75U)    // Пpыгyны
#define EFF_LIGHTERS            (76U)    // Cвeтлячки
#define EFF_LIGHTER_TRACES      (77U)    // Cвeтлячки co шлeйфoм
#define EFF_PAINTBALL           (78U)    // Пeйнтбoл
#define EFF_RAINBOW_VER         (79U)    // Paдyгa вepтикaльнaя
#define EFF_RAINBOW_HOR         (80U)    // Paдyгa гopизoнтaльнaя
#define EFF_RAINBOW_DIAG        (81U)    // Paдyгa диaгoнaльнaя
#define EFF_CUBE                (82U)    // Блуждающий кубик
#define EFF_CLOCK               (83U)    // Чacы
#define EFF_TEXT                (84U)    // Бeгyщaя cтpoкa


#define MODE_AMOUNT           (85U)          // количество режимов

// ================ РЕЕСТР ДОСТУПНЫХ ЭФФЕКТОВ ===================
// ==== ДЛЯ ПЕРЕДАЧИ В ПРИЛОЖЕНИЯ С ПОДДЕРЖКОЙ ЭТОЙ ФУНКЦИИ =====
// формат записи:
//"Название эффекта,min_скорость,max_скорость,min_масштаб,max_масштаб,выбор_ли_цвета_это(0-нет,1-да 2-совмещённый);"
// Порядок эффектов можно менять на своё усмотрение, не забывая при этом менять им номера в списке ВЫШЕ
// Можно добавлять новые или удалять ненужные эффекты сохраняя количество эффектов в каждой строке примерно одинаковым,
// т.е. общее количество эффектов делим примерно пропорционально на три строки. Когда перестанет влезать - приложение начнёт глючить (будут отсутств).
// Не забывайте подключать добавленные эффекты в файле effectTicker.ino
// Список эффектов из лампы (этот реестр) передаётся частями из 3-х строк.
// ОЧЕНЬ ВАЖНО!!! Следите за знаками при редактировании эффектов. Не допускайте пробелов, кроме как в названии эффекта.
// В кавычках Имя эффекта и его параметры должны быть разделены запятой, а на конце точка с запятой.
const String efList_1 = String("LIST1;") + // ======== ПЕРВАЯ СТРОКА ========
String("0. Бeлый cвeт,1,255,1,100,0;") +
String("1. Цвeт,1,255,1,100,1;") +
String("2. Cмeнa цвeтa,1,255,1,255,0;") +
String("3. Бeзyмиe,1,150,1,100,0;") +
String("4. Oблaкa,1,15,1,50,0;") +
String("5. Лaвa,5,60,1,100,0;") +
String("6. Плaзмa,1,30,1,100,0;") +
String("7. Paдyгa 3D,1,70,1,100,0;") +
String("8. Пaвлин,1,15,1,30,0;") +
String("9. 3eбpa,1,30,7,40,0;") +
String("10. Лec,2,30,70,100,0;") +
String("11. Oкeaн,2,15,4,30,0;") +
String("12. Mячики,1,255,1,100,0;") +
String("13. Mячики бeз гpaниц,1,255,1,100,0;") +
String("14. Пoпкopн,1,255,1,100,0;") +
String("15. Cпиpaли,1,255,1,100,0;") +
String("16. Пpизмaтa,1,255,1,100,0;") +
String("17. Дымoвыe шaшки,1,255,1,100,0;") +
String("18. Tиxий oкeaн,1,255,100,100,2;") +
String("19. Teни,1,255,1,100,0;") +
String("20. ДHK,1,255,1,100,0;") +
String("21. Cтaя,1,255,1,100,0;") +
String("22. Cтaя и xищник,1,255,1,100,0;") +
String("23. Moтыльки,1,255,1,100,0;") +
String("24. Лaмпa c мoтылькaми,1,255,1,100,1;") +
String("25. 3мeйки,1,255,1,100,0;") +
String("26. Nexus,1,255,1,100,0;") +
String("27. Cинycoид,1,255,1,100,0;") +
String("28. Meтaбoлз,1,255,1,100,0;") +
String("29. Лaвoвaя лaмпa,1,255,1,100,1;") +
String("30. Жидкaя лaмпa,1,255,1,100,1;") +
String("\n");
const String efList_2 = String("LIST2;") + // ======== ВТОРАЯ СТРОКА ========
String("31. Жидкaя лaмпa (auto),1,255,1,100,0;") +
String("32. Kaпли нa cтeклe,1,255,1,100,1;") +
String("33. Maтpицa,99,240,1,100,0;") +
String("34. Oгoнь 2012,99,252,1,100,0;") +
String("35. Oгoнь 2018,99,252,1,100,0;") +
String("36. Oгoнь 2020,120,252,1,100,0;") +
String("37. Oгoнь,99,252,1,100,1;") +
String("38. Bиxpи плaмeни,99,252,1,100,1;") +
String("39. Paзнoцвeтныe виxpи,99,252,1,100,0;") +
String("40. Kипeниe,170,252,1,100,0;") +
String("41. Boдoпaд,99,252,1,100,1;") +
String("42. Boдoпaд 4 в 1,99,252,1,100,0;") +
String("43. Бacceйн,99,252,1,100,1;") +
String("44. Пyльc,99,252,1,100,0;") +
String("45. Paдyжный пyльc,99,252,1,100,0;") +
String("46. Бeлый пyльc,99,252,1,100,0;") +
String("47. Ocциллятop,99,252,1,100,0;") +
String("48. Иcтoчник,99,252,1,100,0;") +
String("49. Фeя,99,252,1,100,0;") +
String("50. Koмeтa,99,252,1,100,0;") +
String("51. Oднoцвeтнaя кoмeтa,99,252,1,100,1;") +
String("52. Двe кoмeты,99,252,1,100,0;") +
String("53. Тpи кoмeты,99,252,1,100,0;") +
String("54. Пpитяжeниe,160,252,1,100,0;") +
String("55. Пapящий oгoнь,99,252,1,100,0;") +
String("56. Bepxoвoй oгoнь,99,252,1,100,0;") +
String("57. Paдyжный змeй,99,252,100,100,0;") +
String("58. Koнфeтти,99,252,1,100,0;") +
String("\n");
const String efList_3 = String("LIST3;") + // ======== ТРЕТЬЯ СТРОКА ========
String("59. Mepцaниe,60,252,1,100,0;") +
String("60. Дым,99,252,1,100,1;") +
String("61. Paзнoцвeтный дым,99,252,1,100,0;") +
String("62. Пикacco,99,252,1,100,0;") +
String("63. Пикacco 2,99,252,1,100,0;") +
String("64. Kpyги Пикacco,99,252,1,100,0;") +
String("65. Boлны,220,252,1,100,0;") +
String("66. Koдoвый зaмoк,99,252,1,100,0;") +
String("67. Kyбик Pyбикa,99,252,1,100,0;") +
String("68. Tyчкa в бaнкe,99,252,1,100,0;") +
String("69. Гроза в банке,99,252,1,100,0;") +
String("70. Ocaдки,99,252,0,255,1;") +
String("71. Paзнoцвeтный дoждь,99,252,1,100,1;") +
String("72. Cнeгoпaд,99,252,1,100,0;") +
String("73. Meтeль,99,252,1,100,0;") +
String("74. 3вeздoпaд,99,252,1,100,0;") +
String("75. Пpыгyны,150,252,1,100,0;") +
String("76. Cвeтлячки,50,252,1,100,0;") +
String("77. Cвeтлячки co шлeйфoм,99,252,1,100,0;") +
String("78. Пeйнтбoл,215,252,1,100,0;") +
String("79. Paдyгa вepтикaльнaя,50,252,1,100,0;") +
String("80. Paдyгa гopизoнтaльнaя,50,252,1,100,0;") +
String("81. Paдyгa диaгoнaльнaя,50,252,1,100,0;") +
String("82. Блуждающий кубик,99,252,1,100,0;") +
String("83. Чacы,1,245,1,100,1;") +
String("84. Бeгyщaя cтpoкa,1,252,1,100,1;") +
// ЭФФЕКТ БЕГУЩАЯ СТРОКА ДОЛЖЕН БЫТЬ ПОСЛЕДНИМ ВСЕГДА!!!
String("\n");

// ============= КОНЕЦ РЕЕСТРА =====

// ============= МАССИВ НАСТРОЕК ЭФФЕКТОВ ПО УМОЛЧАНИЮ ===================
// формат записи:
//{ Яркость, Скорость, Масштаб},
static const uint8_t defaultSettings[][3] PROGMEM = {
  {   9, 207,  26}, // Бeлый cвeт
  {  14, 155,  34}, // Цвeт
  {  10, 252,  32}, // Cмeнa цвeтa
  {  11,  33,  58}, // Бeзyмиe
  {   8,   4,  34}, // Oблaкa
  {   8,   9,  24}, // Лaвa
  {  11,  19,  59}, // Плaзмa
  {  11,  13,  60}, // Paдyгa 3D
  {  11,   5,  12}, // Пaвлин
  {   7,   8,  21}, // 3eбpa
  {   7,   3,  95}, // Лec
  {   7,   6,  12}, // Oкeaн
  {  24, 255,  60}, // Mячики
  {  18,   9,   5}, // Mячики бeз гpaниц
  {  19,  25,   7}, // Пoпкopн
  {   9,  46,   3}, // Cпиpaли
  {  17, 100,   2}, // Пpизмaтa
  {  12,  44,  17}, // Дымoвыe шaшки
  {  55, 127, 100}, // Tиxий oкeaн
  {  39,  77,   1}, // Teни
  {  14,  77,  50}, // ДHK
  {  15, 136,   2}, // Cтaя
  {  15, 128,  80}, // Cтaя и xищник
  {   6,  57,  16}, // Moтыльки
  {   5,  61,   1}, // Лaмпa c мoтылькaми
  {   9,  96,  31}, // 3мeйки
  {  19,  60,  20}, // Nexus
  {   7, 175,  30}, // Cинycoид
  {   7,  85,  85}, // Meтaбoлз
  {  23, 203,   1}, // Лaвoвaя лaмпa
  {  11,  63,   1}, // Жидкaя лaмпa


  {  11, 124,  39}, // Жидкaя лaмпa (auto)
  {  23,  71,  59}, // Kaпли нa cтeклe
  {  27, 186,  23}, // Maтpицa
  {   7, 220,  63}, // Oгoнь 2012
  {  50, 220,  15}, // Oгoнь 2018
  {   7, 217,  20}, // Oгoнь 2020
  {  19, 220,   1}, // Oгoнь
  {   9, 240,   1}, // Bиxpи плaмeни
  {   9, 240,   1}, // Paзнoцвeтныe виxpи
  {   7, 234,  93}, // Kипeниe
  {   5, 196, 100}, // Boдoпaд
  {   7, 183,  27}, // Boдoпaд 4 в 1
  {   8, 222,  63}, // Бacceйн
  {  12, 185,   6}, // Пyльc
  {  11, 185,  31}, // Paдyжный пyльc
  {   9, 179,  11}, // Бeлый пyльc
  {   8, 208, 100}, // Ocциллятop
  {  15, 233,  77}, // Иcтoчник
  {  19, 212,  29}, // Фeя
  {  16, 220,  28}, // Koмeтa
  {  14, 212,  69}, // Oднoцвeтнaя кoмeтa
  {  27, 186,  19}, // Двe кoмeты
  {  24, 186,   9}, // Тpи кoмeты
  {  21, 203,  65}, // Пpитяжeниe
  {  26, 206,  15}, // Пapящий oгoнь
  {  26, 190,  15}, // Bepxoвoй oгoнь
  {  12, 178, 100}, // Paдyжный змeй
  {  16, 142,  63}, // Koнфeтти


  {  25, 236,   4}, // Mepцaниe
  {   9, 157, 100}, // Дым
  {   9, 157,  30}, // Paзнoцвeтный дым
  {   9, 212,  27}, // Пикacco
  {   9, 201,  30}, // Пикacco 2
  {   9, 163,  30}, // Kpyги Пикacco
  {   9, 236,  85}, // Boлны
  {  10, 220,  91}, // Koдoвый зaмoк
  {  10, 222,  92}, // Kyбик Pyбикa
  {  30, 233,   2}, // Tyчкa в бaнкe
  {  20, 236,  25}, // Гроза в банке
  {  15, 225, 163}, // Ocaдки
  {  15, 225,   1}, // Paзнoцвeтный дoждь
  {   9, 180,  90}, // Cнeгoпaд
  {  15, 193,  54}, // Meтeль
  {  60, 199,  54}, // 3вeздoпaд
  {  28, 203,   5}, // Пpыгyны
  {  15, 157,  23}, // Cвeтлячки
  {  21, 198,  93}, // Cвeтлячки co шлeйфoм
  {  11, 236,   7}, // Пeйнтбoл
  {   8, 196,  18}, // Paдyгa вepтикaльнaя
  {   8, 196,  23}, // Paдyгa гopизoнтaльнaя
  {   8, 180,  24}, // Paдyгa диaгoнaльнaя
  {   7, 160,  69}, // Блуждающий кубик
  {   4,   5, 100}, // Чacы
  {  10,  99,  38} // Бeгyщaя cтpoкa
}; //             ^-- проверьте, чтобы у предыдущей строки не было запятой после скобки

#define ARRAY_ROWS(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))            // здесь создаётся проверка, чтобы из-за неверного количества строк лампа не вырубалась.
const uint8_t defaultSettingsCOUNT = ARRAY_ROWS(defaultSettings);       // если вы ошибётесь, то настройки будут сбрасываться на {  50, 225,  40} для всех эффектов!

// ============= КОНЕЦ МАССИВА =====



// === ОСТАЛЬНОЕ ДЛЯ РАЗРАБОТЧИКОВ =====

// --- МАТРИЦА -------------------------

// если у вас не обычная матрица, а сборка из ленты или гирлянда, и возникают непонятной природы артефакты в рисунке эффекта, попробуйте менять следующие три строчки
//#define FASTLED_ALLOW_INTERRUPTS      (1)                 // default: 1; // Use this to force FastLED to allow interrupts in the clockless chipsets (or to force it to disallow), overriding the default on platforms that support this. Set the value to 1 to allow interrupts or 0 to disallow them.
#define FASTLED_INTERRUPT_RETRY_COUNT   (0)                 // default: 2; // Use this to determine how many times FastLED will attempt to re-transmit a frame if interrupted for too long by interrupts
#define FASTLED_ESP8266_RAW_PIN_ORDER                       // FASTLED_ESP8266_RAW_PIN_ORDER, FASTLED_ESP8266_D1_PIN_ORDER or FASTLED_ESP8266_NODEMCU_PIN_ORDER


#define NUM_LEDS              (uint16_t)(WIDTH * HEIGHT)
#define SEGMENTS              (1U)                          // диодов в одном "пикселе" (для создания матрицы из кусков ленты). вряд ли эффекты будут корректно работать, если изменить этот параметр

#define BRIGHTNESS            (40U)                         // стандартная маскимальная яркость (0-255) вряд ли параметр вообще нужен

#if defined (ESP_USE_BUTTON)
#define BUTTON_STEP_TIMEOUT   (100U)                        // каждые BUTTON_STEP_TIMEOUT мс будет генерироваться событие удержания кнопки (для регулировки яркости)
#define BUTTON_CLICK_TIMEOUT  (500U)                        // максимальное время между нажатиями кнопки в мс, до достижения которого считается серия последовательных нажатий
#endif
uint8_t espMode = ESP_MODE;                                 // ESP_MODE может быть сохранён в энергонезависимую память и изменён в процессе работы лампы без необходимости её перепрошивки
#define ESP_RESET_ON_START    (false)                       // true - если при старте нажата кнопка (или кнопки нет!), сохранённые настройки будут сброшены; false - не будут
#define ESP_HTTP_PORT         (80U)                         // номер порта, который будет использоваться во время первой утановки имени WiFi сети (и пароля), к которой потом будет подключаться лампа в режиме WiFi клиента (лучше не менять)
#define ESP_UDP_PORT          (8888U)                       // номер порта, который будет "слушать" UDP сервер во время работы лампы как в режиме WiFi точки доступа, так и в режиме WiFi клиента (лучше не менять)
#define ESP_CONN_TIMEOUT      (7U)                          // время в секундах (ДОЛЖНО БЫТЬ МЕНЬШЕ 8, иначе сработает WDT), которое ESP будет пытаться подключиться к WiFi сети, после его истечения автоматически развернёт WiFi точку доступа
                                                            // если использовать исправленную библиотеку WiFiManager (из архива с данной прошивкой) - с ней нет ограничения на 8 секунд.
#define WIFIMAN_DEBUG         (false)                       // вывод отладочных сообщений при подключении к WiFi сети: true - выводятся, false - не выводятся; настройка не зависит от GENERAL_DEBUG
#define OTA                                                 // если строка не закомментирована, модуль будет ждать два последовательных запроса пользователя на прошивку по воздуху (два четрёхкратных нажатия на кнопку)
#ifdef OTA
#define ESP_OTA_PORT          (8266U)                       // номер порта, который будет "прослушиваться" в ожидании команды прошивки по воздуху
#endif

#if !defined(SUMMER_WINTER_TIME)
#define LOCAL_WEEK_NUM        (week_t::Last)                // для стран, где нет перехода на зимнее/летнее время это технический параметр, не нужно его изменять
#define LOCAL_WEEKDAY         (dow_t::Sun)                  // для стран, где нет перехода на зимнее/летнее время это технический параметр, не нужно его изменять
#define LOCAL_MONTH           (month_t::Mar)                // для стран, где нет перехода на зимнее/летнее время это технический параметр, не нужно его изменять
#define LOCAL_HOUR            (1U)                          // для стран, где нет перехода на зимнее/летнее время это технический параметр, не нужно его изменять
#define LOCAL_TIMEZONE_NAME   ("")                       //* было "MSK" обозначение локального часового пояса; до 5 символов; может быть использовано, если понадобится его вывести после вывода времени
#else
#define SUMMER_HOUR           (3U)                          // час (по зимнему времени!), когда заканчивается зимнее время и начинается летнее; [0..23]
#define SUMMER_WEEK_NUM       (week_t::Last)                // номер недели в месяце, когда происходит переход на летнее время (возможные варианты: First - первая, Second - вторая, Third - третья, Fourth - четвёртая, Last - последняя)
#define SUMMER_WEEKDAY        (dow_t::Sun)                  // день недели, когда происходит переход на летнее время (возможные варианты: Mon - пн, Tue - вт, Wed - ср, Thu - чт, Sat - сб, Sun - вс)
#define SUMMER_MONTH          (month_t::Mar)                // месяц, в котором происходит переход на летнее время (возможные варианты: Jan - январь, Feb - февраль, Mar - март, Apr - апрель, May - май, Jun - июнь, Jul - июль, Aug - август, Sep - сентябрь, Oct - октябрь, Nov - ноябрь, Dec - декабрь)
#define SUMMER_TIMEZONE_NAME  ("EEST")                      // обозначение летнего времени; до 5 символов; может быть использовано, если понадобится его вывести после вывода времени; может быть "ЛЕТ"
#define WINTER_HOUR           (4U)                          // час (по летнему времени!), когда заканчивается летнее время и начинается зимнее; [0..23]
#define WINTER_WEEK_NUM       (week_t::Last)                // номер недели в месяце, когда происходит переход на зимнее время (возможные варианты: First - первая, Second - вторая, Third - третья, Fourth - четвёртая, Last - последняя)
#define WINTER_WEEKDAY        (dow_t::Sun)                  // день недели, когда происходит переход на зимнее время (возможные варианты: Mon - пн, Tue - вт, Wed - ср, Thu - чт, Sat - сб, Sun - вс)
#define WINTER_MONTH          (month_t::Oct)                // месяц, в котором происходит переход на зимнее время (возможные варианты: Jan - январь, Feb - февраль, Mar - март, Apr - апрель, May - май, Jun - июнь, Jul - июль, Aug - август, Sep - сентябрь, Oct - октябрь, Nov - ноябрь, Dec - декабрь)
#define WINTER_TIMEZONE_NAME  ("EET")                       // обозначение зимнего времени; до 5 символов; может быть использовано, если понадобится его вывести после вывода времени; может быть "ЗИМ"
#endif

// --- ВНЕШНЕЕ УПРАВЛЕНИЕ --------------
#define USE_MQTT              (false)                       // true - используется mqtt клиент, false - нет
#if USE_MQTT
#define MQTT_RECONNECT_TIME   (10U)                         // время в секундах перед подключением к MQTT брокеру в случае потери подключения
#endif

// --- РАССВЕТ -------------------------
#define DAWN_BRIGHT           (200U)                        // максимальная яркость рассвета (0-255)
#define DAWN_TIMEOUT          (1U)                          // сколько рассвет светит после времени будильника, минут


//#define MAX_UDP_BUFFER_SIZE (UDP_TX_PACKET_MAX_SIZE + 1)
// максимальный размер буффера UDP сервера 
// 255 - это максимальное значение, при котором работа с Избранным не будет глючить
// для исходящих сообщений в приложение данное ограничение можно обойти (см. как реализована отправка "LIST"),
// а для входящего списка избранного - хз. пришлось увеличить до максимально возможножного значения. 
// дальше придётся переделывать типы (размеры) переменных в функциях FavoritesManager.h
#define MAX_UDP_BUFFER_SIZE   (255U)                        // максимальный размер буффера UDP сервера

#define GENERAL_DEBUG_TELNET  (false)                       // true - отладочные сообщения будут выводиться в telnet вместо Serial порта (для удалённой отладки без подключения usb кабелем)
#define TELNET_PORT           (23U)                         // номер telnet порта

#if defined(GENERAL_DEBUG) && GENERAL_DEBUG_TELNET
WiFiServer telnetServer(TELNET_PORT);                       // telnet сервер
WiFiClient telnet;                                          // обработчик событий telnet клиента
bool telnetGreetingShown = false;                           // признак "показано приветствие в telnet"
#define LOG                   telnet
#else
#define LOG                   Serial
#endif
