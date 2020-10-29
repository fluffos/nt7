// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m太古[1;33m屎壳螂[2;37;0m[2;37;0m", ({"bugs"}));        
        set("gender", "女性");                
        set("long", "屎壳螂啊，太古的啊，臭气熏天，臭不可闻，闻之即死。[2;37;0m
它是拱屎虫的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bug");
        set("owner_name", "拱屎虫");
        set_temp("owner", "bug");
        set_temp("owner_name", "拱屎虫");
        ::setup();
}
