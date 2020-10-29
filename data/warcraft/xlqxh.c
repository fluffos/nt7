// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m历史书[2;37;0m[2;37;0m", ({"lsbook"}));        
        set("gender", "男性");                
        set("long", "哈哈哈哈h[2;37;0m
它是罗宾的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xlqxh");
        set("owner_name", "罗宾");
        set_temp("owner", "xlqxh");
        set_temp("owner_name", "罗宾");
        ::setup();
}
