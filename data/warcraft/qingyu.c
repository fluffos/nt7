// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青灵[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "女性");                
        set("long", "青灵[2;37;0m
它是张青玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qingyu");
        set("owner_name", "张青玉");
        set_temp("owner", "qingyu");
        set_temp("owner_name", "张青玉");
        ::setup();
}
