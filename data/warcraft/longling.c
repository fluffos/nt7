// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m奶油[2;37;0m[2;37;0m", ({"cake"}));        
        set("gender", "女性");                
        set("long", "没有介绍。[2;37;0m
它是玲珑的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "longling");
        set("owner_name", "玲珑");
        set_temp("owner", "longling");
        set_temp("owner_name", "玲珑");
        ::setup();
}
