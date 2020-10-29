// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小姐[2;37;0m[2;37;0m", ({"girlioi"}));        
        set("gender", "女性");                
        set("long", "小姐[2;37;0m
它是唐唐伯虎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "laoya");
        set("owner_name", "唐唐伯虎");
        set_temp("owner", "laoya");
        set_temp("owner_name", "唐唐伯虎");
        ::setup();
}
