// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("保济[2;37;0m[2;37;0m", ({"swordblong"}));        
        set("gender", "男性");                
        set("long", "燃料油[2;37;0m
它是剑无量的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "swordb");
        set("owner_name", "剑无量");
        set_temp("owner", "swordb");
        set_temp("owner_name", "剑无量");
        ::setup();
}
