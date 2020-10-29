// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m高处不胜寒[2;37;0m[2;37;0m", ({"lcnely"}));        
        set("gender", "男性");                
        set("long", "这是一个猪头[2;37;0m
它是樱叶的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "leaf");
        set("owner_name", "樱叶");
        set_temp("owner", "leaf");
        set_temp("owner_name", "樱叶");
        ::setup();
}
