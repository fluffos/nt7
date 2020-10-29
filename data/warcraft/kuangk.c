// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("着骑[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "一八[2;37;0m
它是狂拾一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuangk");
        set("owner_name", "狂拾一");
        set_temp("owner", "kuangk");
        set_temp("owner_name", "狂拾一");
        ::setup();
}
