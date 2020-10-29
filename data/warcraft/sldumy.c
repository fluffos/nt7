// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "一个睡袋。[2;37;0m
它是空少的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sldumy");
        set("owner_name", "空少");
        set_temp("owner", "sldumy");
        set_temp("owner_name", "空少");
        ::setup();
}
