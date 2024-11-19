1. um Bitmaps in CPP Daten zu Konvertieren benutzten wir https://javl.github.io/image2cpp/ 
2. Draw mode -> Horizontal - 2 bytes per pixels(565)
3. eine .cpp Datei erstellen und den generierten code rein kopieren
4. die Arduino libary mit #include <Arduino.h> in das erstellte file importieren.
5. Das erstellte file mit #include "FILE_NAME.cpp" in den Sketch einbinden
6. Wichtig das sketch und c++ Datei müssen im gleichen verzeichnis sein bzw ansonsten muss der Pfad angepasst werden.
