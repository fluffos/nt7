// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是天梭的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tissot");
        set("owner_name", "天梭");
        set_temp("owner", "tissot");
        set_temp("owner_name", "天梭");
        ::setup();
}
