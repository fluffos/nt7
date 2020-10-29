// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("叫兽[2;37;0m[2;37;0m", ({"aodm"}));        
        set("gender", "男性");                
        set("long", "老虎[2;37;0m
它是日月药丸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dmyao");
        set("owner_name", "日月药丸");
        set_temp("owner", "dmyao");
        set_temp("owner_name", "日月药丸");
        ::setup();
}
