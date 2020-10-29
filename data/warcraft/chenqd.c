// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"rrrr"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是成东的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenqd");
        set("owner_name", "成东");
        set_temp("owner", "chenqd");
        set_temp("owner_name", "成东");
        ::setup();
}
