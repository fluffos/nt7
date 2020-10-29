// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "这是一只麒麟[2;37;0m
它是慕容不在的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "blka");
        set("owner_name", "慕容不在");
        set_temp("owner", "blka");
        set_temp("owner_name", "慕容不在");
        ::setup();
}
