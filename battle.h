#include "monsterImages.h"
#include "menus.h"

// battle functions

int value = 0; //used to pick what the background is for a battle

void partyStats() // prints party stats in combat
{
	int i;
	
	int statsX;
	int statsY;
	
	setCursor(0,0);
	printf("%s",player.p.name);
	printf("\nHP:%d/%d   ",player.p.health,player.p.maxHealth);  
	printf("\nStamina:%d/%d   ",player.p.stamina,player.p.maxStamina);
	
	printf("\nAttack:%d",player.p.att);
	if(player.p.buffAtt != 0)
		printf(" + %d",player.p.buffAtt);
	if(player.p.att == player.p.maxAtt)
		printf(" MAX");
	
	printf("\nDefense:%d",player.p.def);
	if(player.p.buffDef != 0)
		printf(" + %d",player.p.buffDef);
	if(player.p.def == player.p.maxDef)
		printf(" MAX");
	
	printf("\nAgility:%d",player.p.agi);
	if(player.p.buffAgi != 0)
		printf(" + %d",player.p.buffAgi);
	if(player.p.agi == player.p.maxAgi)
		printf(" MAX");
	
	if(player.p.isBlocking == true)
		printf("\nBlocking");
	else if(player.p.stamina <= 0)
		printf("\nExhausted");
	else
		printf("\n            ");
	
	for(i=0;i<3;i++)
	{
		if(party[i] != NULL)
		{
			setCursor(21*(i+1),0);
			printf("%s",party[i]->p.name);
			setCursor(21*(i+1),1);
			printf("HP:%d/%d   ",party[i]->p.health,party[i]->p.maxHealth);
			setCursor(21*(i+1),2);
			printf("Stamina:%d/%d   ",party[i]->p.stamina,party[i]->p.maxStamina);
			setCursor(21*(i+1),3);
			printf("Attack:%d",party[i]->p.att);
			if(party[i]->p.buffAtt != 0)
				printf(" + %d",party[i]->p.buffAtt);	
			setCursor(21*(i+1),4);
			printf("Defense:%d",party[i]->p.def);
			if(party[i]->p.buffDef != 0)
				printf(" + %d",party[i]->p.buffDef);
			setCursor(21*(i+1),5);
			printf("Agility:%d",party[i]->p.def);
			if(party[i]->p.buffAgi != 0)
				printf(" + %d",party[i]->p.buffAgi);
				
			setCursor(21*(i+1),6);
			if(party[i]->p.isBlocking == true)
				printf("Blocking");
			else if(party[i]->p.stamina <= 0)
				printf("Exhausted");
			else
				printf("            ");
		}	
	}
}

int printBackground(int value) // prints battle background
{
	int x,y;
	// behind enemies
	for(y=7;y<CHOICEY;y++)
	{
		for(x=0;x<CHOICEX-20;x++)
		{
			switch(value)
			{
				case 3:
				if(x%10 == y%10)
					setColor(A);
				else if(x%2==0)
					setColor(1);	
				break;
				case 2:
				if(x%3 == 0)
					setColor(B);
				else if(x%2 == 0)
					setColor(4);
				else
					setColor(F);	
				break;
				case 1:
				if(x%2 == 0)
					setColor(1);
				else
					setColor(2);
				break;
			}
			printAt(219,x,y);
		}
	}
	// border patterns
	for(y=0;y<50;y++)
	{
		for(x=CHOICEX-20;x<CHOICEX-1;x++)
		{
			switch(value)
			{
				case 3:
				setColor(D);
				break;
				case 2:
				setColor(C);
				break;
				case 1:
				setColor(2);
				break;
			}
			printAt(219,x,y);
		}
	}
	for(y=7;y<CHOICEY-10;y++)
	{
		for(x=CHOICEX-20;x<CHOICEX+90;x++)
		{
			switch(value)
			{
				case 3:
				setColor(E);
				break;
				case 2:
				setColor(D);
				break;
				case 1:
				setColor(4);
				break;
			}
			printAt(219,x,y);
		}
	}
	setColor(F);
	return 1;
}

void deleteSprite(struct character *en, int enemies, int pos, int value) // deletes sprite when an enemy is down
{
	int x,y;
	switch(pos) // coords for enemy sprites
	{
		case 0:
		x = 10;
		y = 15;
		break;
		case 1:
		x = 30;
		y = 15;
		break;
		case 2:
		x = 50;
		y = 15;
		break;
		case 3:
		x = 70;
		y = 15;
		break;
		case 4:
		x = 10;
		y = 10;
		break;
		case 5:
		x = 30;
		y = 10;
		break;
		case 6:
		x = 50;
		y = 10;
		break;
		case 7:
		x = 70;
		y = 10;
		break;
	}
	
	clearEnemy(en[pos].type,en[pos].race,x,y,value);
}

void printBattle(bool firstTime, bool *thing, struct character *en, int enemies, int val) // print monster sprites
{
	int x,y;
	int a;
	int i;
	bool clearFront = false;
	bool clearBack = false;
	
	if(firstTime == true)
		value = printBackground(val);
	for(a=enemies-1;a>= 0;a--)
	{
		switch(a) // coords for enemy sprites
		{
			case 0: // front row
			x = 10;
			y = 15;
			break;
			case 1:
			x = 30;
			y = 15;
			break;
			case 2:
			x = 50;
			y = 15;
			break;
			case 3:
			x = 70;
			y = 15;
			break;
			case 4: // back row
			x = 10;
			y = 10;
			break;
			case 5:
			x = 30;
			y = 10;
			break;
			case 6:
			x = 50;
			y = 10;
			break;
			case 7:
			x = 70;
			y = 10;
			break;
		}
		if(en[a].health > 0 && thing[a] == true && firstTime == true)
			printEnemy(en[a].type,en[a].race,x,y);
		else if(thing[a] == true && en[a].health <= 0)
		{
			deleteSprite(en,enemies,a,value);
			if(a <= 3 && en[a+4].health > 0) // prints back row enemy if the enemy deleted is in the front
			{
				printEnemy(en[a+4].type,en[a+4].race,x,10);	
			}
			else if(a > 3 && en[a-4].health > 0)
			{
				printEnemy(en[a-4].type,en[a-4].race,x,15);		
			}	
			thing[a] = false;
		}
	}
	setCursor(0,CHOICEY-1); // prints spacer between sprites and text
	
	for(i=0;i<CHOICEX-20;i++)
	{
		printf("-");
	}
}

