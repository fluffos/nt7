// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m可[2;37;0m[2;37;0m", ({"keke"}));        
        set("gender", "男性");                
        set("long", "$HIR$可[2;37;0m
它是布鲁特的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "brute");
        set("owner_name", "布鲁特");
        set_temp("owner", "brute");
        set_temp("owner_name", "布鲁特");
        ::setup();
}
