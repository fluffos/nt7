// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"srfdaa"}));        
        set("gender", "男性");                
        set("long", "BBBB[2;37;0m
它是冷刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rfdaa");
        set("owner_name", "冷刀");
        set_temp("owner", "rfdaa");
        set_temp("owner_name", "冷刀");
        ::setup();
}
