// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m凤舞[2;37;0m[2;37;0m", ({"fenwu"}));        
        set("gender", "女性");                
        set("long", "$HIR$凤舞下届[2;37;0m
它是云霄的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jane");
        set("owner_name", "云霄");
        set_temp("owner", "jane");
        set_temp("owner_name", "云霄");
        ::setup();
}
