// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("没穿裤子[2;37;0m[2;37;0m", ({"plgh"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是押运二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yygb");
        set("owner_name", "押运二");
        set_temp("owner", "yygb");
        set_temp("owner_name", "押运二");
        ::setup();
}
