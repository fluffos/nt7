// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("超级麒麟[2;37;0m[2;37;0m", ({"chqilin"}));        
        set("gender", "女性");                
        set("long", "超级麒麟[2;37;0m
它是欧阳婷的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ouyangt");
        set("owner_name", "欧阳婷");
        set_temp("owner", "ouyangt");
        set_temp("owner_name", "欧阳婷");
        ::setup();
}
