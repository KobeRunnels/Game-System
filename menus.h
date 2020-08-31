#define CHOICEX 120
#define CHOICEY 35
/* Types
	1- Slash
	2- Pierce 
	3- Bludgeon
	4- Ranged
	
	5- Spirit
	6- Holy
	7- Darkness
	8- Eclipse
	
	9- Defense
	10- Healing
*/

struct ability // structure for abilities
{
	char name[30];
	int type; // what move type is it?
	int st_cost; // how much stamina does it cost to use the move
	int hp_cost; // how much health does it cost to use the move
	int rank; // what rank ability in its type is it?
	int ammo_cost; // if the ability is a ranged attack, this is the ammo cost
	int damage; // for certain attacks that do a consistent amount of damage 
};

struct weapon // structure for weapons
{
	char name[20];
	int type; // the type of weapon
	struct ability moves[2]; // abilities that come with the weapons
	int ammo;
};

struct character // structure for characters (enemies and players)
{
	char name[20]; // name
	int att; // attack
	int def; // defense
	int agi; // agility
	
	int health; // health
	int maxHealth; // max health
	
	int scars; // scars
	
	int stamina; // stamina
	int maxStamina; // max stamina
	
	int mp; // muscle points
	int maxMP; // max muscle points
	
	bool isBlocking; // is the person blocking?
	int exhaust_counter; // used to keep track of how the time after stamina goes to 0 in combat

	int buffAtt; // in battle this is how much is added onto attack
	int buffDef; // in battle this is how much is added onto defense
	int buffAgi; // in battle this is how much is added onto agility
	
	int eclipseCounter; // number of turns till death when an eclipse spell hits
	struct ability moves[2];
	
	int weakness; // the type weakness of the character
	
	bool changed; // Used to see if the character is in a pure demonic form
	
	int personality; // the personality of the character
	
	int race; // the race
	int type; // the type of demon with the race
	
	int resist; // the type that the character is resistant to
	
	bool scared; // is the enemy scared
	
	bool undead; // is the player undead?
	
	int undeadCounter; // counts how many turns a character is undead, they die at 2

	int maxAtt; // max attack the character can have
	int maxAgi; // max agility the character can have
	int maxDef; // max defense the character can have
	
	bool increasedDef; // checks if defense has increased for that battle
	
	int tiredCounter; // when dungeon crawling
	
	int dayCounter; // current day since the member join
	int maxDayCounter; // max days a member can stay
	
	int conversMeter; // keeps track of if the enemy is in the mood to talk
	
	int rank; // rank with player, used when a creature is a party member
};

/*  Races
	1 - Human
	2 - Ghost
	3 - Demon
	4 - Angel
	5 - Reaper
	6 - Robot
	7 - God
	8 - Concepts
	9 - Fusion
*/

typedef struct party_member // structure for party members
{
	struct character p;
	struct weapon * currentWpn;
	bool hasWeapon;
} member;

int numinParty = 0; // number of characters in the party
member player = {{"",1,1,1,10,10,0,2,2,0,2,false,2,0,0,0,0,{(struct ability){"Punch",3,2,0,0,0,0},{}},0,false,0,9,0,0,false,false,0,3,3,3}, // stores the main character's info
				NULL,false}; // creates current weapon

member totalparty[20]; // array of all party members

struct weapon storage[10]; // array that stores weapons

member * party[3]; // stores the active party member info

int cash = 100; // the amount of cash the player has

int wins = 0; // how many battles the player has won
int loses = 0;  // how many battles the player has lost

int kills = 0; // number of kills 

int enemiesMet = 0; // number of enemies met in combat

int pleased = 0; // number of demons the player has pleased in a conversation
int angered = 0; //  number of demons the player has angered in a conversation

int conversations = 0; // number of conversations the player had with a demon

// universal functions that can be used in and out of combat


void clearBottom(bool isPlayer) // clears output in battles
{
	int x=1;
	int y=10;
	int i;

	for(y=CHOICEY;y<50;y++)
	{
		for(x=0;x<CHOICEX-20;x++) // CHOICEX-20 is battle text
		{
			setColor(G);
			printAt(219,x,y);	
		}	
	}
	if(isPlayer == true)
	{
		for(y=CHOICEY-10;y<50;y++) // menu box
		{
			for(x=CHOICEX;x<CHOICEX+70;x++)
			{
				setColor(G);
				printAt(219,x,y);	
			}	
		}
	}
	setColor(F);			
}

void restoreHealth() // restores health to max
{
	int i;
	
	player.p.health = player.p.maxHealth;
	player.p.stamina = player.p.maxStamina;
	
	for(i=0;i<numinParty;i++)
	{
		totalparty[i].p.health = totalparty[i].p.maxHealth;
		totalparty[i].p.stamina = totalparty[i].p.maxStamina;
	}
};

