// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("关关[2;37;0m[2;37;0m", ({"kwankwan"}));        
        set("gender", "男性");                
        set("long", "关关[2;37;0m
它是奴才三号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kwanthree");
        set("owner_name", "奴才三号");
        set_temp("owner", "kwanthree");
        set_temp("owner_name", "奴才三号");
        ::setup();
}
