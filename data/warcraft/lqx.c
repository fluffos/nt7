// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m绿色地瓜[2;37;0m[2;37;0m", ({"lqxa"}));        
        set("gender", "男性");                
        set("long", "长得太丑[2;37;0m
它是小星的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lqx");
        set("owner_name", "小星");
        set_temp("owner", "lqx");
        set_temp("owner_name", "小星");
        ::setup();
}
