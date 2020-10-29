// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m凤舞九天[2;37;0m[2;37;0m", ({"jane"}));        
        set("gender", "女性");                
        set("long", "凤凰涅磐，浴火重生[2;37;0m
它是龙之冰清的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "water");
        set("owner_name", "龙之冰清");
        set_temp("owner", "water");
        set_temp("owner_name", "龙之冰清");
        ::setup();
}
