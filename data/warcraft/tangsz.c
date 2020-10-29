// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m墨麒麟[2;37;0m[2;37;0m", ({"whitehorse"}));        
        set("gender", "男性");                
        set("long", "长得像马的一头麒麟。[2;37;0m
它是唐三藏的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tangsz");
        set("owner_name", "唐三藏");
        set_temp("owner", "tangsz");
        set_temp("owner_name", "唐三藏");
        ::setup();
}
