SCREEN 7
RANDOMIZE TIMER
DIM SHARED a(8000)
DIM SHARED sheep1(15, 10)
DIM SHARED sheep2(15, 10)
DIM SHARED fence(9, 13)
DIM SHARED river(19, 13)
DIM SHARED rock(15, 11)
DIM SHARED house(15, 17)
DIM SHARED tree(15, 17)
DIM SHARED mountain(33, 17)
DIM SHARED horse(22, 14)
DIM SHARED Goat(22, 14)
DIM SHARED car1(36, 14)
DIM SHARED car2(36, 14)
DIM SHARED cardead(36, 14)
DIM SHARED express(54, 19)
DIM SHARED truck(42, 14)
DIM SHARED hatch(34, 14)
DIM SHARED ship1(19, 31)
DIM SHARED ship2(19, 31)
DIM SHARED moon(24, 24)
DIM SHARED velcro1(19, 9)
DIM SHARED people(81, 16)


DEF SEG = VARSEG(a(0))
BLOAD "sheepy.bsv ", 0
PUT (0, 0), a, PSET
GET (1, 1)-(17, 10), sheep1
GET (19, 1)-(35, 10), sheep2
GET (36, 1)-(44, 12), fence
GET (45, 0)-(64, 12), river
GET (68, 0)-(83, 11), rock
GET (1, 19)-(15, 35), house
GET (22, 19)-(37, 35), tree
GET (46, 19)-(78, 35), mountain
GET (126, 19)-(148, 33), horse
GET (154, 19)-(175, 33), Goat
GET (1, 38)-(37, 52), car1
GET (1, 54)-(37, 68), car2
GET (40, 38)-(69, 52), cardead
GET (77, 36)-(132, 53), express
GET (136, 39)-(177, 53), truck
GET (76, 57)-(109, 71), hatch
GET (0, 82)-(18, 111), ship1
GET (19, 82)-(37, 111), ship2
GET (45, 83)-(69, 107), moon
GET (81, 86)-(99, 95), velcro1
GET (0, 135)-(81, 151), people
GET (133, 83)-(267, 148), a
stt:
CLS
er:
tim = TIMER
LOCATE 1, 1: PRINT "PRESS ANY KEY TO BEGIN"
IF TIMER - tim < .5 THEN a$ = INKEY$

IF a$ = "1" THEN GOTO gameone
IF a$ = "2" THEN GOTO gametwo
IF a$ = "3" THEN GOTO gamethree
IF a$ = "4" THEN GOTO endgame

IF a$ = "" THEN GOTO er

CLS

PUT (30, 30), a, PSET
LOCATE 20, 10: PRINT "(C) 2017 MONTIE MONGOOSE"
LOCATE 21, 10: PRINT "YouTube.com/montiemongoose"
PLAY "MBO2 EDCDEE t80 e t120 DDD EE t80 e t120 EDCDEEE EDDED T80 C t120"
LOCATE 22, 1: PRINT "(PRESS SPACE TO CONTINUE)"
DO
LOOP WHILE INKEY$ = ""

GOTO nextpart


introa:

PAINT (0, 0), 11
LINE (0, 50)-(320, 50), 2
PAINT (10, 60), 2, 2
LINE (0, 80)-(320, 80), 6
PUT (scrollx, 34), house, PSET
frame = 1
tim = TIMER
LOCATE 20, 1: PRINT B$
LOCATE 21, 1: PRINT C$
LOCATE 22, 1: PRINT d$
DO
IF frame = 1 THEN PUT (50, 120), sheep1, PSET
IF frame = 2 THEN PUT (50, 120), sheep2, PSET
DO
LOOP WHILE TIMER - tim < .1
tim = TIMER
frame = frame + 1: IF frame = 3 THEN frame = 1

LOOP WHILE INKEY$ = ""
RETURN

nextpart:
B$ = "Lambert was a happy sheep."
C$ = "One day, while he was out running,"
d$ = "something terrible happened."
GOSUB introa
CLS
PAINT (0, 0), 11
LINE (0, 50)-(320, 50), 2
PAINT (10, 60), 2, 2
LINE (0, 80)-(320, 80), 6
PUT (scrollx, 34), house, PSET
PUT (50, 120), sheep1, PSET
PUT (70, 35), horse, PSET
PUT (95, 35), Goat, PSET
LOCATE 18, 1: PRINT "His NEIGH-bors, Mr. Goat and Mr. Horse"
LOCATE 19, 1: PRINT "told him that all the people were"
LOCATE 20, 1: PRINT "missing. "
LOCATE 21, 1: PRINT "Lambert said, You've got to be "
LOCATE 22, 1: PRINT "KIDDING me, Mr. Goat!"
SLEEP
CLS
PAINT (0, 0), 11
LINE (0, 50)-(320, 50), 2
PAINT (10, 60), 2, 2
LINE (0, 80)-(320, 80), 6
PUT (scrollx, 34), house, PSET
PUT (50, 120), sheep1, PSET
PUT (70, 35), horse, PSET
PUT (95, 35), Goat, PSET
LOCATE 19, 1: PRINT "But Mr. Horse said NAY!"
LOCATE 20, 1: PRINT "I will find out what happened."
LOCATE 21, 1: PRINT "With no more humans, that means I will"
LOCATE 22, 1: PRINT "starve to death!"
SLEEP

