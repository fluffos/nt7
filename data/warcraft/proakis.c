// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("如意[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "如意麒麟[2;37;0m
它是高封的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "proakis");
        set("owner_name", "高封");
        set_temp("owner", "proakis");
        set_temp("owner_name", "高封");
        ::setup();
}
