// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "男性");                
        set("long", "墨鱼噢[2;37;0m
它是贝塔的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ulianm");
        set("owner_name", "贝塔");
        set_temp("owner", "ulianm");
        set_temp("owner_name", "贝塔");
        ::setup();
}
