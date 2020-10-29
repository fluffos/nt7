// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m雾[2;37;0m[1;35m影[1;33m缭[1;32m绕[2;37;0m[2;37;0m", ({"wuying"}));        
        set("gender", "男性");                
        set("long", "雾影缭绕[2;37;0m
它是雾蒙蒙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "foggy");
        set("owner_name", "雾蒙蒙");
        set_temp("owner", "foggy");
        set_temp("owner_name", "雾蒙蒙");
        ::setup();
}
