// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[33m拉[33m土[33m车[2;37;0m[2;37;0m", ({"fatgg"}));        
        set("gender", "女性");                
        set("long", "拉土车[2;37;0m
它是炼药七的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatg");
        set("owner_name", "炼药七");
        set_temp("owner", "fatg");
        set_temp("owner_name", "炼药七");
        ::setup();
}
