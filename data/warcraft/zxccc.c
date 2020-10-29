// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("垃圾车[2;37;0m[2;37;0m", ({"zxc"}));        
        set("gender", "男性");                
        set("long", "垃圾车[2;37;0m
它是清理工的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zxccc");
        set("owner_name", "清理工");
        set_temp("owner", "zxccc");
        set_temp("owner_name", "清理工");
        ::setup();
}
