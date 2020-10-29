// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "剑仙的座骑[2;37;0m
它是剑仙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jianxian");
        set("owner_name", "剑仙");
        set_temp("owner", "jianxian");
        set_temp("owner_name", "剑仙");
        ::setup();
}
