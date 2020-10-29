// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m阿紫[2;37;0m[2;37;0m", ({"mypet"}));        
        set("gender", "男性");                
        set("long", "阿紫[2;37;0m
它是丁春秋的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ding");
        set("owner_name", "丁春秋");
        set_temp("owner", "ding");
        set_temp("owner_name", "丁春秋");
        ::setup();
}
