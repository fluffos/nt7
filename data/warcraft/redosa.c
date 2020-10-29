// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"mhs"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是再来缘灭的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "redosa");
        set("owner_name", "再来缘灭");
        set_temp("owner", "redosa");
        set_temp("owner_name", "再来缘灭");
        ::setup();
}
