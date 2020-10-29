// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝马[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "宝马[2;37;0m
它是剑辰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jianchen");
        set("owner_name", "剑辰");
        set_temp("owner", "jianchen");
        set_temp("owner_name", "剑辰");
        ::setup();
}
