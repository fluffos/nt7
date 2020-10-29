// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是浮屠的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "robin");
        set("owner_name", "浮屠");
        set_temp("owner", "robin");
        set_temp("owner_name", "浮屠");
        ::setup();
}
