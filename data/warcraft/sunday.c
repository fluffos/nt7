// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m一[1;31m日[5m[1;36m七天[2;37;0m[2;37;0m[2;37;0m", ({"sun"}));        
        set("gender", "女性");                
        set("long", "drop caoyu[2;37;0m
它是星期天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sunday");
        set("owner_name", "星期天");
        set_temp("owner", "sunday");
        set_temp("owner_name", "星期天");
        ::setup();
}
