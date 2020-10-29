// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("还得靠[2;37;0m[2;37;0m", ({"odje"}));        
        set("gender", "男性");                
        set("long", "还得靠[2;37;0m
它是记录路径的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kklkll");
        set("owner_name", "记录路径");
        set_temp("owner", "kklkll");
        set_temp("owner_name", "记录路径");
        ::setup();
}
