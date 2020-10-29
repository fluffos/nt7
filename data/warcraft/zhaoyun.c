// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m赤兔[2;37;0m[2;37;0m", ({"super"}));        
        set("gender", "男性");                
        set("long", "全身血红，四蹄飞雪，马中赤兔，天下无双。[2;37;0m
它是赵云的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zhaoyun");
        set("owner_name", "赵云");
        set_temp("owner", "zhaoyun");
        set_temp("owner_name", "赵云");
        ::setup();
}
