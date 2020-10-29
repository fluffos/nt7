// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m缘起[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "缘起[2;37;0m
它是缘灭的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "msy");
        set("owner_name", "缘灭");
        set_temp("owner", "msy");
        set_temp("owner_name", "缘灭");
        ::setup();
}
