# Radiation Pattern Drone Project 
README

Die mit MMANA oder 4NEC berechneten Antennen sollen mit einer Drohne auf Abstrahlungscharakteristik und Abstrahlungswinkel ausgemessen und überprüft werden. Die erstellten versionierten Dateien sollen für weitere Projektmitglieder lesbar abgelegt werden.

Release 1.3a (diese Aufgabe wurde im September 2021 unterbrochen, weitere Hinweise und Details sind am Schluss aufgeführt).

Release 1.4a es wurden anschliessend zwei Lösungsvarianten evaluiert. 

Variante 1: Welche anfangs Oktober 2021 nun bereits mit einem ersten Test läuft, ist folgende: Mit einem Raspi auf dem rtl_power läuft und RTL-SDR mit einen Transverter
(47g) wird ein Frequenzbereich von 7-14 MHz überwacht und die gemessenen Werte werden mit einem Python Programm auf einem raspi zero W (40g) abgegriffen und dargestellt (Kabel und Antennen ca. 50g). Die ersten Messergebnisse sind so, dass man die gemessenen Werte noch gegenüber dem S-Level kalibrieren muss.

Variante 2: Im Hintergrund ist noch folgende zweite Lösung angedacht und die entsprechende Hardware wurde im September 2021 bereits beschafft.
Mit einem Raspi Zero W (40g) sollen die Messwerte von einem RTL-SDR mit integriertem Transverter aufgesammelt werden und die Daten anschliessend mit rtl_power und/oder Python ausgewertet werden.

Zu der Programmiersprache Python wurde von HB9FRV Ende September 2021 ein USKA HamAcademy durchgeführt. Es gibt voraussichtlich noch weitere Python Kurse. Auch wie man mit Python SDR Implementationen erstellt, wird von Mathias HB9FRV im Rahmen der USKA HamAcademy vermittelt. Daniel HB9GVD wird am 23.10.2021 am Kurs teilnehmen. Die Kurse sind für USKA Mitglieder mit 60.- CHF Kursgeld zugänglich. Auch dieser Kurs wird ev. wiederholt.

Das Team sucht weitere Interessierte, wenn möglich mit Python Kompetenz, welche die Python Aktivitäten unterstützen können. Interessenten melden sich bitte bei Martin HB9GYF oder Daniel HB9GVD.

Release 1.4b (nächste Aufgabe)
Mit einer grösseren Drohne und einer Last von ca. 150g und einem Gesamtgewicht von mehr als 1kg eine zu messenden Antenne (voraussichtlich eine Small Transmitting Loop (STL)) in einem Stufenflug zu erfliegen, damit daraus die Abstrahlcharakteristik der Antenne ermittelt werden kann. Analysieren wieviele Messungen im Flug pro Sekunde durchgeführt werden müssen, damit die Abstrahlcharakteristik ermittelt werden kann. Analysieren, ob sich im PoC dazu der WSPR-Ansatz eignet. Analysieren, wie z.B. grosse Beam-Antennen auf so kleine Aussendungen in 200m rund um die Antenne reagieren/gemessen werden können. Analysieren, ob sich die kleine Stabantenne im PoC eignet oder ob eine Drahtantenne realisiert werden soll. Analysieren, wie sich eine Aussendung z.B. mit 1W im Flug eignet. Die generelle Datensammlung soll im PoC überprüft werden. Die Datenauswertung im PoC soll nach einem Flug innert 12h vorliegen.

Eine Drohne herzustellen inkl. Akku, GPS und allem SDR-Equipmnet unter 250g wäre interessant, um unter den (künftigen) restriktiven gesetzlichen Anforderungen "in die Luft" zu kommen.

