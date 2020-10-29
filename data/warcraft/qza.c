// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("林朝英[2;37;0m[2;37;0m", ({"qzalong"}));        
        set("gender", "女性");                
        set("long", "娉[2;37;0m
它是朝令的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qza");
        set("owner_name", "朝令");
        set_temp("owner", "qza");
        set_temp("owner_name", "朝令");
        ::setup();
}
