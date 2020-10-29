// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("没脸骑[2;37;0m[2;37;0m", ({"nofaceride"}));        
        set("gender", "男性");                
        set("long", "没脸骑[2;37;0m
它是无颜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "noface");
        set("owner_name", "无颜");
        set_temp("owner", "noface");
        set_temp("owner_name", "无颜");
        ::setup();
}
