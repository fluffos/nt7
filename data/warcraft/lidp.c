// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("练风[2;37;0m[2;37;0m", ({"lidoa"}));        
        set("gender", "男性");                
        set("long", "练风[2;37;0m
它是炼叶的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidp");
        set("owner_name", "炼叶");
        set_temp("owner", "lidp");
        set_temp("owner_name", "炼叶");
        ::setup();
}
