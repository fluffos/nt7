// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"qilinshou"}));        
        set("gender", "男性");                
        set("long", "一头威武的火麒麟[2;37;0m
它是诸葛小白的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "celious");
        set("owner_name", "诸葛小白");
        set_temp("owner", "celious");
        set_temp("owner_name", "诸葛小白");
        ::setup();
}
