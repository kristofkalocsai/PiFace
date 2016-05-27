# PiFace Dokumentáció

## Előkövetelmények a fordításhoz:
+ Qt Creator 3.3.1+ [telepítése](https://www.qt.com)

## Működés:
A program csatlakozik a PiFaceServer alkalmazáshoz egy TCP kapcsolaton keresztül a 3344 porton. Induláskor kérést küld a szervernek, ami beolvassa a lábak összes adatát. A bejövő adatokból feltölti a MainWindow `gpios` és `gpio_modes` tömbjeit, majd a Qt keretrendszer megjeleníti grafikus felületet, ahol elérhetjük a funckiókat.

## Publikus függvények:
```c
void MainWindow::closeEvent(QCloseEvent *event)```

A kapcsolat lezárásának kérése, felülírja az örökölt closeEvent tagot.

```c
void MainWindow::connectTCP()```

Példányosít egy QTcpsocketet, amit csatlakoztat a szerverhez.
A socket &QIODevice::readyRead signal-ját a MainWindow::readAllPins slot-jához köti.

```c
void MainWindow::sendGetAll()```

Elküld egyetlen byteot, ami lekérdezi az összes láb állapotát.

```c
void MainWindow::readAllPins()```

Beolvas 64 byteot a socketből, ebből feltölti a gpios és gpio_modes tömböket, majd ezeken végigiterálva hívja a MainWindow::setBgColorFromPin és setBgColorFromMode függvényeket.

```c
void MainWindow::setBgColorFromPin(int gpio, int lvl)```

Az argumentumként kapott gpio lábhoz tartozó jelszintválasztó gomb háttérszínét beállítja a lvl argumentum függvényében.

```c
void MainWindow::setBgColorFromMode(int gpio, int lvl)```

Az argumentumként kapott gpio lábhoz tartozó módválasztó gomb háttérszínét beállítja a lvl argumentum függvényében.

```c
void MainWindow::pinToggle(int pin)```

Összeállít egy üzenetet, amivel a jelszintválasztó gomb aktuális értékét átbillenti a másik állapotba a szerveren, majd elküldi az üzenetet.

```c
void MainWindow::pinModeToggle(int pin)```

Összeállít egy üzenetet, amivel a módválasztó gomb aktuális értékét átbillenti a másik állapotba a szerveren, majd elküldi az üzenetet.

```c
void MainWindow::on_pushButton_clicked()```

Elküldi az összes láb adatait lekérdező függvényt. A refresh gombra van bekötve.

```c
void MainWindow::on_pin_N_clicked()

A jelszintválasztó gombok lekezelő függvényei. A pinToggle() függvényt hívja.

```c
void MainWindow::on_pin_mode_N_clicked()```

A módválasztó gombok lekezelő függvényei. A pinModeToggle() függvényt hívja.



#### Kérések:
+ **A (0x41):**
  + set pin mode:
    + Y: pin
    + Z: ASCII 0 ha kimenet, ASCII 1 ha bemenet
> pl: `A01\n` : a 0-s GPIO lábat kimenetre állítja.


+ **B (0x42):**
  + set pin level:
    + Y: pin
    + Z: 0 ha low, 1 ha high
> pl: `BI0\n` : a 25-ös GPIO lábra magas jelet ad.

+ **C (0x43):**
  + read pin level: Y: pin, Z: omitted!
  + Válasz: egy byte, ami ASCII 1, ha magas, ASCII 0, ha alacsony.
> pl: `C1\n` : beolvassa az 1-es láb szintjét.


+ **D (0x44):**
  + read pin mode: Y: pin, Z: omitted!
  + Válasz: egy byte, ami ASCII 0, ha output, ASCII 1, ha input.
> pl: `DH\n` : beolvassa a 24-es láb funckióját


+ **Y (0x59):**
  + read all pins: Y: omitted!, Z: omitted!
  + Válasz: 64 byte, ahol 2n az n. láb funckiója, és 2n+1 az n. láb szintje.
> pl: `Y\n` : beolvassa az összes láb funkcióját és szintjét.


+ **X (0x58):**
  +exit: Y: omitted!, Z: omitted!
> pl: `X\n` : terminálja a kapcsolatot.
