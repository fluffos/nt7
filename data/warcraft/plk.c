// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m瑞兽[2;37;0m[2;37;0m", ({"xfh"}));        
        set("gender", "男性");                
        set("long", "懶[2;37;0m
它是梦红尘的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "plk");
        set("owner_name", "梦红尘");
        set_temp("owner", "plk");
        set_temp("owner_name", "梦红尘");
        ::setup();
}
