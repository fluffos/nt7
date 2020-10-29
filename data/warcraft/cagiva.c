// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m十绝[1;33m追日[2;37;0m[2;37;0m[2;37;0m", ({"keith"}));        
        set("gender", "男性");                
        set("long", "追日[2;37;0m
它是荆陌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cagiva");
        set("owner_name", "荆陌");
        set_temp("owner", "cagiva");
        set_temp("owner_name", "荆陌");
        ::setup();
}
