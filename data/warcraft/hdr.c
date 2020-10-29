// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[30m世京[2;37;0m[2;37;0m", ({"hdrgo"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$BLK$世京[2;37;0m
它是好多人的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "hdr");
        set("owner_name", "好多人");
        set_temp("owner", "hdr");
        set_temp("owner_name", "好多人");
        ::setup();
}
