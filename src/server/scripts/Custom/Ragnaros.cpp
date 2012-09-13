/* Scripted by Hardcore - For Coyte-Database - DO NOT REMOVE CREDITS
Ragnaros Firelands Script
Script Progress: 30%
Raid Difficulty: 10 Man
*/

#include "ScriptPCH.h"
#include "firelands.h"
// Do not edit above. 
 
 #define Ragnaros 
 
 
 // Ragnaros Yells
 enum Yells 
    {
	
	
    SAY_AGGRO                   = -0,     //Sound id 24517
    SAY_DEATH                   = -0,     //Sound id 24519
    SAY_KILL_1                  = -0,     //Sound id 24531
    SAY_KILL_2                  = -0,     //Sound id 24530
    SAY_KILL_3                  = -0,     //Sound id 24529
    SAY_HAMMER_DROP_1           = -0,     //Sound id 24520
    SAY_HAMMER_DROP_2           = -0,     //Sound id 24521
    SAY_HAMMER_DROP_3           = -0,     //Sound id 24522
    SAY_HAMMER_PICKUP_1         = -0,     //Sound id 24523
    SAY_HAMMER_PICKUP_2         = -0,     //Sound id 24524
    SAY_HAMMER_PICKUP_3         = -0,     //Sound id 24525
    SAY_PURGE                   = -0,     //Sound id 24532

 
 // If attacked, use these spells.
 // Remember there is 4 stages - 1. By Fire Be Purged!  2. Minions of Fire! 3. Begone From My Realm!. 4. 
 enum Spells
    {
	
	// Stage 1
	   SPELL_SULFURAS_SMASH          = 98710, // Ragnaros faces the location of a random player and prepares to smash Sulfuras on the platform.
	   SPELL_LAVA_WAVE   	         = 100293, // If a player touches a moving Lava Wave, the lava inflicts 73125 to 76875 Fire damage, 21937 to 23062 Fire damage every 1 sec. for 5 sec., and knocks the player back.
       SPELL_WRATH_OF_RAGNAROS       = 98263, // Ragnaros blasts the location of a random player, inflicting 43875 to 46125 Fire damage to all players within 6 yards and knocking them back.	   
	   SPELL_HAND_OF_RAGNAROS        = 98237, // Ragnaros inflicts 21937 to 23062 Fire damage to all enemies within 55 yards, knocking them back. 
	   SPELL_MAGMA_TRAP              = 100108, // A triggered Magma Trap erupts for 58500 to 61500 Fire damage to all players, and violently knocks the triggering player into the air. The Magma Trap causes the triggering player to take 50% more damage from other Magma Traps. This effect lasts for 45 sec and stacks.
	   SPELL_MAGMA_BLAST             = 98313, // Ragnaros blasts magma at his current target if he cannot reach and melee them, inflicting 73125 to 76875 Fire damage and increasing Fire damage taken by 50% for 6 sec. 
	 
	   // Intermission: Minions of fire. At 70% health Ragnaros casts Splitting Blow, burying Sulfuras into the platform and creating Sons of Flame across the platform. Ragnaros submerges for 45 seconds or until the players destroy all the Sons of Flame, whichever comes first.
	   SPELL_SPLITTING_BLOW          = 98951, // Ragnaros buries Sulfuras within the platform, inflicting 68250 to 71750 Fire damage every 1 second to players within 6 yards and creating eight Sons of Flame that attempt to reach the mighty hammer.
	   SON_OF_FLAME_ID               = 53140, // This is the spawn id for Son_of_Flame This is not suppost to be here and will be moved later on. Sons of Flame cross the platform and attempt to reform with Sulfuras. A Son of Flame that reaches Sulfuras causes a Supernova.
 	   SPELL_BURNING_SPEED           = 98473, // For every 5% of their remaining health above 50%, Sons of Flame move 75% faster. When players reduce a Son of Flame to below 50% remaining health, the Son of Flame loses the Burning Speed effect. 
	   SPELL_SUPERNOVA               = 100260, // When a Son of Flame reaches Sulfuras it explodes in a Supernova, inflicting 91406 to 96093 Fire damage to all players. 
	   SPELL_LAVA_BOLT               = 98981, // While Ragnaros lies submerged underneath the lava, bolts of hot magma fall on four random players every 4 seconds. A Lava Bolt inflicts 43875 to 46125 Fire Damage.
	   SPELL_LIVING_METEOR           = 99268,    // Meteor rolling towards player. Inflicts high damage on impact.
	   
      // Stage 2 
	   SPELL_SULFURAS_SMASH        = 98710, // Ragnaros faces the location of a random player and prepares to smash Sulfuras on the platform.
	   SPELL_LAVA_WAVE             = 100293, // If a player touches a moving Lava Wave, the lava inflicts 73125 to 76875 Fire damage, 21937 to 23062 Fire damage every 1 sec. for 5 sec., and knocks the player back. 
	   SPELL_ENGULFING_FLAME       = 50407, // Ragnaros periodically engulfs a random third of the platform in flames, immediately inflicting 51187 to 53812 Fire damage to players caught in the conflagration then again inflicting 51187 to 53812 Fire damage one second later. 
	   SPELL_WORLD_IN_FLAMES       = 11108, // Ragnaros periodically casts Engulfing Flames on a random section of the platform every 3 sec for 9 sec. 
	   SPELL_MOLTEN_SEED           = 98498, // Ragnaros creates Molten Seed at the location of 10 random players from the nearby lava, inflicting 40218 to 42281 Fire damage to all players within 6 yards of a seed. After 10 sec the Molten Seed bursts into a Molten Inferno.
	   SPELL_MOLTEN_INFERNO        = 98518, // When Molten Seeds burst they create a Molten Inferno, inflicting 101250 Fire damage to all players and creating a Molten Elemental. The damage inflicted decreases the farther away the player stands from the seed. 
	   SPELL_MOLTEN_POWER          = 100157, // Molten Elementals within 6 yards empower other Molten Elementals, increasing their damage dealt by 25% and granting immunity to snare and stun effects. 
	   SPELL_MAGMA_BLAST           = 98313, // Ragnaros blasts magma at his current target if he cannot reach and melee them, inflicting 73125 to 76875 Fire damage and increasing Fire damage taken by 50% for 6 sec. 
	   
	   // Intermission: Denizens of Flame!. At 40% health Ragnaros casts Splitting Blow, burying Sulfuras into the platform and creating Sons of Flame across the platform. Ragnaros submerges for 45 seconds or until the players destroy all the Sons of Flame, whichever comes first.Ragnaros also creates two Lava Scions that attack the players.
	   SPELL_SPLITTING_BLOW        = 98951, // Ragnaros buries Sulfuras within the platform, inflicting 68250 to 71750 Fire damage every 1 second to players within 6 yards and creating eight Sons of Flame that attempt to reach the mighty hammer. 
	   SPELL_BURNING_SPEED         = 98473, // For every 5% of their remaining health above 50%, Sons of Flame move 75% faster. When players reduce a Son of Flame to below 50% remaining health, the Son of Flame loses the Burning Speed effect. 
	   SPELL_SUPERNOVA             = 100260, // When a Son of Flame reaches Sulfuras it explodes in a Supernova, inflicting 91406 to 96093 Fire damage to all players. 
	   SPELL_BLAZING_HEAT          = 99145, // A Lava Scion inflicts a random player with Blazing Heat, causing the player to create a trail of Blazing Heat in their wake. Blazing Heat inflicts 36562 to 38437 Fire damage every 1 sec on players standing within the trail, and heals Sons of Flame within the trail for 10% every 1 sec. 
	   
	   // Stage 3: Begone From My Realm! 
	  
	  
	  //Stage 4: The True Power of the Firelord!
	   
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
 
	  
	  
	