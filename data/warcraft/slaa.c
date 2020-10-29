// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("萝莉[2;37;0m[2;37;0m", ({"slaalong"}));        
        set("gender", "男性");                
        set("long", "停权[2;37;0m
它是特摩的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "slaa");
        set("owner_name", "特摩");
        set_temp("owner", "slaa");
        set_temp("owner_name", "特摩");
        ::setup();
}
