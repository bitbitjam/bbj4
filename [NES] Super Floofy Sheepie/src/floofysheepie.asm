  .inesprg 1					; 1 bank of program code (16kb)
  .ineschr 1					; 1 bank of picture data (8kb)
  .inesmap 0					; mapper 0
  .inesmir 1					; mirror setting 1

  .bank 0						; Bank 0 - code goes here
  .org $8000					; Begins at $8000 in rom


Init:							; Our Init Game Point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Our Constants - Start
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PPUPLUS32 = %00001100
PPUPLUS1 = %00001000

FULHEDGE = $00					; FULHEDGE
TOPHEDGE = $01					; TOP OF HEDGE
LFTHEDGE = $02					; LEFT END OF HEDGE
RGTHEDGE = $03					; RIGHT END OF HEDGE

VELCROTP = $04					; VELCRO TRAP
FLOOFBAL = $05					; FLOOFBALL

LRENEMYS = $06					; LEFT RIGHT SLOW ENEMY
LRENEMYF = $07					; LEFT RIGHT FAST ENEMY
UDENEMYS = $08					; UP DOWN SLOW ENEMY
UDENEMYF = $09					; UP DOWN FAST ENEMY
FLOWERS1 = $0A					; FLOWER PATCH 1
FLOWERS2 = $0B					; FLOWER PATCH 2
BLANKTLE = $0C					; BLANK TILE
SHEEPSTT = $0E					; SHEEP START POINT
SHEEPGOL = $0F					; SHEEP GOAL LOCATION

lastKeys = $00					; STORES THE KEYS PRESSED ON THE LAST FRAME - 1BYTE
curScreen = $01					; WHICH SCREEN ARE WE ON? 0 =TITLE, 1= GAME, 2 = END OF GAME
frameCounter = $02				; INCREMENTS AFTER EVERY FRAME HAS BEEN REACHED (60 FPS)
bigFrameCounter = $03			; INCREMENTS WHEN OUR FRAMECOUNTER OVERFLOWS
bkgOffset = $04

rng = $FF						; BASIC RNG 0- 255 - POSSIBLY LEAVE THIS UN-INITIALISED FOR BONUS RNG?
rng128 = $FE					; basic rng 0 to 127
rng64 = $FD						; BASIC RNG 0 - 63 - POSSIBLY LEAVE THIS UN-INITIALISED FOR BONUS RNG?
rngAlt = $FC					;ALTERNATIVE RNG

levelHalf = $F0

timerLarge = $05				; SIMPLY COUNTS DOWN IN 10'S - ROUND TIMER
timerSmall = $06				; SIMPLY COUNTS DOWN IN 1's - ROUND TIMER

currentRound = $07				; WHICH ROUND ARE WE AT?




p1ScoreThousands = $09			; P1 SCORE IN THOUSANDS
p1ScoreHundreds = $0A			; P1 SCORE IN HUNDREDS
p1ScoreTens = $0B				; P1 SCORE IN TENS
p1ScoreOnes = $0C				; P1 SCORE IN ONES


p1UpdateScore = $15				; ARE WE UPDATING OUR SCORE NEXT LOOP?
p2UpdateScore = $16				; IS PLAYER 2 UPDATING THEIR SCORE NEXT LOOP?

gamePaused = $17				; IS THE GAME SCREEN PAUSED?

spriteCollider1Width = $18		; WHICH SPRITE ARE WE CHECKING FOR
spriteCollider1Height = $19		; WHICH SPRITE ARE WE CHECKING AGAINST

spriteCollider2Width = $1A		; WHICH SPRITE ARE WE CHECKING FOR
spriteCollider2Height = $1B		; WHICH SPRITE ARE WE CHECKING AGAINST

temp = $1F						; A TEMPORARY VALUE - STORES OUR COLLISION RESULT NORMALLY

cpuTargetX = $20				; WHERE THE CPU IS GOING TO HEAD TOWARDS NEXT - have it run wheneever our randomizer reaches a set value for starters. - attempt to avoid a shot.



playersAnimationFrame = $80		; WHICH FRAME IS OUR SHEEPIE ON?
playerX = $81					; current position
playerY = $82					; current position
playerStartX = $90				; START POSITION IN THE LEVEL
playerStartY = $91				; START POSITION IN THE LEVEL
playerDir = $86					; WHICH DIRECTION IS THE PLAYER FACING  4=LEFT 6 = RIGHT 8=UP 2 = DOWN
bkgTileX = $92					;BKG TILE WE ARE ON IN MEMORY - X
bkgTileY = $93					;BKGTILE WE ARE ON IN MEMORY - Y
bkgMemoryHigh = $94				;HIGH BYTE IN MEMORY
bkgMemoryLow = $95				;LOW BYTE IN MEMORY
bkgTileCur = $96				;WHICH TILE ARE WE ON CURRENTLY?

playerLastX = $97
playerLastY = $98

totalFloofBalls = $83			;STORES THE NUMBER OF FLOOFBALLS ON THE SCREEN
totalEnemies = $84				;STORES TE NUMBER OF ENEMIES ON SCREEN
playerLives = $85				; PLAYERS REMAINING LIVES

JOYPAD1 = $4016
JOYPAD2 = $4017

controller1 = $30
oldcontroller1 = $31
controller2 = $32
oldcontroller2 = $33


BUTTON_A        = $80
BUTTON_B        = $40
BUTTON_SELECT   = $20
BUTTON_START    = $10
BUTTON_UP       = $08
BUTTON_DOWN     = $04
BUTTON_LEFT     = $02
BUTTON_RIGHT    = $01

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; REM, The Stack is located at $01FF and will expand DOWN to $0100 at Most
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Sprite constants - Fills up $0200 until $02FF
;; Transferred at the start of each frame via SPR-RAM 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

spr0_Y = 	$0200					
spr0_tile = $0201
spr0_att = 	$0202
spr0_X = 	$0203

spr1_Y = 	$0204					
spr1_tile = $0205
spr1_att = 	$0206
spr1_X = 	$0207

spr2_Y = 	$0208					
spr2_tile = $0209
spr2_att = 	$020A
spr2_X = 	$020B

spr3_Y = 	$020C					
spr3_tile = $020D
spr3_att = 	$020E
spr3_X = 	$020F

spr4_Y = 	$0210					
spr4_tile = $0211
spr4_att = 	$0212
spr4_X = 	$0213

spr5_Y = 	$0214					
spr5_tile = $0215
spr5_att = 	$0216
spr5_X = 	$0217