void equipWeapon(member * chara, int x) // equips weapon c to chara 
{
	chara->hasWeapon = true;
	chara->currentWpn = &storage[x];
}

void removeWeapon(member * chara) // removes weapon
{
	chara->hasWeapon = false;
}

int partySize() // returns number of members in the active party
{
	int a;
	int size = 0;
	for(a=0;a<3;a++)
	{
		if(party[a] != NULL)
			size++;
	}
	return size;
}

void newMember(int position) // used to add a new member
{
	int a;
	
	system("cls");
	printf("\nEnter the new party member's name:");
	scanf("%s",&totalparty[position].p.name);
	if(position < 3)
	{
		for(a=0;a<3;a++)
		{
			if(party[a] == NULL)
			{
				party[a] = &totalparty[position];
				break;
			}
		}
	}
}

bool equippedWeapon(struct weapon * thing) // checks if thing is equipped to a party member or the player
{
	int a;
	if(player.currentWpn == thing) 
		return true;
	return false;
}

bool inParty(member * c) // checks if member c is in the party
{
	int a;
	for(a=0;a<3;a++)
	{
		if(c == party[a])
			return true;
	}
	return false;	
}

void organizeParty() // organizes party
{
	member * temp[3];
	int b = 0;
	int a;
	for(a=0;a<3;a++)
	{
		if(party[a] != NULL)
		{
			temp[b] = party[a];
			b++;
		}
		party[a] = NULL;
	}
	for(a=0;a<b;a++)
	{
		party[a] = temp[a];
	}
}

int pickMember(int x, int y) // gives a menu to pick an active party member
{
	char * names[3];
	int a;
	int b = 0;
	for(a=0;a<3;a++)
	{
		if(party[a] != NULL)
		{
			names[b] = party[a]->p.name;
			b++;
		}
		else
		{
			names[b] = "";
		}
	}
	return giveChoices(names[0],names[1],names[2],"",x,y);
}

void printPartyD() // prints the active party
{
	int x;
	setCursor(50,1);
	printf("PARTY");
	for(x=0;x<3;x++)
	{
		setCursor(50,2+x);
		if(party[x]!=NULL)
		{
			printf("%d %s",x,party[x]->p.name);
		}
	}
}

void partySelection() // for editing the current party
{
	bool done = false;
	int a;
	int select;
	int selecter;
	while(done == false)
	{
		system("cls");
		printf("\nMembers:");
		for(a=0;a<numinParty;a++)
		{
			printf("\n%d - ",a);
			if(inParty(&totalparty[a]) == true)
			{
				printf("IN PARTY: ");
			}
			printf("%s",totalparty[a].p.name);
		}
		printPartyD();
		switch(giveChoices("Remove member from Party","Add member to party","Back","",1,25))
		{
			case 1:
			if(partySize() > 1)
			{
				setCursor(40,25);
				printf("Which member will you remove from the party?");
				select = pickMember(40,26) - 1;
				party[select] = NULL;
				organizeParty();
			}
			else if(partySize() == 1)
			{
				party[0] = NULL;
			}
			else
			{
				printf("\nYou don't have any members currently");
				preEnter();	
			}	
			break;
			case 2:
			if(partySize() == 3 || partySize() == numinParty)
			{
				printf("\nCan't add any more members");
				preEnter();
			}
			else if(numinParty != 0)
			{
				select = valueSlider("Which number member will you add to your party?",0,numinParty-1,30,25);
				if(inParty(&totalparty[select]) == true)
				{
					setCursor(30,27);
					printf("They're already in your party!");
				}
				else
				{
					party[partySize()] = &totalparty[select];
				}
			}
			break;
			case 3:
			done = true;
			break;
		}	
	}
}

void printAbilityLine(struct ability b) // prints on a new line what an ability does
{
	printf("\n%s ",b.name);
	switch(b.type) // prints how many targets the ability can hit
	{
		case 1:
		printf(" - Physical attack that hits all enemies based on current stamina");
		switch(b.rank)
		{
			case 1:
			printf("\nLowers agility of targets by 1");
			break;
		}
		break;
		case 2:
		printf(" - Physical attack that hits one enemy based on attack");
		switch(b.rank)
		{
			case 1:
			printf("\nLowers defense of target by 1");
			break;
		}
		break;
		case 3:
		printf(" - Physical attack that can hit all enemies but cannot reduce their health to 0");
		break;
		case 4:
		printf(" - Physical attack that can hit one enemy");
		break;
		case 5:
		printf(" - Magic attack that deals damage to one target from spirit health");
		break;
		case 6:
		printf(" - Magic attack that deals damage to one target from human health");
		break;
		case 7:
		printf(" - Magic spell that can");
		break;
		case 8:
		break;
		case 9:
		break;
		case 10:
		break;
	}
	printf("\nSTAMINA COST: %d HP COST: %d AMMO: %d",b.st_cost,b.hp_cost,b.ammo_cost);
	printf("\nRANK:%d		SCAR COST TO UPGRADE:%d\n",b.rank,(2+b.rank*6));
}

