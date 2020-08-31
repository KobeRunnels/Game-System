#include "battle.h"

int main()
{
	srand((unsigned)time(NULL));
	
	player.p.scars = 6;
	
	hideCursor();
	
	int input;
	int battlers = 0;
	
	bool done1,done2,done3;
	
	int a = 0;
	int b;
	
	setUpParty();
	
	int choice, choice2;
	storage[0] = (struct weapon){"Bronze Gunblade",1,
	{(struct ability){"Slash",1,2,0,0},(struct ability){"Fire Bullet",4,0,0,0,1,5}},3};
	equipWeapon(&player,0);
	
	storage[1] = (struct weapon){"Bronze Pistol",4,
	{(struct ability){"Fire Bullet",4,0,0,0,1,5},{}},3};
	
	equipWeapon(&player,0);
	
	printf("\nEnter a character's name:");
	scanf("%s",&player.p.name);
	
	while(done1 != true)
	{
		PlaySound(NULL, 0, 0);
		done3 = false;
		done2 = false;
		done1 = false;
		system("cls");
		partyStats();
		printf("\nCash:%d",cash);
		printf("\nKills:%d",kills);
		
		input = giveChoices("Battle","About Battles","Menu","Quit",2,13);
		if(input == 1)
		{
			a = valueSlider("How many enemies do you want to face?",1,8,2,20);
      		switch(battle(a,0))
			{
				case 0:
				system("cls");
				PlaySound(TEXT("SCOST/Battle/Heated Moment.wav") , NULL,  SND_LOOP | SND_ASYNC);
				printf("\nYou lost...");
				preEnter();
				
				loses+=1;
				break;
				case 1:
				b = rand()%(a*10)+10;	
				system("cls");
				PlaySound(TEXT("SCOST/Battle/We Won.wav") , NULL,  SND_LOOP | SND_ASYNC);
				printf("\nYou won!");
				printf("\nYou earned %d cash",b);
				cash+=b;
				preEnter();
				
				wins+=1;
				break;
			}
			restoreHealth();
		}
		else if(input == 2)
		{
			system("cls");
			printf("\nCombat is turn based with you spending stamina to perform actions.");
			printf("\n\nYour attack increases as you deal damage which is converted into muscle points.");
			printf("\nWhen your muscle points hit a certain cap, your attack stat will increase.");
			printf("\n\nYour defense increases whenever you have 1/2 your max health and you will earn a scar.");
			printf("\nthis will also decrease your max health by 1.");
			printf("\n\nYour agility increases whenever you run out of stamina in battle.");
			printf("\n\nYou can regain lost max health or learn new abilities through spending the scars you earned.");
			preEnter();
			
		}
		else if(input == 3)
			menu();
		else
			done1 = true;
		battlers++;
	}
	
	return 0;
}
