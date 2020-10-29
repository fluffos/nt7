// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("挖菜[2;37;0m[2;37;0m", ({"wacaide"}));        
        set("gender", "女性");                
        set("long", "挖菜[2;37;0m
它是菜弄不的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cainongb");
        set("owner_name", "菜弄不");
        set_temp("owner", "cainongb");
        set_temp("owner_name", "菜弄不");
        ::setup();
}
