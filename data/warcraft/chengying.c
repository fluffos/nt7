// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m幻兽[2;37;0m[2;37;0m", ({"xuanyuan"}));        
        set("gender", "男性");                
        set("long", "你看不到我你看不到我你看不到我[2;37;0m
它是承影的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "chengying");
        set("owner_name", "承影");
        set_temp("owner", "chengying");
        set_temp("owner_name", "承影");
        ::setup();
}
