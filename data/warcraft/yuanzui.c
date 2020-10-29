// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("莫求[2;37;0m[2;37;0m", ({"moqiu"}));        
        set("gender", "男性");                
        set("long", "缘醉莫求[2;37;0m
它是缘醉莫求的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yuanzui");
        set("owner_name", "缘醉莫求");
        set_temp("owner", "yuanzui");
        set_temp("owner_name", "缘醉莫求");
        ::setup();
}
