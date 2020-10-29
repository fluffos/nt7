// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m[1;33m玄兽[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "张牙舞爪的过山猛虎[2;37;0m
它是江河的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sionglee");
        set("owner_name", "江河");
        set_temp("owner", "sionglee");
        set_temp("owner_name", "江河");
        ::setup();
}
