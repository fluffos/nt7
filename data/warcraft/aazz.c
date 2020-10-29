// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小鸟[2;37;0m[2;37;0m", ({"xiaoniao"}));        
        set("gender", "男性");                
        set("long", "$HIG$小鸟[2;37;0m
它是财迷的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "aazz");
        set("owner_name", "财迷");
        set_temp("owner", "aazz");
        set_temp("owner_name", "财迷");
        ::setup();
}
