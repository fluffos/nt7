// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m梦幻[2;37;0m[2;37;0m", ({"meng_huan"}));        
        set("gender", "男性");                
        set("long", "一头[2;37;0m
它是剑云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jianyun");
        set("owner_name", "剑云");
        set_temp("owner", "jianyun");
        set_temp("owner_name", "剑云");
        ::setup();
}