void battleStats(int *rankings, struct character *e,int enemies) // updates the stats of every current character in a battle
{
	int i;
	int a = 1;
	
	bool back = false; // if printing backrow
	
	partyStats();
	for(i = 0;i<enemies;i++) // prints enemy health
	{
		if(enemies > 4 && i == 4)
		{
			a=1;
			setCursor(CHOICEX+35,a);
			printf("Back:");
			back = true;
			a++;
		}
		else if(i == 0 && enemies > 4)
		{
			setCursor(CHOICEX,a);
			printf("Front:");
			a++;
		}
		
		
		if(back == true)
			setCursor(CHOICEX+35,a);
		else
			setCursor(CHOICEX,a);

		rankings[i] = i;
		if(e[i].health > 0)
		{
			printf("%s HP:%d/%d",e[i].name,e[i].health,e[i].maxHealth);	
			if(e[i].stamina <= 0)
				printf(" Exhausted");
			else if(e[i].isBlocking == true)
				printf(" Blocking");
			else
				printf("            ");
		}
		else
			printf("                                 "); 
		a++;
	}
		
}

void changeBuff(struct character *c, int value, int type) // 1- attack 2- defense 3- agility
{
	switch(type)
	{
		case 1: // atttack
		c->buffAtt = c->buffAtt+value;	
		if(c->buffAtt < -3)
			c->buffAtt = -3;
		else if(c->buffAtt > 3)
			c->buffAtt = 3;
		break;
		case 2: // defense
		c->buffDef = c->buffDef+value;	
		if(c->buffDef < -3)
			c->buffDef = -3;
		else if(c->buffDef > 3)
			c->buffDef = 3;
		break;
		case 3: // agility
		c->buffAgi = c->buffAgi+value;	
		if(c->buffAgi < -3)
			c->buffAgi = -3;
		else if(c->buffAgi > 3)
			c->buffAgi = 3;
		break;
	}
}

void blockUp(struct character *c) // when a character puts their guard up to block
{
	setCursor(1,CHOICEY-1);
	printf("\n%s prepares for incoming attacks",c->name);
	c->isBlocking = true;	
}

void exhausted(struct character *e) // shows when a character has no stamina and reduces their counter till they regain stamina
{
	setCursor(1,CHOICEY-1);
	e->exhaust_counter -=1;
	if(e->exhaust_counter == 0)
	{
		printf("\n%s got back up.",e->name);
		e->exhaust_counter = 2;
		if(e->agi < e->maxAgi)
		{	
			e->agi+=1;
			e->maxStamina = e->agi+e->def;
		}
		e->stamina = e->maxStamina;
		preEnter();
		changeBuff(e,-1,1);
		changeBuff(e,-1,2);
		changeBuff(e,-1,3);
		clearBottom(false);	
		e->tiredCounter++;
	}
}	

bool enemiesDown(struct character *e, int enemies) // checks if all enemies are down
{
	bool enemiesDown = false;
	int downed = 0;
	int i;
	
	for(i = 0;i<enemies;i++)
	{
		if(e[i].health <= 0)
			downed++;
	}
	if(downed == enemies)
		enemiesDown = true;
	return enemiesDown;
}

int enemiesAlive(struct character *e, int enemies)
{
	int alive = 0;
	int i;
	
	for(i = 0;i<enemies;i++)
	{
		if(e[i].health > 0)
			alive++;
	}
	return alive;
}

int partyMembersAlive() // returns number of party members alive
{
	int i;
	int down = 0;
	for(i=0;i<3;i++)
	{
		if(party[i] != NULL && party[i]->p.health > 0)
			down++;
	}
	return down;
}

void increaseMuscle(int damage, struct character *e) // increases muscle points and attack if muscle points equal max
{
	if(e->att < e->maxAtt)
	{
			e->mp +=damage;
		if(e->mp >= e->maxMP)
		{
			printf("\n\n%s got stronger!\n",e->name);
			e->mp = 0;
			e->maxMP = e->maxMP*e->maxMP;
			e->att+=1;
		}
	}
}

void charaBlock(int type, int damage, struct character *c, struct character *e) // when character c is blocking, takes away stamina and checks if they have any left
{
	int defense = c->def+c->buffDef;
	
	if(defense <= 0)
		defense = 0;
	
	damage-=defense;
	
	if(damage <= 0)
		damage = 1;
	
	changeBuff(e,-1,1);
	c->stamina -= damage;
	printf("\n%s blocks the attack and takes %d damage in stamina",c->name,damage);
	if(c->stamina < 0)
		c->exhaust_counter = 3;
	if(type != 4)
		increaseMuscle(damage,e);
}

void increaseDef(struct character * c)
{
	if((c->health <= c->maxHealth/2) && c->increasedDef == false)
	{
		if(c->def < c->maxDef)
		{
			c->def++;
			c->scars++;
			c->maxHealth -= 1;
			c->increasedDef = true;
		}
		else
		{
			c->increasedDef = true;
			c->scars++;
			c->maxHealth -= 1;
		}
	}
}

void charStamDamage(int sdamage, struct character * c) // stamina damage
{
	int defense = c->def+c->buffDef; // calculates defense against attack
	
	if(defense <= 0)
		defense = 0;
	
	sdamage-=defense;
	if(sdamage <= 0) // makes 1 in case the damage is less than 0
		sdamage = 1;
	c->stamina -= sdamage;
	printf("\n%s took %d stamina damage",c->name,sdamage);
}

