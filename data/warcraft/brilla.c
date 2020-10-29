// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("松鼠猫猫[2;37;0m[2;37;0m", ({"smellycat"}));        
        set("gender", "男性");                
        set("long", "一只活泼可爱的猫猫[2;37;0m
它是葫芦猫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "brilla");
        set("owner_name", "葫芦猫");
        set_temp("owner", "brilla");
        set_temp("owner_name", "葫芦猫");
        ::setup();
}
