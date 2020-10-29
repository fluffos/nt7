// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m麒麟[2;37;0m[2;37;0m", ({"qlin"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是丁钉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dding");
        set("owner_name", "丁钉");
        set_temp("owner", "dding");
        set_temp("owner_name", "丁钉");
        ::setup();
}
