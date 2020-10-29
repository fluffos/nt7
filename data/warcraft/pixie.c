// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m充血大龟头[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是辟邪的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "pixie");
        set("owner_name", "辟邪");
        set_temp("owner", "pixie");
        set_temp("owner_name", "辟邪");
        ::setup();
}
