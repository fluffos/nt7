// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坑货[2;37;0m[2;37;0m", ({"xing"}));        
        set("gender", "男性");                
        set("long", "xiaoxiao的坐骑[2;37;0m
它是晓晓的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaoxiao");
        set("owner_name", "晓晓");
        set_temp("owner", "xiaoxiao");
        set_temp("owner_name", "晓晓");
        ::setup();
}
