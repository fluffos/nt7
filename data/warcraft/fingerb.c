// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("中纪藤香[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "粉[2;37;0m
它是加藤虎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fingerb");
        set("owner_name", "加藤虎");
        set_temp("owner", "fingerb");
        set_temp("owner_name", "加藤虎");
        ::setup();
}
