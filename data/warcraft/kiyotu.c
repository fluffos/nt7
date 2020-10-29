// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("隐形[2;37;0m[2;37;0m", ({"laihama"}));        
        set("gender", "男性");                
        set("long", "finish[2;37;0m
它是欧阳人杰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kiyotu");
        set("owner_name", "欧阳人杰");
        set_temp("owner", "kiyotu");
        set_temp("owner_name", "欧阳人杰");
        ::setup();
}
