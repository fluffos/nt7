// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[33m拉[33m土[33m车[2;37;0m[2;37;0m", ({"fatff"}));        
        set("gender", "女性");                
        set("long", "拉土车[2;37;0m
它是炼药五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fate");
        set("owner_name", "炼药五");
        set_temp("owner", "fate");
        set_temp("owner_name", "炼药五");
        ::setup();
}
