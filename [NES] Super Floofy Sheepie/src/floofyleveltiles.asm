realShowTopHedge:  
  LDY #$B4
  STY $2007
  STY $2007
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 
  
  LDY #$C4
  STY $2007
  STY $2007 
  JMP nextLevelPiece
  
realShowFullHedge:
  LDY #$A4
  STY $2007
  STY $2007
  
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 
  
  LDY #$A4
  STY $2007
  STY $2007  
  JMP nextLevelPiece
  
realShowFlowers:
  LDY #$26
  STY $2007
  LDY #$27
  STY $2007
  
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 
  
  LDY #$29
  STY $2007
  LDY #$28
  STY $2007  
  JMP nextLevelPiece  
  
realShowFlowers2:
  LDY #$28
  STY $2007
  STY $2007
  
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 
  
  LDY #$27
  STY $2007
  STY $2007  
  JMP nextLevelPiece 
  
realShowLeftHedge:
  LDY #$26
  STY $2007
  LDY #$B3
  STY $2007
  
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 

  LDY #$26
  STY $2007
  LDY #$C3
  STY $2007  
  JMP nextLevelPiece  

realShowRightHedge:
  LDY #$B5
  STY $2007
  LDY #$26
  STY $2007
  
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 

  LDY #$C5
  STY $2007
  LDY #$26
  STY $2007  
  JMP nextLevelPiece

realShowVelcroTrap:
  LDY #$A8
  STY $2007
  LDY #$A9
  STY $2007
  
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 

  LDY #$B8
  STY $2007
  LDY #$B9
  STY $2007  
  JMP nextLevelPiece

realShowSheepGoal:
  LDY #$AD
  STY $2007
  LDY #$AE
  STY $2007
  
  LDY levelHalf
  STY $2006
  CLC
  ADC #$20
  STA $2006 

  LDY #$BD
  STY $2007
  LDY #$BE
  STY $2007  
  JMP nextLevelPiece
  
realPlaceSheep:
  TXA
  LSR A
  LSR A
  LSR A
  LSR A
  ROL A
  ROL A
  ROL A
  ROL A
  CLC
  ADC #$40  
  STA playerY
  STA playerStartY
  STA playerLastY
  CLC
  SBC #$40
  
  STA temp
  TXA
  CLC

  ROL A
  ROL A
  ROL A
  ROL A
 
  STA playerX
  STA playerStartX
  STA playerLastX
  JMP nextLevelPiece
  
realPlaceFloofBall:
  LDY totalFloofBalls
  INY
  INY
  INY
  INY
  STY totalFloofBalls
  TXA
  LSR A
  LSR A
  LSR A
  LSR A
  ROL A
  ROL A
  ROL A
  ROL A
  CLC
  ADC #$3B
  STA floofBallSprite_Y,Y  
  CLC
  SBC #$3B
  STA temp
  TXA
  CLC
  ROL A
  ROL A
  ROL A
  ROL A
  CLC
  ADC #$04
  STA floofBallSprite_X,Y
  LDA #$01
  STA floofBallSprite_tile,Y
  LDA #$00
  STA floofBallSprite_att,Y
  JMP nextLevelPiece 

realPlaceUDEnemyS:
  LDY totalEnemies
  INY
  INY
  INY
  INY
  STY totalEnemies
  TXA
  LSR A
  LSR A
  LSR A
  LSR A
  ROL A
  ROL A
  ROL A
  ROL A
  CLC
  ADC #$40
  STA enemySprite1_Y,Y
  STA enemySprite2_Y,Y
  ADC #$
  
  JMP nextLevelPiece
  
    