spr6_Y = 	$0218					
spr6_tile = $0219
spr6_att = 	$021A
spr6_X = 	$021B

spr7_Y = 	$021C					
spr7_tile = $021D
spr7_att = 	$021E
spr7_X = 	$021F

spr8_Y = 	$0220					
spr8_tile = $0221
spr8_att = 	$0222
spr8_X = 	$0223

spr9_Y = 	$0224					
spr9_tile = $0225
spr9_att = 	$0226
spr9_X = 	$0227

spr10_Y = 	$0228					
spr10_tile = $0229
spr10_att = $022A
spr10_X = 	$022B

spr11_Y = 	$022C					
spr11_tile = $022D
spr11_att = $022E
spr11_X = 	$022F

floofBallSprite_Y = $02A0
floofBallSprite_tile = $02A1
floofBallSprite_att = $02A2
floofBallSprite_X = $02A3


enemySprite1_Y = $0230
enemySprite1_tile = $0231
enemySprite1_att = $0232
enemySprite1_X = $0233

enemySprite2_Y = $0234
enemySprite2_tile = $0235
enemySprite2_att = $0236
enemySprite2_X = $0237

enemySprite3_Y = $0238
enemySprite3_tile = $0239
enemySprite3_att = $023A
enemySprite3_X = $023B

enemySprite4_Y = $023C
enemySprite4_tile = $023D
enemySprite4_att = $023E
enemySprite4_X = $023F



enemy1_Y = $0230
enemy1_tile = $0231
enemy1_att = $0232
enemy1_X = $0233

enemy2_Y = $0234
enemy2_tile = $0235
enemy2_att = $0236
enemy2_X = $0237

enemy3_Y = $0238
enemy3_tile = $0239
enemy3_att = $023A
enemy3_X = $023B

enemy4_Y = $023C
enemy4_tile = $023D
enemy4_att = $023E
enemy4_X = $023F


enemy5_Y = $0240
enemy5_tile = $0241
enemy5_att = $0242
enemy5_X = $0243

enemy6_Y = $0244
enemy6_tile = $0245
enemy6_att = $0246
enemy6_X = $0247

enemy7_Y = $0248
enemy7_tile = $0249
enemy7_att = $024A
enemy7_X = $024B

enemy8_Y = $024C
enemy8_tile = $024D
enemy8_att = $024E
enemy8_X = $024F

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Our Constants - End
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Init The Game Here
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  SEI          ; disable IRQs
  CLD          ; disable decimal mode
  LDX #$40
  STX $4017    ; disable APU frame IRQ
  LDX #$FF
  TXS          ; Set up stack
  INX          ; now X = 0
  STX $2000    ; disable NMI
  STX $2001    ; disable rendering
  STX $4010    ; disable DMC IRQs

ClearSpriteRAM:
  LDA #$00 						; Clear our sprite RAM and zeropage on Init
  STA $0000, x
  STA $0100, x
  STA $0200, x
  STA $0400, x
  STA $0500, x
  STA $0600, x
  STA $0700, x
  LDA #$FE
  STA $0300, x
  INX
  CPX #$00
  BNE ClearSpriteRAM


vblankwait1:       ; First wait for vblank to make sure PPU is ready
  BIT $2002
  BPL vblankwait1

; PREP THE PPU FOR PALETTE STUFFS
  LDA #$3F
  STA $2006
  LDA #$00
  STA $2006

;INSERT OUR PALETTE
  LDX #$00
 loadPaletteLoop:
  LDA palette, X  
  STA $2007
  INX
  CPX #$20
  BNE loadPaletteLoop
  
  JSR loadTitleScreen
  
  JSR displayPlayerSprite



  LDA #%10001000   ; enable NMI, sprites from Pattern Table 1
  STA $2000

  LDA #%00011110   ; enable sprites
  STA $2001


;----------------------------------------------------------------------------------------
; GAME LOOP - GAME CODE GOES HERE!
;----------------------------------------------------------------------------------------
GameLoop:

  LDA #%00011110   ; enable sprites
  STA $2001

; READ A INPUT
ReadP1A:
  LDA controller1
  AND #BUTTON_A
  BEQ inputButtonUp
  
; THIS CODE RUNS IF WE ARE PRESSING A 
  JSR handleButtonDown
  JMP skipButtonUp

;OUR BUTTON IS UP, NOT PRESSED  
inputButtonUp:



; BUTTON IS UP, ROTATE THE PLAYER EVERY 32 FRAMES
  LDA frameCounter
  AND #$3F
  BNE skipButtonUp
  
  LDA playersAnimationFrame
  CMP #$1D
  BEQ turnPlayerRight
  CMP #$21
  BEQ turnPlayerRight
  
  CMP #$05
  BEQ turnPlayerDown
  CMP #$09
  BEQ turnPlayerDown
  
  CMP #$0D
  BEQ turnPlayerUp
  CMP #$11
  BEQ turnPlayerUp
  
  CMP #$15
  BEQ turnPlayerLeft
  CMP #$19
  BEQ turnPlayerLeft
  
turnPlayerRight:
  LDA #$05
  JMP endPlayerRotation
  
turnPlayerDown:
  LDA #$15
  JMP endPlayerRotation
  
turnPlayerUp:
  LDA #$1D
  JMP endPlayerRotation
  
turnPlayerLeft:
  LDA #$0D

endPlayerRotation:
  STA playersAnimationFrame
  JMP skipButtonUp
  
increasePlayersFrame:
  CLC
  ADC #$08
  STA playersAnimationFrame
  


skipButtonUp:  

; THIS AREA ANIMATES OUR SHEEP
; CHECK IF WE ARE CHANGING OUR SHEEPS ANIMATION FRAME
  LDA frameCounter
  AND #$0F
  BNE keepFrame
 
  LDA playersAnimationFrame
  CMP #$05
  BEQ playerRightFrame1
  CMP #$09
  BEQ playerRightFrame2

  CMP #$0D
  BEQ playerLeftFrame1
  CMP #$11
  BEQ playerLeftFrame2
  
  CMP #$15
  BEQ playerDownFrame1
  CMP #$19
  BEQ playerDownFrame2
  
  CMP #$1D
  BEQ playerUpFrame1
  CMP #$21
  BEQ playerUpFrame2
  
playerRightFrame1:
  LDA #$09
  JMP storePlayersAnimationFrame

playerRightFrame2:
  LDA #$05
  JMP storePlayersAnimationFrame
  
playerLeftFrame1:
  LDA #$11
  JMP storePlayersAnimationFrame

