// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("波比[2;37;0m[2;37;0m", ({"bobi"}));        
        set("gender", "男性");                
        set("long", "这奇异的怪兽，背上有着银色毛发，而头上的独角看上去显得神俊。[2;37;0m
它是飞剑便便的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "perform");
        set("owner_name", "飞剑便便");
        set_temp("owner", "perform");
        set_temp("owner_name", "飞剑便便");
        ::setup();
}
