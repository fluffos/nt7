// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m大肠[1;31m干躁[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是雪山的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xueshan");
        set("owner_name", "雪山");
        set_temp("owner", "xueshan");
        set_temp("owner_name", "雪山");
        ::setup();
}
