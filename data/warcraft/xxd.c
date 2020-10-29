// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星云[2;37;0m[2;37;0m", ({"xxdlong"}));        
        set("gender", "女性");                
        set("long", "停权[2;37;0m
它是卫子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xxd");
        set("owner_name", "卫子");
        set_temp("owner", "xxd");
        set_temp("owner_name", "卫子");
        ::setup();
}
