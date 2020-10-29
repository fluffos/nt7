// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m冰[1;31m淇[1;33m淋[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "吃好，跑好，才是好.[2;37;0m
它是苍龙加的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cljia");
        set("owner_name", "苍龙加");
        set_temp("owner", "cljia");
        set_temp("owner_name", "苍龙加");
        ::setup();
}
