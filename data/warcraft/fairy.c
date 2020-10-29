// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小仙女[2;37;0m[2;37;0m", ({"myfairy"}));        
        set("gender", "女性");                
        set("long", "这是一个小仙女。[2;37;0m
它是丁小仙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fairy");
        set("owner_name", "丁小仙");
        set_temp("owner", "fairy");
        set_temp("owner_name", "丁小仙");
        ::setup();
}
