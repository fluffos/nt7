// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "男性");                
        set("long", "这是一只麒麟[2;37;0m
它是菩丹壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wdpta");
        set("owner_name", "菩丹壹");
        set_temp("owner", "wdpta");
        set_temp("owner_name", "菩丹壹");
        ::setup();
}
