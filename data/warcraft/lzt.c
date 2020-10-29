// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是绿洲提的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lzt");
        set("owner_name", "绿洲提");
        set_temp("owner", "lzt");
        set_temp("owner_name", "绿洲提");
        ::setup();
}
