// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("着骑[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "一八[2;37;0m
它是狂草地的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuangx");
        set("owner_name", "狂草地");
        set_temp("owner", "kuangx");
        set_temp("owner_name", "狂草地");
        ::setup();
}
