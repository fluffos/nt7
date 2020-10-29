// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("慕容雪[2;37;0m[2;37;0m", ({"mrblong"}));        
        set("gender", "男性");                
        set("long", "美少女[2;37;0m
它是一哥的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mrb");
        set("owner_name", "一哥");
        set_temp("owner", "mrb");
        set_temp("owner_name", "一哥");
        ::setup();
}
