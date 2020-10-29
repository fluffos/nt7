// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[36m极[1;31m品[33m馒[1;37m头[2;37;0m[2;37;0m", ({"laohu"}));        
        set("gender", "男性");                
        set("long", "女职工[2;37;0m
它是向往自由的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tma");
        set("owner_name", "向往自由");
        set_temp("owner", "tma");
        set_temp("owner_name", "向往自由");
        ::setup();
}
