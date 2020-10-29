// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("可谓我去[2;37;0m[2;37;0m", ({"yudqinga"}));        
        set("gender", "男性");                
        set("long", "可谓我去[2;37;0m
它是司马玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yudqing");
        set("owner_name", "司马玉");
        set_temp("owner", "yudqing");
        set_temp("owner_name", "司马玉");
        ::setup();
}
