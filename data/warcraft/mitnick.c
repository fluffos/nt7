// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("博尔顿[2;37;0m[2;37;0m", ({"bolton"}));        
        set("gender", "男性");                
        set("long", "跑得快.[2;37;0m
它是米特尼克的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mitnick");
        set("owner_name", "米特尼克");
        set_temp("owner", "mitnick");
        set_temp("owner_name", "米特尼克");
        ::setup();
}
