// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火鸟[2;37;0m[2;37;0m", ({"kie"}));        
        set("gender", "女性");                
        set("long", "火鸟飞来了[2;37;0m
它是儒可就的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "janwite");
        set("owner_name", "儒可就");
        set_temp("owner", "janwite");
        set_temp("owner_name", "儒可就");
        ::setup();
}
