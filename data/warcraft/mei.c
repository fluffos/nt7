// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啦啦啦[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "啦啦啦[2;37;0m
它是张飞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mei");
        set("owner_name", "张飞");
        set_temp("owner", "mei");
        set_temp("owner_name", "张飞");
        ::setup();
}
