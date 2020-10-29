// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"qinin"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是小剑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dlin");
        set("owner_name", "小剑");
        set_temp("owner", "dlin");
        set_temp("owner_name", "小剑");
        ::setup();
}
