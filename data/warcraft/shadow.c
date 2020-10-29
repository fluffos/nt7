// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m浴火重生[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "Fuck[2;37;0m
它是影魔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shadow");
        set("owner_name", "影魔");
        set_temp("owner", "shadow");
        set_temp("owner_name", "影魔");
        ::setup();
}
