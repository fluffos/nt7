// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是刀疯的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "simmmer");
        set("owner_name", "刀疯");
        set_temp("owner", "simmmer");
        set_temp("owner_name", "刀疯");
        ::setup();
}
