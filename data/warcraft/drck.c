// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("纸包子[2;37;0m[2;37;0m", ({"laohu"}));        
        set("gender", "男性");                
        set("long", "纸包子[2;37;0m
它是水云的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "drck");
        set("owner_name", "水云");
        set_temp("owner", "drck");
        set_temp("owner_name", "水云");
        ::setup();
}
