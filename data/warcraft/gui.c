// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"guii"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是龟丞相的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "gui");
        set("owner_name", "龟丞相");
        set_temp("owner", "gui");
        set_temp("owner_name", "龟丞相");
        ::setup();
}
