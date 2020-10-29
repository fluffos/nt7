// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yaoppp"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是药配盘的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaopp");
        set("owner_name", "药配盘");
        set_temp("owner", "yaopp");
        set_temp("owner_name", "药配盘");
        ::setup();
}
