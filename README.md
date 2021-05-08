# Radiation Pattern Drone Project 
README

Die mit MMANA oder 4NEC berechneten Antennen sollen mit einer Drohne auf Abstrahlungscharakteristik und Abstrahlungswinkel ausgemessen und überprüft werden. Die erstellten versionierten Sources, Compiler Scripts für ESP32, das Schema, das KICAD für die Plattine, Silicon Labs Hersteller Unterlagen zum benutzten SDR-Chipset sowie Hersteller Antennen Spezifikation oder ähnlich und die Dokumentationen in Mind Map, pdf-Files, HTML-Files und Word-Files sollen für weitere Projektmitglieder lesbar abgelegt werden.

Release 1.3a (Aufgabe, wird aus Sicht Mitte April 2021 voraussichtlich Ende Mai 2021 abgeschlossen)
beinhaltet die Realisierung auf einem eigenen Board mit einem ESP32 Prozessor für die Scriptsprache Phyton mit WLAN und Bluetooth Schnittstelle, welches mit KICAD geplant wird (Design per 15.04.2021 abgeschlossen) und dessen PCB-Fertigung in China inklusive Bestückung erfolgt. Dabei können nur Bauteile vom Produzenten auf der Platine eingebaut werden. Die Integration des Silicon Labs SDR Chipset SI4734-D60-GU (SSOP Bauweise) und weitere 1-2 Bauteile werden dann abschliessend manuell in der Schweiz bestückt und danach getestet. Die Box ohne Antenne ist ca. 5x5x3 cm gross und wird mit ca. 30g Last berechnet. Professionelle Drohne aus US mit 780g Fluggewicht und Funktionen wie u.a. Motion Tracking, Way Point Skills ist nach längeren Shiping Aktionen in der CH eingetroffen und sie wurde getestet. Die vorhandenen Flug Management Skills sind hervorragend, aber u.a. aus Lizenzgründen vermutlich "zu gut". Aus der Sicht maximales Gesamtgewicht, welches unter 250g angestrebt wird (somit ist ein Flug bis 250m Höhe ohne grosse Voranmeldung möglich, gesetzliche Randbedingung) wurde für das PoC eine noch leichtere Drohne bestellt. Die PoC Anforderungen an diese leichte Drohne sind mit Last gesamthaft nicht schwerer als 250g, Way Points zu fliegen, Position halten zu können und alles bis ca. 15 km Wind auf +/- 0.5m genau zu fliegen, und dabei die GPS-Daten zu speichern.  

Das SDR PCB ist am 08.05.2021 fertig "designed" und geht bald in die Fertigung nach China. Screenshot von Daniel HB9GVD erhalten. 

![image](https://user-images.githubusercontent.com/75325994/117536307-9287f300-affa-11eb-81f5-2ee2100f6795.png)

Release 1.3b (nächste Aufgabe)
Mit der kleinen Drohne und einer Last von 30g und einem Gesamtgewicht kleiner 250g eine zu messenden Antenne (voraussichtlich eine STL) in einem Stufenflug zu erfliegen, damit daraus die Abstrahlcharakteristik der Antenne ermittelt werden kann. Analysieren wieviele Messungen im Flug pro Sekunde durchgeführt werden müssen, damit die Abstrahlcharakteristik ermittelt werden kann. Analysieren, ob sich im PoC dazu der WSPR-Ansatz eignet. Analysieren, wie z.B. grosse Beam-Antennen auf so kleine Aussendungen in 200m rund um die Antenne reagieren/gemessen werden können. Analysieren, ob sich die kleine Stabantenne im PoC eigenet oder ob eine Drahtantenne realisiert werden soll. Analysieren, wie sich eine Aussendung z.B. mit 1W im Flug eignet. Die generelle Datensammlung soll im PoC überprüft werden. Die Datenauswertung im PoC soll nach einem Flug innert 12h vorliegen. 

Die Drohne Plan B1 wiegt mit Akku unter 250g und so werden wir dann unter den restriktiven gesetzlichen Anforderungen "in die Luft" kommen.

![image](https://user-images.githubusercontent.com/75325994/117536469-76388600-affb-11eb-8f5e-1f46c41599b1.png)

Die Drohne Plan B1 kann mehrere Way Points xyz fliegen und so müssten wir in der Lage sein, unser Stufenprofil auf verschiedenen Höhen auszufliegen. Die Drohne Plan B2 wurde bestellt und ist noch unterwegs in die Schweiz. 

![image](https://user-images.githubusercontent.com/75325994/117536531-cc0d2e00-affb-11eb-9d3a-64735a4267c8.png)

Release 1.3c (übernächste Aufgabe)
beinhaltet die Realisierung des sogenannten Datensammelpunkts gemäss Datenmodell sowie der Speicherung der Daten für spätere Auswertungen. Die Empfangssignalstärke sowie die GPS-Daten (es könnten die GPS-Daten der Drohne sein) sollen aufgenommen, zeitlich verknüpft und raw gespeichert werden. 

Release 1.4 (weitere Aufgaben) 
beinhaltet die Realisierung von Auswertungen nach Abzug über WLAN oder Bluetooth von der Drohne auf einen PC. Diese können als erstes Proof of Concept für die Auswertung des Abstrahlwinkels und den weiteren Sendekeulen manuell oder automatisch mit einer Python Programmierung erfolgen. 

Abgeschlossene oder gestrichene Releases:
Release 1.1 (am 23.12.2020 abgeschlossen)
beinhaltete die Realisierung im November/Dezember 2020 auf einem Breadboard mit dem Silicon Labs Chipset 30, welcher "nur" MW und FM kann. Die Realiserung mit dem Display ST7735SB mit einer SD-Speicherkarte wurde am 01.12.2020 wegen Inkompatibilität zur Original Display Library eingestellt. Weiter verfolgt wurde die Realisierung mit dem Display ST7735S. Die Realisierung wurde in Woche 50 erfolgreich abgeschlossen. Die erreichten Ergebnisse von diesem Release sind in der Dokumentation festgehalten. 

Release 1.2 (auf diesen Schritt wird am 23.12.2020 verzichtet, weil zwei andere OM's diesen Nachweis bereits vollbracht haben, Verweis auf zwei you tube Videos)
beinhaltet die Realisierung auf einem Breadboard mit dem Silicon Labs SDR Chipset SI4734-D60-GU (in der SSOP Bauweise mit oder ohne Breakout Board), welcher MW, FM und SW, inbesondere LSB, USB und CW, kann. Das Display und die Bedienung wird mit einer App realisiert. 

