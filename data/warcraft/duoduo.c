// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("移动钱庄[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "一只麒麟[2;37;0m
它是太多钱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "duoduo");
        set("owner_name", "太多钱");
        set_temp("owner", "duoduo");
        set_temp("owner_name", "太多钱");
        ::setup();
}
