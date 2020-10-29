// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("座机[2;37;0m[2;37;0m", ({"zuoji"}));        
        set("gender", "男性");                
        set("long", "座机[2;37;0m
它是以请啊的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wjysjcc");
        set("owner_name", "以请啊");
        set_temp("owner", "wjysjcc");
        set_temp("owner_name", "以请啊");
        ::setup();
}
