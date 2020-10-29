// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"out"}));        
        set("gender", "男性");                
        set("long", "龙是一种善变化能兴云雨利万物的神异动物，为鳞虫之长[2;37;0m
它是朔风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shuo");
        set("owner_name", "朔风");
        set_temp("owner", "shuo");
        set_temp("owner_name", "朔风");
        ::setup();
}
