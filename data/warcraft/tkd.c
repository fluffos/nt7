// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("要以[2;37;0m[2;37;0m", ({"dtk"}));        
        set("gender", "男性");                
        set("long", "要以[2;37;0m
它是在前的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tkd");
        set("owner_name", "在前");
        set_temp("owner", "tkd");
        set_temp("owner_name", "在前");
        ::setup();
}
