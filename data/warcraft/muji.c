// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m莲花宝座[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "一个金黄色的莲花宝座[2;37;0m
它是木机的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "muji");
        set("owner_name", "木机");
        set_temp("owner", "muji");
        set_temp("owner_name", "木机");
        ::setup();
}
