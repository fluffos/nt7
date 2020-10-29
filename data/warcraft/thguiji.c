// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火鸡[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "火鸡[2;37;0m
它是飞龙吹雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "thguiji");
        set("owner_name", "飞龙吹雪");
        set_temp("owner", "thguiji");
        set_temp("owner_name", "飞龙吹雪");
        ::setup();
}
