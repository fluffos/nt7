// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥人糊麒麟[2;37;0m[2;37;0m", ({"nirenqilin"}));        
        set("gender", "男性");                
        set("long", "泥人糊麒麟[2;37;0m
它是泥人胡的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "niren");
        set("owner_name", "泥人胡");
        set_temp("owner", "niren");
        set_temp("owner_name", "泥人胡");
        ::setup();
}
