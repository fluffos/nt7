// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("削[2;37;0m[2;37;0m", ({"xiaox"}));        
        set("gender", "男性");                
        set("long", "削[2;37;0m
它是冷削的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lengleng");
        set("owner_name", "冷削");
        set_temp("owner", "lengleng");
        set_temp("owner_name", "冷削");
        ::setup();
}