void charaDamage(int damage, int type, struct character *c, struct character *e,bool isPlayer) // deals damage to character c from user and increases e's muscle points
{
	int defense = c->def+c->buffDef; // calculates defense against attack
	int sdamage = damage; // stamina damage for bludgeon moves
	
	if(defense <= 0)
		defense = 0;
	
	sdamage-=defense;
	damage-=defense;
	
	if(type == 3 && damage >= c->health) 
		damage = rand()%3+1;
	
	if(type == c->weakness && type != 0 && c->isBlocking == false)
	{
		printf("\n%s was weak against the attack and lost stamina",c->name);
		c->stamina -= (int)(c->stamina/2);
	}
	else if(type == c->resist && type != 0 && c->isBlocking == false)
	{
		printf("\n%s was resistant against the attack",c->name);
		damage = (int)(damage/2);
	}
	
	if(damage <= 0) // makes 1 in case the damage is less than 0
		damage = 1;
	if(sdamage <= 0) // makes 1 in case the damage is less than 0
		sdamage = 1;
	if(c->stamina <= 0) // doubles damage if the enemy is down
		damage*=2;
	
	if(c->isBlocking == false && damage >= c->health) // sound effect
		Beep(400,200);
	else
		Beep(300,200);
		
	if((c->isBlocking == false || c->stamina <=0) || (c->isBlocking == true && c->stamina <= 0))
	{
		c->health -= damage;
		if(type == 3)
			c->stamina -= sdamage;
		printf("\n%s took %d damage",c->name,damage);
		if(type == 3)
		{
			printf(" and %d in stamina damage",sdamage);
		}
	}	
	else
		charaBlock(type, damage,c,e);
		
	if(c->health <= 0)
	{
		printf("\n%s was defeated.",c->name);
		if(isPlayer == true)
			kills++;
	}
	increaseDef(c);
	if(type != 4) // makes sure the character can't earn muscle points from ranged attacks
	{
		if(type == 3)
			increaseMuscle(2*damage,e);
		else
			increaseMuscle(damage,e);
	}
}

bool partyMoveType(member *z, int t, bool hasWeapon) // returns if a player character has an ability of type t
{
	int i;
	for(i=0;i<2;i++)
	{
		if(z->p.moves[i].type == t)
			return true;
	}
	if(hasWeapon == true)
	{
		for(i=0;i<2;i++)
		{
			if(z->currentWpn->moves[i].type == t)
				return true;
		}
	}
	return false;
}

bool hasMoveType(struct character z, int t) // returns if a character has an ability of type t they can use
{
	int i;
	for(i=0;i<2;i++)
	{
		if(z.moves[i].type == t && ((z.stamina >= z.moves[i].st_cost 
		&& z.moves[i].st_cost != 0) || (z.health >= z.moves[i].hp_cost && z.moves[i].hp_cost != 0)))
			return true;
	}
	return false;
}

int moveLocation(struct character z, int t) // returns location of move type t for enemy AI
{
	int i;
	for(i=0;i<2;i++)
	{
		if(z.moves[i].type == t)
			return i;
	}
	return 0;
}

int exhaustedMember() // returns which party member is exhausted for enemy AI
{
	int i;
	if(player.p.stamina <= 0)
		return 1;
	else if(numinParty > 0)
	{
		for(i=0;i<3;i++)
		{
			if(party[i] != NULL && party[i]->p.stamina <= 0)
				return i+2;
		}
	}	
	return 0;
}

struct character * picEnemy(struct character *c,int enemies, bool frontOrBack) // for selecting enemies in combat to attack with an ability
{
	int picky;
	int i;
	int a = 0;
	
	char *choices[4] = {"","","",""};
	
	struct character * picks[4];
	
	if(frontOrBack == false || enemiesAlive(c,enemies) < 5)
	{	
		for(i=0;i<enemies;i++)
		{
			if(c[i].health > 0)
			{
				choices[a] = c[i].name;
				picks[a] = &c[i];
				a++;
			}
		}
	}
	else
	{
		switch(giveChoices("Front Row","Back Row","","",CHOICEX+30,CHOICEY+5))
		{
			case 1:
			for(i=0;i<4;i++)
			{
				if(c[i].health > 0)
				{
					choices[a] = c[i].name;
					picks[a] = &c[i];
					a++;
				}
			}
			break;
			case 2:
			for(i=4;i<enemies;i++)
			{
				if(c[i].health > 0)
				{
					choices[a] = c[i].name;
					picks[a] = &c[i];
					a++;
				}
			}	
			break;
		}
	}
	picky = giveChoices(choices[0],choices[1],choices[2],choices[3],CHOICEX+60,CHOICEY+5);
	return picks[picky-1];
}

