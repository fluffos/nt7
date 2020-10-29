// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("九尾灵狐[2;37;0m[2;37;0m", ({"minerride"}));        
        set("gender", "男性");                
        set("long", "千年老妖[2;37;0m
它是唐伯虎的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "realsim");
        set("owner_name", "唐伯虎");
        set_temp("owner", "realsim");
        set_temp("owner_name", "唐伯虎");
        ::setup();
}
