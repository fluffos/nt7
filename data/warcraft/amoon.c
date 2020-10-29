// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猫[2;37;0m[2;37;0m", ({"mao"}));        
        set("gender", "女性");                
        set("long", "一只猫[2;37;0m
它是阿月的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "amoon");
        set("owner_name", "阿月");
        set_temp("owner", "amoon");
        set_temp("owner_name", "阿月");
        ::setup();
}
