// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碧血麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "碧血麒麟[2;37;0m
它是以太小虾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ether");
        set("owner_name", "以太小虾");
        set_temp("owner", "ether");
        set_temp("owner_name", "以太小虾");
        ::setup();
}
