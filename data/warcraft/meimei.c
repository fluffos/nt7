// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;37m小鲜肉[2;37;0m[2;37;0m", ({"xian"}));        
        set("gender", "男性");                
        set("long", "小鲜肉[2;37;0m
它是美眉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "meimei");
        set("owner_name", "美眉");
        set_temp("owner", "meimei");
        set_temp("owner_name", "美眉");
        ::setup();
}
