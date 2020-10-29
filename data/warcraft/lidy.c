// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"lidwa"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是星用上的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidy");
        set("owner_name", "星用上");
        set_temp("owner", "lidy");
        set_temp("owner_name", "星用上");
        ::setup();
}
