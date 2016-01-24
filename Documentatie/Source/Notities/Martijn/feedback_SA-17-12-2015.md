#Soorten objecten
- boundary
    + geen gedrag, alleen hardware i/o: 
    +   moet het lampje knipperen? -> gebruik een controller
- controller
    + er mogen meer controllers dan use cases zijn

#packages
Gebruik packages om zaken die bij elkaar horen te groeperen


#ons diagram
- superklasse voor boundary objecten
- boundary - listener relatie
- waar is het wasprogramma?
    + wasprogramma is een set van wasstappen
        * actie -> controle
        * controle of je kan starten -> ...
        * actie -> controle of je klaar bent


#centrale klasse
mensen lezen van links boven naar rechts onder

- belangrijkste klasse midden bovenin
- belanrgijkste klasse links bovenin (net wat minder netjes)

#taakstructuering
- wijs ieder object toe aan een eigen taak
    + periodiek / passief / asynchroon
    + evt periode
    + deadlines
- pas samenvoegingscriteria toe
    + temporele cohesie
    + control cohesie
    + sequentiële cohesie

Taakstructuering leidt tot een taakstructuur-diagram 