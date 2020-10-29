// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m吞田[2;37;0m[2;37;0m", ({"tuantian"}));        
        set("gender", "男性");                
        set("long", "威风凛凛[2;37;0m
它是断沧海的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "canghai");
        set("owner_name", "断沧海");
        set_temp("owner", "canghai");
        set_temp("owner_name", "断沧海");
        ::setup();
}
