// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m铜[1;35m板[1;35m[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "男性");                
        set("long", "长得好像飞毯一样的铜板[2;37;0m
它是贾富贵的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xjia");
        set("owner_name", "贾富贵");
        set_temp("owner", "xjia");
        set_temp("owner_name", "贾富贵");
        ::setup();
}
