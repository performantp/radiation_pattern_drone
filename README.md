# Radiation Pattern Drone Project 
README

Die mit MMANA oder 4NEC berechneten Antennen sollen mit einer Drohne auf Abstrahlungscharakteristik und Abstrahlungswinkel ausgemessen und überprüft werden. Die erstellten versionierten Sources, Compiler Scripts für ESP32, das Schema, das KICAD für die Plattine, Silicon Labs Hersteller Unterlagen zum benutzten SDR-Chipset sowie Hersteller Antennen Spezifikation oder ähnlich und die Dokumentationen in Mind Map, pdf-Files, HTML-Files und Word-Files sollen für weitere Projektmitglieder lesbar abgelegt werden.

Release 1.1 (am 23.12.2020 abgeschlossen)
beinhaltete die Realisierung im November/Dezember 2020 auf einem Breadboard mit dem Silicon Labs Chipset 30, welcher "nur" MW und FM kann. Die Realiserung mit dem Display ST7735SB mit einer SD-Speicherkarte wurde am 01.12.2020 wegen Inkompatibilität zur Original Display Library eingestellt. Weiter verfolgt wwurde die Realisierung mit dem Display ST7735S. Die Realisierung wurde in Woche 50 erfolgreich abgeschlossen. Die erreichten Ergebnisse von diesem Release sind in der Dokumentation festgehalten. 

Release 1.2 (auf diesen Schritt wird am 23.12.2020 verzichtet, weil zwei andere OM's diesen Nachweis bereits vollbracht haben, Verweis auf zwei you tube Videos)
beinhaltet die Realisierung auf einem Breadboard mit dem Silicon Labs SDR Chipset SI4734-D60-GU (in der SSOP Bauweise mit oder ohne Breakout Board), welcher MW, FM und SW, inbesondere LSB, USB und CW, kann. Das Display und die Bedienung wird mit einer App realisiert. 

Release 1.3 (Aufgabe)
beinhaltet die Realisierung auf einem eigenen Board mit einem ESP32 Prozessor mit WLAN und Bluetooth Schnittstelle, welches mit KICAD geplant wird und dessen PCB-Fertigung in China inklusive Bestückung erfolgt. Dabei können nur Bauteile vom Produzenten auf der Platine eingebaut werden. Die Integration des Silicon Labs SDR Chipset SI4734-D60-GU (SSOP Bauweise) wird dann abschliessend manuell in der Schweiz bestückt und getestet.

Release 1.3a (nächste Aufgabe)
beinhaltet die Realisierung des sogenannten Datensammelpunkts gemäss Datenmodell sowie der Speicherung der Daten für spätere Auswertungen. Die Empfangssignalstärke sowie die GPS-Daten (es könnten die GPS-Daten der Drohne sein) sollen aufgenommen, zeitlich verknüpft und raw gespeichert werden. 

Release 1.4 (weitere Aufgaben) 
beinhaltet die Realisierung von Auswertungen nach Abzug über WLAN oder Bluetooth von der Drohne auf einen PC. Diese können als erstes Proof of Concept für die Auswertung des Abstrahlwinkels und den weiteren Sendekeulen manuell oder automatisch mit einer Python Programmierung erfolgen. 

