// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙[2;37;0m[2;37;0m", ({"xiaolong"}));        
        set("gender", "男性");                
        set("long", "小龙[2;37;0m
它是杨不过的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shsji");
        set("owner_name", "杨不过");
        set_temp("owner", "shsji");
        set_temp("owner_name", "杨不过");
        ::setup();
}