void useAbilities(const struct ability thing, struct character *user, int enemies, struct character *receiver, bool isPlayer) // used to execute abilities in combat by both enemies and player characters
{
	int i;
	int damage;
	int value;
	
	struct character *target;
	
	bool foundTarget = false;
	
	srand((unsigned)time(NULL));
	
	setCursor(1,CHOICEY);
	switch(thing.type)
	{
		case 1: // slash
		damage = rand()%(user->stamina)+1;
		
		if((isPlayer == false && numinParty > 0) || (isPlayer == true && enemies > 1))
			printf("\n%s slashes %s and their party",user->name,receiver->name);	
		else
			printf("\n%s slashes %s",user->name,receiver->name);
		if(isPlayer == true) // if it's a player character using slash
		{
			if(enemies > 4 && enemiesAlive(receiver,enemies) > 4)
			{
				for(i=0;i<4;i++)
				{
					damage = rand()%(user->stamina)+1;
					if(receiver[i].health > 0 && i < enemies)
					{
						charaDamage(damage,1,&receiver[i],user,isPlayer);	
						switch(thing.rank)
						{
							case 1:
							changeBuff(&receiver[i],-1,2);
							break;
							case 4:
							changeBuff(&receiver[i],-2,2);	
							break;
						}
					}
				}
			}
			else
			{
				for(i=0;i<enemies;i++)
				{
					damage = rand()%(user->stamina)+1;
					if(receiver[i].health > 0 && i < enemies)
					{
						charaDamage(damage,1,&receiver[i],user,isPlayer);	
						switch(thing.rank)
						{
							case 1:
							changeBuff(&receiver[i],-1,2);
							break;
							case 4:
							changeBuff(&receiver[i],-2,2);	
							break;
						}
					}
				}
			}
		}
		else // if it's the enemy using slash
		{
			if(receiver->health > 0)
			{
				charaDamage(damage,1,receiver,user,isPlayer);		
				switch(thing.rank)
				{
					case 1:
					changeBuff(receiver,-1,2);
					break;
					case 2:
					charStamDamage((int)(damage/2),receiver);
					break;
					case 3:
					changeBuff(receiver,-2,2);	
					break;
				}
			}
			for(i = 0;i<3;i++)
			{
				damage = rand()%(user->stamina)+1;
				if(party[i] != NULL && party[i]->p.health > 0)
				{
					charaDamage(damage,1,&party[i]->p,user,isPlayer);
					switch(thing.rank)
					{
						case 1:
						changeBuff(&party[i]->p,-1,2);
						break;
						case 4:
						changeBuff(&party[i]->p,-2,2);
						break;
					}
				}
			}
		}
		break;
		case 2: // pierce
		damage = rand()%(user->att+user->buffAtt)+1;
		target = receiver;			
		if(isPlayer == true) // if it's the player using pierce and selects a target
		{
			target = picEnemy(receiver,enemies,false);
		}
		else if(numinParty != 0) // for when the enemy selects a target
		{ 
			while(foundTarget == false)
			{
				switch(rand()%2+1)
				{
					case 1:
					target = receiver;
					if(player.p.health > 0)
						foundTarget = true;
					break;
					case 2:
					i=rand()%3;
					target = &party[i]->p;
					if(party[i]->p.health > 0 && party[i] != NULL)
						foundTarget = true;
					break;	
				}
			}
		}		
		setCursor(1,CHOICEY);
		printf("\n%s lunges at %s",user->name,target->name);
		charaDamage(damage,2,target,user,isPlayer);
		switch(thing.rank)
		{
			case 1:
			changeBuff(target,-1,3);
			break;
			case 2:
			changeBuff(target,-2,3);
			break;
			case 3:
			changeBuff(target,-1,2);
			changeBuff(target,-1,1);
			break;
			case 4:
			changeBuff(target,-1,1);
			changeBuff(target,-1,2);
			changeBuff(target,-1,3);
			break;
			case 5:
			value = rand()%damage+1;
			printf("\n%s gained %d health",user->name,value);
			user->health+=damage;
			if(user->health > user->maxHealth)
				user->health = user->maxHealth;	
			break;
		}
		break;
		case 3: // bludgeon
		damage = rand()%3+1;
		if(thing.rank%2==1) // if the move is a kick move
		{
			if((isPlayer == false && numinParty > 0) || (isPlayer == true && enemies > 1))
				printf("\n%s kicks %s and their party",user->name,receiver->name);	
			else
				printf("\n%s kicks %s",user->name,receiver->name);
			if(isPlayer == true) // if a player character is performing kick
			{
				if(enemies > 4 && enemiesAlive(receiver,enemies) > 4) // hits front row if there is a completely front row
				{
					for(i=0;i<4;i++)
					{
						damage = rand()%3+1;
						if(receiver[i].health > 0 && i < enemies)
						{
							charaDamage(damage,3,&receiver[i],user,isPlayer);	
							switch(thing.rank)
							{
								case 3:
								changeBuff(&receiver[i],-1,3);
								break;
								case 5:
								changeBuff(&receiver[i],-1,1);
								changeBuff(&receiver[i],-1,2);
								changeBuff(&receiver[i],-1,3);
								break;
							}
						}
					}
				}
				else
				{
					for(i=0;i<enemies;i++)
					{
						damage = rand()%3+1;
						if(receiver[i].health > 0 && i < enemies)
						{
							charaDamage(damage,3,&receiver[i],user,isPlayer);	
							switch(thing.rank)
							{
								case 3:
								changeBuff(&receiver[i],-1,3);
								break;
								case 5:
								changeBuff(&receiver[i],-1,1);
								changeBuff(&receiver[i],-1,2);
								changeBuff(&receiver[i],-1,3);
								break;
							}
						}
					}
				}
			}
			else // if the enemy is performing kick
			{
				if(receiver->health > 0)
				{
					switch(thing.rank)
					{
						case 3:
						changeBuff(receiver,-1,3);
						break;
						case 5:
						changeBuff(receiver,-1,1);
						changeBuff(receiver,-1,2);
						changeBuff(receiver,-1,3);
						break;
					}
					charaDamage(damage,3,receiver,user,isPlayer);
				}
				for(i = 0;i<3;i++)
				{
					damage = rand()%3+2;
					if(party[i] != NULL && party[i]->p.health > 0)
					{
						switch(thing.rank)
						{
							case 3:
							changeBuff(&party[i]->p,-1,3);
							break;
							case 5:
							changeBuff(&party[i]->p,-1,1);
							changeBuff(&party[i]->p,-1,2);
							changeBuff(&party[i]->p,-1,3);
							break;
						}
						charaDamage(damage,3,&party[i]->p,user,isPlayer);
					}
				}
			}
		}
		else // if it is a punching move
		{
			target = receiver;			
			if(isPlayer == true) // if it's the player using pierce and selects a target
			{
				target = picEnemy(receiver,enemies,false);
			}
			else if(numinParty != 0) // for when the enemy selects a target
			{ 
				while(foundTarget == false)
				{
					switch(rand()%2+1)
					{
						case 1:
						target = receiver;
						if(player.p.health > 0)
							foundTarget = true;
						break;
						case 2:
						i=rand()%3;
						target = &party[i]->p;
						if(party[i]->p.health > 0 && party[i] != NULL)
							foundTarget = true;
						break;	
					}
				}
			}		
			setCursor(1,CHOICEY);
			if(thing.rank == 4)
				damage = rand()%user->att+1;
			printf("\n%s punches %s",user->name,target->name);
			charaDamage(damage,3,target,user,isPlayer);
			switch(thing.rank)
			{
				case 2:
				changeBuff(receiver,-1,1);
				break;
				case 4:
				changeBuff(receiver,-1,1);
				changeBuff(receiver,-1,2);
				break;
			}
		}
		break;
		case 4: // ranged
		switch(thing.rank)
		{
			case 4:
			changeBuff(receiver,-1,1);	
			case 2:
			changeBuff(receiver,-1,2);	
			case 0:
			damage = thing.ammo_cost*thing.damage;
			if(isPlayer == true)
				target = picEnemy(receiver,enemies,true);
			printf("\n%s fired a projectile at %s",user->name,receiver->name);
			charaDamage(damage,4,target,user,isPlayer);
			break;
			case 6:
			changeBuff(user,1,2);	
			case 5:
			case 1:
			damage = thing.ammo_cost*thing.damage;
			printf("\n%s fired a projectile at the enemies",user->name);
			for(i=0;i<thing.ammo_cost;i++)
			{
				if(receiver[i].health > 0 && i < enemies)
					charaDamage(damage,4,&receiver[i],user,isPlayer);
			}
			break;
		}
		break;
		
	}
	
	user->stamina-=thing.st_cost;
	user->health-=thing.hp_cost;
}

