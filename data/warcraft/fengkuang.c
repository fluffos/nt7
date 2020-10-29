// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("凤狂灵[2;37;0m[2;37;0m", ({"fkll"}));        
        set("gender", "女性");                
        set("long", "fkll[2;37;0m
它是疯狂的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fengkuang");
        set("owner_name", "疯狂");
        set_temp("owner", "fengkuang");
        set_temp("owner_name", "疯狂");
        ::setup();
}
