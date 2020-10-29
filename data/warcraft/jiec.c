// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狂[2;37;0m[2;37;0m", ({"kuangf"}));        
        set("gender", "女性");                
        set("long", "nod[2;37;0m
它是杰三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jiec");
        set("owner_name", "杰三");
        set_temp("owner", "jiec");
        set_temp("owner_name", "杰三");
        ::setup();
}
