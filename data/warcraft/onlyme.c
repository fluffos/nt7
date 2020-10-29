// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"pet"}));        
        set("gender", "男性");                
        set("long", "qinglong[2;37;0m
它是杨杨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "onlyme");
        set("owner_name", "杨杨");
        set_temp("owner", "onlyme");
        set_temp("owner_name", "杨杨");
        ::setup();
}
