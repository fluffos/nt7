// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m专用麒麟[2;37;0m[2;37;0m", ({"qmdd"}));        
        set("gender", "男性");                
        set("long", "专用麒麟[2;37;0m
它是寡言沉默的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qmddami");
        set("owner_name", "寡言沉默");
        set_temp("owner", "qmddami");
        set_temp("owner_name", "寡言沉默");
        ::setup();
}