a:

sheeplechase:
CLS
frame = 1
x1 = 100
y1 = 150
enemyx = 300
scrollx = 150
backg = 1
score = 0
jump = 0
jumps = 15
LOCATE 10, 17: PRINT "LEVEL 1"
LOCATE 12, 14: PRINT "SHEEPLECHASE"
SLEEP

PAINT (0, 0), 11
LINE (0, 50)-(320, 50), 2
PAINT (10, 60), 2, 2
LINE (0, 80)-(320, 80), 6
PUT (scrollx, 34), house, PSET
PUT (enemyx, 150), fence, PSET

gameone:
tim = TIMER
enspeed = 10
tim3 = TIMER
IF frame = 1 THEN PUT (x1, y1), sheep1, PSET
IF frame = 2 THEN PUT (x1, y1), sheep2, PSET
IF jump <> 1 THEN LINE (100, 120)-(116, 132), 2, BF

DO
a$ = INKEY$
IF a$ = " " THEN
IF jumps > 0 THEN
SOUND 300, .25
jumps = jumps - 1

IF q <> 1 THEN
LINE (x1, y1)-(x1 + 16, y1 + 12), 2, BF
jump = 1
tim3 = TIMER
y1 = 120

END IF
END IF
q = 1
tim2 = TIMER
END IF
LOOP WHILE TIMER - tim < .25
LOCATE 1, 1: PRINT "Jumps left:", jumps
IF POINT(enemyx - 1, 155) <> 2 THEN GOTO dead
                     
IF TIMER - tim2 > 1 THEN
y1 = 150
q = 0
jump = 0
END IF

tim = TIMER
LINE (enemyx, 150)-(enemyx + 20, 170), 2, BF
enemyx = enemyx - enspeed
IF enemyx = 0 THEN
enemyx = 300
score = score + 1
enspeed = enspeed + 1
END IF

PUT (enemyx, 150), fence, PSET
              



IF scrollx = 0 THEN
scrollx = 300
backg = backg + 1
IF backg = 3 THEN backg = 1
LINE (0, 33)-(16, 49), 11, BF
END IF

SELECT CASE backg
CASE IS = 1
'PUT (scrollx, 34), house, XOR
scrollx = scrollx - 1
PUT (scrollx, 34), house, PSET
PSET (scrollx + 15, 50), 2
LINE (scrollx + 15, 34)-(scrollx + 15, 49), 11

CASE IS = 2
'PUT (scrollx, 34), tree, XOR
scrollx = scrollx - 1
PUT (scrollx, 34), tree, PSET
LINE (scrollx + 15, 34)-(scrollx + 15, 49), 11
PSET (scrollx + 15, 50), 2

CASE IS = 3
END SELECT
frame = frame + 1
IF frame = 3 THEN frame = 1
IF score > 6 THEN GOTO gametwo

GOTO gameone
dead:
CLS
FOR q = 0 TO 40
SOUND INT(RND * 100) + 40, .2
NEXT q
LOCATE 2, 2: PRINT "YOU DIED"
LOCATE 3, 2: PRINT "Lambert has failed his mission."
LOCATE 4, 2: PRINT "Try again?"
dde:
a$ = INKEY$
a$ = UCASE$(a$)
IF a$ = "Y" THEN GOTO sheeplechase
IF a$ = "N" THEN END

GOTO dde


END
gametwo:
CLS
LOCATE 1, 2: PRINT "EWE see a note on the ground,"
LOCATE 2, 2: PRINT "it says..."
LOCATE 3, 2: PRINT "We are the Vile Extra-Terrestial"
LOCATE 4, 2: PRINT "Loud Coldhearted Raucous Offenders"
LOCATE 5, 2: PRINT "(V.E.L.C.R.O.)"
LOCATE 6, 2: PRINT "We have kidnapped the humans"
LOCATE 7, 2: PRINT "Don't even think about saving them!"
PLAY "mb o1 t180 aefdecdb t90 a "