playerLeftFrame2:
  LDA #$0D
  JMP storePlayersAnimationFrame  

playerDownFrame1:
  LDA #$19
  JMP storePlayersAnimationFrame

playerDownFrame2:
  LDA #$15
  JMP storePlayersAnimationFrame  

playerUpFrame1:
  LDA #$21
  JMP storePlayersAnimationFrame

playerUpFrame2:
  LDA #$1D
  JMP storePlayersAnimationFrame  

  
storePlayersAnimationFrame:
  STA playersAnimationFrame
  JMP keepFrame
  
; END ANIMATE SHEEP FRAMES  


keepFrame:
  
  LDA curScreen
  CMP #$00
  BNE useActualControls
  LDX playerX
  INX
  STX playerX
  JMP skipUseActualControls
  
 ;HAVE OUR CONTROLS OCCUR IN THIS BRANCH OF CODE
useActualControls:

skipUseActualControls:  

;DISPLAY OUR SHEEPIE
  JSR displayPlayerSprite


;DISPLAY A WOLFY
  LDA #$30
  STA enemy1_tile
  CLC
  ADC #$01
  STA enemy2_tile
  ADC #$01
  STA enemy3_tile
  ADC #$01
  STA enemy4_tile
  
  
  LDA #%00000001
  STA enemy1_att
  STA enemy2_att
  STA enemy3_att
  STA enemy4_att
  
  LDA #$60
  STA enemy1_X
  STA enemy3_X
  CLC
  ADC #$08
  STA enemy2_X
  STA enemy4_X
  
  LDA #$40
  STA enemy1_Y
  STA enemy2_Y
  CLC
  ADC #$08
  STA enemy3_Y
  STA enemy4_Y
  
;REDUCE TIMER BY ONE EVERY 64 FRAMES
  LDA frameCounter
  AND #$3F
  BNE skipReduceTimer
  LDY timerSmall
  DEY
  CPY #$FF
  BNE updateSmallTimer
  TYA
  CLC
  ADC #$0A
  TAY
  LDX timerLarge
  DEX
  STX timerLarge
  
updateSmallTimer:  
  STY timerSmall 
  
skipReduceTimer:
;END HANDLE TIMER
  
 ; ANIMATE FLOOFBALLS
  LDA frameCounter
  AND #$0F
  BNE skipFloofAnimation

  LDX #$00
  LDY #$00
  
floofLoop:  
  LDA floofBallSprite_tile,Y
  CMP #$00
  BEQ skipFloofBall
  
  CLC
  ADC #$01
  CMP #$05
  BEQ floofFrame1
  STA floofBallSprite_tile,Y
  JMP skipFloofBall
  
floofFrame1: 
  LDA #$01
  STA floofBallSprite_tile,Y

skipFloofBall:  
  INX
  INY
  INY
  INY
  INY
  CPY #$40
  BNE floofLoop
  
  
skipFloofAnimation:
; END FLOOF ANIMATION LOOP

;CHECK FOR COLLISIONS WITH FLOOFBALLS - START

  LDA #$10
  STA spriteCollider1Width   
  STA spriteCollider1Height
  lda #$08
  STA spriteCollider2Width
  STA spriteCollider2Height
  
  LDX #$00		; PLAYER SPRITE
  LDY #$A0		; FLOOF SPRITE
  
checkFloofCollision:  
  INY
  INY
  INY
  INY
  JSR DetectCollisions
  LDA temp
  CMP #$01
  BNE noFloofCollision
  LDA #$05
  STA p1UpdateScore
  JSR UpdatePlayer1Score
  LDA #$00
  STA spr0_X,Y
  STA spr0_tile,Y  
  
noFloofCollision:
  CPY #$E0
  BNE checkFloofCollision
  
; END CHECK FOR COLLISIONS WITH FLOOF BALLS


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;CHECK FOR COLLISIONS WITH BACKGROUND TILES
;($2100 TO $23BF)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  LDA playerX
  LSR A
  LSR A
  LSR A
  STA bkgTileX ;( RANGE OF 00 TO 1F) - NEEDS AN OFFSET
  
  LDA playerY
  CLC
  ADC #$10
  LSR A
  LSR A
  LSR A
  STA bkgTileY; (RANGE OF 00 TO 1F) 
  
  CMP #$07
  BPL bkgCollisions1
  LDX #$20
  STX bkgMemoryHigh	;OUR HIHG MEMORY BYTE IS #$20
  CLC
  ; A * 32 + bkgTileX == bkgMemeoryLow
  ASL A
  ASL A
  ASL A
  ASL A
  ASL A

  CLC
  ADC bkgTileX
  STA bkgMemoryLow  ;LOW BYTE IS 00-FF
  
bkgCollisions1:
  CMP #$0F
  BPL bkgCollisions2
  LDX #$21
  STX bkgMemoryHigh
  CLC
  SBC #$08
  ASL A
  ASL A
  ASL A
  ASL A
  ASL A
  CLC
  ADC bkgTileX
  STA bkgMemoryLow
  JMP endBkgCollision
  
bkgCollisions2:
  CMP #$17
  BPL bkgCollisions3
  LDX #$22
  STX bkgMemoryHigh
  CLC
  SBC #$10
  ASL A
  ASL A
  ASL A
  ASL A
  ASL A
  CLC
  ADC bkgTileX
  STA bkgMemoryLow
  JMP endBkgCollision
bkgCollisions3:
  LDX #$23
  STX bkgMemoryHigh
  CLC
  SBC #$18
  ASL A
  ASL A
  ASL A
  ASL A
  ASL A
  CLC
  ADC bkgTileX
  STA bkgMemoryLow


endBkgCollision:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;CHECK FOR COLLISIONS WITH BACKGROUND TILES - END
;($2100 TO $23BF)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 
; RANDOM NUMBER GENERATOR  
updateRNG:

  LDA rng
  ADC frameCounter 
  ADC spr0_X
  STA rng	;RANDOM 0 TO 255
  SBC spr2_X
  STA rngAlt; RANDOM 0 TO 255
  LSR A
  STA rng128;RANDOM 0 TO 2127
  LSR A
  STA rng64	;RANDOM 0 TO 63


; UPDATE OUR FRAMECOUNTER
  LDX frameCounter
  INX
  STX frameCounter


;  LDA #%11111110		;THIS LINE PLAYS WITH THE COLOURS ON SCREEN - USE THIS  TO CHECK CPU USAGE
;  STA $2001  			; AND STORES IT IN THE PPU DIRECTLY, NICE


  
  JSR vblankwaiter
  JMP GameLoop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; END OF GAME LOOP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


