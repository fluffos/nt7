// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccmm"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学嘛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ccm");
        set("owner_name", "学嘛");
        set_temp("owner", "ccm");
        set_temp("owner_name", "学嘛");
        ::setup();
}