SLEEP
CLS
LOCATE 1, 2: PRINT "Lambert, knows what to do now!"
LOCATE 2, 2: PRINT "The VELCRO can't pull the wool"
LOCATE 3, 2: PRINT "over his eyes."
LOCATE 4, 2: PRINT "He just gets in his Lamborghini"
LOCATE 5, 2: PRINT "to drive to the space depot."
SLEEP
CLS
LOCATE 10, 15: PRINT "LEVEL 2"
LOCATE 11, 7: PRINT "ASHEEP AT THE WHEEL"
PLAY "MBo1t220 d#D# f# G# A A# t120A# t220"
'PLAY "D#D#F#G#AA# t120A# t220 BB D#FF#F#F# BB D#FF#F#F# D# G#AA#A#t120D#t220"

SLEEP
CLS
scrollx = 280
LINE (0, 0)-(320, 50), 11, BF
PUT (scrollx, 35), mountain, PSET
LINE (0, 51)-(320, 100), 2, BF
LINE (0, 101)-(320, 199), 8, BF
carpos = 1
x1 = 10
frame = 1
tim = TIMER
enpos = 1
enx = 265
enemyspeed = 20
enemytype = 1

gametwogo:
'IF enpos = 1 THEN LINE (enx, 110)-(enx + 55, 130), 7, BF
'IF enpos = 2 THEN LINE (enx, 160)-(enx + 55, 190), 8, BF
IF enx < 265 THEN
LINE (x1 - 20, 110)-(x1 + 86, 140), 8, BF
LINE (x1 - 20, 150)-(x1 + 86, 180), 8, BF


SELECT CASE enemytype
CASE IS = 1
IF enpos = 1 THEN PUT (enx, 110), express, PSET
IF enpos = 2 THEN PUT (enx, 160), express, PSET

CASE IS = 2
IF enpos = 1 THEN PUT (enx, 110), truck, PSET
IF enpos = 2 THEN PUT (enx, 160), truck, PSET

CASE IS = 3
IF enpos = 1 THEN PUT (enx, 110), hatch, PSET
IF enpos = 2 THEN PUT (enx, 160), hatch, PSET

END SELECT
END IF

IF enpos = 1 THEN
IF carpos = 1 THEN
         IF enx < x1 + 20 THEN
          IF enx > x1 THEN
           IF POINT(enx + 10, 120) <> 8 THEN GOTO deadcar
          END IF
        END IF
END IF

END IF
IF enpos = 2 THEN
        IF carpos = 2 THEN
         IF enx < x1 + 20 THEN
          IF enx > x1 THEN
           IF POINT(enx + 10, 170) <> 8 THEN GOTO deadcar
          END IF
        END IF
        END IF
END IF



SELECT CASE carpos

CASE IS = 1
IF frame = 1 THEN PUT (x1, 110), car1, PSET
IF frame = 2 THEN PUT (x1, 110), car2, PSET

CASE IS = 2
IF frame = 1 THEN PUT (x1, 160), car1, PSET
IF frame = 2 THEN PUT (x1, 160), car2, PSET
'LINE (0, 145)-(320, 145), 15, , 7

END SELECT

DO
a$ = INKEY$
IF a$ = " " THEN
SOUND 100, .3
carpos = carpos + 1
IF carpos = 3 THEN carpos = 1
END IF
LOOP WHILE TIMER - tim < .25


frame = frame + 1
IF frame = 3 THEN frame = 1
tim = TIMER
x1 = x1 + 1
IF x1 > 260 THEN GOTO gamethree

IF enpos = 1 THEN LINE (enx, 110)-(enx + 56, 140), 8, BF
IF enpos = 2 THEN LINE (enx, 150)-(enx + 56, 190), 8, BF

enx = enx - enemyspeed



IF enx < 0 THEN
enx = 320
pn = INT(RND * 100)
IF pn < 50 THEN enpos = 1
IF pn > 49 THEN enpos = 2
cee = INT(RND * 100)
IF cee < 33 THEN enemytype = 1
IF cee < 66 THEN enemytype = 2
IF cee > 65 THEN enemytype = 3
END IF

scrollx = scrollx - 1
IF scrollx = 0 THEN
LINE (0, 0)-(320, 50), 11, BF
scrollx = 280
END IF

PUT (scrollx, 35), mountain, PSET
PSET (scrollx + 33, 50), 11

GOTO gametwogo

