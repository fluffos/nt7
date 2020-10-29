// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m刹[1;33m那[2;37;0m[1;31m邪恶[2;37;0m[2;37;0m", ({"evil"}));        
        set("gender", "男性");                
        set("long", "刹那间，萌生，邪恶的念头... [2;37;0m
它是邪恶瞬间的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evillive");
        set("owner_name", "邪恶瞬间");
        set_temp("owner", "evillive");
        set_temp("owner_name", "邪恶瞬间");
        ::setup();
}
