// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("零零一[2;37;0m[2;37;0m", ({"xiaodamiaa"}));        
        set("gender", "男性");                
        set("long", "零零一[2;37;0m
它是零零壹的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaodamia");
        set("owner_name", "零零壹");
        set_temp("owner", "xiaodamia");
        set_temp("owner_name", "零零壹");
        ::setup();
}