vblankwaiter:       ; First wait for vblank to make sure PPU is ready
  BIT $2002
  BPL vblankwaiter
  RTS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; WHAT HAPPENS WHEN OUR BUTTON IS DOWN?
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
handleButtonDown:

  LDX curScreen	; WHICH SCREEN ARE WE ON?
  CPX #$00
  BNE buttonDownMainScreen
  ; THIS CODE RUNS IF SCREEN = 0
  
  JSR initGame	; INITIALISE OUR GAME
  
  RTS	; RETURN TO OUR MAIN GAME LOOP
  
buttonDownMainScreen:
  
  LDA playersAnimationFrame
  CMP #$05  
  BEQ movePlayerRight
  CMP #$09
  BEQ movePlayerRight

  CMP #$0D
  BEQ movePlayerLeft
  CMP #$11
  BEQ movePlayerLeft
  
  CMP #$15
  BEQ movePlayerDown
  CMP #$19
  BEQ movePlayerDown
  
  CMP #$1D
  BEQ movePlayerUp
  CMP #$21
  BEQ movePlayerUp
  
movePlayerRight:
  LDX #$06
  STX playerDir
  LDX playerX
  STX playerLastX
  INX
  STX playerX
  JMP endMotion

movePlayerLeft: 
  LDX #$04
  STX playerDir
  LDX playerX
  STX playerLastX
  DEX
  STX playerX
  JMP endMotion

movePlayerDown:
  LDX #$02
  STX playerDir
  LDX playerY
  STX playerLastY
  INX
  STX playerY
  JMP endMotion

movePlayerUp:
  LDX #$08
  STX playerDir
  LDX playerY
  STX playerLastY
  DEX
  STX playerY

endMotion:  
  
  RTS


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; INIT THE GAME MAIN SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
initGame:

  SEI
  LDA #$00
  
  STA $2000    ; disable NMI
  STA $2001    ; disable rendering
  STA $4010    ; disable DMC IRQs

  LDA #$40
  STA $4017    ; disable APU frame IRQ

  LDA #$01
  STA curScreen ; CURSCREEN IS NOW 1
  
  LDX #$09			;GAME TIMER
  STX timerLarge
  STX timerSmall
  
  LDX #$03			; STARTING NUMBER OF LIVES
  STX playerLives
  
  LDX #$00
  LDY #$00

  LDA #$20
  STA $2006
  LDA #$20
  STA $2006  
  
  
printOutScore:
  
  LDA gameScreenLinesSky,X
  STA $2007
  INX
  CPX #$40
  BNE printOutScore


  LDA #$21
  STA $2006
  LDA #$00
  STA $2006  

  LDX #$00
  LDY #$00
  
initGameLoop1:
  LDA #$26					; A CLEAR GREEN BKG SPRITE
  STA $2007					; WRITE IT TO OUR BACKGROUND SCREEN
  INX
  CPX #$20
  BNE initGameLoop1
  JSR vblankwaiter
  INY 
  CPY #$05
  BNE initGameLoop1


;SET UP OUR BACKGROUND ATTRIBUTE TABLES
  LDA #$23
  STA $2006
  LDA #$C0
  STA $2006
  LDA #$00
  LDX #$00
  
loadAttributeTableGameLoop:
  STA $2007
  INX
  CPX #$40
  BNE loadAttributeTableGameLoop



; LOAD UP OUR LEVEL FOR REAL NOW!

;FULHEDGE = $00					; FULHEDGE
;TOPHEDGE = $01					; TOP OF HEDGE
;LFTHEDGE = $02					; LEFT END OF HEDGE
;RGTHEDGE = $03					; RIGHT END OF HEDGE

;VELCROTP = $04					; VELCRO TRAP
;FLOOFBAL = $05					; FLOOFBALL

;LRENEMYS = $06					; LEFT RIGHT SLOW ENEMY
;LRENEMYF = $07					; LEFT RIGHT FAST ENEMY
;UDENEMYS = $08					; UP DOWN SLOW ENEMY
;UDENEMYF = $09					; UP DOWN FAST ENEMY
;FLOWERS1 = $0A					; FLOWER PATCH 1
;FLOWERS2 = $0B					; FLOWER PATCH 2
;BLANKTLE = $0C					; BLANK TILE
;SHEEPSTT = $0E					; SHEEP START POINT
;SHEEPGOL = $0F					; SHEEP GOAL LOCATION


  LDX #$21
  STX levelHalf
  LDX #$00
  STX bkgOffset
  
nextLevelBlock:  
  
  
  LDA levelHalf
  STA $2006


  CMP $23
  BNE firstPartOfScreen
  TXA
  CLC
  ASL A
  CLC
  LDY level1c,X
  JMP endFirstPartOfScreen
  
firstPartOfScreen:  
  TXA
  ASL A
  LDY level1a,X
  
endFirstPartOfScreen:  
  CLC
  ADC bkgOffset
  STA $2006   
  
  
  CPY #FULHEDGE
  BEQ showFullHedge
  CPY #TOPHEDGE
  BEQ showTopHedge
  CPY #FLOWERS1
  BEQ showFlowers
  CPY #FLOWERS2
  BEQ showFlowers2
  CPY #LFTHEDGE
  BEQ showLeftHedge
  CPY #RGTHEDGE
  BEQ showRightHedge
  CPY #VELCROTP
  BEQ showVelcroTrap
  CPY #SHEEPGOL
  BEQ showSheepGoal
  CPY #SHEEPSTT
  BEQ placeSheep
  CPY #FLOOFBAL
  BEQ placeFloofBall
  CPY #UDENEMYS
  BEQ placeUDEnemyS
  JMP nextLevelPiece
  
  

showFullHedge:
  JMP realShowFullHedge
  
showTopHedge:
  JMP realShowTopHedge
 
showFlowers:
  JMP realShowFlowers

showFlowers2:
  JMP realShowFlowers2

showLeftHedge:
  JMP realShowLeftHedge

showRightHedge:
  JMP realShowRightHedge

showVelcroTrap:
  JMP realShowVelcroTrap

showSheepGoal:
  JMP realShowSheepGoal

placeSheep:
  JMP realPlaceSheep

placeFloofBall:
  JMP realPlaceFloofBall

placeUDEnemyS:
  JMP realPlaceUDEnemyS

 .include "floofyleveltiles.asm"
  
