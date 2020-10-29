// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("轻龙[2;37;0m[2;37;0m", ({"lon"}));        
        set("gender", "男性");                
        set("long", "轻龙[2;37;0m
它是刘浮屠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tana");
        set("owner_name", "刘浮屠");
        set_temp("owner", "tana");
        set_temp("owner_name", "刘浮屠");
        ::setup();
}
