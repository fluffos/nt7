// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白眼狼[2;37;0m[2;37;0m", ({"baiyan"}));        
        set("gender", "男性");                
        set("long", "白眼狼[2;37;0m
它是江枫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jiangfeng");
        set("owner_name", "江枫");
        set_temp("owner", "jiangfeng");
        set_temp("owner_name", "江枫");
        ::setup();
}
