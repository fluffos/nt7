// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "男性");                
        set("long", "墨鱼再生！[2;37;0m
它是渡瞅的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ulianchat");
        set("owner_name", "渡瞅");
        set_temp("owner", "ulianchat");
        set_temp("owner_name", "渡瞅");
        ::setup();
}
