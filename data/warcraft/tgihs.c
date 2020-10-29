// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("土龙[2;37;0m[2;37;0m", ({"tgihsd"}));        
        set("gender", "男性");                
        set("long", "金蛇[2;37;0m
它是硫磺华山的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tgihs");
        set("owner_name", "硫磺华山");
        set_temp("owner", "tgihs");
        set_temp("owner_name", "硫磺华山");
        ::setup();
}
