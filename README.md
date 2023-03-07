# Duck-Hunt
  Primul proiect la materia "Element de Grafica pe Calculator" a constat in implentarea renumitului joc "DUCK HUNT", utilizand C++ si GFX-Framework.
  Jocul original poate fi vizualizat aici: https://www.duck-hunt.org/
  
  
  ANIMARE
    Pentru a construi rața va fi așadar nevoie de un ansamblu de mai multe obiecte definite manual (vedeți modalitatea de definirea a pătratului din laborator) care se vor mișca împreuna, dar vor avea și animații independente. Astfel, rața:
        - va avea o animație de zbor: va da din aripi - puteți aplica de exemplu o rotație simplă pe fiecare aripă;
        - va zbura în diverse direcții în mod unitar - tot asamblul obiectelor care compun rața se va mișca sau roti împreună;
        
  
  MISCARE
    Rațele apar în partea de jos a ecranului și își vor începe zborul pe o direcție aleatoare în plan. Continuând pe acea direcție, la un moment dat vor ajunge la marginea ecranului. În această situație, rața trebuie să se “reflecte” și să își continue drumul în direcția aferentă, asemenea unei bile de biliard care lovește marginea mesei. Dacă rața este împușcată, aceasta va cădea pe sol mișcându-se printr-o animație vertical în jos, respectiv dacă evadează va zbura în afara ecranului mișcându-se printr-o animație vertical in sus.
  După un număr rezonabil de secunde, în care rața s-a ciocnit de câteva ori de marginea ecranului, aceasta va evada. Numărul de secunde va depinde de viteza cu care se mișcă rața în implementarea voastră, dar propunem să fie în jur de 3-5 secunde pentru a nu sta foarte mult o singură rață pe ecran.
  
  Așadar, rațele au 3 moduri de mișcare:
    1. Activ: rața a apărut pe ecran și se mișcă pe o direcție, aceasta schimbându-se la momentul ciocnirii cu marginea ecranului. Din această stare, rata va tranziționa ori către starea de împușcat, ori către starea de evadat;
    2. Împușcat: rața a fost împușcată și se va mișca vertical în jos, până ajunge la marginea de jos a ecranului, moment în care dispare;
    3. Evadat: rața a evadat și se va mișca vertical in sus, până ajunge la marginea de sus a ecranului, moment în care dispare.
    
    
    GAMEPLAY
      Scopul jocului este ca jucătorul să împuște cât mai multe rațe înainte să rămână fără vieți. Jocul începe cu un număr de vieți disponibile, dintre care se pierde câte una de fiecare dată când o rața reușește să scape fără să fie împușcată.
      Rațele apar câte una singură pe ecran, pe rând, fiecare după dispariția (prin evadarea sau împușcarea) celei anterioare. O rață va cădea pe sol când este împușcată și va zbura vertical în sus pentru a simboliza evadarea (sunt descrise deja detalii în secțiunile “Rațe - Afișare” și “Rațe - Mișcare”). Ele se mișcă după regulile descrise la secțiunea “Rațe - Mișcare”. După generarea a câte 5 rațe, viteza de mișcare a acestora va crește și, ca atare, dificultatea jocului va crește.


    TRASUL CU PUSCA
      Pentru a împușca o rață, jucătorul are la dispoziție 3 gloanțe care se reîncarcă de fiecare dată când apare o nouă rață. De fiecare dată când acesta face clic pe ecran, se va considera ca un glonț a fost tras în acel punct pe ecran și numărul de gloanțe disponibile va scădea cu 1. Dacă punctul de pe ecran (detalii secțiunea “Intersecția glonțului cu rața”) care a fost împușcat intersectează rața, ea va fi considerată împușcată, scorul (detalii secțiunea “Scor”) va crește și rața va cădea pe sol.


    INTERSECTIA GLONTULUI CU RATA
      Având în vedere că rațele au o formă destul de complexă, ar fi greu de calculat exact ce puncte de pe ecran se intersectează cu ele. Așadar, le puteți aproxima sub forma unui dreptunghi în care este încadrată rața (similar figurii de mai jos). Pentru a calcula coordonatele colțurilor acestui pătrat, puteți folosi câteva noțiuni de geometrie în plan, aplicate în funcție de coordonatele la care se află punctele de pe silueta raței.
      Pătratul încadrator este mult mai ușor de calculat dacă toate coordonatele locale ale primitivelor din care este construită rața sunt calculate față de un punct cât mai apropiat de centrul raței (detalii secțiunea “Rața - Construcție”).
      Pentru a afla dacă mouse-ul se află în interiorul dreptunghiului încadrator al raței, trebuie făcută o conversie din coordonate de vizualizare către coordonatele logice în care rața se plimbă pe ecran. Dacă va folosiți de scheletul laboratorului 3, aceste 2 spații de coordonate corespund 1:1 întrucât spațiul de desenare este limitat la rezoluția porții de afișare și se poate considera că poziția cursorului mouse-ului este și poziția sa în coordonate logice. Altfel, va trebui aplicată o transformare similară cu transformarea fereastră - poartă (detaliată tot în laboratorul 3), doar ca inversă. Atenție la corecția coordonatei Y.


    MOUSE INPUT
      Input-ul de la mouse se poate trata în funcția “OnMouseMove” din framework. Aceasta are 4 parametri: mouseX, mouseY, deltaX, deltaY. Primele 2 se referă la poziția la care se află cursorul în momentul în care se apelează funcția, în pixeli. Numerotarea începe din colțul stânga-sus al ferestrei de vizualizare în (0, 0). Cei 2 parametri din urmă se referă la deplasarea exactă (tot în pixeli) a cursorului de la poziția sa în frame-ul anterior pana la poziția sa în frame-ul în care a fost apelată funcția. De exemplu, daca mouse-ul s-a mișcat de la poziția (1200, 300) la poziția (1220, 294) în intervalul de la ultimul frame până la cel curent, vom avea următoarele valori: mouseX = 1220, mouseY = 294, deltaX = 20, deltaY = -6.
      
    EVADAREA RATEI
      În momentul în care toate cele 3 gloanțe au fost consumate fără a fi fost împușcată rața, aceasta evadează. De asemenea, dacă rața nu a fost împușcată timp de un număr de secunde, va evada. În ambele situații în care rața evadează, jucătorul va pierde o viață (detalii secțiunea “Vieți”) și nu va primi scorul aferent raței respective.
