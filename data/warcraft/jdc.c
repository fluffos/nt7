// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m幻[2;37;0m[2;37;0m", ({"huanhuan"}));        
        set("gender", "男性");                
        set("long", "梦幻之圣兽[2;37;0m
它是铁中棠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jdc");
        set("owner_name", "铁中棠");
        set_temp("owner", "jdc");
        set_temp("owner_name", "铁中棠");
        ::setup();
}
