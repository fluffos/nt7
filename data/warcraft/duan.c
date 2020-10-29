// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狂人[2;37;0m[2;37;0m", ({"feng"}));        
        set("gender", "男性");                
        set("long", "分[2;37;0m
它是段无命的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "duan");
        set("owner_name", "段无命");
        set_temp("owner", "duan");
        set_temp("owner_name", "段无命");
        ::setup();
}
