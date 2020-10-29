// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("诺特[2;37;0m[2;37;0m", ({"nott"}));        
        set("gender", "男性");                
        set("long", "一条小蛇[2;37;0m
它是江山如画的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "picland");
        set("owner_name", "江山如画");
        set_temp("owner", "picland");
        set_temp("owner_name", "江山如画");
        ::setup();
}