deadcar:
IF carpos = 1 THEN PUT (x1, 110), cardead, PSET
IF carpos = 2 THEN PUT (x1, 160), cardead, PSET
FOR q = 0 TO 40
SOUND INT(RND * 100) + 40, .2
NEXT q
LOCATE 5, 2: PRINT "EWE HAVE CRASHED YOUR LAMB-BORGHINI!"
SLEEP
LOCATE 6, 3: PRINT "DO YOU WANT TO TRY AGAIN?"
d:
a$ = INKEY$
a$ = UCASE$(a$)
IF a$ = "" THEN GOTO d
IF a$ = "Y" THEN GOTO gametwo
IF a$ = "N" THEN END
GOTO d

gamethree:
CLS
PUT (100, 30), ship1
LINE (0, 60)-(320, 199), 2, BF
LINE (0, 180)-(320, 90), 8
LINE (0, 250)-(320, 150), 8
PAINT (100, 180), 8, 8
tim = TIMER
ee = 0
FOR qre = 170 TO 190
PUT (qre, 160 + ee), car1, PSET
SOUND 38, .245
DO
LOOP WHILE TIMER - tim < .05
tim = TIMER
ee = ee - 1
NEXT
SLEEP
CLS
LOCATE 2, 2: PRINT "Lambert hops in the STARSHEEP ONE!"
SLEEP
CLS
PUT (200, 20), moon, PSET
tim = TIMER
FOR qre = 170 TO 0 STEP -1
PUT (20, qre), ship2, PSET
LINE (20, qre + 30)-(40, qre + 30), 0
DO
LOOP WHILE TIMER - tim < .05
SOUND 39 + qre, .23
tim = TIMER

NEXT
SLEEP
LOCATE 19, 1: PRINT "Lambert moves in to engage the"
LOCATE 20, 1: PRINT "VELCRO mothership."
LOCATE 21, 1: PRINT "Dodge the lasers!"



SLEEP
CLS
level3:
CLS
LOCATE 10, 15: PRINT "LEVEL THREE"
LOCATE 12, 14: PRINT "STARSHEEP ONE"
PLAY "mbt140  o3L16dd+el8>c<l16e>l8c<l16e>l4cl16dd+ecdecl8dl8cg>cp8"

SLEEP

shippos = 150
mov = 5
ppp = 150
tim = TIMER
CLS
PUT (shippos, 150), ship1, XOR
x42 = 1
y2 = 0
LINE (x42, 199)-(x42, 0), 7
LINE (319 - x42, 199)-(319 - x42, 0), 7
klsr = 0
moven = 1
timegame = TIMER
PUT (ppp, 0), velcro1, XOR

gamethreego:

IF TIMER - timegame > 40 THEN GOTO endgame

DO
a$ = INKEY$
IF a$ = " " THEN
mov = mov * -1
END IF
LOOP WHILE TIMER - tim < .25
klsr = klsr + 1

PUT (shippos, 150), ship1, XOR
shippos = shippos + mov
PUT (shippos, 150), ship1, XOR

IF shippos < 0 THEN shippos = 0
IF shippos > 319 THEN shippos = 319


tim = TIMER
IF x42 < 115 THEN x42 = x42 + 1

LINE (x42, 199)-(x42, 0), 7
LINE (319 - x42, 199)-(319 - x42, 0), 7

IF shippos < x42 THEN GOTO dead
IF shippos + 19 > (319 - x42) THEN GOTO dead

IF x42 > 1 THEN
     
      PUT (ppp, 0), velcro1, XOR

      ppp = ppp + moven
     
      IF ppp < 120 THEN
      moven = moven * -1
      END IF
      IF ppp > 160 THEN
      moven = moven * -1
      END IF

      PUT (ppp, 0), velcro1, XOR

END IF

IF klsr = 10 THEN
  FOR qqq = 100 TO 1000 STEP 100
  SOUND qqq, .5
  NEXT qqq
  LINE (ppp + 9, 10)-(ppp + 11, 199), 10, BF
  pp2 = ppp
  klsr = 0
tim2 = TIMER
END IF
IF TIMER - tim2 > 1 THEN
      IF TIMER - tim2 < 1.25 THEN
    LINE (pp2 + 9, 10)-(pp2 + 11, 199), 0, BF

      END IF
END IF

FOR q = 0 TO 18
IF POINT(shippos + q, 149) <> 0 THEN
FOR qx = 0 TO 40
SOUND INT(RND * 100) + 40, .2
NEXT qx

