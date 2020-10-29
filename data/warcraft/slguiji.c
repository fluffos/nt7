// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小毛驴[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "小毛驴[2;37;0m
它是天生秃头的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "slguiji");
        set("owner_name", "天生秃头");
        set_temp("owner", "slguiji");
        set_temp("owner_name", "天生秃头");
        ::setup();
}
