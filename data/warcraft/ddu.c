// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"dduu"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂有的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddu");
        set("owner_name", "堂有");
        set_temp("owner", "ddu");
        set_temp("owner_name", "堂有");
        ::setup();
}