bool anyAbilities(member c) // checks if any abilities can be used
{	
	int a = 0;
	int i;
	for(i=0;i<2;i++)
	{
		if((c.p.stamina >= c.p.moves[i].st_cost && c.p.moves[i].st_cost != 0) 
		|| (c.p.health >= c.p.moves[i].hp_cost && c.p.moves[i].hp_cost != 0))
			return true;
	}	
	if(c.hasWeapon == true && c.currentWpn != NULL) // bug here
	{
		for(i=0;i<2;i++)
		{
			if((c.p.stamina >= c.currentWpn->moves[i].st_cost && c.currentWpn->moves[i].st_cost != 0) 
			|| (c.p.health >= c.currentWpn->moves[i].hp_cost && c.currentWpn->moves[i].hp_cost != 0)
			|| ((c.currentWpn->ammo > 0 && c.currentWpn->moves[i].rank%2==1) 
			|| (c.currentWpn->ammo >= c.currentWpn->moves[i].ammo_cost)))
				return true;
		}
	}
		
	return false;
}

void selectAbilities(member *c, struct character *e, int enemies) // when a party member is selecting an ability
{
	struct ability current;
	int select;
	int i;
	int b = 0;
	int a = 0;
	
	char holder[20];
	char holder2[20];
	
	char *choices[4] = {"","","",""};
	char *info[4] = {"","","",""};
	
	char *final[4] = {"","","",""};
	
	char final1[40] = "";
	char final2[40] = "";
	char final3[40] = "";
	char final4[40] = "";
	struct ability picks[4];
	
	member dave = *c;
	for(i=0;i<2;i++) // checks which basic skills can be performed from the player
	{ 
		if(dave.p.moves[i].type !=0  && ((dave.p.stamina >= dave.p.moves[i].st_cost && dave.p.moves[i].st_cost != 0) || (dave.p.health >= dave.p.moves[i].hp_cost && dave.p.moves[i].hp_cost != 0) ))
		{
			// assigns move name to string menu spot
			if(a == 0) // for some reason this fixes some sort of bug with the move name assignment process
				strcpy(final1,dave.p.moves[i].name);
			else
				strcpy(final2,dave.p.moves[i].name);
			
			// adds info on what the move will cost
			if(dave.p.moves[i].hp_cost > 0 && dave.p.moves[i].st_cost > 0)
			{
				sprintf(holder," and %d stamina",dave.p.moves[i].st_cost);
				sprintf(holder2," - for %d health",dave.p.moves[i].hp_cost);
				if(a==0)
					strcat(final1,holder2);			
				else
					strcat(final2,holder2);			
			}
			else if(dave.p.moves[i].st_cost > 0)
				sprintf(holder," - for %d stamina",dave.p.moves[i].st_cost);
			else	
				sprintf(holder," - for %d health",dave.p.moves[i].hp_cost);
			
			// adds move info onto string
			if(a == 0)
				strcat(final1,holder);
			else
				strcat(final2,holder);
			
			// points to abilities so it aligns with selection
			picks[a] = dave.p.moves[i];
			if(a == 0)
				final[a] = final1;
			else
				final[a] = final2;
			a++;
		}
		strcpy(holder,"");
		strcpy(holder2,"");
	}
	b = a;
	a = 0;
	if(dave.hasWeapon == true) // checks skills from weapon
	{
		for(i=0;i<2;i++) 
		{
			if(dave.currentWpn->moves[i].type !=0  // checks which moves can be added based on what they ask of the player
			  && ((dave.currentWpn->moves[i].type == 4 && dave.currentWpn->ammo > 0 && dave.currentWpn->moves[i].ammo_cost != 0 
			  	  && (dave.currentWpn->moves[i].rank % 2 == 1 || (dave.currentWpn->ammo >= dave.currentWpn->moves[i].ammo_cost))) 
			  || (dave.currentWpn->moves[i].st_cost != 0 && (dave.p.stamina >= dave.currentWpn->moves[i].st_cost)) 
			  || ((dave.currentWpn->moves[i].hp_cost != 0 && (dave.p.health >= dave.currentWpn->moves[i].hp_cost))))
			  )
			{
				if(a == 0) // for some reason this fixes some sort of bug with the move name assignment process
					strcpy(final3,dave.currentWpn->moves[i].name);
				else
					strcpy(final4,dave.currentWpn->moves[i].name);
				
				if(dave.currentWpn->moves[i].hp_cost > 0 && dave.currentWpn->moves[i].st_cost > 0)
				{
					sprintf(holder," and %d stamina",dave.currentWpn->moves[i].st_cost);
					sprintf(holder2," - for %d health",dave.currentWpn->moves[i].hp_cost);
					if(a==0)
						strcat(final3,holder2);			
					else
						strcat(final4,holder2);			
				}
				else if(dave.currentWpn->moves[i].st_cost > 0)
					sprintf(holder," - for %d stamina",dave.currentWpn->moves[i].st_cost);
				else if(dave.currentWpn->moves[i].hp_cost > 0)	
					sprintf(holder," - for %d health",dave.currentWpn->moves[i].hp_cost);
				else
				{
					if((dave.currentWpn->ammo > 0 && dave.currentWpn->moves[i].rank % 2 == 1))
					{
						if(enemies >= 4 && dave.currentWpn->ammo >= 4 || dave.currentWpn->ammo >= enemies)
							dave.currentWpn->moves[i].ammo_cost = enemies;	
						else
							dave.currentWpn->moves[i].ammo_cost = dave.currentWpn->ammo;
					}	
					sprintf(holder," - for %d ammo",dave.currentWpn->moves[i].ammo_cost);	
				}
		
				if(a == 0)
					strcat(final3,holder);
				else
					strcat(final4,holder);
				
				picks[a+b] = dave.currentWpn->moves[i];
				
				if(a == 0)
					final[a+b] = final3;
				else
					final[a+b] = final4;
				a++;
			}
			strcpy(holder,"");
			strcpy(holder2,"");
		}
	}
	select = giveChoices(final[0],final[1],final[2],final[3],CHOICEX,CHOICEY+5);
	setCursor(1,CHOICEY);
	if(picks[select-1].ammo_cost > 0)
		c->currentWpn->ammo -= picks[select-1].ammo_cost;
	useAbilities(picks[select-1],&c->p,enemies,e,true);
}

