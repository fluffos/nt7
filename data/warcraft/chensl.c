// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"uiui"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是少临的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chensl");
        set("owner_name", "少临");
        set_temp("owner", "chensl");
        set_temp("owner_name", "少临");
        ::setup();
}
