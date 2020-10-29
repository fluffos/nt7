// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("羽毛[2;37;0m[2;37;0m", ({"yuata"}));        
        set("gender", "男性");                
        set("long", "22[2;37;0m
它是羽落的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jsata");
        set("owner_name", "羽落");
        set_temp("owner", "jsata");
        set_temp("owner_name", "羽落");
        ::setup();
}
