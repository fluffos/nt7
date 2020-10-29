// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("追风兽[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "追风兽[2;37;0m
它是掌仓的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "handsck");
        set("owner_name", "掌仓");
        set_temp("owner", "handsck");
        set_temp("owner_name", "掌仓");
        ::setup();
}
