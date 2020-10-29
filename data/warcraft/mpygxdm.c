// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m血色之刃[2;37;0m[2;37;0m", ({"xuedaomen"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIR$血色之刃[2;37;0m
它是万佛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mpygxdm");
        set("owner_name", "万佛");
        set_temp("owner", "mpygxdm");
        set_temp("owner_name", "万佛");
        ::setup();
}
