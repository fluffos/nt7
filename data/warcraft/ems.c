// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一只麒麟[2;37;0m
它是马企鹅的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ems");
        set("owner_name", "马企鹅");
        set_temp("owner", "ems");
        set_temp("owner_name", "马企鹅");
        ::setup();
}
