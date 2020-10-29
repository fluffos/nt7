// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙[2;37;0m[2;37;0m", ({"xlong"}));        
        set("gender", "男性");                
        set("long", "小龙[2;37;0m
它是杨很过的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shsjk");
        set("owner_name", "杨很过");
        set_temp("owner", "shsjk");
        set_temp("owner_name", "杨很过");
        ::setup();
}
