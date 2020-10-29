// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("王语嫣[2;37;0m[2;37;0m", ({"dlalong"}));        
        set("gender", "男性");                
        set("long", "卧人[2;37;0m
它是卖灵感的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "dla");
        set("owner_name", "卖灵感");
        set_temp("owner", "dla");
        set_temp("owner_name", "卖灵感");
        ::setup();
}
