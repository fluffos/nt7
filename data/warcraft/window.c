// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "天[2;37;0m
它是唐阿门的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "window");
        set("owner_name", "唐阿门");
        set_temp("owner", "window");
        set_temp("owner_name", "唐阿门");
        ::setup();
}