![image](https://user-images.githubusercontent.com/75325994/117536469-76388600-affb-11eb-8f5e-1f46c41599b1.png)

Die Drohne Plan B1 kann mehrere Way Points xyz fliegen und so müssten wir in der Lage sein, unser Stufenprofil auf verschiedenen Höhen auszufliegen. Die Drohne Plan B2 wurde bestellt und ist im September 2021 ebenfalls in der Schweiz bei Daniel HB9GVD. 

![image](https://user-images.githubusercontent.com/75325994/117536531-cc0d2e00-affb-11eb-9d3a-64735a4267c8.png)

Release 1.4c (übernächste Aufgabe)
beinhaltet die Realisierung des sogenannten Datensammelpunkts gemäss Datenmodell sowie der Speicherung der Daten für spätere Auswertungen. Die Empfangssignalstärke sowie die GPS-Daten (es könnten die GPS-Daten der Drohne sein) sollen aufgenommen, zeitlich verknüpft und raw gespeichert werden. 

Release 1.5 (weitere Aufgaben) 
beinhaltet die Realisierung von Auswertungen nach Abzug über WLAN oder Bluetooth von der Drohne auf einen PC. Diese können als erstes Proof of Concept für die Auswertung des Abstrahlwinkels und den weiteren Sendekeulen manuell oder automatisch mit einer Python Programmierung erfolgen. 


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Release 1.3a (diese Aufgabe wurde im September 2021 unterbochen)


Aufgabenstellung: Beinhaltet die Realisierung auf einem eigenen Board mit einem ESP32 Prozessor für die Scriptsprache Phyton mit WLAN und Bluetooth Schnittstelle, welches mit KICAD geplant wird (Design per 15.04.2021 abgeschlossen) und dessen PCB-Fertigung in China inklusive Bestückung erfolgt. Dabei können nur Bauteile vom Produzenten auf der Platine eingebaut werden. Die Integration des Silicon Labs SDR Chipset SI4734-D60-GU (SSOP Bauweise) und weitere 1-2 Bauteile werden dann abschliessend manuell in der Schweiz bestückt und danach getestet. Die Box ohne Antenne ist ca. 5x5x3 cm gross und wird mit ca. 30g Last berechnet. Professionelle Drohne aus US mit 780g Fluggewicht und Funktionen wie u.a. Motion Tracking, Way Point Skills ist nach längeren Shiping Aktionen in der CH eingetroffen und sie wurde getestet. Die vorhandenen Flug Management Skills sind hervorragend, aber u.a. aus Lizenzgründen vermutlich "zu gut". Aus der Sicht maximales Gesamtgewicht, welches unter 250g angestrebt wird (somit ist ein Flug bis 250m Höhe ohne Voranmeldung möglich, gesetzliche Randbedingung) wurde für das PoC eine noch leichtere Drohne bestellt. Die PoC Anforderungen an diese leichte Drohne sind mit Last gesamthaft nicht schwerer als 250g, Way Points zu fliegen, Position halten zu können und alles bis ca. 15 km Wind auf +/- 0.5m genau zu fliegen, und dabei die GPS-Daten zu speichern.  

Das SDR PCB ist am 08.05.2021 fertig "designed" und geht bald in die Fertigung nach China. Screenshot von Daniel HB9GVD erhalten. 

![image](https://user-images.githubusercontent.com/75325994/117536307-9287f300-affa-11eb-81f5-2ee2100f6795.png)

Warum wurde unterbrochen? Beim Testen des Boards sind im August/September 2021 Design-Fehler aufgetreten. Einige Verbindungen konnten zwar mit einer ad hoc Verbindung/Korrektur korrigiert werden. Trotz mehreren Anläufen das Board "zum Laufen" zu bringen, und weiteren Arbeiten wurde der "Durchbruch" leider nicht erreicht. Die Arbeiten zu Release 1.3a wurden deshalb vorläuftig eingestellt, alternative Lösungswege wurden analysiert und gefunden. Gerne lädt das Team Interessierte ein, das Board und die entsprechende Programmierung weiterzuführen. Daniel HB9GVD teilt sein Wissen gerne. Die Gewichtsvorteile der eigenen Hardware würden eher eine <250g Drohne erlauben.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Abgeschlossene oder gestrichene Releases:
Release 1.1 (am 23.12.2020 abgeschlossen)
beinhaltete die Realisierung im November/Dezember 2020 auf einem Breadboard mit dem Silicon Labs Chipset 30, welcher "nur" MW und FM kann. Die Realiserung mit dem Display ST7735SB mit einer SD-Speicherkarte wurde am 01.12.2020 wegen Inkompatibilität zur Original Display Library eingestellt. Weiter verfolgt wurde die Realisierung mit dem Display ST7735S. Die Realisierung wurde in Woche 50/2020 erfolgreich abgeschlossen. Die erreichten Ergebnisse von diesem Release sind in der Dokumentation festgehalten. 

Release 1.2 (auf diesen Schritt wird am 23.12.2020 verzichtet, weil zwei andere OM's diesen Nachweis bereits vollbracht haben, Verweis auf zwei you tube Videos)
beinhaltet die Realisierung auf einem Breadboard mit dem Silicon Labs SDR Chipset SI4734-D60-GU (in der SSOP Bauweise mit oder ohne Breakout Board), welcher MW, FM und SW, inbesondere LSB, USB und CW, kann. Das Display und die Bedienung wird mit einer App realisiert. 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


