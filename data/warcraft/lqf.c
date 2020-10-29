// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猫[2;37;0m[2;37;0m", ({"xmao"}));        
        set("gender", "男性");                
        set("long", "一只猫[2;37;0m
它是李秋风的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lqf");
        set("owner_name", "李秋风");
        set_temp("owner", "lqf");
        set_temp("owner_name", "李秋风");
        ::setup();
}
