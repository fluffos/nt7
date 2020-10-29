// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("加颜[2;37;0m[2;37;0m", ({"feifeihou"}));        
        set("gender", "男性");                
        set("long", "加颜[2;37;0m
它是张誉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yuolecom");
        set("owner_name", "张誉");
        set_temp("owner", "yuolecom");
        set_temp("owner_name", "张誉");
        ::setup();
}