void playerAttack(member *chara, struct character *c) // when the player attacks character c
{
	srand((unsigned)time(NULL));
	
	bool missed = false;
	bool crit = false;
	
	int attack = chara->p.att+chara->p.buffAtt;
	
	int agility = (chara->p.agi+chara->p.buffAgi);
	
	int eE = (c->agi+c->buffAgi);
	
	if(attack <= 0)
		attack = 1;
	if(agility <= 0)
		agility = 1;
	if(eE <= 0)
		eE = 1;
	
	int damage = rand()%attack+attack;
	
	// uses the targeted enemy's agility to calculate a stat to be compared to the hit rate
	int hit= rand()%agility+1;
	
	int target = rand()%eE+1;
	
	if(hit < target && c->stamina > 0)
		missed = true;
	
	setCursor(1,CHOICEY);
	printf("\n%s attacks %s",chara->p.name,c->name);
	if(missed == false)
	{
		charaDamage(damage,0,c,&chara->p,true);
	}
	else
	{
		Beep(200,200);
		printf("\n\n%s missed",chara->p.name);
	}
		
	chara->p.stamina-=1;
}

void pickEnemies(member *chara, struct character *c,int enemies) // for selecting enemies in combat that are still alive
{
	int picky;
	int i;
	int a = 0;
	
	char *frontChoices[4] = {"","","",""};
	char *backChoices[4] = {"","","",""};
	
	struct character * frontPicks[4];
	struct character * backPicks[4];
	
	struct character *point;
	
	if(enemies > 4 && enemiesAlive(c,enemies) > 4)
	{
		for(i=0;i<4;i++) // get enemies in front
		{
			if(c[i].health > 0)
			{
				frontChoices[a] = c[i].name;
				frontPicks[a] = &c[i];
				a++;
			}
		}
		a = 0;
		for(i=0;i<enemies-4;i++) // gets enemies in back
		{
			if(c[i+4].health > 0)
			{
				backChoices[a] = c[i+4].name;
				backPicks[a] = &c[i+4];
				a++;
			}
		}
		switch(giveChoices("Front Row","Back Row","","",CHOICEX,CHOICEY-5))
		{
			case 1:
			picky = giveChoices(frontChoices[0],frontChoices[1],frontChoices[2],frontChoices[3],CHOICEX+25,CHOICEY-5);
			point = frontPicks[picky-1];
			break;
			case 2:
			picky = giveChoices(backChoices[0],backChoices[1],backChoices[2],backChoices[3],CHOICEX+25,CHOICEY-5);
			point = backPicks[picky-1];	
			break;
		}
	}
	else
	{
		for(i=0;i<enemies;i++)
		{
			if(c[i].health > 0)
			{
				frontChoices[a] = c[i].name;
				frontPicks[a] = &c[i];
				a++;
			}	
		}
		picky = giveChoices(frontChoices[0],frontChoices[1],frontChoices[2],frontChoices[3],CHOICEX+25,CHOICEY-5);
		point = frontPicks[picky-1];
	}
	playerAttack(chara,point);
}

int playerPersonality() // determines the player's personality based on their kills and choices
{
	double pleasedConv = ((pleased*100)/conversations);
	double angeredConv = ((angered*100)/conversations);
	if(kills != 0) // if the player has killed
	{
		double killPerc = (kills*100)/enemiesMet;
		if(killPerc <= 70) // (Neutral)
		{
			if(pleasedConv > angeredConv)
				return 2;
			else if(pleasedConv == angeredConv)
				return 5;
			else
				return 8;
		}
		else // (Violent)
		{
			if(pleasedConv > angeredConv)
				return 1;
			else if(pleasedConv == angeredConv)
				return 4;
			else
				return 7;
		}
	}
	else // has never killed (Pacifist)
	{
		if(pleasedConv > angeredConv)
			return 3;
		else if(pleasedConv == angeredConv)
			return 6;
		else
			return 9;
	}
}

bool anyTalkableEnemies(struct character *e, int enemies) // checks if any of the enemies can be talked with
{
	int a;
	for(a=0;a<enemies;a++)
	{
		if(e[a].conversMeter >= 5)
			return true;
	}
	return false;
}

