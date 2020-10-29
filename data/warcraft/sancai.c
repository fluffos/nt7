// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三彩瑞兽麒麟[2;37;0m[2;37;0m", ({"sancaiqilin"}));        
        set("gender", "男性");                
        set("long", "三彩瑞兽麒麟[2;37;0m
它是唐三彩的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sancai");
        set("owner_name", "唐三彩");
        set_temp("owner", "sancai");
        set_temp("owner_name", "唐三彩");
        ::setup();
}
