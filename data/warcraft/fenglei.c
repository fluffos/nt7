// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狂龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "大长金[2;37;0m
它是风雷的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fenglei");
        set("owner_name", "风雷");
        set_temp("owner", "fenglei");
        set_temp("owner_name", "风雷");
        ::setup();
}
