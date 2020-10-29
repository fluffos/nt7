// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贝贝[2;37;0m[2;37;0m", ({"tjwxczq"}));        
        set("gender", "男性");                
        set("long", "小贝贝[2;37;0m
它是晓飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tdtkyl");
        set("owner_name", "晓飞");
        set_temp("owner", "tdtkyl");
        set_temp("owner_name", "晓飞");
        ::setup();
}
