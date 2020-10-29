// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m保时捷[2;37;0m[2;37;0m", ({"porche"}));        
        set("gender", "女性");                
        set("long", "运输工具[2;37;0m
它是苏琪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "suckgg");
        set("owner_name", "苏琪");
        set_temp("owner", "suckgg");
        set_temp("owner_name", "苏琪");
        ::setup();
}
