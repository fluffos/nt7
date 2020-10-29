// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟兽[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "一只小小的麒麟兽[2;37;0m
它是小马哥哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "majun");
        set("owner_name", "小马哥哥");
        set_temp("owner", "majun");
        set_temp("owner_name", "小马哥哥");
        ::setup();
}
