// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白光虎[2;37;0m[2;37;0m", ({"sdbea"}));        
        set("gender", "男性");                
        set("long", "相当神秘[2;37;0m
它是天空五号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sdbe");
        set("owner_name", "天空五号");
        set_temp("owner", "sdbe");
        set_temp("owner_name", "天空五号");
        ::setup();
}
