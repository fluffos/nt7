// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛟龙[2;37;0m[2;37;0m", ({"jiaolong"}));        
        set("gender", "男性");                
        set("long", "蛟龙[2;37;0m
它是朱大能的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hajkl");
        set("owner_name", "朱大能");
        set_temp("owner", "hajkl");
        set_temp("owner_name", "朱大能");
        ::setup();
}
