// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小武[2;37;0m[2;37;0m", ({"xwu"}));        
        set("gender", "男性");                
        set("long", "小武[2;37;0m
它是狐狸的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "huli");
        set("owner_name", "狐狸");
        set_temp("owner", "huli");
        set_temp("owner_name", "狐狸");
        ::setup();
}
