// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马上跑[2;37;0m[2;37;0m", ({"mashangpao"}));        
        set("gender", "男性");                
        set("long", "马上跑[2;37;0m
它是神盾牌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sysi");
        set("owner_name", "神盾牌");
        set_temp("owner", "sysi");
        set_temp("owner_name", "神盾牌");
        ::setup();
}
