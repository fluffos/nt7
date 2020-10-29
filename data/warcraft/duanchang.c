// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("段式麒麟[2;37;0m[2;37;0m", ({"duanchangqilin"}));        
        set("gender", "男性");                
        set("long", "段式麒麟[2;37;0m
它是段常的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "duanchang");
        set("owner_name", "段常");
        set_temp("owner", "duanchang");
        set_temp("owner_name", "段常");
        ::setup();
}
