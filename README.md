# Ball Roller game
Ball Roller is a game inspired by "The Incredible Machine". It is a project for Computer Game Technologies for Computer Science class on AGH university of Krakow.

# Compilation
To compile project, Visual Studio 2022 Community tools were used. Other tools tried to be used (like MingW and VS 2019 Community), however compilation errors or segmentation faults occured.

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

# Control
- klawisze 1- 9 – wybór obiektu do postawienia
- klawisze , oraz . – wybór obiektu do usunięcia
- klawisz BACKSPACE – usunięcie wybranego obiektu
- klawisz P – Play, rozpoczęcie symulacji
- klawisz R – Reset, powrót z symulacji do stawiania obiektów, postawione obiekty nie są usuwane
- klawisz S – Save, zapisuje poziom pod nazwą podaną w menu głównym (działa tylko w scenie Level Builder)
- klawisz ESC – powrót do menu głównego
- klawisz A – po wciśnięciu możliwe jest przesuwanie kamery
- klawisze LEWA/PRAWA STRZAŁKA – obracanie obiektu
- klawisze GÓRA/DÓŁ STRZAŁKA – przybliżanie/oddalanie kamery

