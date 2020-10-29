// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m华山破骑士[2;37;0m[2;37;0m", ({"qmff"}));        
        set("gender", "女性");                
        set("long", "华山破骑士[2;37;0m
它是华山清风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qmf");
        set("owner_name", "华山清风");
        set_temp("owner", "qmf");
        set_temp("owner_name", "华山清风");
        ::setup();
}
