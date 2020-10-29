// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"lupp"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是恒二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zzhb");
        set("owner_name", "恒二");
        set_temp("owner", "zzhb");
        set_temp("owner_name", "恒二");
        ::setup();
}