LOCATE 10, 3: PRINT "EWE HAVE DESTROYED YOUR SPACESHEEP!"
LOCATE 12, 3: PRINT "EWE WANT TO TRY AGAIN?"
dd:
a$ = INKEY$
a$ = UCASE$(a$)
IF a$ = "" THEN GOTO dd
IF a$ = "Y" THEN GOTO level3
IF a$ = "N" THEN END
GOTO dd


END IF
NEXT q

GOTO gamethreego

endgame:
CLS
LOCATE 1, 2: PRINT "Time to shoot your laser!"
LOCATE 2, 2: PRINT "Time your shot right!"
tim = TIMER
DO
LOOP WHILE TIMER - tim < 1

DO
a$ = INKEY$
LOOP WHILE a$ = ""

CLS


PUT (150, 0), velcro1
PUT (150, 140), ship1
tim = TIMER
FOR qq = 0 TO 120
IF qq > 100 THEN LINE (qq, 190)-(qq, 200), 4
IF qq < 100 THEN LINE (qq, 190)-(qq, 200), 2
IF qq < 90 THEN LINE (qq, 190)-(qq, 200), 14
IF qq < 33 THEN LINE (qq, 190)-(qq, 200), 4


DO
a$ = INKEY$
IF a$ = " " THEN GOTO shootfirst

LOOP WHILE TIMER - tim < .1
SOUND 40 + qq, .05
tim = TIMER

NEXT qq
GOTO failshot
shootfirst:

IF qq > 100 THEN GOTO failshot
IF qq <= 100 THEN
        IF qq > 89 THEN
        SOUND 600, .5
        col = 14
        FOR ss = 0 TO 6
        LINE (160 + ss, 138)-(160 + ss, 0), col
        LINE (160 - ss, 138)-(160 - ss, 0), col
        IF ss = 3 THEN col = 12
        IF ss > 4 THEN col = 4
        NEXT ss
       GOTO finish
       
        END IF
      
END IF

failshot:
FOR q = 1 TO 30
CIRCLE (160, 150), q, 4
SOUND 40 + INT(RND * 100), .25

NEXT q

LOCATE 2, 2: PRINT "YOUR SHOT HAS FAILED"
LOCATE 3, 2: PRINT "TRY AGAIN?"
ddds:
DO
a$ = INKEY$
LOOP WHILE a$ = ""
a$ = UCASE$(a$)
IF a$ = "Y" THEN GOTO endgame
IF a$ = "N" THEN END
GOTO ddds:






finish:
SLEEP
CLS
LINE (0, 150)-(320, 200), 6, BF
PUT (120, 0), velcro1
FOR qqq = 80 TO 180
LINE (130, 15)-(qqq, 148), 14
tim = TIMER
'DO
'LOOP WHILE TIMER - tim < .01
SOUND 800 - qqq, .1
NEXT
PUT (90, 133), people, PSET

FOR qqq = 180 TO 80 STEP -1
LINE (130, 15)-(qqq, 148), 0
tim = TIMER
PUT (90, 133), people, PSET

SOUND 800 + qqq, .1
NEXT
LOCATE 3, 3: PRINT "The people have been returned!"
LOCATE 4, 3: PRINT "Lambert has finished his quest!"
PLAY "MBo1t220 d#D# f# G# A A# t120A# t220"
PLAY "mb D#D#F#G#AA# t120A# t220 BB D#FF#F#F# BB D#FF#F#F# D# G#AA#A#t120D#t220"
SLEEP
DO
CLS
PAINT (0, 0), 11
LINE (0, 50)-(320, 50), 2
PAINT (10, 60), 2, 2
LINE (0, 80)-(320, 80), 6
PUT (scrollx, 34), house, PSET
frame = 1
tim = TIMER
LOCATE 20, 1: PRINT B$
LOCATE 21, 1: PRINT C$
LOCATE 22, 1: PRINT d$
PUT (100, 0), a, XOR
LOCATE 18, 2: PRINT "THANK YOU FOR PLAYING!"
LOCATE 19, 2: PRINT "MADE FOR BITBITJAM2017"
LOCATE 20, 2: PRINT "MONTIE MONGOOSE 2017 YouTube.com/montiemongoose"
LOCATE 21, 2: PRINT "PRESS Y to Play again, N to QUIT"
FOR qi = 0 TO 10000
a$ = INKEY$
a$ = UCASE$(a$)
IF a$ = "Y" THEN GOTO stt:
IF a$ = "N" THEN END

IF frame = 1 THEN PUT (50, 120), sheep1, PSET
IF frame = 2 THEN PUT (50, 120), sheep2, PSET
DO
LOOP WHILE TIMER - tim < .1
tim = TIMER
frame = frame + 1: IF frame = 3 THEN frame = 1
NEXT qi
LOOP
END








