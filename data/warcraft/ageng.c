// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("更更[2;37;0m[2;37;0m", ({"genggeng"}));        
        set("gender", "男性");                
        set("long", "更更[2;37;0m
它是阿更的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ageng");
        set("owner_name", "阿更");
        set_temp("owner", "ageng");
        set_temp("owner_name", "阿更");
        ::setup();
}
