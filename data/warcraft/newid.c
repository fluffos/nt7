// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽兽[2;37;0m[2;37;0m", ({"newidid"}));        
        set("gender", "男性");                
        set("long", "兽兽[2;37;0m
它是飞飞杨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "newid");
        set("owner_name", "飞飞杨");
        set_temp("owner", "newid");
        set_temp("owner_name", "飞飞杨");
        ::setup();
}
