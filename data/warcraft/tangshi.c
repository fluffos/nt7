// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m唐柔[2;37;0m[2;37;0m[2;37;0m", ({"tangshiq"}));        
        set("gender", "女性");                
        set("long", "好看好厉害的坐骑[2;37;0m
它是唐诗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tangshi");
        set("owner_name", "唐诗");
        set_temp("owner", "tangshi");
        set_temp("owner_name", "唐诗");
        ::setup();
}
