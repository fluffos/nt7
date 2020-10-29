// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("捡垃圾[2;37;0m[2;37;0m", ({"bbxlqx"}));        
        set("gender", "男性");                
        set("long", "捡垃圾[2;37;0m
它是东方星的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bxlqx");
        set("owner_name", "东方星");
        set_temp("owner", "bxlqx");
        set_temp("owner_name", "东方星");
        ::setup();
}