void printSkills(member p) // prints the skills of a member
{
	int i;
	int a = 0;
	system("cls");
	setCursor(0,0);
	printf("\n%s",p.p.name);
	
	for(i=0;i<2;i++)
	{
		if(p.p.moves[i].st_cost > 0 || p.p.moves[i].hp_cost > 0)
			a++;
	}
	printf("\nCharacter Abilities:");
	for(i=0;i<2;i++)
	{
		if(p.p.moves[i].st_cost > 0 || p.p.moves[i].hp_cost > 0)
			printAbilityLine(p.p.moves[i]);
	}
	if(p.hasWeapon)
	{
		printf("\n\nWeapon Abilities:");
		for(i=0;i<2;i++)
		{
			if(p.currentWpn->moves[i].st_cost > 0 || p.currentWpn->moves[i].hp_cost > 0 || p.currentWpn->moves[i].ammo_cost > 0)
				printAbilityLine(p.currentWpn->moves[i]);
			
		}
	}
	if(a==0)
		printf("\nNONE");
	printf("\n\nScars:%d",p.p.scars);
	
}

void pickMoves(member * c,int pick) // selecting moves to upgrade
{
	int a;
	int b = 0;
	int d = 0;
	char final1[40] = "";
	char final2[40] = "";
	char *info[2] = {"",""};
	
	struct ability * picks[2];
	switch(pick)
	{
		case 1:
		for(a=0;a<2;a++)
		{
			if(c->p.moves[a].type != 0)
			{
				switch(b)
				{
					case 0:
					strcpy(final1,c->p.moves[a].name);
					break;
					case 1:
					strcpy(final2,c->p.moves[a].name);
					break;	
				}
				picks[b] = &c->p.moves[a];
				b++;
			}
		}
		break;
		case 2:
		for(a=0;a<2;a++)
		{
			if(c->currentWpn->moves[a].type != 0)
			{
				switch(b)
				{
					case 0:
					strcpy(final1,c->currentWpn->moves[b].name);
					break;
					case 1:
					strcpy(final2,c->currentWpn->moves[b].name);
					break;	
				}
				picks[b] = &c->currentWpn->moves[b];
				b++;
			}	
		}	
		break;
	}
	if(b== 2)
		d = giveChoices(final1,final2,"Quit","",1,30);
	else
		d = giveChoices(final1,"Quit","","",1,30);	
	if(!((b == 1 && d==2) ||(b==2 && d==3)))
	{
		if((picks[d-1]->rank)*6+2 <= c->p.scars)
		{
			c->p.scars -= picks[d-1]->rank*6+2;	
			picks[d-1]->rank++;
			
			if(picks[d-1]->type == 4)
			{
				switch(picks[d-1]->rank)
				{
					case 1:
					picks[d-1]->damage = 5;
					picks[d-1]->ammo_cost = 4;
					break;
					case 2:
					picks[d-1]->damage = 10;
					picks[d-1]->ammo_cost = 1;
					picks[d-1]->st_cost = 5;
					break;
					case 3:
					picks[d-1]->ammo_cost = 4;
					picks[d-1]->damage = 10;
					picks[d-1]->st_cost = 5;
					break;
					case 4:
					picks[d-1]->ammo_cost = 1;
					picks[d-1]->damage = 10;
					picks[d-1]->st_cost = 8;
					break;
					case 5:
					picks[d-1]->ammo_cost = 8;
					picks[d-1]->damage = 15;
					picks[d-1]->st_cost = 10;
					break;
					case 6:
					picks[d-1]->ammo_cost = 1;
					picks[d-1]->damage = 20;	
					picks[d-1]->st_cost = 20;
					break;	
				}
			}
			if(picks[d-1]->st_cost>0)
				picks[d-1]->st_cost++;
			if(picks[d-1]->hp_cost>0)
				picks[d-1]->hp_cost++;
		} 
		else
		{
			printf("\nYou don't have enough");
			preEnter();
		}
	}
}

void changeMoves(member * p) // when leveling up moves in the menu
{
	int choice;
	int b;
	
	printSkills(*p);
	setCursor(1,28);
	printf("Which type of move will you upgrade?");
	if(p->hasWeapon == true)
		choice = giveChoices("Character Abilities","Weapon Abilities","Quit","",1,30);
	else
		choice = giveChoices("Character Abilities","Quit","","",1,30);
	clearBottom(false);
	if((p->hasWeapon == true && choice != 3 ) || (p->hasWeapon== false && choice != 2))
	{
		printSkills(*p);
		printf("\nWhich move will you upgrade?");
		pickMoves(p,choice);
	}
}

