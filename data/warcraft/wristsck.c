// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("追风兽[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "追风兽[2;37;0m
它是湖湾仓的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wristsck");
        set("owner_name", "湖湾仓");
        set_temp("owner", "wristsck");
        set_temp("owner_name", "湖湾仓");
        ::setup();
}
