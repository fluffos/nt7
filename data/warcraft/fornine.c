// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天乐龙龙[2;37;0m[2;37;0m", ({"ttlongq"}));        
        set("gender", "男性");                
        set("long", "天乐龙龙[2;37;0m
它是阳九的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fornine");
        set("owner_name", "阳九");
        set_temp("owner", "fornine");
        set_temp("owner_name", "阳九");
        ::setup();
}
