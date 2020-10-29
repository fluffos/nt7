// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[33m拉[33m土[33m车[2;37;0m[2;37;0m", ({"foxxs"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$YEL$拉$YEL$土$YEL$车[2;37;0m
它是阿绣的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "foxx");
        set("owner_name", "阿绣");
        set_temp("owner", "foxx");
        set_temp("owner_name", "阿绣");
        ::setup();
}
