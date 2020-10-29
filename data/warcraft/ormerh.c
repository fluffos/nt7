// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小影[2;37;0m[2;37;0m", ({"ying"}));        
        set("gender", "男性");                
        set("long", "小影[2;37;0m
它是鲍洁颖的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ormerh");
        set("owner_name", "鲍洁颖");
        set_temp("owner", "ormerh");
        set_temp("owner_name", "鲍洁颖");
        ::setup();
}
