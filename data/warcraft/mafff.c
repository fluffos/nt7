// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小熊[2;37;0m[2;37;0m", ({"makkk"}));        
        set("gender", "男性");                
        set("long", "我的小熊[2;37;0m
它是小强强的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mafff");
        set("owner_name", "小强强");
        set_temp("owner", "mafff");
        set_temp("owner_name", "小强强");
        ::setup();
}
