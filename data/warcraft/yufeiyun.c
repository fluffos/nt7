// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m碧水[2;37;0m[2;37;0m", ({"qiling"}));        
        set("gender", "男性");                
        set("long", "飞天遁地[2;37;0m
它是枫叶的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yufeiyun");
        set("owner_name", "枫叶");
        set_temp("owner", "yufeiyun");
        set_temp("owner_name", "枫叶");
        ::setup();
}
