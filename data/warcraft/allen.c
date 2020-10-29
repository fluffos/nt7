// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"mwm"}));        
        set("gender", "女性");                
        set("long", "小马[2;37;0m
它是大二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "allen");
        set("owner_name", "大二");
        set_temp("owner", "allen");
        set_temp("owner_name", "大二");
        ::setup();
}
