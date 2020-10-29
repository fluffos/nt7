// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m妖[1;35m精[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "$HIG$妖$HIM$精[2;37;0m
它是看砍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "test");
        set("owner_name", "看砍");
        set_temp("owner", "test");
        set_temp("owner_name", "看砍");
        ::setup();
}
