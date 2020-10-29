// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m去[2;37;0m[2;37;0m", ({"nach"}));        
        set("gender", "男性");                
        set("long", "是多少[2;37;0m
它是修炼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiulian");
        set("owner_name", "修炼");
        set_temp("owner", "xiulian");
        set_temp("owner_name", "修炼");
        ::setup();
}
