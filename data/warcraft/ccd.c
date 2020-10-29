// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccdd"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是学到的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ccd");
        set("owner_name", "学到");
        set_temp("owner", "ccd");
        set_temp("owner_name", "学到");
        ::setup();
}
