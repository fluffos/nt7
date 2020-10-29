// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿狸爱国[2;37;0m[2;37;0m", ({"adsl"}));        
        set("gender", "男性");                
        set("long", "阿狸爱国[2;37;0m
它是啊二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chickenb");
        set("owner_name", "啊二");
        set_temp("owner", "chickenb");
        set_temp("owner_name", "啊二");
        ::setup();
}
