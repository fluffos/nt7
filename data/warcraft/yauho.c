// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狗狗[2;37;0m[2;37;0m", ({"dog"}));        
        set("gender", "男性");                
        set("long", "hahah[2;37;0m
它是刈那的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yauho");
        set("owner_name", "刈那");
        set_temp("owner", "yauho");
        set_temp("owner_name", "刈那");
        ::setup();
}