void playerTurn(member *chara, struct character *c, int enemies, bool isPlayer) // prompting the player in combat
{
	int in;
	int input;
	
	int i;
	
	int a = 0;
	
	int activeEnemies[8] = {0,0,0,0,0,0,0,0};
	
	struct character* eeee[8];
	
	chara->p.isBlocking = false;	
	
	notDoneYet: // for if the player decides to go back on an option
	if(chara->p.stamina > 0)
	{
		setCursor(CHOICEX,CHOICEY-1);
		printf("What will %s do?",chara->p.name);
		if(chara->hasWeapon && (chara->currentWpn->type == 4 || chara->currentWpn->ammo > 0))
		{
			setCursor(CHOICEX,CHOICEY);
			printf("Ammo:%d",chara->currentWpn->ammo);
		}
		if(anyAbilities(*chara) == true && anyTalkableEnemies(c,enemies) == true)
			input = giveChoices("Attack","Abilities","Block","Try Talking",CHOICEX,CHOICEY+1);
		else if(anyTalkableEnemies(c,enemies) == true)
			input = giveChoices("Attack","Block","Try Talking","",CHOICEX,CHOICEY+1);
		else if(anyAbilities(*chara) == true)
			input = giveChoices("Attack","Abilities","Block","",CHOICEX,CHOICEY+1);
		else
			input = giveChoices("Attack","Block","","",CHOICEX,CHOICEY+1);
		setCursor(1,CHOICEY);		
		switch(input)
		{
			case 1:
			if(enemies == 1)
				playerAttack(chara,c);
			else
				pickEnemies(chara,c,enemies);
			break;
			case 2:
			if(anyAbilities(*chara) == true)
			{
				selectAbilities(chara,c,enemies);
			}
			else
				blockUp(&chara->p);
			break;
			case 3:
			if(anyAbilities(*chara) == true)
			{
				blockUp(&chara->p);
			}
			else
			{
				
			}
			break;
			case 4:
			break;
		}
		preEnter();
		clearBottom(true);
	}
	else
		exhausted(&chara->p);
}

void enemyAttack(struct character *e, struct character *c) // when the enemy attacks
{
	srand((unsigned)time(NULL));
	
	bool missed = false;
	bool crit = false;
	
	int attack = e->att+e->buffAtt;
	
	int agility = (e->agi+e->buffAgi);
	
	int eE = (c->agi+c->buffAgi);
	
	if(attack <= 0)
		attack = 1;
	if(agility <= 0)
		agility = 1;
	if(eE <= 0)
		eE = 1;
	
	int damage = rand()%attack+attack;
	
	// uses the targeted enemy's agility to calculate a stat to be compared to the hit rate
	int hit= rand()%agility+1;
	
	int target = rand()%eE+1;
	
	if(hit < target && c->stamina > 0)
		missed = true;
	else if(hit >= agility)
		crit = true;
	
	setCursor(1,CHOICEY);
	printf("\n%s attacks %s",e->name,c->name);
	if(missed == false)
		charaDamage(damage,0,c,e,false);
	else
	{
		Beep(200,200);
		printf("\n\n%s missed",e->name);
	}
	e->stamina-=1;
	
}

void enemyTurn(struct character *e, struct character *c, int enemies) // when it's the enemy's turn
{
	srand((unsigned)time(NULL));
	
	bool enemyPick = false;
	
	int i;
	partyStats();		
	setCursor(1,CHOICEY-1);
	
	int targ = rand()%(3)+1;
	
	e->isBlocking = false;
	if(e->stamina > 0)
	{
		if(e->health > e->maxHealth/2 ||  e->stamina != e->maxStamina || exhaustedMember() != 0)
		{
			if(partyMembersAlive() > 0) // checks if the party members are around
			{
				while(enemyPick == false)
				{
					switch(rand()%2+1)
					{
						case 1:
						if(c->health > 0)
						{
							enemyAttack(e,c);
							enemyPick = true;
						}
						break;
						case 2:
						targ = rand()%3;
						if(party[targ] != NULL && party[targ]->p.health > 0)
						{
							enemyAttack(e,&party[targ]->p);
							enemyPick = true;	
						}
						break;
					}
				}
			}
			else
			{
				enemyAttack(e,c);
			}
		}
		else
			blockUp(e);
		preEnter();
		clearBottom(false);	
	}
	else
		exhausted(e);
}

void goParty(bool *aliveEnemies, int *rankings, struct character *e, int enemies, int val) // when it's the player's turn
{
	int i;
	battleStats(rankings,e,enemies);
	partyStats();
	if(player.p.health > 0)
		playerTurn(&player,e,enemies,true);
	battleStats(rankings,e,enemies);
	printBattle(false,aliveEnemies,e,enemies,val); // prints enemies if some are down
	for(i=0;i<3;i++)
	{
		partyStats();
		if(party[i] != NULL && !enemiesDown(e,enemies) && party[i]->p.health > 0 )
		{	
			battleStats(rankings,e,enemies);
			playerTurn(party[i],e,enemies,false);
		}
		printBattle(false,aliveEnemies,e,enemies,val); // prints enemies if some are down
	}
}	

bool partyDown() // checks if every party member is down
{
	int i;
	int downed = 0;
	for(i=0;i<3;i++)
	{
		if(party[i] != NULL && party[i]->p.health <= 0)
			downed++;
	}
	if(numinParty == 0 && player.p.health <= 0)
		return true;
	else if(downed == numinParty && player.p.health <= 0 && numinParty > 0)
		return true;
	return false;
}

void buffReset() // resets all buffs to 0 in the party
{
	int i;
	player.p.buffAgi =0;
	player.p.buffAtt =0;
	player.p.buffDef =0;
	player.p.undead = false;
	player.p.increasedDef = false;
	
	for(i=0;i<numinParty;i++)
	{
		totalparty[i].p.buffAgi = 0;
		totalparty[i].p.buffDef = 0;
		totalparty[i].p.buffAtt = 0;
		totalparty[i].p.undead = false;
		totalparty[i].p.increasedDef = false;
	}
}	

