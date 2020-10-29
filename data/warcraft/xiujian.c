// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("晓晓[2;37;0m[2;37;0m", ({"xiaoxiao"}));        
        set("gender", "男性");                
        set("long", "这是一只小小的麒麟。[2;37;0m
它是锈剑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiujian");
        set("owner_name", "锈剑");
        set_temp("owner", "xiujian");
        set_temp("owner_name", "锈剑");
        ::setup();
}
