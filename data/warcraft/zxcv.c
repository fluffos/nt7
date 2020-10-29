// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小飞侠[2;37;0m[2;37;0m", ({"ttqilin"}));        
        set("gender", "女性");                
        set("long", "小飞侠[2;37;0m
它是刀小刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zxcv");
        set("owner_name", "刀小刀");
        set_temp("owner", "zxcv");
        set_temp("owner_name", "刀小刀");
        ::setup();
}
