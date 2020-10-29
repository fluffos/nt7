// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yuetee"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是元宝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ctcc");
        set("owner_name", "元宝");
        set_temp("owner", "ctcc");
        set_temp("owner_name", "元宝");
        ::setup();
}
