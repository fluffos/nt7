// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m神[1;36m器[2;37;0m[2;37;0m", ({"goodmt"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIR$神$HIC$器[2;37;0m
它是九月天空的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jytk");
        set("owner_name", "九月天空");
        set_temp("owner", "jytk");
        set_temp("owner_name", "九月天空");
        ::setup();
}
