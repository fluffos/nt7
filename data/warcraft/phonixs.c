// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("追风狂马[2;37;0m[2;37;0m", ({"phonixsa"}));        
        set("gender", "男性");                
        set("long", "1234567[2;37;0m
它是芦屋雪介的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "phonixs");
        set("owner_name", "芦屋雪介");
        set_temp("owner", "phonixs");
        set_temp("owner_name", "芦屋雪介");
        ::setup();
}
