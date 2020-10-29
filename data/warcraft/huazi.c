// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("花子的麒麟[2;37;0m[2;37;0m", ({"huaziride"}));        
        set("gender", "男性");                
        set("long", "花子的麒麟[2;37;0m
它是苏三的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "huazi");
        set("owner_name", "苏三");
        set_temp("owner", "huazi");
        set_temp("owner_name", "苏三");
        ::setup();
}
