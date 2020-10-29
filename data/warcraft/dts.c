// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天猫[2;37;0m[2;37;0m", ({"tmall"}));        
        set("gender", "男性");                
        set("long", "一只猫[2;37;0m
它是唐泰斯的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dts");
        set("owner_name", "唐泰斯");
        set_temp("owner", "dts");
        set_temp("owner_name", "唐泰斯");
        ::setup();
}
