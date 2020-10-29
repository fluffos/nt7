// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("余小兽[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "我的小麒麟[2;37;0m
它是余青风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "acalstar");
        set("owner_name", "余青风");
        set_temp("owner", "acalstar");
        set_temp("owner_name", "余青风");
        ::setup();
}