nextLevelPiece:
  INX
  
  CPX #$10
  BEQ addOffset
  CPX #$20
  BEQ addOffset
  CPX #$30
  BEQ addOffset  
  CPX #$40
  BEQ resetOffset    
  CPX #$50
  BEQ addOffset 
  CPX #$60
  BEQ addOffset 
  CPX #$70
  BEQ addOffset
  CPX #$80
  BEQ resetOffset   
  CPX #$90
  BEQ addOffset
  CPX #$A0
  BEQ addOffset
  JMP skipAddOffset

resetOffset:
  LDA #$00
  STA bkgOffset
  LDA levelHalf
  CLC
  ADC #$01
  STA levelHalf
  JMP skipAddOffset

addOffset:
  LDA bkgOffset
  CLC
  ADC #$20
  STA bkgOffset

skipAddOffset:  

  CPX #$B0
  BEQ escapeLevelLoad
  JMP nextLevelBlock



  
escapeLevelLoad:


 


;SET OUR GAMEBKG ATTRIBUTE TABLES HERE
  LDX #$00
  LDY #$D0
setBkgAttributes:
  LDA #$23
  STA $2006
  STY $2006

  
 ; LDA #%00000000		;br(2), bl(2), tr(2), tl(2)
  LDA level1BkgAttributes,X
  STA $2007
  INX
  INY
  CPX #$30
  BNE setBkgAttributes

;SET OUR SKY ATTRIBUTE TILES HERE

  LDX #$C0
setSkyAttributes:  
  LDA #$23
  STA $2006
  STX $2006  
  LDA #%01010101
  STA $2007
  INX
  CPX #$C8
  BNE setSkyAttributes  




  LDA #%10001000   ; enable NMI, sprites from Pattern Table 1
  STA $2000

  LDA #%00011110   ; enable sprites
  STA $2001


  RTS






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; THE START OF V-BLANK DRAWING STUFF AND JOYPAD INPUT AND A SMALL AMOUNT OF DRAWING LOGIC
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
NMI:

; GET LAST FRAMES INPUTS, STORE THEM IN LASTKEYS EASY MODES
  LDA controller1
  STA oldcontroller1
  LDA controller2
  STA oldcontroller2

; PUSH OUR SPRITE OAM TO THE SCREEN - FIRST THING TO DO AS WE ARE AT THE START OF V-BLANK
;Move Sprite Data to OAM
  LDA #$00
  STA $2003
  LDA #$02
  STA $4014

;READ CONTROLLER STATUS HERE INSTEAD
   ldx #1             ; even odd          <- strobe code must take an odd number of cycles total
   stx controller1    ; even odd even
   stx $4016          ; odd even odd even
   dex                ; odd even
   stx $4016          ; odd even odd even
 read_loop:
   lda $4017          ; odd even odd EVEN <- loop code must take an even number of cycles total
   and #3             ; odd even
   cmp #1             ; odd even
   rol controller2, x ; odd even odd even odd even (X = 0; waste 1 cycle and 0 bytes for alignment)
   lda $4016          ; odd even odd EVEN
   and #3             ; odd even
   cmp #1             ; odd even
   rol controller1    ; odd even odd even odd
   bcc read_loop      ; even odd [even]


;RETURN OUR TILE WE'RE ON TOP OF
  
  
  LDX bkgMemoryHigh
  STX $2006
  LDX bkgMemoryLow
  STX $2006
  
  LDA $2007
  STA bkgTileCur  
  CMP #$B4
  BEQ stopPlayer
  CMP #$A4  
  BEQ stopPlayer  
  CMP #$B3
  BEQ stopPlayer  
  CMP #$B5
  BEQ stopPlayer  
  
  JMP endBkgCheck
  
stopPlayer:  
  LDY playerDir
  CPY #$02
  BNE playerDirCheck2
  LDY playerY
  DEY
  STY playerY
  JMP endBkgCheck

playerDirCheck2:
  LDY playerDir 
  CPY #$08
  BNE playerDirCheck3
  LDY playerY
  INY
  STY playerY
  JMP endBkgCheck

playerDirCheck3:
  LDY playerDir 
  CPY #$04
  BNE playerDirCheck4
  LDY playerX
  INY
  STY playerX
  JMP endBkgCheck
  
playerDirCheck4:
  LDY playerX
  DEY
  STY playerX

 
 
endBkgCheck:

 

; UPDATE OUR TIMER DISPLAY IF WE ARE ON THE MAIN SCREEN
  LDA curScreen
  CMP #$01
  BNE FinishedDisplayingStuff
  
 ;POSITION OUR UPDATE CO-ORDS TO OUR TIMER
  LDA #$20
  STA $2006
  LDA #$50
  STA $2006
  CLC
  LDA timerLarge
  ADC #$E0
  STA $2007
  LDA timerSmall
  ADC #$E0
  STA $2007
  
; END UPDATE OUR TIMER DISPLAY ON THE MAIN SCREEN

; DISPLAY LIVES REMAINING
  LDA #$20
  STA $2006
  LDA #$48
  STA $2006
  LDA playerLives
  CLC
  ADC #$E0
  STA $2007

; DISPLAY player1s scoreSCORE
  LDA #$23
  STA $2006
  LDA #$01
  STA $2006
  
; DISPLAY player1s scoreSCORE
  LDA #$20
  STA $2006
  LDA #$5B
  STA $2006
  
  CLC
  LDA p1ScoreThousands
  ADC #$E0
  STA $2007
  
  LDA p1ScoreHundreds
  ADC #$E0
  STA $2007
  
  LDA p1ScoreTens
  ADC #$E0
  STA $2007
  
  LDA p1ScoreOnes
  ADC #$E0
  STA $2007


;RESET OUR SCROLL POSITION AND PROCEED AS NORMAL THROUGH THE FRAME
FinishedDisplayingStuff:
  
;RESET OUR LEFT AND TOP
  LDA #$20
  STA $2006
  LDA #$00
  STA $2006
; MOVE OUR ENEMY PLAYER ABOUT THE SCREEN

; RESET OUR FRAME BASED VARIABLES TO ZERO AT THE START OF EACH FRAME
  STA p1UpdateScore
  
  
  RTI

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; END OF VBLANK STUFFS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; LOAD TITLE SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
loadTitleScreen:

; SHOULD SET OUR CURRENT SCREEN TO 0 - TITLE SCREEN
  LDA #$00
  STA curScreen

 
;LOAD UP OUR BACKGROUND LAYER
  LDA #$20
  STA $2006
  LDA #$00
  STA $2006
 
 ; INIT OUR BACKGROUND DATA WITH X AND Y REFERENCES
  LDY #$00
  LDX #$00

