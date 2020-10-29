// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟[2;37;0m[2;37;0m", ({"jackya"}));        
        set("gender", "男性");                
        set("long", "这是只乌龟[2;37;0m
它是一样的是的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jackyb");
        set("owner_name", "一样的是");
        set_temp("owner", "jackyb");
        set_temp("owner_name", "一样的是");
        ::setup();
}
