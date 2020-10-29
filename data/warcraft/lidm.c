// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("练花[2;37;0m[2;37;0m", ({"lidmm"}));        
        set("gender", "男性");                
        set("long", "练花[2;37;0m
它是炼米飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidm");
        set("owner_name", "炼米飞");
        set_temp("owner", "lidm");
        set_temp("owner_name", "炼米飞");
        ::setup();
}
