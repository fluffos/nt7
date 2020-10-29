// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤风[2;37;0m[2;37;0m", ({"windy"}));        
        set("gender", "男性");                
        set("long", "四足踏火的异兽[2;37;0m
它是云翼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yunyi");
        set("owner_name", "云翼");
        set_temp("owner", "yunyi");
        set_temp("owner_name", "云翼");
        ::setup();
}
