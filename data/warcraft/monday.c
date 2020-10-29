// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m一[1;31m日[5m[1;31m[1;36m一天[2;37;0m[2;37;0m[2;37;0m", ({"mon"}));        
        set("gender", "女性");                
        set("long", "一天一日[2;37;0m
它是星期一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "monday");
        set("owner_name", "星期一");
        set_temp("owner", "monday");
        set_temp("owner_name", "星期一");
        ::setup();
}
