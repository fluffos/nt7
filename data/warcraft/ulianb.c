// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火源[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "嘿嘿[2;37;0m
它是楚米二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ulianb");
        set("owner_name", "楚米二");
        set_temp("owner", "ulianb");
        set_temp("owner_name", "楚米二");
        ::setup();
}
