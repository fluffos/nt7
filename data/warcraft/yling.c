// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"xuxu"}));        
        set("gender", "男性");                
        set("long", "finish[2;37;0m
它是天灵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yling");
        set("owner_name", "天灵");
        set_temp("owner", "yling");
        set_temp("owner_name", "天灵");
        ::setup();
}
