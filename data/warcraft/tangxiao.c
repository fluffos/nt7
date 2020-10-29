// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"xing"}));        
        set("gender", "女性");                
        set("long", "唐筱的朱雀[2;37;0m
它是唐筱的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tangxiao");
        set("owner_name", "唐筱");
        set_temp("owner", "tangxiao");
        set_temp("owner_name", "唐筱");
        ::setup();
}