loadTiles:
  ;TWO STAGE LOOP IN ACTION
  

  CPY #$00
  BEQ LoadStartScreen1
  CPY #$01
  BEQ LoadStartScreen2
  CPY #$02
  BEQ LoadStartScreen3
  
  JMP keepLoadingTiles 
 
LoadStartScreen1:
  LDA titleScreenBkgLines1,X
  JMP keepLoadingTiles 
 
LoadStartScreen2:
  LDA titleScreenBkgLines2,X
  JMP keepLoadingTiles
 
LoadStartScreen3:
  LDA titleScreenBkgLines3,X
  JMP keepLoadingTiles 
 

keepLoadingTiles:
  
  STA $2007
  INX
  CPX #$00
  BNE loadTiles
  LDX #$00
  INY
  CPY #$03
  BNE loadTiles

  LDX #$00
  
loadLastFewTiles:
  LDA titleScreenBkgLines4,X
  STA $2007
  INX
  CPX #$C0
  BNE loadLastFewTiles

;SET UP OUR BACKGROUND ATTRIBUTE TABLES
  LDA #$23
  STA $2006
  LDA #$C0
  STA $2006
  LDA #$00
  LDX #$00
  
loadAttributeTableLoop:
  STA $2007
  INX
  CPX #$40
  BNE loadAttributeTableLoop

  
  
  
  
  LDA #$0D
  STA playersAnimationFrame  
  
  LDA #$20
  STA playerX
  
  LDA #$B0
  STA playerY

  RTS


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DISPLAY PLAYER SPRITE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
displayPlayerSprite:

  LDA playerY
  STA spr0_Y
  
  LDA playersAnimationFrame
  STA spr0_tile  

  LDA #%00000000
  STA spr0_att						; PALETTE 0-4, X FLIP, Y FLIP  

  LDA playerX
  STA spr0_X

;INIT A SPRITE - SPRITE 1

  LDA playerY
  STA spr1_Y						; Y POSITION 
  
  LDA playersAnimationFrame
  CLC
  ADC #$01
  STA spr1_tile						; SPRITE INDEX 
  
  LDA #%00000000
  STA spr1_att						; PALETTE 0-4, X FLIP, Y FLIP
  
  LDA playerX
  CLC
  ADC #$08
  STA spr1_X				; X POSITION 


  LDA playerY
  CLC
  ADC #$08
  STA spr2_Y
  
  LDA playersAnimationFrame
  CLC
  ADC #$02
  STA spr2_tile  

  LDA #%00000000
  STA spr2_att						; PALETTE 0-4, X FLIP, Y FLIP  

  LDA playerX
  STA spr2_X

  LDA playerY
  CLC
  ADC #$08
  STA spr3_Y						; Y POSITION 
  
  LDA playersAnimationFrame
  CLC
  ADC #$03
  STA spr3_tile						; SPRITE INDEX 
  
  LDA #%00000000
  STA spr3_att						; PALETTE 0-4, X FLIP, Y FLIP
  
  LDA playerX
  CLC
  ADC #$08
  STA spr3_X				; X POSITION 

  RTS


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;UPDATE PLAYER1 SCORE - AMOUNT TO INCREMENT IS STORED IN p1UpdateScore
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
UpdatePlayer1Score:
  CLC
  LDA p1ScoreOnes  
  ADC p1UpdateScore
  CLC
  SBC #$00
  STA p1ScoreOnes
  CMP #$0A
  BMI FinishUpdatingPlayer1Score
  
  SBC #$0A
  STA p1ScoreOnes
  LDA p1ScoreTens
  ADC #$00
  STA p1ScoreTens
  CMP #$0A
  BMI FinishUpdatingPlayer1Score  

  SBC #$0A
  STA p1ScoreTens
  LDA p1ScoreHundreds
  ADC #$00
  STA p1ScoreHundreds
  CMP #$0A
  BMI FinishUpdatingPlayer1Score  

  SBC #$0A
  STA p1ScoreHundreds
  LDA p1ScoreThousands
  ADC #$00
  STA p1ScoreThousands
    
FinishUpdatingPlayer1Score:  
  RTS
  
  


;Collision Detection
DetectCollisions:

  LDA #$00		
  STA temp								;INITIALIZE temp to 0 (no collision found)
  ; START FIRST BRACKET
  CLC  
  LDA spr0_X,X							; TOP LEFT OF OUR OPPONENTS SHIP
  ADC spriteCollider1Width				; ADD 16 FOR ITS WIDTH
  CMP spr0_X,Y							; COMPARE X2+W2 WITH A
  BMI FinishCollisionCheck				; IF GREATER THAN RETURN TEMP 

  ; START 2ND BRACKET
  CLC  
  LDA spr0_X,Y
  ADC spriteCollider1Height
  CMP spr0_X,X
  BMI FinishCollisionCheck

  ; START THIRD BRACKET
  CLC  
  LDA spr0_Y,X							; TOP LEFT OF OUR OPPONENTS SHIP
  ADC spriteCollider2Width				; ADD 16 FOR ITS WIDTH
  CMP spr0_Y,Y							; COMPARE X2+W2 WITH A
  BMI FinishCollisionCheck				; IF GREATER THAN RETURN TEMP 

  ; START FOURTH BRACKET
  CLC  
  LDA spr0_Y,Y
  ADC spriteCollider2Height
  CMP spr0_Y,X
  BMI FinishCollisionCheck
 
  
  LDA #$01
  STA temp


FinishCollisionCheck:
  RTS



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; LOAD GAMESCREEN FROM OUR DATABASE VALUES SHOWN BELOW
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LoadGameScreen:
  JSR vblankwaiter
  SEI
  LDA #$00
  STA $2000    ; disable NMI
  STA $2001    ; disable rendering
  STX $4010    ; disable DMC IRQs

  LDA #$40
  STA $4017    ; disable APU frame IRQ

; INIT OUR TIMER VARIABLES
  LDA #$06
  STA timerLarge
  LDA #$00
  STA timerSmall

  
  LDX #$00
  LDY #$00
;RESET OUR SCORE TO ZERO  
  STX p1ScoreThousands
  STX p1ScoreHundreds
  STX p1ScoreTens
  STX p1ScoreOnes    

 
;SET UP OUR BACKGROUND ATTRIBUTE TABLES
  
  LDA #$20
  STA $2006
  LDA #$00
  STA $2006
  

