// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m取名字这么难[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "shit[2;37;0m
它是九阳的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jiuy");
        set("owner_name", "九阳");
        set_temp("owner", "jiuy");
        set_temp("owner_name", "九阳");
        ::setup();
}
