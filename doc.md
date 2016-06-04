# PiFace Dokumentáció

## Előkövetelmények a fordításhoz:
+ Qt Creator 3.3.1+ [telepítése](https://www.qt.com)

## Működés:
A program csatlakozik a PiFaceServer alkalmazáshoz egy TCP kapcsolaton keresztül a 3344 porton. Induláskor kérést küld a szervernek, ami beolvassa a lábak összes adatát. A bejövő adatokból feltölti a MainWindow **gpios** és **gpio_modes** tömbjeit, majd a Qt keretrendszer megjeleníti grafikus felületet, ahol elérhetjük a funckiókat.

## Publikus függvények:

```c
void MainWindow::closeEvent(QCloseEvent *event)```

A kapcsolat lezárásának kérése, felülírja az örökölt _closeEvent_ tagot.

```c
void MainWindow::connectTCP()```

Példányosít egy QTcpsocketet, amit csatlakoztat a szerverhez.
A socket _&QIODevice::readyRead_ signal-ját a _MainWindow::readAllPins_ slot-jához köti.

```c
void MainWindow::sendGetAll()```

Elküld egyetlen byteot, ami lekérdezi az összes láb állapotát.

```c
void MainWindow::readAllPins()```

Beolvas 64 byteot a socketből, ebből feltölti a **gpios** és **gpio_modes** tömböket, majd ezeken végigiterálva hívja a _MainWindow::setBgColorFromPin_ és _MainWindow::setBgColorFromMode_ függvényeket.

```c
void MainWindow::setBgColorFromPin(int gpio, int lvl)```

Az argumentumként kapott **gpio** lábhoz tartozó jelszintválasztó gomb háttérszínét beállítja a **lvl** argumentum függvényében.

```c
void MainWindow::setBgColorFromMode(int gpio, int lvl)```

Az argumentumként kapott **gpio** lábhoz tartozó módválasztó gomb háttérszínét beállítja a **lvl** argumentum függvényében.

```c
void MainWindow::pinToggle(int pin)```

Összeállít egy üzenetet, amivel a jelszintválasztó gomb aktuális értékét átbillenti a másik állapotba a szerveren, majd elküldi az üzenetet.

```c
void MainWindow::pinModeToggle(int pin)```

Összeállít egy üzenetet, amivel a módválasztó gomb aktuális értékét átbillenti a másik állapotba a szerveren, majd elküldi az üzenetet.

```c
void MainWindow::on_pushButton_clicked()```

Elküldi az összes láb adatait lekérdező függvényt. A **refresh** gombra van bekötve.

```c
void MainWindow::on_pin_N_clicked()```

A jelszintválasztó gombok lekezelő függvényei. A _pinToggle()_ függvényt hívja.

```c
void MainWindow::on_pin_mode_N_clicked()```

A módválasztó gombok lekezelő függvényei. A _pinModeToggle()_ függvényt hívja.
