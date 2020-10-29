// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m龙龙[2;37;0m[2;37;0m", ({"longlong"}));        
        set("gender", "男性");                
        set("long", "$HIR$龙龙[2;37;0m
它是女剑侠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aaqq");
        set("owner_name", "女剑侠");
        set_temp("owner", "aaqq");
        set_temp("owner_name", "女剑侠");
        ::setup();
}
