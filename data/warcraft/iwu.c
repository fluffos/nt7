// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qsq"}));        
        set("gender", "男性");                
        set("long", "幻兽呀！请你以最深的灵性，聆听我的倾诉[2;37;0m
它是城化粪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "iwu");
        set("owner_name", "城化粪");
        set_temp("owner", "iwu");
        set_temp("owner_name", "城化粪");
        ::setup();
}
