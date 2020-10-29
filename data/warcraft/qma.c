// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m只做门派[2;37;0m[2;37;0m", ({"qmaa"}));        
        set("gender", "男性");                
        set("long", "只做门派[2;37;0m
它是鸠摩不智的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qma");
        set("owner_name", "鸠摩不智");
        set_temp("owner", "qma");
        set_temp("owner_name", "鸠摩不智");
        ::setup();
}