LoadGameScreenLoop:  
  CPY #$00
  BEQ LoadGameScreen1
  CPY #$01
  BEQ LoadGameScreen2
  CPY #$02
  BEQ LoadGameScreen3
;  LDA mainScreenPt4,X
  JMP PushLoadGameScreen 
 
 LoadGameScreen1:
;  LDA mainScreen,X
  JMP PushLoadGameScreen 
 
 LoadGameScreen2:
 ; LDA mainScreenPt2,X
  JMP PushLoadGameScreen 
 
 LoadGameScreen3:
;  LDA mainScreenPt3,X
  JMP PushLoadGameScreen 
 
 
 
 PushLoadGameScreen:
  
  STA $2007
  INX
  CPX #$E0
  BNE LoadGameScreenLoop

  JSR vblankwaiter
  LDX #$00
  
  INY
  CPY #$05
  BNE LoadGameScreenLoop



;SET UP OUR BACKGROUND ATTRIBUTE TABLES
  LDA #$23
  STA $2006
  LDA #$C0
  STA $2006
  

  
; SET OUR PALEETE UP

; PREP THE PPU FOR PALETTE STUFFS
  LDA #$3F
  STA $2006
  LDA #$00
  STA $2006

;INSERT OUR PALETTE
  LDX #$00
 loadPaletteLoop2:
  LDA palette, X  
  STA $2007
  INX
  CPX #$20
  BNE loadPaletteLoop2 
  
  LDA #$00
  STA curScreen    ; CURRENT SCREEN = 0
  
  
  LDA #%10010000   ; enable NMI, sprites from Pattern Table 1
  STA $2000

  LDA #%00011110   ; enable sprites
  STA $2001 

  RTS


vblankWait:       ; First wait for vblank to make sure PPU is ready
  BIT $2002
  BPL vblankWait
  RTS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SETS UP OUR BACKGROUND SCREEN TILES

gameScreenLinesSky:
  .db $EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB,$EB
  .db $EB,$EB,$D0,$D1,$D2,$D2,$D3,$EB,$E3,$EB,$EB,$D4,$D5,$D6,$D2,$EB,$E6,$E0,$EB,$EB,$D0,$D7,$D8,$D9,$D2,$EB,$E0,$E0,$E0,$E0,$EB,$EB
  
  ; SHEEP 3  TIME 60 SCORE 00000
titleScreenBkgLines1:
  .db $2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A
  .db $2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A
  .db $2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A
  .db $2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A,$2A
  .db $2A,$3F,$2A,$2A,$2A,$3F,$2A,$2A,$2A,$3F,$2A,$2A,$2A,$3F,$2A,$2A,$2A,$3F,$2A,$2A,$2A,$3F,$2A,$2A,$2A,$3F,$2A,$2A,$2A,$3F,$2A,$2A
  .db $3D,$3E,$3D,$3D,$3D,$3E,$3D,$3D,$3D,$3E,$3D,$3D,$3D,$3E,$3D,$3D,$3D,$3E,$3D,$3D,$3D,$3E,$3D,$3D,$3D,$3E,$3D,$3D,$3D,$3E,$3D,$3D
  .db $2A,$3C,$2A,$2A,$2A,$3C,$2A,$2A,$2A,$3C,$2A,$2A,$2A,$3C,$2A,$2A,$2A,$3C,$2A,$2A,$2A,$3C,$2A,$2A,$2A,$3C,$2A,$2A,$2A,$3C,$2A,$2A
  .db $2B,$2C,$2D,$2E,$2F,$30,$31,$32,$33,$34,$2B,$2D,$2B,$2C,$2D,$2E,$2F,$30,$31,$32,$33,$34,$2B,$2D,$2B,$2C,$2D,$2E,$2F,$30,$31,$32
;  .db $26,$26,$26,$26,$26,$28,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$27,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26

titleScreenBkgLines2:
  .db $26,$26,$27,$26,$26,$26,$26,$26,$26,$27,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$29,$26,$26,$27,$26,$26,$26,$26,$26
  .db $26,$28,$26,$26,$26,$26,$27,$26,$26,$26,$26,$26,$28,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$29,$26,$26,$26
  .db $26,$26,$26,$29,$26,$26,$26,$26,$40,$41,$42,$43,$44,$45,$46,$47,$48,$49,$4A,$4B,$4C,$4D,$4E,$4F,$26,$26,$26,$26,$26,$26,$26,$26
  .db $26,$26,$26,$26,$26,$26,$26,$26,$50,$51,$52,$53,$54,$55,$56,$57,$58,$59,$5A,$5B,$5C,$5D,$5E,$5F,$28,$26,$26,$26,$26,$26,$26,$26
  .db $26,$26,$26,$26,$27,$26,$26,$26,$60,$61,$62,$63,$64,$65,$66,$67,$68,$69,$6A,$6B,$6C,$6D,$6E,$6F,$26,$27,$26,$26,$26,$26,$29,$27
  .db $26,$29,$26,$26,$26,$26,$26,$26,$70,$71,$72,$73,$74,$75,$76,$77,$78,$79,$7A,$7B,$7C,$7D,$7E,$7F,$26,$26,$26,$26,$26,$26,$26,$26
  .db $26,$26,$26,$28,$26,$26,$29,$26,$80,$81,$82,$83,$84,$85,$86,$87,$88,$89,$8A,$8B,$8C,$8D,$8E,$8F,$26,$26,$26,$29,$26,$26,$26,$26
  .db $26,$26,$26,$26,$26,$26,$26,$27,$90,$91,$92,$93,$94,$95,$96,$97,$98,$99,$9A,$9B,$9C,$9D,$9E,$9F,$26,$26,$26,$26,$26,$26,$26,$28

titleScreenBkgLines3:
  .db $27,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26
  .db $26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$27,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$27,$26,$26,$26  
  .db $26,$26,$26,$26,$26,$26,$26,$26,$19,$1B,$0E,$1C,$1C,$26,$0A,$26,$1D,$18,$26,$0B,$0E,$10,$12,$17,$26,$26,$26,$26,$26,$26,$26,$26  ;PRESS A TO BEGIN
  .db $26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$29,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26 
  .db $26,$26,$0C,$18,$15,$15,$0E,$0C,$1D,$26,$0F,$15,$18,$18,$0F,$24,$26,$0A,$1F,$18,$12,$0D,$26,$20,$18,$15,$1F,$0E,$1C,$24,$26,$26  ;COLLECT FLOOF! AVOID WOLVES!
  .db $26,$26,$26,$27,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26
  .db $26,$26,$26,$26,$26,$26,$26,$27,$26,$26,$26,$28,$26,$26,$26,$26,$26,$26,$26,$26,$28,$26,$26,$26,$26,$26,$26,$26,$26,$26,$27,$26
  .db $26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26

