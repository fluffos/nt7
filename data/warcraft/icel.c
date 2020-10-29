// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("鸿鸿[2;37;0m[2;37;0m", ({"hoho"}));        
        set("gender", "女性");                
        set("long", "咻[2;37;0m
它是月光倾城的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "icel");
        set("owner_name", "月光倾城");
        set_temp("owner", "icel");
        set_temp("owner_name", "月光倾城");
        ::setup();
}
