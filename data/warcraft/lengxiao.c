// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("咳咳[2;37;0m[2;37;0m", ({"keke"}));        
        set("gender", "男性");                
        set("long", "咳咳[2;37;0m
它是冷笑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lengxiao");
        set("owner_name", "冷笑");
        set_temp("owner", "lengxiao");
        set_temp("owner_name", "冷笑");
        ::setup();
}
