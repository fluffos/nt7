// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "火[2;37;0m
它是长安的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "changan");
        set("owner_name", "长安");
        set_temp("owner", "changan");
        set_temp("owner_name", "长安");
        ::setup();
}
