// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拿书专用坐骑[2;37;0m[2;37;0m", ({"thdmm"}));        
        set("gender", "男性");                
        set("long", "拿书专用坐骑[2;37;0m
它是桃花多多的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "thdm");
        set("owner_name", "桃花多多");
        set_temp("owner", "thdm");
        set_temp("owner_name", "桃花多多");
        ::setup();
}