int battle(int enemies, int battleType) // the main battle loop
{
	srand((unsigned)time(NULL));
	
	struct character e[8]= {}; // stores enemies
	
	bool aliveEnemies[8] = {};
	int i; // Variable used for loops
	int hr; // used for generating stats
	
	int turns = 0; // # of phases in battle
	
	int v;
	
	system("cls");
	switch(battleType)
	{
		default: // starting enemies
		for(i = 0;i<enemies;i++)
		{	
			switch(rand()%2+1) // assigns enemy
			{
				case 1:
				hr = rand()%5+5;
				e[i] = (struct character){"Stranjer",2,1,1,hr,hr,0,3,3,0,2,false,2,0,0,0,0,
										 {(struct ability){"Punch",3,1,0,0,0,0},
										 (struct ability){"Lunge",2,2,0,0,0,0}},
										 1,false,0,1,1,0,false};
				break;
				case 2:
				hr = rand()%3+6;
				e[i] = (struct character){"Hunter",1,2,1,hr,hr,0,4,4,0,2,false,2,0,0,0,0,
										 {(struct ability){"Punch",3,1,0,9,0,0},
										 (struct ability){"Lunge",2,2,0,0,0,0}},
										 2,false,0,1,2,0,false};
				break;
				/*case 3:
				hr = rand()%3+6;
				e[i] = (struct character){"Snamension",rand()%3+1,rand()%3+1,rand()%3+1,hr,hr,0,4,4,0,2+rand()%4,false,2,0,0,0,0,
										 {(struct ability){"Slash",1,1,0,1},{"Lunge",2,1,0,0}},
										 4,false,0,2,3,0,false};	
				break;*/
			}
			aliveEnemies[i] = true;
		}
		v = 3;
		break;
		case 1:
		break;
	}
	
	// resets buff values for new fight
	int rankings[8] = {0,0,0,0,0,0,0,0}; // stores the agility rankings of the enemies
	
	int eHighAgi = 0; // highest agility on the enemy side
	int localAgi = 0; // which enemy has the highest agility?
	
	bool playedHalf = false; // is the player at half health? Used for music
	
	buffReset();
	switch(rand()%3+1)
	{
		case 1:
		PlaySound(TEXT("Music/Not a Fight, Just a Challenge.wav") , NULL,  SND_LOOP | SND_ASYNC);
		break;
		case 2:
		PlaySound(TEXT("Music/The Close Encounter.wav") , NULL,  SND_LOOP | SND_ASYNC);
		break;
		case 3:
		PlaySound(TEXT("Music/Outside Encounter.wav") , NULL,  SND_LOOP | SND_ASYNC);
		break;
	}
	printBattle(true,aliveEnemies,e,enemies,v);
	while(!partyDown() && !enemiesDown(e,enemies))
	{
		for(i = 0;i<enemies;i++) // organizes the rank of the highest and lowest agility for the enemies
		{
			for(hr=0;hr<enemies;hr++)
			{
				if((e[i].agi+e[i].buffAgi) > e[rankings[hr]].agi)
				{
					rankings[hr] = i; 
				}
			}
		}
		battleStats(rankings,e,enemies);
		
		if(player.p.health <= player.p.maxHealth/2 && playedHalf == false) // plays new theme if the player is at half health
		{
			PlaySound(TEXT("Music/Stress Management.wav") , NULL,  SND_LOOP | SND_ASYNC);
			playedHalf = true;
		}
		if((player.p.agi) >= e[rankings[0]].agi) // if the player has more agility than the highest enemy with agility
		{
			goParty(aliveEnemies,rankings,e,enemies,v);
			for(i =0;i<enemies;i++)
			{
				battleStats(rankings,e,enemies);
				if(e[i].health > 0 && partyDown() == false)
				{
					enemyTurn(&e[i],&player.p,enemies);
				}
			}
		}
		else // if the enemy goes first
		{
			for(i =0;i<enemies;i++)
			{
				battleStats(rankings,e,enemies);
				if(e[i].health > 0 && partyDown() == false)
					enemyTurn(&e[i],&player.p,enemies);
			}
			if(!partyDown())
				goParty(aliveEnemies,rankings,e,enemies,v);	
		}
		
		// adjusts max stamina  based on current agility and defense
		player.p.maxStamina = player.p.agi+player.p.def;
		for(i=0;i<partySize();i++)
			party[i]->p.maxStamina = party[i]->p.agi + party[i]->p.def;
		for(i=0;i<enemies;i++) 
			e[i].maxStamina = e[i].agi+e[i].def;	
		
		turns++;
	}
	buffReset();
	if(partyDown() == true) // player lost
		return 0;
	else // player won
		return 1;
}

// out of combat commands

void setUpParty() // sets party to empty values
{
	int a;
	
	for(a = 0;a < 20;a++)
	{
		totalparty[a] = (member){{"",1,1,1,10,10,0,2,2,0,2,false,2,0,0,0,0,
		{(struct ability){"Slash",1,1,0,0,0,0},(struct ability){"Kick",3,2,0,0,0,0}}},NULL,false};
	}
}

void setUpGame() // sets up player stats and such
{
	setUpParty();
	
	srand((unsigned)time(NULL));
	
	hideCursor();
	
	int input;
	int battlers = 0;
	
	bool done1,done2,done3;
	
	int a = 0;
	int b;
	
	setUpParty();
	
	int choice, choice2;
	storage[0] = (struct weapon){"Bronze Gunblade",1,
	{(struct ability){"Slash",1,2,0,0,0,0},(struct ability){"Fire Bullet",4,0,0,0,1,5}},3};
	equipWeapon(&player,0);
	
	storage[1] = (struct weapon){"Bronze Pistol",4,
	{(struct ability){"Fire Bullet",4,0,0,0,1,5},{}},3};
	
	equipWeapon(&player,0);
	
	printf("\nEnter a character's name:");
	scanf("%s",&player.p.name);
}

void endResult(int a) // when the player wins a battle against a # enemies
{
	srand((unsigned)time(NULL));
	int b;
	
	b = rand()%(a*10)+10;	
	system("cls");
	PlaySound(TEXT("SCOST/Battle/We Won.wav") , NULL,  SND_LOOP | SND_ASYNC);
	printf("\nYou won!");
	printf("\nYou earned %d cash",b);
	cash+=b;
	preEnter();
			
	wins+=1;
				
}
