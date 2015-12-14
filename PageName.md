# Andis Feedback 18.04.12 #

Die Grundidee wie ihr sie mir vor einer Woche vorgestellt habt, ist OK, aber die Implementierung ist leider fehlerhaft, was auch zu den Fehlern in der Ausgabe führt, dass Variablen bereits deklariert wurden, obwohl sie im aktuellen Scope noch nicht deklariert wurden. Der Fehler ist:

identified a global variable "a"
searching for symbol "a" in global table
ERROR    --    multiple declaration of variable "a"

Der grobe Grund dafür ist, dass ihr lediglich eine verkette Liste für globale wie auch lokale Symbole verwendet, was natürlich nicht korrekt ist. Wie schon mehrfach in der Vorlesung erläutert, hat _jede_ Funktion eine eigene Symboltabelle, d.h. im Konext eures Projektes eine eigene verkette Liste, die in der func Struktur stehen sollte.

Hier noch ein paar weitere Anmerkungen zur aktuellen Struktur der Symboltabelle: ich hatte euch bereits das Feedback gegeben, dass in der Symbolsstruktur eine union besser geeignet ist für var & func - das ist aber soweit ok. Was aber dann nicht mehr wirklich sauber ist, den type mit in den symbol Struktur zu packen und zusätzlich in der func Struktur einen Rückgabetyp zu definieren. Wenn ihr schon strikt trennt zwischen var und func - was gut ist - dann sollte die Trennung wirklich strikt sein, d.h. die notwendigen Felder (siehe Aufgabenbeschreibung) für Variablen und Funktionen in die jeweiligen Strukturen. D.h. der type sollte in die Variablenstruktur geschrieben werden. In der Funktionsstruktur fehlt wie oben erwähnt die lokale Symboltabelle sowie die Informationen über die Übergabeparameter (mind. Typ und Reihenfolge).

Also das globale Feedback ist: seht zu, dass ihr brauchbaren Code entwickelt in den nächsten Wochen. Bislang sehe lediglich etwas brauchbaren Code in der Symboltabelle. Gerade noch ein Hinweis zu dem Code in der IR-Code-Erzeugung:

a) sie enthält noch die alten OP-Codes, wie z.B. MEM\_LD, etc.
b) seit C99 gibt es eine elegante Möglichkeit, um (String-)Arrays zu deklarieren deren Inhalt 1:1 zur Reihenfolge von einer enum passen muss. Hier eine schematische Darstellung:

enum op\_codes {
> OP\_CODE\_ASSIGN = 0,
> OP\_CODE\_PLUS,
> /**add new op codes above**/
> OP\_CODE\_COUNT
> /**OP\_CODE\_COUNTS contains the number of op codes which can be used to set the size of the array**/
};

char **op\_code\_names[OP\_CODE\_COUNT](OP_CODE_COUNT.md) = {
> [OP\_CODE\_ASSIGN](OP_CODE_ASSIGN.md) = "ASSIGN",
> [OP\_CODE\_PLUS](OP_CODE_PLUS.md) = "PLUS"
};**

Mit dieser Schreibweise wird es möglich jedes einzelne Feld des Arrays explizit über einen enum-Wert zu addressieren, wodurch nicht unbedingt auf die exakte Reihenfolge geachtet werden muss, wodurch dieser Code übersichtlicher und weniger fehleranfällig ist.