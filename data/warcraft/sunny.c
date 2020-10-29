// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火鸟[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "一只可爱的小鸟。[2;37;0m
它是阳光少女的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sunny");
        set("owner_name", "阳光少女");
        set_temp("owner", "sunny");
        set_temp("owner_name", "阳光少女");
        ::setup();
}
