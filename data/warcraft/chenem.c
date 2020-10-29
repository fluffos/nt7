// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m倚天之剑[2;37;0m[2;37;0m", ({"eme"}));        
        set("gender", "男性");                
        set("long", "倚天剑[2;37;0m
它是峨眉女郎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenem");
        set("owner_name", "峨眉女郎");
        set_temp("owner", "chenem");
        set_temp("owner_name", "峨眉女郎");
        ::setup();
}
