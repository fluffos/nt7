// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("名流座[2;37;0m[2;37;0m", ({"mingliu"}));        
        set("gender", "男性");                
        set("long", "九皇座[2;37;0m
它是段章甫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zhangfu");
        set("owner_name", "段章甫");
        set_temp("owner", "zhangfu");
        set_temp("owner_name", "段章甫");
        ::setup();
}
