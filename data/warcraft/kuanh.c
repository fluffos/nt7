// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "火灰白[2;37;0m
它是狂八的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuanh");
        set("owner_name", "狂八");
        set_temp("owner", "kuanh");
        set_temp("owner_name", "狂八");
        ::setup();
}