int weaponsInEquipment()
{
	int i;
	int a;
	char * thing;
	for(i=0;i<10;i++)
	{
		thing = NULL;
		switch(storage[i].type)
		{
			case 1:
			thing = "TYPE: SLASH";
			break;
			case 2:
			thing = "TYPE: PIERCE";
			break;
			case 3:
			thing = "TYPE: BLUDGEON";
			break;
			case 4:
			thing = "TYPE: RANGED";
			break;
		}
		if(thing != NULL)
		{
			a++;
		}	
	}	
	return a;	
}

void printWeapons() // prints all weapons in storage
{
	int i;
	char * thing;
	for(i=0;i<10;i++)
	{
		thing = NULL;
		switch(storage[i].type)
		{
			case 1:
			thing = "TYPE: SLASH";
			break;
			case 2:
			thing = "TYPE: PIERCE";
			break;
			case 3:
			thing = "TYPE: BLUDGEON";
			break;
			case 4:
			thing = "TYPE: RANGED";
			break;
		}
		if(thing != NULL)
		{
			printf("\n%d - %s\t%s",i,storage[i].name,thing);
			if(equippedWeapon(&storage[i]) == true)
				printf(" EQUIPPED");
		}
	}
}

void equipNewWeapon() // for equipping a party member with a weapon
{
	int val;
	if(partySize() >= 1)
	{
		system("cls");
		printf("\nWho will you equip a weapon to?");
		switch(giveChoices(player.p.name,"a party member","","",1,1))
		{
			case 1:
			system("cls");
			break;
			case 2:
			system("cls");
			printf("\nWhich member will you equip a weapon to?");
			val = pickMember(1,1);
			break;
		}	
	}
	else
	{
		printWeapons();
		val = valueSlider("Which # weapon will you equip?",0,weaponsInEquipment()-1,1,20);
		equipWeapon(&player,val);
	}
}

void menu() // out of combat menu
{
	bool done2 = false;
	bool done3;
	int choice, choice2;
	
	char * names[4] = {"","","",""}; // for holding strings for options
	
	int a;
	int b;
	int c;
	int d;
	
	while(done2 != true)
	{
		done3 = false;
		system("cls");
		choice = giveChoices("Spend Scars","Organize Party","Organize Weapons","Go Back",2,10);
		switch(choice)
		{
			case 1:
			while(done3 != true)
			{
				system("cls");
				printf("\n\nScars:%d\nMax Health:%d",player.p.scars,player.p.maxHealth);
				choice2 = giveChoices("Raise Max Health","Upgrade Abilities","Go back","",2,10);
				switch(choice2)
				{
					case 1:
					system("cls");
					printf("\n%s\nScars:%d\nMax Health:%d",player.p.name,player.p.scars,player.p.maxHealth);
					a = valueSlider("How much do you want to increase your max health? (1 point = 2 scars)",0,player.p.scars/2,1,10);
					if(a != 0)
					{
						player.p.scars -= a*2;
						player.p.maxHealth+=a;
						restoreHealth();
					}
					for(b=0;b<numinParty;b++)
					{
						system("cls");
						printf("\n%s\nScars:%d\nMax Health:%d",totalparty[b].p.name,totalparty[b].p.scars,totalparty[b].p.maxHealth);
						a = valueSlider("How much do you want to increase your max health? (1 point = 2 scars)",0,totalparty[b].p.scars/2,1,10);
						if(a != 0)
						{
							totalparty[b].p.scars -= a*2;
							totalparty[b].p.maxHealth+=a;
							restoreHealth();
						}
					
					}
					break;
					case 2:
					names[0] = player.p.name;
					for(b=0;b<numinParty;b++)
					{
						names[b+1] = totalparty[b].p.name;
					}
					system("cls");
					printf("\nWhich member will have their moves changed?");
					d = giveChoices(names[0],names[1],names[2],names[3],1,3);
					switch(d)
					{
						case 1:
						changeMoves(&player);
						break;
						default:
						break;
					}
					break;
					case 3:
					done3 = true;
					break;
				}
			}	
			break;
			case 2:
			system("cls");
			partySelection();
			break;
			case 3:
			system("cls");
			switch(giveChoices("Equip Weapon","Look at weapons","Go Back","",2,10))
			{
				case 1:
				equipNewWeapon();	
				break;
				case 2:
				system("cls");
				printWeapons();
				preEnter();
				break;
				case 3:
				break;
			}
			break;
			case 4:
			done2 = true;
			break;
				
		}
	}
}

