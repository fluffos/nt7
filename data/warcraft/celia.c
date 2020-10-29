// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猫猫[2;37;0m[2;37;0m", ({"ccmao"}));        
        set("gender", "女性");                
        set("long", "小猫猫[2;37;0m
它是龙美美的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "celia");
        set("owner_name", "龙美美");
        set_temp("owner", "celia");
        set_temp("owner_name", "龙美美");
        ::setup();
}
