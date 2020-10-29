// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("噜噜[2;37;0m[2;37;0m", ({"ssx"}));        
        set("gender", "男性");                
        set("long", "啊[2;37;0m
它是古剑的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "halt");
        set("owner_name", "古剑");
        set_temp("owner", "halt");
        set_temp("owner_name", "古剑");
        ::setup();
}
