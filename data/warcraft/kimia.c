// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m火舞[2;37;0m[2;37;0m", ({"fire"}));        
        set("gender", "女性");                
        set("long", "一只火麒麟[2;37;0m
它是南瓜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kimia");
        set("owner_name", "南瓜");
        set_temp("owner", "kimia");
        set_temp("owner_name", "南瓜");
        ::setup();
}
