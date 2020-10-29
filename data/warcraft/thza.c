// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m驴[1;33m车[2;37;0m[2;37;0m", ({"lvche"}));        
        set("gender", "男性");                
        set("long", "这是给长工们的坐骑[2;37;0m
它是长工甲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "thza");
        set("owner_name", "长工甲");
        set_temp("owner", "thza");
        set_temp("owner_name", "长工甲");
        ::setup();
}
