// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m轮椅[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "$HIW$轮椅[2;37;0m
它是唐棉花的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tmh");
        set("owner_name", "唐棉花");
        set_temp("owner", "tmh");
        set_temp("owner_name", "唐棉花");
        ::setup();
}
