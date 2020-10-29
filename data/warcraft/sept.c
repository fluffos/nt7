// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m九小月份[2;37;0m[2;37;0m", ({"septa"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是九月份的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sept");
        set("owner_name", "九月份");
        set_temp("owner", "sept");
        set_temp("owner_name", "九月份");
        ::setup();
}
