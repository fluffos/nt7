// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("享受[2;37;0m[2;37;0m", ({"xiangshou"}));        
        set("gender", "男性");                
        set("long", "享受[2;37;0m
它是自控的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "denise");
        set("owner_name", "自控");
        set_temp("owner", "denise");
        set_temp("owner_name", "自控");
        ::setup();
}
