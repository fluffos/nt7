// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小狗[2;37;0m[2;37;0m", ({"xgg"}));        
        set("gender", "女性");                
        set("long", "小狗[2;37;0m
它是童颜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lao");
        set("owner_name", "童颜");
        set_temp("owner", "lao");
        set_temp("owner_name", "童颜");
        ::setup();
}
