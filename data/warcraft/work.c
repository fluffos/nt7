// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "万里投荒，一身吊影，成何欢意。[2;37;0m
它是东风一号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "work");
        set("owner_name", "东风一号");
        set_temp("owner", "work");
        set_temp("owner_name", "东风一号");
        ::setup();
}
