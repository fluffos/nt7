// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("超级神兽[2;37;0m[2;37;0m", ({"ljs"}));        
        set("gender", "男性");                
        set("long", "防御超强[2;37;0m
它是顺哽在的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lusssss");
        set("owner_name", "顺哽在");
        set_temp("owner", "lusssss");
        set_temp("owner_name", "顺哽在");
        ::setup();
}
