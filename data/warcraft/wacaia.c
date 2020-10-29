// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蜀犬吠日[2;37;0m[2;37;0m", ({"kdkdk"}));        
        set("gender", "男性");                
        set("long", "地三轮车[2;37;0m
它是在轩在的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wacaia");
        set("owner_name", "在轩在");
        set_temp("owner", "wacaia");
        set_temp("owner_name", "在轩在");
        ::setup();
}
