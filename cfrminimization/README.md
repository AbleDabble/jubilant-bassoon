# Counterfactual regret minimzation
## rps.py
Finds the optimum strategy in rock paper scissors against an oppenent with a specified strategy (might need to change the for 
loop).

## rpsequillibrium.py 
Finds the Nash equillibrium in rock paper scissors when both players are given the same initial strategy (works).

## ColonelBlotto/
Finds the Nash equillibrium in the game Colonel Blotto. Colonel Blotto and his arch-enemy, Boba Fett, are at war.  Each commander hasSsoldiers in total,and each soldier can be assigned to one ofN < Sbattlefields.  Naturally, these commanders do notcommunicate and hence direct their soldiers independently.  Any number of soldiers can be allocatedto  each  battlefield,  including  zero.   A  commander  claims  a  battlefield  if  they  send  more  soldiers  tothe battlefield than their opponent.  The commander’s job is to break down his pool of soldiers intogroups to which he assigned to each battlefield.  The winning commander is the one who claims themost battlefields.  For example, with (S,N) = (10,4) a Colonel Blotto may choose to play (2,2,2,4)while  Boba  Fett  may  choose  to  play  (8,1,1,0).   In  this  case,  Colonel  Blotto  would  win  by  claimingthree of the four battlefields.  The war ends in a draw if both commanders claim the same number ofbattlefields.Write a program where each player alternately uses regret-matching to find a Nash equilibrium forthis  game  withS=  5  andN=  3.   Some  advice:  before  starting  the  training  iterations,  first  thinkabout all the valid pure strategies for one player; then, assign each pure strategy an ID number.  Purestrategies can be represented as strings, objects, or 3-digit numbers:  make a global array of these purestrategies whose indices refer to the ID of the strategy.  Then, make a separate function that returnsthe utility of the one of the players given the IDs of the strategies used by each commander

