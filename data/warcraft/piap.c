// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小李子[2;37;0m[2;37;0m", ({"lijie"}));        
        set("gender", "女性");                
        set("long", "忠实的伙伴[2;37;0m
它是苍苍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "piap");
        set("owner_name", "苍苍");
        set_temp("owner", "piap");
        set_temp("owner_name", "苍苍");
        ::setup();
}
