// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("你好[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "111122[2;37;0m
它是刘备的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "crazyf");
        set("owner_name", "刘备");
        set_temp("owner", "crazyf");
        set_temp("owner_name", "刘备");
        ::setup();
}
