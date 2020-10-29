// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝马[2;37;0m[2;37;0m", ({"vik"}));        
        set("gender", "男性");                
        set("long", "。。。。。。[2;37;0m
它是司马乘风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "viki");
        set("owner_name", "司马乘风");
        set_temp("owner", "viki");
        set_temp("owner_name", "司马乘风");
        ::setup();
}
