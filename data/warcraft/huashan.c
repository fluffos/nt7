// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("看[2;37;0m[2;37;0m", ({"sss"}));        
        set("gender", "男性");                
        set("long", "看[2;37;0m
它是打开是的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "huashan");
        set("owner_name", "打开是");
        set_temp("owner", "huashan");
        set_temp("owner_name", "打开是");
        ::setup();
}
