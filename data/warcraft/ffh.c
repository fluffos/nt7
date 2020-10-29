// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"sads"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是飞飞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ffh");
        set("owner_name", "飞飞");
        set_temp("owner", "ffh");
        set_temp("owner_name", "飞飞");
        ::setup();
}
