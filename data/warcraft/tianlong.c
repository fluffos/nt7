// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("冲出来[2;37;0m[2;37;0m", ({"tianlongb"}));        
        set("gender", "男性");                
        set("long", "冲出来[2;37;0m
它是天战的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "tianlong");
        set("owner_name", "天战");
        set_temp("owner", "tianlong");
        set_temp("owner_name", "天战");
        ::setup();
}
