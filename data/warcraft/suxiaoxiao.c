// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m晓晓胯下物[2;37;0m[2;37;0m", ({"suxx"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是苏晓晓的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "suxiaoxiao");
        set("owner_name", "苏晓晓");
        set_temp("owner", "suxiaoxiao");
        set_temp("owner_name", "苏晓晓");
        ::setup();
}
