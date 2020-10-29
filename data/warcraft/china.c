// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "这是一只九天十地菩萨摇头怕怕霹雳精光火麒麟。[2;37;0m
它是炎黄子孙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "china");
        set("owner_name", "炎黄子孙");
        set_temp("owner", "china");
        set_temp("owner_name", "炎黄子孙");
        ::setup();
}
