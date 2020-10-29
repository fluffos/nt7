// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;33m万毒蛊[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "Fuck you[2;37;0m
它是金蚕蛊的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jin");
        set("owner_name", "金蚕蛊");
        set_temp("owner", "jin");
        set_temp("owner_name", "金蚕蛊");
        ::setup();
}
