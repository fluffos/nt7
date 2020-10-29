// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yuetee"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是金山的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dtdd");
        set("owner_name", "金山");
        set_temp("owner", "dtdd");
        set_temp("owner_name", "金山");
        ::setup();
}
