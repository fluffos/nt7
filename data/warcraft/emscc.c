// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一头麒麟[2;37;0m
它是主人您好的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emscc");
        set("owner_name", "主人您好");
        set_temp("owner", "emscc");
        set_temp("owner_name", "主人您好");
        ::setup();
}