titleScreenBkgLines4:
  .db $26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$29,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$28
  .db $26,$26,$27,$26,$26,$26,$26,$26,$26,$28,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26
  .db $26,$26,$26,$26,$26,$26,$26,$29,$0B,$22,$26,$1B,$0E,$0F,$1B,$0E,$1C,$11,$26,$10,$0A,$16,$0E,$1C,$26,$26,$26,$26,$26,$26,$26,$26	;BY REFRESH GAMES
  .db $26,$26,$26,$26,$26,$26,$26,$26,$0F,$18,$1B,$26,$0B,$12,$1D,$0B,$12,$1D,$13,$0A,$16,$26,$25,$04,$26,$26,$26,$26,$26,$27,$26,$26 
  .db $26,$28,$26,$29,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26
  .db $26,$26,$26,$26,$27,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$29,$26,$26,$26,$26,$26,$28,$26,$26,$26,$28,$26,$26,$26,$26,$26
  .db $26,$26,$26,$26,$26,$26,$28,$26,$26,$29,$26,$26,$26,$26,$26,$28,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$27,$26
  .db $26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26,$26




;FULHEDGE = $00					; FULHEDGE
;TOPHEDGE = $01					; TOP OF HEDGE
;LFTHEDGE = $02					; LEFT END OF HEDGE
;RGTHEDGE = $03					; RIGHT END OF HEDGE

;VELCROTP = $04					; VELCRO TRAP
;FLOOFBAL = $05					; FLOOFBALL

;LRENEMYS = $06					; LEFT RIGHT SLOW ENEMY
;LRENEMYF = $07					; LEFT RIGHT FAST ENEMY
;UDENEMYS = $08					; UP DOWN SLOW ENEMY
;UDENEMYF = $09					; UP DOWN FAST ENEMY
;FLOWERS1 = $0A					; FLOWER PATCH 1
;FLOWERS2 = $0B					; FLOWER PATCH 2
;BLANKTLE = $0C					; BLANK TILE
;SHEEPSTT = $0E					; SHEEP START POINT
;SHEEPGOL = $0F					; SHEEP GOAL LOCATION

;ONE LEVEL IN 3 BITS
level1a:
  .db FULHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, FULHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, FULHEDGE
  .db FULHEDGE, FLOWERS1, SHEEPSTT, BLANKTLE, BLANKTLE, FLOOFBAL, FLOOFBAL, BLANKTLE, BLANKTLE, FULHEDGE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FLOWERS1, FULHEDGE
  .db FULHEDGE, FLOWERS2, BLANKTLE, FLOWERS1, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, TOPHEDGE, BLANKTLE, BLANKTLE, SHEEPGOL, BLANKTLE, BLANKTLE, FULHEDGE
  .db FULHEDGE, FLOWERS1, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FLOWERS2, BLANKTLE, BLANKTLE, BLANKTLE, FLOWERS1, FLOOFBAL, BLANKTLE, FLOOFBAL, BLANKTLE, FULHEDGE
  .db FULHEDGE, FLOWERS2, BLANKTLE, BLANKTLE, FLOOFBAL, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FULHEDGE, UDENEMYS, FLOOFBAL, BLANKTLE, FLOWERS2, FLOWERS1, FULHEDGE
  .db FULHEDGE, FLOWERS1, BLANKTLE, BLANKTLE, BLANKTLE, LRENEMYS, BLANKTLE, FLOOFBAL, LFTHEDGE, FULHEDGE, RGTHEDGE, BLANKTLE, BLANKTLE, FLOWERS1, FLOWERS2, FULHEDGE
  .db FULHEDGE, FLOWERS2, BLANKTLE, BLANKTLE, BLANKTLE, FLOWERS2, BLANKTLE, BLANKTLE, BLANKTLE, FULHEDGE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FULHEDGE
  .db FULHEDGE, FLOWERS2, BLANKTLE, FLOWERS1, BLANKTLE, BLANKTLE, VELCROTP, BLANKTLE, BLANKTLE, FULHEDGE, BLANKTLE, FLOOFBAL, BLANKTLE, BLANKTLE, BLANKTLE, FULHEDGE  
level1c:
  .db FULHEDGE, FLOOFBAL, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FULHEDGE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FULHEDGE
  .db FULHEDGE, BLANKTLE, FLOWERS1, BLANKTLE, FLOWERS2, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FULHEDGE, BLANKTLE, BLANKTLE, BLANKTLE, BLANKTLE, FLOOFBAL, FULHEDGE
  .db TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE, TOPHEDGE

level1BkgAttributes: ;(2)BR, 2(BL), 2(TR), 2(TL)

  .db %00101010, %00001010, %00001010, %00001010, %10101010, %00001010, %00001010, %10111010  ;08
  .db %10100010, %00000000, %00000000, %00000000, %10001000, %00000000, %00000000, %10001000  ;10
  .db %10100010, %00000000, %00000000, %00000000, %10001000, %00000000, %00000000, %10001000  ;18
  .db %10100010, %00000000, %00000000, %00000000, %10101000, %10101010, %00000000, %10001000  ;20   
  .db %00100010, %00000000, %00000000, %00000000, %10001000, %00000000, %00000000, %10001000  ;28
  .db %10101010, %10101010, %10101010, %10101010, %10101010, %10101010, %10101010, %10101010  ;30
; END ONE LEVEL




palette:
;   PURPLE        ; MENU LEFTSIDE
  .db $00,$2C,$09,$38,$36,$2C,$30,$3C,$0F,$23,$09,$1A,$0F,$27,$06,$37    ;BACKGROUND PALETTE
  .db $29,$01,$3C,$30,$29,$1D,$16,$06,$0F,$1D,$07,$17,$0F,$04,$34,$30    ; SPRITE PALETTE

  
  .bank 1						; bank 1
  .org $FFFA					; START AT $FFFA
  .dw NMI						; JUMP TO THIS LINE WHEN WE ENTER VBLANK
  .dw Init						; WHEN RESET THE NES WILL START AT THIS LABEL
  .dw 0

  .bank 2						; bank 2 - picture data goes here
  .org $0000					; START AT $0000 IN ROM
  .incbin "floofysheepie.chr"   ;includes 8KB graphics file movesprite.chr ROM