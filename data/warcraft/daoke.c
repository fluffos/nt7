// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;37m小李他妈飞刀[2;37;0m[2;37;0m", ({"feidao"}));        
        set("gender", "男性");                
        set("long", "小李他妈飞刀[2;37;0m
它是刀客的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "daoke");
        set("owner_name", "刀客");
        set_temp("owner", "daoke");
        set_temp("owner_name", "刀客");
        ::setup();
}
